# FluidEngine

This is a fluid simulation engine for computer graphics applications. I adopt it from Doyub Kim's [fluid-engine-dev](https://github.com/doyubkim/fluid-engine-dev). It's built on C++11 and compiled with Microsoft Visual Studio 2017. This fluid engine is just for personal learning and interest. 



## Features

- Basic math and geometry operations and data structures
- Jacobi, Gauss-Seidel, SOR, MG, CG, ICCG, and MGPCG linear system solvers
- Spherical, SPH, Zhu & Bridson, and Anisotropic kernel for points-to-surface converter
- Intel TBB multi-threading backends
- SPH and PCISPH fluid simulators
- Converters between signed distance function and triangular mesh
- Stable fluids-based smoke simulator (Pure Euler fluid solver)
- Fluid solvers have both 2-D and 3-D version



## Start

Just clone the code and open it with Microsoft Visual Studio 2017.  There are three vs2017 projects. **FluidEngine** is the core of engine.  **Test** is for unit test while **FluidExample** includes several fluid demos.



## Todo

- PIC, FLIP, and APIC fluid simulators
- Level set-based liquid simulator
- Position based fluid simulator



## Learning Notes(In Chinese)

These are not documentations for the engine but simulation algorithm notes.

- [流体模拟Fluid Simulation：流体模拟基础](https://yangwc.com/2019/05/01/fluidSimulation/)
- [流体模拟Fluid Simulation：Level Set & Marching Cube](https://yangwc.com/2019/07/30/LevelSet/)
- [流体模拟Fluid Simulation：求解流体不可压缩的泊松方程](https://yangwc.com/2019/08/03/MakingFluidImcompressible/)
- [流体模拟Fluid Simulation：基于SPH的拉格朗日流体模拟](https://yangwc.com/2019/08/29/SPH/)



## Example

The engine is just for simulation and can use some renderers (such as  [Mitsuba renderer](https://www.mitsuba-renderer.org/)) to render it for visualization.

#### PCISPH Simulation Example

![image](pictures/1.jpg)



## Acknowledgement

Thanks very much for Doyub Kim's book, ["Fluid Engine Development"](https://www.crcpress.com/Fluid-Engine-Development/Kim/p/book/9781498719926). I highly recommend this book if you are interested in fluid simulation.