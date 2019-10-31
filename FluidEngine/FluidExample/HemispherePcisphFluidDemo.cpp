#include "HemispherePcisphFluidDemo.h"

#include "Engine/Geometry/Plane3.h"
#include "Engine/Geometry/Sphere3.h"
#include "Engine/Geometry/TriangleMesh3.h"
#include "Engine/Geometry/ImplicitTriangleMesh3.h"
#include "Engine/Geometry/ImplicitSurfaceSet3.h"
#include "Engine/Geometry/BoundingBox3.h"
#include "Engine/Geometry/Box3.h"
#include "Engine/Geometry/Cylinder3.h"
#include "Engine/Simulation/PciSphSolver3.h"
#include "Engine/Simulation/RawParticleEmitter3.h"
#include "Engine/Simulation/VolumeParticleEmitter3.h"
#include "Engine/Simulation/RigidBodyCollider3.h"

#include <sstream>

using namespace Engine;

void HemispherePcisphFluidDemo::setup(double radius)
{
	BoundingBox3D domain(Vector3D(-2.5, 0.0, -1.5), Vector3D(2.5, 4.0, 1.5));

	minX = domain.lowerCorner.x;
	minY = domain.lowerCorner.y;
	minZ = domain.lowerCorner.z;
	maxX = domain.upperCorner.x;
	maxY = domain.upperCorner.y;
	maxZ = domain.upperCorner.z;

	double lz = domain.depth();

	_origin = Vector3D(minX, minY, minZ);
	_resolution = Size3(domain.width() / radius + 5, domain.height() / radius + 5, domain.depth() / radius + 5);

	// Build solver
	auto solver = PciSphSolver3::builder()
		.withTargetDensity(1000.0)
		.withTargetSpacing(radius)
		.makeShared();
	solver->setPseudoViscosityCoefficient(0.0);
	solver->setTimeStepLimitScale(4.0);

	// Build emitter.
	BoundingBox3D sourceBound(domain);
	sourceBound.expand(-radius);

	auto box = Box3::builder()
		.withLowerCorner({ -2.4, 0.45, -1.45 })
		.withUpperCorner({ -0.5, 1.50, +1.45 })
		.makeShared();

	auto sphere = Sphere3::builder()
		.withCenter(-domain.midPoint())
		.withRadius(0.0 )
		.makeShared();

	auto surfaceSet = ImplicitSurfaceSet3::builder()
		.withExplicitSurfaces({ box, sphere })
		.makeShared();

	auto emitter = VolumeParticleEmitter3::builder()
		.withImplicitSurface(surfaceSet)
		.withSpacing(radius)
		.withMaxRegion(sourceBound)
		.withIsOneShot(true)
		.makeShared();
	solver->setEmitter(emitter);

	// Build collider.
	auto constraint = Box3::builder()
		.withIsNormalFlipped(true)
		.withBoundingBox(domain)
		.makeShared();

	Vector3D p1(-2.5, 0.40, -1.5);
	Vector3D p2(-2.5, 0.40, +1.5);
	Vector3D p3(+2.5, 0.0, +1.5);
	auto plane = std::shared_ptr<Plane3>(new Plane3(p1, p2, p3));

	auto sphere1 = Sphere3::builder()
		.withCenter({ 1.5, 0.10, -0.8 })
		.withRadius(0.40)
		.makeShared();

	auto sphere2 = Sphere3::builder()
		.withCenter({ 1.5, 0.10, 0.8 })
		.withRadius(0.40)
		.makeShared();

	auto colliderSet = ImplicitSurfaceSet3::builder()
		.withExplicitSurfaces({ constraint, plane, sphere1, sphere2 })
		.makeShared();

	auto collider = RigidBodyCollider3::builder()
		.withSurface(colliderSet)
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
	ss << "<point name=\"center\" x=\"" << sphere1->center.x << "\" y=\"" << sphere1->center.y
		<< "\" z=\"" << sphere1->center.z << "\"/>";
	ss << "<float name=\"radius\" value=\"" << sphere1->radius << "\"/>";
	ss << "<bsdf type=\"diffuse\">";
	ss << "<rgb name=\"diffuseReflectance\" value=\".9, .0, .0\"/>";
	ss << "</bsdf>";
	ss << "</shape>";

	ss << "<shape type=\"sphere\">";
	ss << "<point name=\"center\" x=\"" << sphere2->center.x << "\" y=\"" << sphere2->center.y
		<< "\" z=\"" << sphere2->center.z << "\"/>";
	ss << "<float name=\"radius\" value=\"" << sphere2->radius << "\"/>";
	ss << "<bsdf type=\"diffuse\">";
	ss << "<rgb name=\"diffuseReflectance\" value=\".9, .0, .0\"/>";
	ss << "</bsdf>";
	ss << "</shape>";

	ss << "<texture type=\"checkerboard\" id=\"floortex\">";
	ss << "<rgb name=\"color0\" value=\"0.6\"/>";
	ss << "<rgb name=\"color1\" value=\"0.0\"/>";
	ss << "<float name=\"uscale\" value=\"6.0\"/>";
	ss << "<float name=\"vscale\" value=\"6.0\"/>";
	ss << "<float name=\"uoffset\" value=\"0.0\"/>";
	ss << "<float name=\"voffset\" value=\"0.0\"/>";
	ss << "</texture>";

	ss << "<shape type=\"obj\">";
	ss << "<string name=\"filename\" value=\"floor.obj\"/>";
	ss << "<bsdf type=\"diffuse\">";
	ss << "<ref name=\"reflectance\" id=\"floortex\"/>";
	ss << "</bsdf>";
	ss << "</shape>";

	_sceneXml = ss.str();
}

