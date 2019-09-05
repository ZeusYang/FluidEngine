#include <iostream>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fstream>

#include "Engine/Utils/Logging.h"

using namespace std;
using namespace Engine;

int main(int argc, char *argv[])
{
	::testing::InitGoogleMock(&argc, argv);
	::testing::InitGoogleTest(&argc, argv);

	
	std::ofstream logFile("unit_tests.log");
	if (logFile) {
		Logging::setAllStream(&logFile);
	}

	int ret = RUN_ALL_TESTS();

	return ret;
}