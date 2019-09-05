
#include "Engine/Geometry/Transform2.h"

#include "gtest/gtest.h"

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

TEST(Transform2, Constructors) {
	Transform2 t1;

	EXPECT_EQ(Vector2D(), t1.translation());
	EXPECT_EQ(0.0, t1.orientation());

	Transform2 t2({ 2.0, -5.0 }, kQuarterPiD);

	EXPECT_EQ(Vector2D(2.0, -5.0), t2.translation());
	EXPECT_EQ(kQuarterPiD, t2.orientation());
}

TEST(Transform2, Transform) {
	Transform2 t({ 2.0, -5.0 }, kHalfPiD);

	auto r1 = t.toWorld({ 4.0, 1.0 });
	EXPECT_DOUBLE_EQ(1.0, r1.x);
	EXPECT_DOUBLE_EQ(-1.0, r1.y);

	auto r2 = t.toLocal(r1);
	EXPECT_DOUBLE_EQ(4.0, r2.x);
	EXPECT_DOUBLE_EQ(1.0, r2.y);

	auto r3 = t.toWorldDirection({ 4.0, 1.0 });
	EXPECT_DOUBLE_EQ(-1.0, r3.x);
	EXPECT_DOUBLE_EQ(4.0, r3.y);

	auto r4 = t.toLocalDirection(r3);
	EXPECT_DOUBLE_EQ(4.0, r4.x);
	EXPECT_DOUBLE_EQ(1.0, r4.y);

	BoundingBox2D bbox({ -2, -1 }, { 2, 1 });
	auto r5 = t.toWorld(bbox);
	EXPECT_BOUNDING_BOX2_EQ(BoundingBox2D({ 1, -7 }, { 3, -3 }), r5);

	auto r6 = t.toLocal(r5);
	EXPECT_BOUNDING_BOX2_EQ(bbox, r6);
}