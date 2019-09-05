
#include "Engine/Geometry/Transform3.h"

#include <gtest/gtest.h>

using namespace Engine;

#define EXPECT_VECTOR2_EQ(expected, actual)     \
    EXPECT_DOUBLE_EQ((expected).x, (actual).x); \
    EXPECT_DOUBLE_EQ((expected).y, (actual).y);

#define EXPECT_VECTOR2_NEAR(expected, actual, eps) \
    EXPECT_NEAR((expected).x, (actual).x, eps);    \
    EXPECT_NEAR((expected).y, (actual).y, eps);

#define EXPECT_VECTOR3_EQ(expected, actual)     \
    EXPECT_DOUBLE_EQ((expected).x, (actual).x); \
    EXPECT_DOUBLE_EQ((expected).y, (actual).y); \
    EXPECT_DOUBLE_EQ((expected).z, (actual).z);

#define EXPECT_VECTOR3_NEAR(expected, actual, eps) \
    EXPECT_NEAR((expected).x, (actual).x, eps);    \
    EXPECT_NEAR((expected).y, (actual).y, eps);    \
    EXPECT_NEAR((expected).z, (actual).z, eps);

#define EXPECT_VECTOR4_EQ(expected, actual)     \
    EXPECT_DOUBLE_EQ((expected).x, (actual).x); \
    EXPECT_DOUBLE_EQ((expected).y, (actual).y); \
    EXPECT_DOUBLE_EQ((expected).z, (actual).z); \
    EXPECT_DOUBLE_EQ((expected).w, (actual).w);

#define EXPECT_VECTOR4_NEAR(expected, actual, eps) \
    EXPECT_NEAR((expected).x, (actual).x, eps);    \
    EXPECT_NEAR((expected).y, (actual).y, eps);    \
    EXPECT_NEAR((expected).z, (actual).z, eps);    \
    EXPECT_NEAR((expected).w, (actual).w, eps);

#define EXPECT_BOUNDING_BOX2_EQ(expected, actual)                    \
    EXPECT_VECTOR2_EQ((expected).lowerCorner, (actual).lowerCorner); \
    EXPECT_VECTOR2_EQ((expected).upperCorner, (actual).upperCorner);

#define EXPECT_BOUNDING_BOX2_NEAR(expected, actual, eps)                    \
    EXPECT_VECTOR2_NEAR((expected).lowerCorner, (actual).lowerCorner, eps); \
    EXPECT_VECTOR2_NEAR((expected).upperCorner, (actual).upperCorner, eps);

#define EXPECT_BOUNDING_BOX3_EQ(expected, actual)                    \
    EXPECT_VECTOR3_EQ((expected).lowerCorner, (actual).lowerCorner); \
    EXPECT_VECTOR3_EQ((expected).upperCorner, (actual).upperCorner);

#define EXPECT_BOUNDING_BOX3_NEAR(expected, actual, eps)                    \
    EXPECT_VECTOR3_NEAR((expected).lowerCorner, (actual).lowerCorner, eps); \
    EXPECT_VECTOR3_NEAR((expected).upperCorner, (actual).upperCorner, eps);

TEST(Transform3, Constructors) {
	Transform3 t1;

	EXPECT_EQ(Vector3D(), t1.translation());
	EXPECT_EQ(0.0, t1.orientation().angle());

	Transform3 t2({ 2.0, -5.0, 1.0 }, QuaternionD({ 0.0, 1.0, 0.0 }, kQuarterPiD));

	EXPECT_EQ(Vector3D(2.0, -5.0, 1.0), t2.translation());
	EXPECT_EQ(Vector3D(0.0, 1.0, 0.0), t2.orientation().axis());
	EXPECT_DOUBLE_EQ(kQuarterPiD, t2.orientation().angle());
}

TEST(Transform3, Transform) {
	Transform3 t({ 2.0, -5.0, 1.0 }, QuaternionD({ 0.0, 1.0, 0.0 }, kHalfPiD));

	auto r1 = t.toWorld({ 4.0, 1.0, -3.0 });
	EXPECT_NEAR(-1.0, r1.x, 1e-9);
	EXPECT_NEAR(-4.0, r1.y, 1e-9);
	EXPECT_NEAR(-3.0, r1.z, 1e-9);

	auto r2 = t.toLocal(r1);
	EXPECT_NEAR(4.0, r2.x, 1e-9);
	EXPECT_NEAR(1.0, r2.y, 1e-9);
	EXPECT_NEAR(-3.0, r2.z, 1e-9);

	auto r3 = t.toWorldDirection({ 4.0, 1.0, -3.0 });
	EXPECT_NEAR(-3.0, r3.x, 1e-9);
	EXPECT_NEAR(1.0, r3.y, 1e-9);
	EXPECT_NEAR(-4.0, r3.z, 1e-9);

	auto r4 = t.toLocalDirection(r3);
	EXPECT_NEAR(4.0, r4.x, 1e-9);
	EXPECT_NEAR(1.0, r4.y, 1e-9);
	EXPECT_NEAR(-3.0, r4.z, 1e-9);

	BoundingBox3D bbox({ -2, -1, -3 }, { 2, 1, 3 });
	auto r5 = t.toWorld(bbox);
	EXPECT_BOUNDING_BOX3_NEAR(BoundingBox3D({ -1, -6, -1 }, { 5, -4, 3 }), r5, 1e-9);

	auto r6 = t.toLocal(r5);
	EXPECT_BOUNDING_BOX3_NEAR(bbox, r6, 1e-9);
}