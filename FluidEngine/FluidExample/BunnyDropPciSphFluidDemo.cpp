#include "BunnyDropPciSphFluidDemo.h"

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

void BunnyDropPciSphFluidDemo::setup(double radius)
{
	BoundingBox3D domain(Vector3D(-2.0, 0.0, -2.0), Vector3D(2.0, 5.0, 2.0));

	BoundingBox3D another = domain;
	//another.expand(2 * radius);
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
	solver->setTimeStepLimitScale(5.0);

	// Build emitter.
	BoundingBox3D sourceBound(domain);
	sourceBound.expand(-radius);

	auto bunnyMesh = TriangleMesh3::builder().makeShared();
	std::ifstream objFile("bunny.obj");
	if (objFile)
		bunnyMesh->readObj(&objFile);
	else
	{
		fprintf(stderr, "Cannot open dragon.obj\n");
		exit(EXIT_FAILURE);
	}
	bunnyMesh->scale(0.7f);
	bunnyMesh->translate(Vector3D(0, 1.2, 0));
	auto bunny = ImplicitTriangleMesh3::builder()
		.withTriangleMesh(bunnyMesh)
		.withMargin(radius)
		.makeShared();

	auto plane = Plane3::builder()
		.withNormal({ 0,1,0 })
		.withPoint({ 0, 0.1*domain.height(), 0 })
		.makeShared();

	auto sphere = Sphere3::builder()
		.withCenter(-domain.midPoint())
		.withRadius(0.0 * domain.width())
		.makeShared();

	auto surfaceSet = ImplicitSurfaceSet3::builder()
		.withExplicitSurfaces({plane, sphere })
		.makeShared();
	surfaceSet->addSurface(bunny);

	auto emitter = VolumeParticleEmitter3::builder()
		.withImplicitSurface(surfaceSet)
		.withSpacing(radius)
		.withMaxRegion(sourceBound)
		.withIsOneShot(true)
		.makeShared();
	solver->setEmitter(emitter);

	// Build collider.
	auto box = Box3::builder()
		.withIsNormalFlipped(true)
		.withBoundingBox(domain)
		.makeShared();

	auto collider = RigidBodyCollider3::builder()
		.withSurface(box)
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

	_sceneXml = ss.str();
}
