# Assignment_02
####Team members: Christopher Murray

#Prerequisites

- GNU Autotools
- OpenGL 3.0
- C++11 compiler
- Boost
- GLEW
- SDL2
- GLM
- GL
- SOIL

On Fedora 20 or later the libraries can all be installed by using the command (as root):

> $ yum install boost-* glew-devel SDL2_* glm-devel SOIL-devel SOIL.x86_64 GL

#Prerequisites for build commands
To be able to use the 'autoreconf -i' command you must have GNU autotools installed.
To install use the command (as root):

> $ yum install autoconf automake

Libtool will also need to be installed:

> $ yum install libtool

To install the gcc C++11 compiler support use the command (as root):

> $ yum install gcc-c++.x86_64

#Building
After cloning the source code, change to the directory where the source code is and enter the following commands:

> $ autoreconf -i
> $ ./configure
> $ make

#Running
To build the program enter the command:

> $ ./assignment


####Aim
The aim of this project is to learn how to apply textures and lighting to a 3D scene. This will consist of rendering a 
3D scene of the Earth rotating realistically with the Moon in orbit around it. At the very least the Earth and Moon will 
be textured and have lighting. The scene will include a camera for the user to navigate around the scene.

####Objectives

- Lighting
  <br /> - Use of ambient and directional lighting
- Apply a texture to both the Earth and the Moon
- Deform the sphere geometry to give more detail, such as mountains.
- Collision detection
  <br /> - Camera cannot pass through the objects
- Camera
  <br />- The camera will be controlled by the WASD keys with the ability to move forward, backwards, strafe left and strafe 
					right.
  <br />- The camera can be zoomed by scrolling the mouse wheel.
  <br />- Extension: Camera mimics a spacecraft movement.

####Timing and milestones (approximated)

-	Draw window (3 hours)
-	Create automated (6 hours)
-	Draw a simple shape in the scene (square) (2 hours)
-	**Camera (2 weeks)**
  <br /> - MVP
  	<br /> - Create vertex shader (12  hours)
  	<br /> - Create projection/ perspective matrix (6 hours)
  	<br /> - Create model matrix (2 hours)
  	<br /> - Create view matrix (5 hours)
	<br /> - Implement basic key event control (1 day)
	<br /> - Rotate camera using mouse events (3 days)
- Create sphere geometry (2 days)
-	**Lighting (2 weeks)**
	<br /> - Ambient lighting (6 days)
	<br /> - Directional lighting (6 days)
-	**Collision detection (2 weeks)**
-	Rotate the light source around the Earth and rotate the Earth on its axis. (2 days)
-	Create Moon geometry (2 hours)
-	**Texture both Earth and Moon geometries (1 weeks)**
	<br /> - Generate noise to displace the geometry’s surface (apply to at least the Moon) (Extension: If time permits)

####Project Plan
The program will be created using C++ as the primary language and the IDE used will be Eclipse.
<br />
<br />
I plan to create the sphere by using polygon subdivision as is illustrated here [1]. I will use this method as opposed to just
using gluSphere() because it will allow me to have more control over the sphere for instance the closer the camera gets the
more subdivision is applied for greater detail, I will also learn a lot more using this method. 
<br />
<br />
The lighting shall be a combination of ambient and directional lighting to mimic the sun. A possible solution for the 
collision detection is to use axis aligned bounding boxes for simple collision detection. This likely won’t be accurate enough 
collision detection for a sphere, so another method will be researched and implemented to obtain the higher marks.
<br />
<br />
The textures will likely just be single images, a possible solution may be mipmaps or using GLFW. A noise map (similar to this
method [2]) or height map will be used to determine where the sphere geometry is deformed to create the Earth’s detail (NASA 
has flat maps of the Earth, separate clouds, and height map which can be used as textures). 

####Proposed technology
IDE: Eclipse
<br />Source control: GitHub
<br />Primary Language: C++
<br />
<br />OpenGL 
<br />GLSL – shaders
<br />GLM
<br />GLFW - texturing
<br />GLEW

####Marking Scheme
Quality of code – 30%
<br />Lighting – 30%
<br />Texturing – 30%
<br />Collision Detection – 10%

[1] http://stackoverflow.com/questions/7687148/drawing-sphere-in-opengl-without-using-glusphere/ <br />
[2] http://www.gamedev.net/topic/637715-terrain-generation/page-2/
