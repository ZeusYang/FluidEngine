#include <iostream>
#include <string>
#include "WaterDropSphFluidDemo.h"
#include "DamBreakingSphFluidDemo.h"
#include "WaterDropPciSphFluidDemo.h"
#include "DamBreakingPciSphFluidDemo.h"
#include "FallPciSphFluidDemo.h"
#include "SmokeRisingEulerFluidDemo.h"

using namespace std;
using namespace Engine;

#define FORMAT "obj"
#define DESKTOP_PATH "C:/Users/ywc/Desktop"

void runWaterDropSphFluidDemo(int numberOfFrames, double fps, const std::string &dir);
void runDamBreakingSphFluidDemo(int numberOfFrames, double fps, const std::string &dir);
void runDamBreakingPciSphFluidDemo(int numberOfFrames, double fps, const std::string &dir);
void runWaterDropPciSphFluidDemo(int numberOfFrames, double fps, const std::string &dir);
void runFallPciSphFluidDemo(int numberOfFrames, double fps, const std::string &dir);
void runSmokeRisingEulerFluidDemo(int numberOfFrames, double fps, const std::string &dir);

int main(int argc, char *argv[])
{
	int numberOfFrames = 240;
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

	// Euler example.
	runSmokeRisingEulerFluidDemo(numberOfFrames, fps, rootDir + "/FluidSimRet/SmokeEuler/");


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