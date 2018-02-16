Helicopter Demo readme file
============================

Minimum requirements
====================

Nvidia Geforce 3, or equivilent ATI card required,
Nvidia Geforce 4ti or better is recommended.

(It is possible that the application may run on anything from a Geforce upwards,
 but this cannot be guaranteed due to lack of hardware to test on. 
The game has been tested on a Geforce 5200 FX, and Geforce 4 ti 4600, and runs
well on this hardware)

It is recommended that the application be run in fullscreen mode, for maximum performance.

Microsoft DirectX 9.0c - April 2005 update, or later is required. 
This version is recommended, as it is the version that the application was built and tested with.

The DirectX runtime can be downloaded from
http://www.microsoft.com/downloads/details.aspx?FamilyId=0A9B6820-BFBB-4799-9908-D418CDEAC197&displaylang=en


Gameplay Instructions
======================

Use your helicopter to destroy all the SAM sites in the quickest time possible.


Controls
=========

W - Forward
S - Backward
A - Strafe left
D - Strafe right
R - Gain height
F - Lose height
Esc - Exit program
Mouse Move - Turn
Mouse1 - Fire Missile


Features:
=========

A customisable effect file system, which parses effect files from disk,
describing the process of rendering an object in an arbitrary number of passes.
The rendering effects of the sky and terrain are not hard coded, they are parsed
from effect files in the Data\Art\Effects directory. Each effect consists of
a series of techniques, which are validated for support on the target hardware.
The effect system automatically selects an appropriate technique for the hardware
from the effect file.

A DirectInput based input system, allowing the application to capture and react to
keyboard and mouse input.

A font system, which allows any of the system fonts to be loaded and displayed for
in-game text.

A sky dome.

A scene graph.

A terrain, divided into chunks, using the scene graph to place terrain chunks appropriately.


Future improvements:
=====================

In the near future, I plan to add the following:

Newton Physics library

Python scripting support. I plan to integrate the python scripting from my 
last project into the engine, and use this to script more complex/story based gameplay.
My plan is to create a game vaguely similar to the old Desert Strike games.

Vertex and pixel shaders, supported by the effect file system.

Support for different render targets, allowing effects like refraction, and glow.

Support for cubemap textures.

Terrain texture splatting, to give a more varied terrain appearance.

A user interface, allowing access to a quake like console. The underlying
console system exists, but due to time constraints, I have not yet 
had the time to implement the user interface.

Refractive and reflective water.


Known issues
==============

The application may fail to start, with a missing DirectX DLL error: This application requires the April 2005
version of DirectX (or later). If this error is encountered, then install the correct version of the DirectX runtime.

http://www.microsoft.com/downloads/details.aspx?FamilyId=0A9B6820-BFBB-4799-9908-D418CDEAC197&displaylang=en

There seems to be a driver bug on certain versions of the Nvidia drivers
that causes objects to be flatly textured with the average of the pixels in the top row of the texture.
If this happens, then update to the latest version of the Nvidia drivers. This problem happens very rarely
on my laptop, but I've not been able to reproduce it on any other computer. 
I've not seen the problem for several months, so this shouldn't happen.

If any other problems are encountered, please email me at bryanrobertsoncv@blueyonder.co.uk, with a 
thorough description of the problem, and preferrably, the log file "TerrainDemo log.txt" that was created
on the desktop.



Building the project
====================

A project file for Microsoft Visual Studio 2002 is provided. 
The Terrain demo requires the following libraries to build:

Newton Dynamics - http://www.newtondynamics.com
Boost - www.boost.org - Version 1.32.0 recommended
STLPort - www.stlport.com - Version 4.6.2 recommended
Microsoft DirectX SDK - msdn.microsoft.com/directX - April 2005 update recommended

The application was built with the specified versions of the libraries, and they are known to work.

The tools flex++, and bison++ are required to generate the effect file parser. The executables are located in
the Tools\flex++bison++ subdirectory. Custom header/cpp skeleton files for flex++ and bison++ can also
be found in this directory. Visual Studio should call these automatically during the build process.


Copyright notices
=================

STLPort
Boris Fomitchev grants Licensee a non-exclusive, non-transferable, royalty-free license to use STLport and its documentation without fee.

By downloading, using, or copying STLport or any portion thereof,  Licensee agrees to abide by the intellectual property laws and all other applicable laws of the United States of America, and to all of the terms and conditions of this Agreement.

Licensee shall maintain the following copyright and permission  notices on STLport sources and its documentation unchanged :
Copyright 1999,2000 Boris Fomitchev

------

Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.