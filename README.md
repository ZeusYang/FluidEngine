# FluidEngine

This is a fluid simulation engine for computer graphics applications. I adopt it from Doyub Kim's [fluid-engine-dev](https://github.com/doyubkim/fluid-engine-dev). It's built on C++11 and compiled with Microsoft Visual Studio 2017. This fluid engine is just for personal learning and interest. 



## Features

- Basic math and geometry operations and data structures
- Jacobi, Gauss-Seidel, SOR, MG, CG, ICCG, and MGPCG linear system solvers
- Spherical, SPH, Zhu & Bridson, and Anisotropic kernel for points-to-surface converter
- Intel TBB multi-threading backends
- SPH and PCISPH fluid simulators
- Converters between signed distance function and triangular mesh
- Fluid solvers have both 2-D and 3-D version



## Start

Just clone the code and open it with Microsoft Visual Studio 2017.  There are three vs2017 projects. **FluidEngine** is the core of engine.  **Test** is for unit test while **FluidExample** includes several fluid demos.



## Todo

- Stable fluids-based smoke simulator
- PIC, FLIP, and APIC fluid simulators
- Level set-based liquid simulator



## Example

The engine is just for simulation and can use some renderers (such as  [Mitsuba renderer](https://www.mitsuba-renderer.org/)) to render it for visualization.

#### PCISPH Simulation Example

![image](pictures/1.jpg)



## Acknowledgement

Thanks very much for Doyub Kim's book, ["Fluid Engine Development"](https://www.crcpress.com/Fluid-Engine-Development/Kim/p/book/9781498719926). I highly recommend this book if you are interested in fluid simulation.