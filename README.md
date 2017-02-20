## Hangman

This is a command line interface hangman game, implemented in C, with basic graphics functionality.  

![alt text](https://github.com/robertnowell/3d_wireframe/blob/master/images/giphy.gif "42fdf")

## Implementation

This program does the following:  

1. Makes an http request from the supplied dictionary URL and parses returned data into an array of strings.  
2. Queries user as to whether they want to play hangman.  
3. Sets up game by picking a random word, initializing a t_game struct used to hold relevant variables, and initiating two loops, one which handles user guesses within a game, and one which enables the user to play multiple games within the same session.  
4. Throughout the game, system() is used at certain points to execute shell scripts which run executable "wireframe" that allow for graphical functionality like the following:  
//image here

### Details and Code

<img src="https://github.com/robertnowell/hangman/blob/master/images/main.png" 
alt="main" width="400" height="400" border="10"/>

Within the main function, at the bottom of src/hangman.c, the first operation is to declare a struct of type t_game. t_game is declared in includes/hangman.h and looks like this:

<img src="https://github.com/robertnowell/hangman/blob/master/images/t_game.png" 
alt="t_view" width="300" height="300" border="10"/>  

a struct of type t_game with name 'game' holds all of the variables that the game needs to run.  

game->words is assigned to the result of a call to curl_and_split(), which is responsible for making an http request and handling its output. This function and its associated functions are located in src/http_request.c. Curl_and_split handles two operations: making a request to the specified (hard coded) URL, and splitting the received data into an array of strings, using a newline as a delimiter. In the case of this URL, using this delimiter means that each string in the array will hold one word.  
  
To make the http request, the c curl library is relied upon. With this library, an http request is completed in about six function calls. These functions set up the operations to be performed when the call is made and then execute the call. Normally, output is directed to stdout. So, to save the output, write_func() is defined within src/http_request to redirect the retrieved data into a string. Even using a library, this is a relatively complicated process for retrieving data from a website relative to other programming languages. Once the data is retrieved and split into separate strings, the array of strings, is returned. There are approximately 160000 words stored in the website at the time of writing.  

Returning to the main function, ask() is called which queries the user if they would like to play the game. ask() is the first appearance in the program of a system() call, and it runs a shell script that starts the wireframe executable which provides graphics functionality for the game. The wireframe is a program I created with its own readme: https://github.com/robertnowell/3d_wireframe  
The shell script and wireframe functionality of the game is discussed further, below. Other than this, ask() is as simple as a few if statements, and returns 1 for yes (the user's response started with a 'y') or 0 for no (any other input). If the answer is no, allocated memory is freed and the program exits. Otherwise, main makes a call to game_loop(). Game loop is relatively important:  
<img src="https://github.com/robertnowell/hangman/blob/master/images/game_loop.png"  
alt="t_view" width="550" height="600" border="10"/>  

This function starts a loop which will be active for the majority of the remainder of the time the program is open. That is, game_loop() runs as long as the user is playing a game or being asked if they would like to play again. This loop enables users to play more than one game. Each iteration through the loop can be thought of as a full setup and playthrough of a game of hangman. For each playthrough, the first operation is a call to init_game_vars() which chooses a random word for the game and initializes the variables of the t_game struct based on this word. Next is a call to game_engine():  
<img src="https://github.com/robertnowell/hangman/blob/master/images/game_engine.png"  
alt="t_view" width="600" height="450" border="10"/>  
game_engine() is responsible for gameplay within a particular playthrough. It handles all in-game logic. That is, it handles all guesses and responses to guesses, and sends calls to incorrect_guesses() when an incorrect guess is made in order to make system calls to run a different wireframe image, corresponding to the number of guesses remaining in the game. The wireframe and shell script functionality is described below. game_engine() will exit its loop either when all characters of the word have been guessed or when no more guesses remain (that is, the number of incorrect guesses is 6). game_engine() returns a boolean value for whether the word was successfully guessed or not.  

Returning to game_loop, the program outputs either a "game over" or "congratulations" message based on the return value from game_engine(), and it frees the memory from struct game that was only important for that playthrough (essentially all variables are freed except for the array of strings names "words". This could be made more efficieent by only clearing some variables, rather than freeing the memory associated with them.) The program then asks the user if they would like to play again, and, if they said yes, continues to the next iteration or, otherwise, returns to main to free memory and exit.  

### Wireframe and Shellscripts

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
