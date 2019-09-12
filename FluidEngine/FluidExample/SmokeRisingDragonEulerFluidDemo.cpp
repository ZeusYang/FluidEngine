#include "SmokeRisingDragonEulerFluidDemo.h"

#include "Engine/Geometry/Box3.h"
#include "Engine/Geometry/Sphere3.h"
#include "Engine/Geometry/TriangleMesh3.h"
#include "Engine/Geometry/ImplicitTriangleMesh3.h"
#include "Engine/Simulation/RigidBodyCollider3.h"
#include "Engine/Simulation/GridSmokeSolver3.h"
#include "Engine/Simulation/VolumeGridEmitter3.h"
#include "Engine/Simulation/CubicSemiLagrangian3.h"

#include <sstream>

using namespace Engine;

void SmokeRisingDragonEulerFluidDemo::setup(size_t resolutionX)
{
	// build solver.
	auto solver = GridSmokeSolver3::builder()
		.withResolution({ resolutionX ,  resolutionX / 4 * 5 ,resolutionX / 2 })
		.withDomainSizeX(2.0)
		.withOrigin({ -1, -0.15, -0.5 })
		.makeShared();

	solver->setAdvectionSolver(std::make_shared<CubicSemiLagrangian3>());

	auto grid = solver->gridSystemData();
	BoundingBox3D domain = grid->boundingBox();
	minX = domain.lowerCorner.x;
	minY = domain.lowerCorner.y;
	minZ = domain.lowerCorner.z;
	maxX = domain.upperCorner.x;
	maxY = domain.upperCorner.y;
	maxZ = domain.upperCorner.z;

	// build emitter.
	auto dragonMesh = TriangleMesh3::builder().makeShared();
	std::ifstream objFile("dragon.obj");
	if (objFile) 
		dragonMesh->readObj(&objFile);
	else
	{
		fprintf(stderr, "Cannot open dragon.obj\n");
		exit(EXIT_FAILURE);
	}
	auto dragon = ImplicitTriangleMesh3::builder()
		.withTriangleMesh(dragonMesh)
		.withResolutionX(resolutionX)
		.makeShared();

	auto emitter = VolumeGridEmitter3::builder()
		.withSourceRegion(dragon)
		.withIsOneShot(false)
		.makeShared();

	solver->setEmitter(emitter);
	emitter->addStepFunctionTarget(solver->smokeDensity(), 0, 1);
	emitter->addStepFunctionTarget(solver->temperature(), 0, 1);

	// build collider.
	auto sphere = Sphere3::builder()
		.withCenter({ (minX + maxX) * 0.5, (minY + maxY) * 0.5, (minZ + maxZ) * 0.5 })
		.withRadius(0.15 * domain.width())
		.makeShared();

	auto collider = RigidBodyCollider3::builder()
		.withSurface(sphere)
		.makeShared();

	solver->setCollider(collider);

	_solver = solver;

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
	ss << "<shape type=\"sphere\">";
	ss << "<point name=\"center\" x=\"" << sphere->center.x << "\" y=\"" << sphere->center.y
		<< "\" z=\"" << sphere->center.z << "\"/>";
	ss << "<float name=\"radius\" value=\"" << sphere->radius << "\"/>";
	ss << "<bsdf type=\"diffuse\">";
	ss << "<rgb name=\"diffuseReflectance\" value=\".9, .0, .0\"/>";
	ss << "</bsdf>";
	ss << "</shape>";
	_sceneXml = ss.str();
}
