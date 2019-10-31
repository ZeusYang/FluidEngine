#include <iostream>
#include <string>
#include "WaterDropSphFluidDemo.h"
#include "DamBreakingSphFluidDemo.h"
#include "WaterDropPciSphFluidDemo.h"
#include "DamBreakingPciSphFluidDemo.h"
#include "FallPciSphFluidDemo.h"
#include "SmokeRisingEulerFluidDemo.h"
#include "BunnyDropEulerLiquidDemo.h"
#include "SmokeRisingDragonEulerFluidDemo.h"
#include "FluidPipeDropPciSphFluidDemo.h"
#include "BunnyDropPciSphFluidDemo.h"
#include "HemispherePcisphFluidDemo.h"

using namespace std;
using namespace Engine;

#define FORMAT "xyz"
#define DESKTOP_PATH "C:/Users/ywc/Desktop"

void runWaterDropSphFluidDemo(int numberOfFrames, double fps, const std::string &dir);
void runDamBreakingSphFluidDemo(int numberOfFrames, double fps, const std::string &dir);
void runDamBreakingPciSphFluidDemo(int numberOfFrames, double fps, const std::string &dir);
void runWaterDropPciSphFluidDemo(int numberOfFrames, double fps, const std::string &dir);
void runFallPciSphFluidDemo(int numberOfFrames, double fps, const std::string &dir);
void runSmokeRisingEulerFluidDemo(int numberOfFrames, double fps, const std::string &dir);
void runSmokeRisingDragonEulerFluidDemo(int numberOfFrames, double fps, const std::string &dir);
void runBunnyDropEulerFluidDemo(int numberOfFrames, double fps, const std::string &dir);
void runFluidPipeDropPciSphFluidDemo(int numberOfFrames, double fps, const std::string &dir);
void runBunnyDropPcisphFluidDemo(int numberOfFrames, double fps, const std::string &dir);
void runHemispherePcisphFluidDemo(int numberOfFrames, double fps, const std::string &dir);
void runHemispherePcisphFluidDemoFromXyz(int beginFrame, int numberOfFrames, double fps, const std::string &dir);


int main(int argc, char *argv[])
{
	int numberOfFrames = 1;
	double fps = 30.0;
	string rootDir = DESKTOP_PATH;

	// Sph example.
	//runWaterDropSphFluidDemo(numberOfFrames, fps, rootDir + "/FluidSimRet/WaterDropSph/");
	//runDamBreakingSphFluidDemo(numberOfFrames, fps, rootDir + "/FluidSimRet/DamBreakingSph/");

	// PciSph example.
	//runDamBreakingPciSphFluidDemo(numberOfFrames, fps, rootDir + "/FluidSimRet/DamBreakingPciSph/");
	//runWaterDropPciSphFluidDemo(numberOfFrames, fps, rootDir + "/FluidSimRet/WaterDropPciSph/");
	//runFallPciSphFluidDemo(numberOfFrames, fps, rootDir + "/FluidSimRet/FallPciSph/");
	//runDamBreakingPciSphFluidDemo(numberOfFrames, fps, rootDir + "/FluidSimRet/test/");
	//runFluidPipeDropPciSphFluidDemo(numberOfFrames, fps, rootDir + "/FluidSimRet/FluidPipe/");
	//runBunnyDropPcisphFluidDemo(numberOfFrames, fps, rootDir + "/FluidSimRet/BunnyDrop/");
	//runHemispherePcisphFluidDemo(numberOfFrames, fps, rootDir + "/FluidSimRet/Hemisphere/");
	runHemispherePcisphFluidDemoFromXyz(18, numberOfFrames, fps, rootDir + "/FluidSimRet/Hemisphere/");

	// Euler example.
	//runSmokeRisingEulerFluidDemo(numberOfFrames, fps, rootDir + "/FluidSimRet/SmokeEuler/");
	//runSmokeRisingDragonEulerFluidDemo(numberOfFrames, fps, rootDir + "/FluidSimRet/SmokeDragonEuler/");
	//runBunnyDropEulerFluidDemo(numberOfFrames, fps, rootDir + "/FluidSimRet/BunnyDropEuler/");


	return 0;
}

void runWaterDropSphFluidDemo(int numberOfFrames, double fps, const std::string &dir)
{
	double targetSpacing = 0.02;
	WaterDropSphFluidDemo::ptr simulator = 
		std::shared_ptr<WaterDropSphFluidDemo>(new WaterDropSphFluidDemo());
	simulator->setup(targetSpacing);
	simulator->run(dir, numberOfFrames, FORMAT, fps);
}

