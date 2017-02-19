/*this file contains functions with simple logic and names that are meant to make their utility clear.*/

#include "hangman.h"

/*
  free_game_memory:
    -frees memory allocated for each game instance. 
*/
void free_game_memory(t_game *game){
  free(game->output_string);
  for(int i = 0; i < 100; i++)
    free((game->prev_guesses)[i]);
  free(game->prev_guesses);
}

/* clears screen by printing new lines*/
int clear_screen()
{  
  for (int i = 0; i < SCREEN_HEIGHT; i++ )
    ft_putchar ('\n');
  return 0;
}

/*returns length a null terminated array of strings*/
int ft_array_len(char **array){
  int count = 0;
  int i = 0;
  while (array[i][0]){
    count++;
    i++;
  }
  return count;
}

/*prints to stdout the game interface before each guess*/
void ft_output(t_game *game) {
  printf(CYAN "%s\nGuesses Remaining: %d\nPrevious Guesses: ", game->output_string, 6 - game->num_incorrect);
  for (int i = 0; i < ft_array_len(game->prev_guesses); i++){
    printf(CYAN "%s, " RESET, (game->prev_guesses)[i]);
  }
  printf("\n");
}

/*updates output string based on most recent guess*/
void update_output_string(t_game *game, char guess){
  for (int i = 0; i < ft_strlen(game->output_string); i++){
    if (game->word[i] == guess)
      (game->output_string)[i] = guess;
  }
}

/*prints to stdout a null terminated array of strings*/
void print_array(char **array){
  for (int i = 0; i < ft_array_len(array); i++){
    ft_putendl(array[i]);
  }
}

/*appends most recent guess to prev_guesses array*/
void ft_append_guess(t_game *game, char guess){
  for (int i = 0; i < 100; i++)
  {
    if ((game->prev_guesses)[i][0] == 0){
      game->prev_guesses[i][0] = guess;
      return;
    }
  }
}

/*checks to see if a letter has been guessed before*/
bool find_in_prev_guess(t_game *game, char guess){
  for (int i = 0; i < ft_array_len(game->prev_guesses); i++){
    if ((game->prev_guesses)[i][0] == guess){
      return true;
    }
  }
  return false;
}