void HemispherePcisphFluidDemo::setupFromPreviousFrame(double radius, const std::string &dir, int frameCnt)
{
	BoundingBox3D domain(Vector3D(-2.5, 0.0, -1.5), Vector3D(2.5, 4.0, 1.5));

	minX = domain.lowerCorner.x;
	minY = domain.lowerCorner.y;
	minZ = domain.lowerCorner.z;
	maxX = domain.upperCorner.x;
	maxY = domain.upperCorner.y;
	maxZ = domain.upperCorner.z;

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

	auto box = Box3::builder()
		.withLowerCorner({ -2.4, 0.45, -1.45 })
		.withUpperCorner({ -0.5, 1.50, +1.45 })
		.makeShared();

	auto sphere = Sphere3::builder()
		.withCenter(-domain.midPoint())
		.withRadius(0.0)
		.makeShared();

	auto surfaceSet = ImplicitSurfaceSet3::builder()
		.withExplicitSurfaces({ box, sphere })
		.makeShared();

	// load the particles from .xyz file.
	Array1<Vector3D> positionsFromFile;
	ParticleFluidDemo::readParticleFromFile(positionsFromFile, dir, frameCnt);
	auto emitter = RawParticleEmitter3::builder()
		.withPositions(&positionsFromFile)
		.withIsOneShot(true)
		.makeShared();
	solver->setEmitter(emitter);
	_bFrame = frameCnt + 1;

	// Build collider.
	auto constraint = Box3::builder()
		.withIsNormalFlipped(true)
		.withBoundingBox(domain)
		.makeShared();

	Vector3D p1(-2.5, 0.40, -1.5);
	Vector3D p2(-2.5, 0.40, +1.5);
	Vector3D p3(+2.5, 0.0, +1.5);
	auto plane = std::shared_ptr<Plane3>(new Plane3(p1, p2, p3));

	auto sphere1 = Sphere3::builder()
		.withCenter({ 1.5, 0.10, -0.8 })
		.withRadius(0.40)
		.makeShared();

	auto sphere2 = Sphere3::builder()
		.withCenter({ 1.5, 0.10, 0.8 })
		.withRadius(0.40)
		.makeShared();

	auto colliderSet = ImplicitSurfaceSet3::builder()
		.withExplicitSurfaces({ constraint, plane, sphere1, sphere2 })
		.makeShared();

	auto collider = RigidBodyCollider3::builder()
		.withSurface(colliderSet)
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
	ss << "<point name=\"center\" x=\"" << sphere1->center.x << "\" y=\"" << sphere1->center.y
		<< "\" z=\"" << sphere1->center.z << "\"/>";
	ss << "<float name=\"radius\" value=\"" << sphere1->radius << "\"/>";
	ss << "<bsdf type=\"diffuse\">";
	ss << "<rgb name=\"diffuseReflectance\" value=\".9, .0, .0\"/>";
	ss << "</bsdf>";
	ss << "</shape>";

	ss << "<shape type=\"sphere\">";
	ss << "<point name=\"center\" x=\"" << sphere2->center.x << "\" y=\"" << sphere2->center.y
		<< "\" z=\"" << sphere2->center.z << "\"/>";
	ss << "<float name=\"radius\" value=\"" << sphere2->radius << "\"/>";
	ss << "<bsdf type=\"diffuse\">";
	ss << "<rgb name=\"diffuseReflectance\" value=\".9, .0, .0\"/>";
	ss << "</bsdf>";
	ss << "</shape>";

	ss << "<texture type=\"checkerboard\" id=\"floortex\">";
	ss << "<rgb name=\"color0\" value=\"0.6\"/>";
	ss << "<rgb name=\"color1\" value=\"0.0\"/>";
	ss << "<float name=\"uscale\" value=\"6.0\"/>";
	ss << "<float name=\"vscale\" value=\"6.0\"/>";
	ss << "<float name=\"uoffset\" value=\"0.0\"/>";
	ss << "<float name=\"voffset\" value=\"0.0\"/>";
	ss << "</texture>";

	ss << "<shape type=\"obj\">";
	ss << "<string name=\"filename\" value=\"floor.obj\"/>";
	ss << "<bsdf type=\"diffuse\">";
	ss << "<ref name=\"reflectance\" id=\"floortex\"/>";
	ss << "</bsdf>";
	ss << "</shape>";

	_sceneXml = ss.str();
}
