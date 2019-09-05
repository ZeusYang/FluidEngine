#include "Engine/Geometry/Plane2.h"

#include <gtest/gtest.h>

using namespace Engine;

TEST(Plane2, Builder) {
	Plane2 plane = Plane2::builder()
		.withNormal({ 1, 0 })
		.withPoint({ 2, 3 })
		.build();

	EXPECT_EQ(Vector2D(1, 0), plane.normal);
	EXPECT_EQ(Vector2D(2, 3), plane.point);
}