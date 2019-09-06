#include "EulerFluidDemo.h"

#include "Engine/Simulation/GridSmokeSolver3.h"

#include <iostream>

using namespace Engine;

void EulerFluidDemo::run(const std::string & rootDir, int numberOfFrames,
	const std::string & format, double fps)
{
	if (_solver == nullptr)
	{
		std::cout << "You have not set a solver to run.\n";
		return;
	}

	for (Frame frame(0, 1.0 / fps); frame.index < numberOfFrames; ++frame)
	{
		_solver->update(frame);
		if (format == "vol")
		{
			auto density = (reinterpret_cast<GridSmokeSolver3*>(_solver.get()))->smokeDensity();
			saveAsSmokeXml(density, rootDir, frame.index);
		}
	}
}

void EulerFluidDemo::saveAsSmokeXml(const Engine::ScalarGrid3Ptr & density,
	const std::string & rootDir, int frameCnt)
{
	const size_t kEdgeBlur = 3;
	const float kEdgeBlurF = 3.f;

	// Save to .vol format file.
	char basename[256];
	snprintf(basename, sizeof(basename), "frame_%06d.vol", frameCnt);
	std::string objName = std::string(basename);
	std::string filename = rootDir + objName;
	std::ofstream file(filename.c_str(), std::ofstream::binary);
	if (file)
	{
		printf("Writing %s...\n", filename.c_str());

		// Mitsuba 0.5.0 gridvolume format
		char header[48];
		memset(header, 0, sizeof(header));

		header[0] = 'V';
		header[1] = 'O';
		header[2] = 'L';
		header[3] = 3;
		int32_t* encoding = reinterpret_cast<int32_t*>(header + 4);
		encoding[0] = 1;  // 32-bit float
		encoding[1] = static_cast<int32_t>(density->dataSize().x);
		encoding[2] = static_cast<int32_t>(density->dataSize().y);
		encoding[3] = static_cast<int32_t>(density->dataSize().z);
		encoding[4] = 1;  // number of channels
		BoundingBox3D domain = density->boundingBox();
		float* bbox = reinterpret_cast<float*>(encoding + 5);
		bbox[0] = static_cast<float>(domain.lowerCorner.x);
		bbox[1] = static_cast<float>(domain.lowerCorner.y);
		bbox[2] = static_cast<float>(domain.lowerCorner.z);
		bbox[3] = static_cast<float>(domain.upperCorner.x);
		bbox[4] = static_cast<float>(domain.upperCorner.y);
		bbox[5] = static_cast<float>(domain.upperCorner.z);

		file.write(header, sizeof(header));

		Array3<float> data(density->dataSize());
		data.parallelForEachIndex([&](size_t i, size_t j, size_t k)
		{
			float d = static_cast<float>((*density)(i, j, k));

			// Blur the edge for less-noisy rendering
			if (i < kEdgeBlur) {
				d *= smoothStep(0.f, kEdgeBlurF, static_cast<float>(i));
			}
			if (i > data.size().x - 1 - kEdgeBlur) {
				d *= smoothStep(0.f, kEdgeBlurF,
					static_cast<float>((data.size().x - 1) - i));
			}
			if (j < kEdgeBlur) {
				d *= smoothStep(0.f, kEdgeBlurF, static_cast<float>(j));
			}
			if (j > data.size().y - 1 - kEdgeBlur) {
				d *= smoothStep(0.f, kEdgeBlurF,
					static_cast<float>((data.size().y - 1) - j));
			}
			if (k < kEdgeBlur) {
				d *= smoothStep(0.f, kEdgeBlurF, static_cast<float>(k));
			}
			if (k > data.size().z - 1 - kEdgeBlur) {
				d *= smoothStep(0.f, kEdgeBlurF,
					static_cast<float>((data.size().z - 1) - k));
			}

			data(i, j, k) = d;
		});
		file.write(
			reinterpret_cast<const char*>(data.data()),
			sizeof(float) * data.size().x * data.size().y * data.size().z);

		file.close();
	}
	else
		std::cout << "Failed to save the file:" << filename << std::endl;

	// Save to .xml format file.
	char basenameXml[256];
	snprintf(basenameXml, sizeof(basenameXml), "frame_%06d.xml", frameCnt);
	std::string filenameXml = rootDir + std::string(basenameXml);
	std::ofstream xmlfile(filenameXml.c_str());

	// calculate camera.
	double midX = (maxX + minX) / 2;
	double midY = minY + (maxY - minY) * 0.3;
	double midZ = (maxZ + minZ) / 2;
	double width = maxX - minX;
	double height = maxY - minY;
	double depth = maxZ - minZ;
	double longest = std::max(std::max(maxX - minX, maxY - minY), maxZ - minZ) * 2.3;
	Vector3D target({ midX, midY, midZ });
	Vector3D origin({ 0.3,0.5,1 });
	origin.normalize();
	origin = origin * longest + target;

	if (xmlfile)
	{
		xmlfile << "<scene version=\"0.5.0\">";
		xmlfile << "<integrator type=\"volpath_simple\">";
		xmlfile << "<integer name=\"maxDepth\" value=\"15\"/>";
		xmlfile << "</integrator>";
		xmlfile << "<sensor type=\"perspective\">";
		xmlfile << "<transform name=\"toWorld\">\n";
		xmlfile << "<lookat target=\"" << target.x << "," << target.y << "," << target.z
			<< "\" origin=\"" << origin.x << "," << origin.y << "," << origin.z
			<< "\" up=\"" << 0.0 << "," << 1.0 << "," << 0.0 << "\"/>\n";
		xmlfile << "</transform>";
		xmlfile << "<sampler type=\"ldsampler\">";
		xmlfile << "<integer name=\"sampleCount\" value=\"128\"/>";
		xmlfile << "</sampler>";
		xmlfile << "<film type=\"ldrfilm\">";
		xmlfile << "<integer name=\"width\" value=\"800\"/>";
		xmlfile << "<integer name=\"height\" value=\"600\"/>";
		xmlfile << "<string name=\"pixelFormat\" value=\"rgb\"/>";
		xmlfile << "</film>";
		xmlfile << "</sensor>";
		xmlfile << _sceneXml;
		xmlfile << "<emitter type=\"envmap\" id=\"envmapLight\">";
		xmlfile << "<string name=\"filename\" value=\"../envmap.exr\"/>";
		xmlfile << "<transform name=\"toWorld\">";
		xmlfile << "</transform>";
		xmlfile << "<float name=\"scale\" value=\"2.75\"/>";
		xmlfile << "</emitter>";
		xmlfile << "<medium type=\"heterogeneous\" id=\"smoke\">";
		xmlfile << "<string name=\"method\" value=\"woodcock\"/>";
		xmlfile << "<volume name=\"density\" type=\"gridvolume\">";
		xmlfile << "<string name=\"filename\" value=\"" << objName << "\"/>";
		xmlfile << "</volume>";
		xmlfile << "<volume name=\"albedo\" type=\"constvolume\">";
		xmlfile << "<rgb name=\"value\" value=\"0.27, 0.51, 0.71\"/>";
		xmlfile << "</volume>";
		xmlfile << "<float name=\"scale\" value=\"100\"/>";
		xmlfile << "</medium>";
		xmlfile << "<shape type=\"cube\">";
		xmlfile << "<transform name=\"toWorld\">";
		xmlfile << "<scale x=\"" << width * 0.5 << "\" y=\"" << height * 0.5 << "\" z=\"" << depth * 0.5 << "\"/>";
		xmlfile << "<translate x=\"" << midX << "\" y=\"" << midY << "\" z=\"" << midZ << "\"/>";
		xmlfile << "</transform>";
		xmlfile << "<ref name=\"interior\" id=\"smoke\"/>";
		xmlfile << "</shape>";
		xmlfile << "</scene>";
	}
	else
		std::cout << "Failed to save the file:" << filenameXml << std::endl;

}

float EulerFluidDemo::smoothStep(float edge0, float edge1, float x)
{
	float t = clamp((x - edge0) / (edge1 - edge0), 0.f, 1.f);
	return t * t * (3.f - 2.f * t);
}
