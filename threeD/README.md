## 3d Wireframe

This is a 3d wireframe renderer that allows for rotation in 3d space. Perspective projection is used to add realism. The provided tools for this project were a function to put a pixel on a screen and a key hook function for user input.  
  
![alt text](https://github.com/robertnowell/3d_wireframe/blob/master/images/giphy.gif "42fdf")

## Implementation

This program does the following:  

1. Reads input from a file formatted like this:  
<img src="https://github.com/robertnowell/3d_wireframe/blob/master/images/42.png" 
alt="fdf" width="300" height="140" border="10"/>

2. Creates the "mesh" (a two dimensional array) to represent the contents of the file. Each element of this mesh is a three dimensional vector. Each vector represents a point in three dimensional space.
3. Creates the "points" (also a two dimensional array). Each element of the points array is a two dimensional vector, which is a perspective projection of the corresponding three dimensional vector from the mesh. This is where three dimensional space is projected into two dimensional space.  
4. Draws each element of the initial (i.e. prior to any rotation) points array on the screen, and also draws horizontal and vertical lines between the points.  
5. Handles user input by listening for key hooks (via keyboard_event()) that signal requests for the wireframe to rotate on a particular access.
6. In response to each user input, copies the "mesh" and alters each vector based on the x, y, and z rotation angles input by the user and then projects these points into a new "points" array.
7. Outputs the image to the screen and then calls to the keyboard event function again.

The program operates in an infinite loop until an escape key (ESC) is received.  

### Details and Code

<img src="https://github.com/robertnowell/3d_wireframe/blob/master/images/main2.png" 
alt="main" width="400" height="400" border="10"/>

In lines 91-111 of the main function error checks the file and file descriptor and counts the file's rows and columns, using lseek() to reset the file offset.  
  
Next initialize_view() is called to initialize the struct t_view which is relied upon in this program. t_view is defined in includes/wireframe.h and looks like this:  
<img src="https://github.com/robertnowell/3d_wireframe/blob/master/images/t_view.png" 
alt="t_view" width="300" height="300" border="10"/>  
mlx and win are variables which allow for the presentation of visual output to the user. Proportionality is the degree of perspective projection applied (its default value is somewhat arbitrary). x_angle, y_angle, and z_angle store the value of the rotation (in radians) for each axis and are initialized to zero in initialize_view() in main.c:  
<img src="https://github.com/robertnowell/3d_wireframe/blob/master/images/initialize_view.png" 
alt="initialize_view" width="550" height="300" border="10"/>  
Mesh and points are created here, making calls to functions in create.c. SIZE is the size of the window created and is a macro defined in wireframe.h. It can be changed there and is set to 1000 by default.  
Once t_view is initialized, the main function makes a call to draw_points(), which exists in draw.c, and finally the main function calls keyboard_event_function via mlx_hook. mlx_hook was a provided function for this project, as was mlx_loop.   
<img src="https://github.com/robertnowell/3d_wireframe/blob/master/images/keyboard_event.png" 
alt="keyboard_event" width="350" height="450" border="10"/>  
In keyboard_event() a switch adds or subtracts pi/96 (an arbitrary quantity of radians) from the x, y, or z angle (or exits (case 53), or resets the window (case 15), then clears the screen. Each case is a key on the keyboard. The particular mapping is explained in installation and usage, below. Next, keyboard_event() makes a call to create_image():  
<img src="https://github.com/robertnowell/3d_wireframe/blob/master/images/create_image.png" 
alt="keyboard_event" width="400" height="200" border="10"/>  
create image makes a copy of the mesh, changes each constituent vector of this mesh copy based on the user-input rotation angles of the wireframe on the x, y, and z axes. These rotation functions are in rotate.c. This is the x axis rotation function:  
<img src="https://github.com/robertnowell/3d_wireframe/blob/master/images/rot_x.png" 
alt="keyboard_event" width="400" height="200" border="10"/>  
X, Y, and Z are macros for accessing elements from the mesh, and these macros are defined in wireframe.h.  
After rotating the mesh copy, a new "points" array is created (a two-d perspective projection representation of the three-d mesh), this points array is drawn on the screen, and then the program waits for user input for more rotation, an image reset, or an escape command.  

## Installation and Usage

First clone the repo and then generate the executable:
```
git clone https://github.com/robertnowell/3d_wireframe.git
cd 3d_wireframe
make re
```
A successful make will output a message that confirms that an executable called 'wireframe' has been created. In test_maps, there are a number of files that can be used to display the functionality of this program. Type a command like the following from the root of the cloned repository to start the program:
```
./wireframe test_maps/mars.fdf
```
A window should appear with a wireframe, and in the above case the map is a topographical representation of a section of the planet mars. The image can be rotated from the window with the Q, W, E, A, S, and D keys. Q and E rotate along the z axis, W and S rotate along the x axis, and A and D rotate along the y axis. The R key will reset the image, and the escape (ESC) key will terminate the execution of the program. A variety of color macros can be found in wireframe.h. To change the color of the wireframe drawing, change the COLOR macro, save the file, "make re" from the root directory, and run the program again.  
  
![alt text](https://github.com/robertnowell/3d_wireframe/blob/master/images/giphy%20(1).gif)
## Author

Robert Nowell

## Acknowledgement

This project was completed at School 42 in Fremont, California.
