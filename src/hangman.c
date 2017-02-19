/*dependencies
  libcurl: install libcurl from https://curl.haxx.se/download.html
   in untarred directory, run ./configure --prefix=/path/to/curl/tree
						then run: make
						then: make install
  run curl-config --cflags
  run curl-config --libs
  compile with "gcc -o executable_name hangman.c -L ./ -l ft" plus the output
          of the call to curl-config --cflags and curl-config --libs.
   for example, my final command is 
   gcc -o test -L ./ -lft -L/usr/local/lib -lcurl -lldap -lz -I/usr/local/include hangman.c
   from https://curl.haxx.se/docs/install.html
   programming tutorial: https://curl.haxx.se/libcurl/c/libcurl-tutorial.html
  think about implementing binary search for isolating a word?
*/

/*possible extensions
  -prepare to discuss:
      -how to go about -sending different kinds of http requests
                       -incorporating a high score leaderboard
                       -create a hint function (and have a set quantity of allowed hints)
                       -handle strings as guesses
                       -how would I implement this in oop?
                          -game object with methods
                       -using something better than system() to call shell scripts

  any guess longer than malloced size of guess in play game will cause a heap buffer overflow
  same thing in answer and prev_guesses
  
  make it so that the wireframe window doesn't close and open each time. This can be done by using script to input into stdin which file to load.
  -then loading it from within wireframe program.
  -add text to wireframe images.
  -think about prerotating wireframe images.

  -make code pretty
    -separate into files with sensible function organization
    -function names, especially the gameplay functions
    -variable names
    -

  -make a readme
    -be able to explain every function
    -create guide to library functions that I wrote myself
      -ft_strnew(), ft_strdup(), ft_strchr(), 
  /did have a segfault today...no idea why. on second guess.

*/

#include "hangman.h"


/*
  incorrect_guess:
    -is called when an incorrect guess is made
    -updates relevant variables
    -calls to wireframe generator to display new bodypart
    -see README for more information about 
        shellscript management of wireframe generator
*/
void incorrect_guess(t_game *game, char guess){
    ft_putendl(RED "incorrect guess\n\n\n" RESET);
    game->num_incorrect++;
    ft_append_guess(game, guess);
    switch(game->num_incorrect){
      case 1:
        system("sh ./shells/hangman_wireframe1.sh");
        break;
      case 2:
        system("sh ./shells/hangman_wireframe2.sh");
        break;
      case 3:
        system("sh ./shells/hangman_wireframe3.sh");
        break;
      case 4:
        system("sh ./shells/hangman_wireframe4.sh");
        break;
      case 5:
        system("sh ./shells/hangman_wireframe5.sh");
        break;
      case 6:
        system("sh ./shells/hangman_wireframe6.sh");
        break;
      default:
        return;
    }
}

/*
  game_engine:
      -this function handles the central mechanics of the game, including:
      -calling ft_output() to print user interface
      -requesting and receiving user guesses
      -determining and outputting whether a guess is correct
      -updating user interface after each guess
      -calling to incorrect_guess() when appropriate to update
          wireframe graphic with a new bodypart
*/
bool game_engine(t_game *game){
  char *guess = ft_strnew(100);
  bool complete = false;
  while (!complete && game->num_incorrect < 6){
    ft_output(game);
    ft_putendl(INTENSE CYAN "please make a guess:" RESET);
    scanf("%s", guess);
    clear_screen();
    if (ft_strlen(guess) != 1){
      ft_putendl(MAGENTA "please input a single character to guess\n\n\n" RESET);
      continue;
    }
    if (find_in_prev_guess(game, *guess)) {
      ft_putstr(MAGENTA "this letter has already been guessed\n\n\n\n" RESET);
    }
    else if (ft_strchr(game->word, *guess))
    {
      ft_putendl(GREEN "good guess!\n\n\n" RESET);
      update_output_string(game, *guess);
      ft_append_guess(game, *guess);
    } else {
      incorrect_guess(game, *guess);
    }
    if (!ft_strchr(game->output_string, '_'))
      complete = true;
  }
  free(guess);
  return complete;
}

/*
  init_game_vars
    -determines random word for the game.
    -initializes struct game by allocating memory for relevant fields.
*/
void init_game_vars(t_game *game){
  int r;

  srand(time(NULL));
  r = rand() % 162412;
  game->word = game->words[r];
  printf("word : (%s)\n", game->word);
  game->output_string = ft_strnew(ft_strlen(game->word)+1);
  ft_memset(game->output_string, '_', ft_strlen(game->word));
  if (!(game->prev_guesses = (char **)malloc(sizeof(char *) * 100)))
    return;
  for(int i = 0; i < 100; i++) {
    (game->prev_guesses)[i] = ft_strnew(100);
    ft_memset((game->prev_guesses)[i], 0, 100);
  }
  game->num_incorrect = 0;
}

/*
    game_loop:
        -loop allows users to play game more than once
        -calls to init_game_vars() to intialize game struct
        -handles gamplay and game result
        -frees and allocates memory each playthrough
        -determines if user wants to play again
*/
void game_loop(t_game *game)
{
  bool complete;
  char *again;

  while (1) {
      init_game_vars(game);
      complete = game_engine(game);
      if (complete){
        ft_putstr(GREEN "congratulations! the word was " INTENSE);
        ft_putendl(game->word);
        ft_putstr("\n\n" RESET);
      }
      else {
        clear_screen();
        ft_putstr(RED "GAME OVER\n\nNo more guesses remain.\n\n\n" RESET \
                  GREEN "Better luck next time! The word was ");
        ft_putendl(game->word);
        ft_putstr("\n" RESET);
      }
      free_game_memory(game);
      again = ft_strnew(100);
      ft_putendl("Would you like to play again? (y or n)");
      scanf("%s", again);
      if (again[0] == 'y'){
        clear_screen();
        system("sh ./shells/clear.sh");
        free(again);
      }
      else{
        clear_screen();
        system("sh ./shells/close.sh");
        ft_putstr("Okay. Have a nice day!\n");
        free(again); 
        return;
      }    
  }

}

/*
  ask() determines whether or not the play wants to play the game
  returns 1 for yes, and 0 for no.
  -if yes, makes first system call to run a hangman_wireframe shell script
  the hangman_wireframe shell scripts cause a wireframe program to run 
*/
int ask(){
  char *answer;

  answer = ft_strnew(100);
  ft_memset(answer, 0, 100);
  clear_screen();
  printf(GREEN "How about a game of hangman? (y or n)" OFFSET RESET);
  if (scanf("%s", answer) < 0){
    ft_puterr("error reading user input");
    free(answer);
    return (0);
  }
  if (answer[0] == 'y') {
    clear_screen();
    ft_putendl(GREEN "Super. Let's play!\n\n" RESET);
    system("sh ./shells/hangman_wireframe0.sh");
    free(answer);
    return (1);
  }
  else {
    clear_screen();
    ft_putstr("Okay. Have a nice day!\n");
    free(answer);
    return (0);
  }
}

/*main:   declare and allocate memory for pointer to t_game struct
          call to curl_and_split() to retrieve and split word list into a two-d array
          call to ask() to see if user wants to play hangman
          if so, make call to game_loop()
          If player said no, or once game_loop() has returned,
            free memory and exit.  
*/
int main(void)
{
  t_game *game;

  if (!(game = (t_game *)malloc(sizeof(t_game))))
    return -1;
  game->words = curl_and_split();
  if (ask())
    game_loop(game);

  int len = ft_array_len(game->words);
  for (int i = 0; i < len; i++)
    free((game->words)[i]);
  free(game->words);
  free(game);
  return 0;
}