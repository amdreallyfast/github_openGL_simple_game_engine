These projects were created in Visual Studio 2013.  There is a “middleware” 
folder that contains the third-party (Qt, glew, and gtest) functionality that 
my program needs to compile.  I couldn’t get around needing the header, source, 
.lib, and .dll files, so the middleware fold got a little bloated.  

To build, open the .sln file in the "my project files"/SandboxGame subfolder.  
This is primary solution.

There is one .dll project (Engine) and two executable projects (EngineTest and 
SandboxGame).  The startup project in the files that I am sending you is the 
EngineTester.  Build that and run it to see my tests all pass (little to see 
except that I wrote organized unit tests).

Build and run the SandboxGame to see my simple 2D "game".  It consists of a 
triangle "ship" that you can move around a diamond-shaped area with the left, 
right, and up arrow keys (down does nothing).  Use those keys to increase 
angular and linear acceleration in a particular direction.  I query the CPU 
counter (in my "game clock" class) to determine the fraction of a second that 
passed since the previous frame started to render, and I use this time to 
determine where the ship's rotation and location should be on the current 
frame.  I have implemented basic boundary collision and bouncing use dot 
product calculations and the center of the ship.
 
If it doesn’t build or display, please let me know the error and I’ll try to 
fix it.
 

John Cox