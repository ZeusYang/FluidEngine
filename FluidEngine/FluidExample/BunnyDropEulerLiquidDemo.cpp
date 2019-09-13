#include "BunnyDropEulerLiquidDemo.h"

#include <sstream>

#include "Engine/Simulation/VolumeGridEmitter3.h"
#include "Engine/Geometry/TriangleMesh3.h"
#include "Engine/Geometry/ImplicitTriangleMesh3.h"
#include "Engine/Simulation/LevelSetLiquidSolver3.h"

using namespace Engine;

void BunnyDropEulerLiquidDemo::setup(size_t resolutionX)
{
	auto solver = LevelSetLiquidSolver3::builder()
		.withResolution({ resolutionX ,resolutionX ,resolutionX })
		.withDomainSizeX(1.0)
		.makeShared();
	solver->setUseCompressedLinearSystem(true);

	solver->setViscosityCoefficient(0.0);
	solver->setIsGlobalCompensationEnabled(true);

	auto grids = solver->gridSystemData();
	auto bunnyMesh = TriangleMesh3::builder().makeShared();
	std::ifstream objFile("bunny.obj");
	if (objFile)
	{
		bunnyMesh->readObj(&objFile);
	}
	else
	{
		fprintf(stderr, "Cannot open resources/bunny.obj\n");
		exit(EXIT_FAILURE);
	}

	auto bunny = ImplicitTriangleMesh3::builder()
		.withTriangleMesh(bunnyMesh)
		.withResolutionX(resolutionX)
		.makeShared();

	auto emitter = VolumeGridEmitter3::builder().withSourceRegion(bunny).makeShared();

	solver->setEmitter(emitter);
	emitter->addSignedDistanceTarget(solver->signedDistanceField());

	_solver = solver;

	auto domain = grids->boundingBox();

	minX = domain.lowerCorner.x;
	minY = domain.lowerCorner.y;
	minZ = domain.lowerCorner.z;
	maxX = domain.upperCorner.x;
	maxY = domain.upperCorner.y;
	maxZ = domain.upperCorner.z;

	std::stringstream ss;
	ss << "<texture type=\"checkerboard\" id=\"__planetex\">";
	ss << "<rgb name=\"color0\" value=\"0.4\"/>";
	ss << "<rgb name=\"color1\" value=\"0.2\"/>";
	ss << "<float name=\"uscale\" value=\"8.0\"/>";
	ss << "<float name=\"vscale\" value=\"8.0\"/>";
	ss << "<float name=\"uoffset\" value=\"0.0\"/>";
	ss << "<float name=\"voffset\" value=\"0.0\"/>";
	ss << "</texture>";
	ss << "<shape type=\"obj\">";
	ss << "<string name=\"filename\" value=\"plane.obj\"/>";
	ss << "<bsdf type=\"diffuse\">";
	ss << "<ref name=\"reflectance\" id=\"__planetex\"/>";
	ss << "</bsdf>";
	ss << "<transform name=\"toWorld\">";
	ss << "<scale value=\"10.0\"/>";
	ss << "</transform>";
	ss << "</shape>";
	_sceneXml = ss.str();

}