void runDamBreakingSphFluidDemo(int numberOfFrames, double fps, const std::string &dir)
{
	double targetSpacing = 0.02;
	DamBreakingSphFluidDemo::ptr simulator =
		std::shared_ptr<DamBreakingSphFluidDemo>(new DamBreakingSphFluidDemo());
	simulator->setup(targetSpacing);
	simulator->run(dir, numberOfFrames, FORMAT, fps);
}

void runDamBreakingPciSphFluidDemo(int numberOfFrames, double fps, const std::string &dir)
{
	double targetSpacing = 0.02;
	DamBreakingPciSphFluidDemo::ptr simulator =
		std::shared_ptr<DamBreakingPciSphFluidDemo>(new DamBreakingPciSphFluidDemo());
	simulator->setup(targetSpacing);
	simulator->run(dir, numberOfFrames, FORMAT, fps);
}

void runWaterDropPciSphFluidDemo(int numberOfFrames, double fps, const std::string &dir)
{
	double targetSpacing = 0.02;
	WaterDropPciSphFluidDemo::ptr simulator =
		std::shared_ptr<WaterDropPciSphFluidDemo>(new WaterDropPciSphFluidDemo());
	simulator->setup(targetSpacing);
	simulator->run(dir, numberOfFrames, FORMAT, fps);
}

void runFallPciSphFluidDemo(int numberOfFrames, double fps, const std::string &dir)
{
	double targetSpacing = 0.04;
	FallPciSphFluidDemo::ptr simulator =
		std::shared_ptr<FallPciSphFluidDemo>(new FallPciSphFluidDemo());
	simulator->setup(targetSpacing);
	simulator->run(dir, numberOfFrames, FORMAT, fps);
}

void runSmokeRisingEulerFluidDemo(int numberOfFrames, double fps, const std::string &dir)
{
	size_t resolutionX = 50;
	SmokeRisingEulerFluidDemo::ptr simulator =
		std::shared_ptr<SmokeRisingEulerFluidDemo>(new SmokeRisingEulerFluidDemo());
	simulator->setup(resolutionX);
	simulator->run(dir, numberOfFrames, "vol", fps);
}

void runSmokeRisingDragonEulerFluidDemo(int numberOfFrames, double fps, const std::string &dir)
{
	size_t resolutionX = 100;
	SmokeRisingDragonEulerFluidDemo::ptr simulator =
		std::shared_ptr<SmokeRisingDragonEulerFluidDemo>(new SmokeRisingDragonEulerFluidDemo());
	simulator->setup(resolutionX);
	simulator->run(dir, numberOfFrames, "vol", fps);
}

void runBunnyDropEulerFluidDemo(int numberOfFrames, double fps, const std::string &dir)
{
	size_t resolutionX = 50;
	BunnyDropEulerLiquidDemo::ptr simulator = std::shared_ptr<BunnyDropEulerLiquidDemo>(new BunnyDropEulerLiquidDemo());
	simulator->setup(resolutionX);
	simulator->run(dir, numberOfFrames, "obj", fps);
}

void runFluidPipeDropPciSphFluidDemo(int numberOfFrames, double fps, const std::string &dir)
{
	double targetSpacing = 0.02;
	FluidPipeDropPciSphFluidDemo::ptr simulator =
		std::shared_ptr<FluidPipeDropPciSphFluidDemo>(new FluidPipeDropPciSphFluidDemo());
	simulator->setup(targetSpacing);
	simulator->run(dir, numberOfFrames, FORMAT, fps);
}

void runBunnyDropPcisphFluidDemo(int numberOfFrames, double fps, const std::string &dir)
{
	double targetSpacing = 0.02;
	BunnyDropPciSphFluidDemo::ptr simulator =
		std::shared_ptr<BunnyDropPciSphFluidDemo>(new BunnyDropPciSphFluidDemo());
	simulator->setup(targetSpacing);
	simulator->run(dir, numberOfFrames, FORMAT, fps);
}

void runHemispherePcisphFluidDemo(int numberOfFrames, double fps, const std::string &dir)
{
	double targetSpacing = 0.015;
	HemispherePcisphFluidDemo::ptr simulator =
		std::shared_ptr<HemispherePcisphFluidDemo>(new HemispherePcisphFluidDemo());
	simulator->setup(targetSpacing);
	simulator->run(dir, numberOfFrames, FORMAT, fps);
}

void runHemispherePcisphFluidDemoFromXyz(int beginFrame, int numberOfFrames, double fps, const std::string &dir)
{
	double targetSpacing = 0.015;
	HemispherePcisphFluidDemo::ptr simulator =
		std::shared_ptr<HemispherePcisphFluidDemo>(new HemispherePcisphFluidDemo());
	simulator->setupFromPreviousFrame(targetSpacing, dir, beginFrame);
	simulator->run(dir, numberOfFrames, FORMAT, fps);
}