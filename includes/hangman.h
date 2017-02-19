#ifndef HANGMAN_H
# define HANGMAN_H

#include  <curl/curl.h>
#include "libft.h"

# define SCREEN_HEIGHT 500
# define OFFSET "\n\n\n\n\n\n\n\n"
# define INTENSE "\x1b[1m"

# define RED      "\x1b[31m"
# define GREEN    "\x1b[32m"
# define YELLOW   "\x1b[33m"
# define BLUE     "\x1b[34m"
# define MAGENTA  "\x1b[35m"
# define CYAN     "\x1b[36m"
# define RESET    "\x1b[0m"

typedef int bool;
# define true 1
# define false 0

struct string {
  char *data;
  size_t len;
};

typedef struct  s_game {
  char  *word;
  char  *output_string;
  char  **prev_guesses;
  char  **words;
  int   num_incorrect;
}               t_game;

// http_request.c:
void init_string(struct string *s);
size_t write_func(void *data, size_t size, size_t nmemb, struct string *s);
char **ft_strsplt(char *data);
char **curl_and_split(void);

//utilities.c
void free_game_memory(t_game *game);
int clear_screen();
int ft_array_len(char **array);
void ft_output(t_game *game) ;
void update_output_string(t_game *game, char guess);
void print_array(char **array);
void ft_append_guess(t_game *game, char guess);
bool find_in_prev_guess(t_game *game, char guess);


#endif
