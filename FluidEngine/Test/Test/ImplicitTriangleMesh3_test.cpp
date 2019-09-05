#include "Engine/Geometry/ImplicitTriangleMesh3.h"
#include "Engine/Geometry/Box3.h"
#include "Engine/Geometry/Sphere3.h"
#include "Engine/Geometry/SurfaceToImplicit3.h"
#include "test_utils.h"
#include <gtest/gtest.h>

using namespace Engine;

TEST(ImplicitTriangleMesh3, SignedDistance) {
	auto box = Box3::builder()
		.withLowerCorner({ 0, 0, 0 })
		.withUpperCorner({ 1, 1, 1 })
		.makeShared();
	SurfaceToImplicit3 refSurf(box);

	std::ifstream objFile("cube.obj");
	auto mesh = TriangleMesh3::builder().makeShared();
	mesh->readObj(&objFile);

	auto imesh = ImplicitTriangleMesh3::builder()
		.withTriangleMesh(mesh)
		.withResolutionX(20)
		.makeShared();

	for (size_t i = 0; i < getNumberOfSamplePoints3(); ++i) {
		auto sample = getSamplePoints3()[i];
		auto refAns = refSurf.signedDistance(sample);
		auto actAns = imesh->signedDistance(sample);

		EXPECT_NEAR(refAns, actAns, 1.0 / 20);
	}
}
