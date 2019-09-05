#include "DamBreakingSphFluidDemo.h"

#include "Engine/Geometry/Plane3.h"
#include "Engine/Geometry/Sphere3.h"
#include "Engine/Geometry/Cylinder3.h"
#include "Engine/Geometry/ImplicitSurfaceSet3.h"
#include "Engine/Geometry/BoundingBox3.h"
#include "Engine/Geometry/Box3.h"
#include "Engine/Simulation/SphSolver3.h"
#include "Engine/Simulation/VolumeParticleEmitter3.h"
#include "Engine/Simulation/RigidBodyCollider3.h"

#include <sstream>

using namespace Engine;

void DamBreakingSphFluidDemo::setup(double radius)
{
	BoundingBox3D domain(Vector3D(), Vector3D(3, 2, 1.5));
	minX = domain.lowerCorner.x;
	minY = domain.lowerCorner.y;
	minZ = domain.lowerCorner.z;
	maxX = domain.upperCorner.x;
	maxY = domain.upperCorner.y;
	maxZ = domain.upperCorner.z;

	_origin = Vector3D(minX, minY, minZ);
	_resolution = Size3(domain.width() / radius + 5, domain.height() / radius + 5, domain.depth() / radius + 5);

	double lz = domain.depth();

	// Build solver
	auto solver = SphSolver3::builder()
		.withTargetDensity(1000.0)
		.withTargetSpacing(radius)
		.makeShared();
	solver->setPseudoViscosityCoefficient(0.0);
	solver->setTimeStepLimitScale(1.0);

	// Build emitter.
	BoundingBox3D sourceBound(domain);
	sourceBound.expand(-radius);
	auto box1 = Box3::builder()
		.withLowerCorner({ 0, 0, 0 })
		.withUpperCorner({ 0.5 + 0.001, 0.75 + 0.001, 0.75*lz + 0.001 })
		.makeShared();
	auto box2 = Box3::builder()
		.withLowerCorner({ 2.5 - 0.001, 0, 0.25*lz - 0.001 })
		.withUpperCorner({ 3.5 + 0.001,0.75 + 0.001,1.5*lz + 0.001 })
		.makeShared();
	auto boxSet = ImplicitSurfaceSet3::builder()
		.withExplicitSurfaces({ box1, box2 })
		.makeShared();
	auto emitter = VolumeParticleEmitter3::builder()
		.withSurface(boxSet)
		.withMaxRegion(sourceBound)
		.withSpacing(radius)
		.makeShared();
	solver->setEmitter(emitter);

	// Build collider.
	auto cyl1 = Cylinder3::builder()
		.withCenter({ 1, 0.375, 0.375 })
		.withRadius(0.1)
		.withHeight(0.75)
		.makeShared();

	auto cyl2 = Cylinder3::builder()
		.withCenter({ 1.5, 0.375, 0.75 })
		.withRadius(0.1)
		.withHeight(0.75)
		.makeShared();

	auto cyl3 = Cylinder3::builder()
		.withCenter({ 2, 0.375, 1.125 })
		.withRadius(0.1)
		.withHeight(0.75)
		.makeShared();
	auto box = Box3::builder()
		.withIsNormalFlipped(true)
		.withBoundingBox(domain)
		.makeShared();

	auto surfaceSet = ImplicitSurfaceSet3::builder()
		.withExplicitSurfaces({ cyl1, cyl2, cyl3, box })
		.makeShared();

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

	// cylinder object.
	Vector3D p0, p1;

	// cyl1
	p0 = cyl1->endpoint(0);
	p1 = cyl1->endpoint(1);
	ss << "<shape type=\"cylinder\">";
	ss << "<float name=\"radius\" value=\"" << cyl1->radius << "\"/>";
	ss << "<point name=\"p0\" x=\"" << p0.x << "\" y=\"" << p0.y << "\" z=\"" << p0.z << "\"/>";
	ss << "<point name=\"p1\" x=\"" << p1.x << "\" y=\"" << p1.y << "\" z=\"" << p1.z << "\"/>";
	ss << "<bsdf type=\"diffuse\">";
	ss << "<rgb name=\"diffuseReflectance\" value=\".9, .0, .0\"/>";
	ss << "</bsdf>";
	ss << "</shape>";
	// disk1
	ss << "<shape type=\"disk\">";
	ss << "<transform name=\"toWorld\">";
	ss << "<rotate x=\"1\" angle=\"-90\"/>";
	ss << "<scale value=\"0.1\"/>";
	ss << "<translate x=\"" << p1.x << "\" y=\"" << p1.y << "\" z=\"" << p1.z << "\"/>";
	ss << "</transform>";
	ss << "<bsdf type=\"diffuse\">";
	ss << "<rgb name=\"diffuseReflectance\" value=\".9, .0, .0\"/>";
	ss << "</bsdf>";
	ss << "</shape>";

	// cyl2
	p0 = cyl2->endpoint(0);
	p1 = cyl2->endpoint(1);
	ss << "<shape type=\"cylinder\">";
	ss << "<float name=\"radius\" value=\"" << cyl2->radius << "\"/>";
	ss << "<point name=\"p0\" x=\"" << p0.x << "\" y=\"" << p0.y << "\" z=\"" << p0.z << "\"/>";
	ss << "<point name=\"p1\" x=\"" << p1.x << "\" y=\"" << p1.y << "\" z=\"" << p1.z << "\"/>";
	ss << "<bsdf type=\"diffuse\">";
	ss << "<rgb name=\"diffuseReflectance\" value=\".9, .0, .0\"/>";
	ss << "</bsdf>";
	ss << "</shape>";
	// disk2
	ss << "<shape type=\"disk\">";
	ss << "<transform name=\"toWorld\">";
	ss << "<rotate x=\"1\" angle=\"-90\"/>";
	ss << "<scale value=\"0.1\"/>";
	ss << "<translate x=\"" << p1.x << "\" y=\"" << p1.y << "\" z=\"" << p1.z << "\"/>";
	ss << "</transform>";
	ss << "<bsdf type=\"diffuse\">";
	ss << "<rgb name=\"diffuseReflectance\" value=\".9, .0, .0\"/>";
	ss << "</bsdf>";
	ss << "</shape>";

	// cyl3
	p0 = cyl3->endpoint(0);
	p1 = cyl3->endpoint(1);
	ss << "<shape type=\"cylinder\">";
	ss << "<float name=\"radius\" value=\"" << cyl3->radius << "\"/>";
	ss << "<point name=\"p0\" x=\"" << p0.x << "\" y=\"" << p0.y << "\" z=\"" << p0.z << "\"/>";
	ss << "<point name=\"p1\" x=\"" << p1.x << "\" y=\"" << p1.y << "\" z=\"" << p1.z << "\"/>";
	ss << "<bsdf type=\"diffuse\">";
	ss << "<rgb name=\"diffuseReflectance\" value=\".9, .0, .0\"/>";
	ss << "</bsdf>";
	ss << "</shape>";
	// disk3
	ss << "<shape type=\"disk\">";
	ss << "<transform name=\"toWorld\">";
	ss << "<rotate x=\"1\" angle=\"-90\"/>";
	ss << "<scale value=\"0.1\"/>";
	ss << "<translate x=\"" << p1.x << "\" y=\"" << p1.y << "\" z=\"" << p1.z << "\"/>";
	ss << "</transform>";
	ss << "<bsdf type=\"diffuse\">";
	ss << "<rgb name=\"diffuseReflectance\" value=\".9, .0, .0\"/>";
	ss << "</bsdf>";
	ss << "</shape>";

	_sceneXml = ss.str();

}
