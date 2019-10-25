#include "FluidPipeDropPciSphFluidDemo.h"

#include "Engine/Geometry/Plane3.h"
#include "Engine/Geometry/Sphere3.h"
#include "Engine/Geometry/TriangleMesh3.h"
#include "Engine/Geometry/ImplicitTriangleMesh3.h"
#include "Engine/Geometry/ImplicitSurfaceSet3.h"
#include "Engine/Geometry/BoundingBox3.h"
#include "Engine/Geometry/Box3.h"
#include "Engine/Geometry/Cylinder3.h"
#include "Engine/Simulation/PciSphSolver3.h"
#include "Engine/Simulation/VolumeParticleEmitter3.h"
#include "Engine/Simulation/RigidBodyCollider3.h"

#include <sstream>

using namespace Engine;

void FluidPipeDropPciSphFluidDemo::setup(double radius)
{
	BoundingBox3D domain(Vector3D(-2.0, 0.0, -2.0), Vector3D(+2.0, 6.0, 2.0));

	BoundingBox3D another = domain;
	another.expand(2 * radius);
	minX = another.lowerCorner.x;
	minY = another.lowerCorner.y;
	minZ = another.lowerCorner.z;
	maxX = another.upperCorner.x;
	maxY = another.upperCorner.y;
	maxZ = another.upperCorner.z;

	double lz = domain.depth();

	_origin = Vector3D(minX, minY, minZ);
	_resolution = Size3(domain.width() / radius + 5, domain.height() / radius + 5, domain.depth() / radius + 5);

	// Build solver
	auto solver = PciSphSolver3::builder()
		.withTargetDensity(1000.0)
		.withTargetSpacing(radius)
		.makeShared();
	solver->setPseudoViscosityCoefficient(0.0);
	solver->setTimeStepLimitScale(3.0);

	// Build emitter.
	BoundingBox3D sourceBound(domain);
	sourceBound.expand(-radius);
	auto cylinder = Cylinder3::builder()
		.withCenter({ 0, 3.8, 0 })
		.withRadius(0.8)
		.withHeight(1.8)
		.makeShared();
	auto emitter = VolumeParticleEmitter3::builder()
		.withSurface(cylinder)
		.withMaxRegion(sourceBound)
		.withSpacing(radius)
		.withIsOneShot(true)
		.withAllowOverlapping(false)
		.makeShared();
	solver->setEmitter(emitter);

	// Build collider.
	auto dragonMesh = TriangleMesh3::builder().makeShared();
	std::ifstream objFile("bunny.obj");
	if (objFile)
		dragonMesh->readObj(&objFile);
	else
	{
		fprintf(stderr, "Cannot open dragon.obj\n");
		exit(EXIT_FAILURE);
	}

	auto dragon = ImplicitTriangleMesh3::builder()
		.withTriangleMesh(dragonMesh)
		.withMargin(radius)
		.makeShared();

	auto box = Box3::builder()
		.withIsNormalFlipped(true)
		.withBoundingBox(domain)
		.makeShared();

	auto surfaceSet = ImplicitSurfaceSet3::builder()
		.withExplicitSurfaces({ box })
		.makeShared();

	surfaceSet->addSurface(dragon);

	auto collider = RigidBodyCollider3::builder()
		.withSurface(surfaceSet)
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

	// cyl1
	ss << "<shape type=\"obj\">";
	ss << "<string name=\"filename\" value=\"bunny.obj\"/>";
	ss << "<bsdf type=\"diffuse\">";
	ss << "<rgb name=\"diffuseReflectance\" value=\".9, .9, .9\"/>";
	ss << "</bsdf>";
	ss << "</shape>";

	_sceneXml = ss.str();
}
