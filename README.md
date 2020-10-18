# wxMathPanel
Classes derived from wxPanel for function plotting.  
Contains two main classes:  
**wxMathPanelGraph** -- for plotting functions by equation.  
**wxMathPanelPointGraph** -- for plotting interpolated curves by points.  
The classes do not need to be compiled as a library, just add them into a project.  

**Screenshots**  
<img src="https://github.com/PeterLaptik/wxMathPanel/blob/master/samples/snapshots/sample_graph.png" height="35%" width="35%">
<img src="https://github.com/PeterLaptik/wxMathPanel/blob/master/samples/snapshots/sample_points.png" height="35%" width="35%">

### Features:
- interactive scaling and moving screen by mouse.
- changing between linear and logarithmic axis scales.
- movable legend.
- panel snapshot output to image file.

### Requirements:  
Depends on wxWidgets library 3.0 or higher.

### Usage:
Classes can be added onto a parent frame as a usual wxPanel.  
**wxMathPanelGraph**. The class can plot curves for objects that implement IDrawableFunction interface. See examples in the [sample folder](https://github.com/PeterLaptik/wxMathPanel/tree/master/samples).  
**wxMathPanelPointGraph**. The class can plot curves for objects that implement interface IPointSet. See examples in the [sample folder](https://github.com/PeterLaptik/wxMathPanel/tree/master/samples).

See detailed description in Doxygen generated [documentation](https://github.com/PeterLaptik/wxMathPanel/releases/download/1.0/wxmathpanel-docs.7z).  

## Samples assembling
A sample folder contains two makefiles:  
**Makefile.msvc** for nmake of Windows msvc compiller and wxWidgets dynamic link libraries. Before start, open it in notepad and change paths to the wxWidgets libraries 
(variables LIBINCLUDE, LIBSETUP, LIBA, LIBS).  
**Makefile** for FreeBSD clang. Open it and change wx-config utility name if requires. Use make-utility for assembling.  
Generated executables will be created in /samples/bin directory.
