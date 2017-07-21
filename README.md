## Hangman 

This is a command line interface hangman game, implemented in C, with basic graphics functionality. Since it relies on the directory from which it was executed for graphics files, it works best when opened from the terminal, rather than being opened from a finder window. With a wireframe window open, the image can be rotated using the Q, W, E, A, S, and D keys.   
    
  
![alt text](https://github.com/robertnowell/hangman/blob/master/images/hangman.gif "42fdf")
     
## Motivation     
   
The prompt for this programming challenge was the following: implement a hangman game in a language of your choice, using libraries of your choice, and the only requirement was to make a single http request to retrieve the word list. I decided that implementing the program in C would be an interesting challenge. Two fun things I learned through this implementation were how to make http requests in C and how to integrate multiple running processes (which was required to have both command line gameplay and a 3-d graphics component to the game. Also, a good majority of the functions used were written by myself. Only scanf, printf, malloc, the curl functions, and a few others were built in functions that I used. Otherwise, all functions were written as a part of this project, another project which involved a partial recoding of the c standard library, and creating the referenced 3d wireframe project. The project ended up being more challenging than I anticipated, and I learned quite a bit through the experience. 
   
## Implementation

This program does the following:  

1. Makes an http request from the supplied dictionary URL and parses returned data into an array of strings.  
2. Queries user as to whether they want to play hangman.  
3. Sets up game by picking a random word, initializing a t_game struct used to hold relevant variables, and initiating two loops, one which handles user guesses within a game, and one which enables the user to play multiple games within the same session.  
4. Throughout the game, system() is used at certain points to execute shell scripts which run executable "wireframe" that allow for graphical functionality like the image at the top of this README.

### Details and Code
 
<img src="https://github.com/robertnowell/hangman/blob/master/images/main.png" 
alt="main" border="10"/>

Within the main function, at the bottom of src/hangman.c, the first operation is to declare a struct of type t_game. t_game is defined in includes/hangman.h and looks like this:

<img src="https://github.com/robertnowell/hangman/blob/master/images/t_game.png" 
alt="t_game" border="10"/>  

a struct of type t_game with name 'game' holds all of the variables that the game needs to run.  

game->words is assigned to the result of a call to curl_and_split(), which is responsible for making an http request and handling its output. This function and its associated functions are located in src/http_request.c. Curl_and_split handles two operations: making a request to the specified (hard coded) URL, and splitting the received data into an array of strings, using a newline as a delimiter. In the case of this URL, using this delimiter means that each string in the array will hold one word.  
  
To make the http request, the c curl library is relied upon. With this library, an http request is completed in about six function calls. These functions set up the operations to be performed when the call is made and then execute the call. Normally, output is directed to stdout. So, to save the output, write_func() is defined within src/http_request to redirect the retrieved data into a string. Even using a library, this is a relatively complicated process for retrieving data from a website relative to other programming languages. Once the data is retrieved and split into separate strings, the array of strings, is returned. There are approximately 160000 words stored in the website at the time of writing.  

Returning to the main function, ask() is called which queries the user if they would like to play the game. ask() is the first appearance in the program of a system() call, and it runs a shell script that starts the wireframe executable which provides graphics functionality for the game. The wireframe is a program I created with its own readme: https://github.com/robertnowell/3d_wireframe  
The shell script and wireframe functionality of the game is discussed further, below. Other than this, ask() is as simple as a few if statements, and returns 1 for yes (the user's response started with a 'y') or 0 for no (any other input). If the answer is no, allocated memory is freed and the program exits. Otherwise, main makes a call to game_loop(). Game loop is relatively important:  
<img src="https://github.com/robertnowell/hangman/blob/master/images/game_loop.png"  
alt="game loop" width="550" height="600" border="10"/>  

This function starts a loop which will be active for the majority of the remainder of the time the program is open. That is, game_loop() runs as long as the user is playing a game or being asked if they would like to play again. This loop enables users to play more than one game. Each iteration through the loop can be thought of as a full setup and playthrough of a game of hangman. For each playthrough, the first operation is a call to init_game_vars() which chooses a random word for the game and initializes the variables of the t_game struct based on this word. Next is a call to game_engine():  
<img src="https://github.com/robertnowell/hangman/blob/master/images/game_engine.png"  
alt="game engine" width="600" height="450" border="10"/>  
game_engine() is responsible for gameplay within a particular playthrough. It handles all in-game logic. That is, it handles all guesses and responses to guesses, and sends calls to incorrect_guesses() when an incorrect guess is made in order to make system calls to run a different wireframe image, corresponding to the number of guesses remaining in the game. The wireframe and shell script functionality is described below. game_engine() will exit its loop either when all characters of the word have been guessed or when no more guesses remain (that is, the number of incorrect guesses is 6). game_engine() returns a boolean value for whether the word was successfully guessed or not.  

Returning to game_loop, the program outputs either a "game over" or "congratulations" message based on the return value from game_engine(), and it frees the memory from struct game that was only important for that playthrough (essentially all variables are freed except for the array of strings names "words". This could be made more efficieent by only clearing some variables, rather than freeing the memory associated with them.) The program then asks the user if they would like to play again, and, if they said yes, continues to the next iteration or, otherwise, returns to main to free memory and exit.  

### Wireframe and Shellscripts

This program graphically represents the hangman figure by simultaneously running a 3-d rendering program called wireframe, which I completed at school 42. The wireframe program is called by running a shell script which calls an apple script which interacts with the terminal application to open and run the wireframe app, and to change the displayed file based on in-game events, such as an incorrect guess. Documentation for the wireframe can be found here: https://github.com/robertnowell/3d_wireframe

These are seven images run during the game. The number at the top of each wirefream represents the remaining number of guesses:  
<img src="https://github.com/robertnowell/hangman/blob/master/images/hang0.png" 
alt="" width="400" height="400" border="10"/>
<img src="https://github.com/robertnowell/hangman/blob/master/images/hang1.png" 
alt="" width="400" height="400" border="10"/>
<img src="https://github.com/robertnowell/hangman/blob/master/images/hang2.png" 
alt="" width="400" height="400" border="10"/>
<img src="https://github.com/robertnowell/hangman/blob/master/images/hang3.png" 
alt="" width="400" height="400" border="10"/>
<img src="https://github.com/robertnowell/hangman/blob/master/images/hang4.png" 
alt="" width="400" height="400" border="10"/>
<img src="https://github.com/robertnowell/hangman/blob/master/images/hang5.png" 
alt="" width="400" height="400" border="10"/>
<img src="https://github.com/robertnowell/hangman/blob/master/images/hang6.png" 
alt="" width="400" height="400" border="10"/>

## Installation and Usage

First clone the repo. Then, from within the repo, run
```
./hangman
```
in the terminal application on a mac os computer, preferably using bash.  
  
When a wireframe window opens, the image can be rotated using the Q, W, E, A, S, and D keys.

### Limitations

The system calls to shell scripts which run apple scripts on the terminal application in order to call the wireframe program is convoluted and places limitations on the game. For all intents and purposes, the game will only run in the terminal application on a mac os machine. And in fact, its functionality may differ between zsh and bash shells, and furthermore its reliance on the libcurl c library, the installation for which library is not exactly simple, makes it challenging to recompile the executable file. So, it's not exactly universal. It's possible this could be fixed with significant time investment, but may also just be a part of the challenge of working with relatively old c libraries to create a game with a 3-d graphics component.


## Author

Robert Nowell
