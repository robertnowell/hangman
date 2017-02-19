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

#include "libft.h"
#include <curl/curl.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false 0

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

void init_string(struct string *s) {
  s->len = 0;
  s->data = malloc(s->len+1);
  if (s->data == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->data[0] = '\0';
}

size_t writefunc(void *data, size_t size, size_t nmemb, struct string *s)
{
  size_t new_len = s->len + size*nmemb;
  s->data = realloc(s->data, new_len+1);
  if (s->data == NULL) {
    ft_puterr("realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->data+s->len, data, size*nmemb);
  s->data[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}

char **ft_strsplt(char *data){
	int count = 0;
	int i = 0;
	char *current;
	char **res;
	int len = ft_strlen(data);

	for (i = 0; i < len; i++) {
		if (data[i] == '\n')
			count++;
	}
	if (!(res = (char **)malloc(sizeof(char *) * (count + 2)))){
		return (NULL);
	}
	i = 0;
  // printf("current:%p\nres:%p\n", current, res);
	while ((current = strsep(&data, "\n")))
		res[i++] = ft_strdup(current);
	res[i] = "\0";
	return res;
}

#define SCREEN_HEIGHT 500

int clear_screen()
{
  int i;
  
  for ( i = 0; i < SCREEN_HEIGHT; i++ )
    putchar ( '\n' );
    
  return 0;
}

int ft_array_len(char **array){
  int count = 0;
  int i = 0;
  while (array[i][0]){
    count++;
    i++;
  }
  return count;
}



void ft_output(t_game *game) {
  printf("%s\nGuesses Remaining: %d\nPrevious Guesses: ", game->output_string, 6 - game->num_incorrect);
  for (int i = 0; i < ft_array_len(game->prev_guesses); i++){
    printf("%s, ", (game->prev_guesses)[i]);
  }
  printf("\n");
}



// void clear_screen()
// {
//   const char* CLEAR_SCREE_ANSI = "\e[1;1H\e[2J";
//   write(1 , CLEAR_SCREE_ANSI,12);
// }

void update_string(t_game *game, char guess){
  for (int i = 0; i < ft_strlen(game->output_string); i++){
    if (game->word[i] == guess)
      (game->output_string)[i] = guess;
  }
}

// int ft_find_in_string(char const *s, int c)
// {
//   char  *str;
//   size_t  i;

//   str = (char *)s;
//   i = ft_strlen(s) - 1;
//   if (str[i + 1] == c)
//     return (i + 1);
//   while (str[i])
//   {
//     if (str[i] == c)
//       return (i);
//     i--;
//   }
//   return (-1);
// }

/*possible extensions
  any guess longer than malloced size of guess in play game will cause a heap buffer overflow
  same thing in answer and prev_guesses
  use fdf animate result of guesses.
*/
void print_words(char **words){
  for (int i = 0; i < ft_array_len(words); i++){
    ft_putendl(words[i]);
  }
}

void ft_append_guess(t_game *game, char guess){
  for (int i = 0; i < ft_array_len(game->prev_guesses); i++)
  {
    if ((game->prev_guesses)[i][0] == 0){
      game->prev_guesses[i][0] = guess;
      return;
    }
  }
}

bool find_in_prev_guess(t_game *game, char guess){
  for (int i = 0; i < ft_array_len(game->prev_guesses); i++){
    if ((game->prev_guesses)[i][0] == guess){
      return true;
    }
  }
  return false;
}

int play_game(t_game *game)
{
  bool complete = false;
  char *guess;
  char *again;

  guess = ft_strnew(100);
  while (!complete && game->num_incorrect < 6){
    ft_output(game);
    ft_putendl("please make a guess");
    scanf("%s", guess);
    // printf("%s\n", guess);
    clear_screen();
    if (ft_strlen(guess) != 1){
      ft_putendl("please input a single character to guess");
      continue;
    }
    printf("found char (%c) in word (%s)? %s\n", *guess, game->word, ft_strchr(game->word, *guess));
    if (find_in_prev_guess(game, *guess)) {
      ft_putstr("this letter has already been guessed\n");
    }
    else if (ft_strchr(game->word, *guess))
    {
      ft_putendl("good guess!");
      update_string(game, *guess);
      ft_append_guess(game, *guess);
    } else {
      ft_putendl("incorrect guess");
      game->num_incorrect++;
      ft_append_guess(game, *guess);
    }
    if (!ft_strchr(game->output_string, '_'))
      complete = true;
  }
  if (complete){
    ft_putstr("congratulations! the word was ");
    ft_putendl(game->word);
  }
  else {
    clear_screen();
    ft_putstr("GAME OVER\n\nNo more guesses remain. Better luck next time! The word was ");
    ft_putendl(game->word);
  }
  free(guess);
  again = ft_strnew(100);
  ft_putendl("Would you like to play again? (y or n)");
  scanf("%s", again);
  if (again[0] == 'y'){
    free(again); 
    return 1;
  }
  else{
    free(again); 
    return 0;
  }
}

int pop_the_question(){
  char *answer;

  answer = ft_strnew(100);
  ft_memset(answer, 0, 100);
  clear_screen();
  printf("Hello, would you like to play a game?\n");
  if (scanf("%s", answer) < 0){
    ft_puterr("error reading user input");
    free(answer);
    return (0);
  }
  if (ft_strcmp(answer, "no") == 0 || ft_strcmp(answer, "n") == 0){
    free(answer);
    return (0);
  }
  clear_screen();
  if (ft_strcmp(answer, "yes") != 0)
    ft_putendl("Let's pretend you said 'yes'");
  free(answer);
  return (1);
}

void init_game_vars(int r, t_game *game){
  game->word = game->words[r];
  printf("word : (%s)\n", game->word);

  game->output_string = ft_strnew(ft_strlen(game->word)+1);
  ft_memset(game->output_string, '_', ft_strlen(game->word));
  printf("output_string: (%s)\n", game->output_string);

  if (!(game->prev_guesses = (char **)malloc(sizeof(char *) * 100)))
    return;
  for(int i = 0; i < 100; i++) {
    (game->prev_guesses)[i] = ft_strnew(100);
    ft_memset((game->prev_guesses)[i], 0, 100);
  }
  game->num_incorrect = 0;
}

void free_game_memory(t_game *game){
  // free(game->words);
  free(game->output_string);
  for(int i = 0; i < 100; i++)
    free((game->prev_guesses)[i]);
  free(game->prev_guesses);
}

void setup_game(t_game *game)
{
  int r;
  int again = 1;

  srand(time(NULL));
  r = rand() % 162412;
  printf("number: (%d)\n", r);
  // printf("word len: %zu\n, word pointer: %p\nwords pointer: \
      %p\nwords[r] pointer: %p\nwords[r-1] pointer: %p\n", \
      ft_strlen((game->words)[r]), game->word, game->words, \
      (game->words)[r], (game->words)[r-1]);
  init_game_vars(r, game);
  ft_putstr("Please enter \"1\" to begin\n");
  int i;
  scanf("%d", &i);
  while (1){
    if ((again = play_game(game)) == 0)
      break;
    free_game_memory(game);
    setup_game(game);
  }
  free_game_memory(game);
}

char **curl_and_split(void){
  CURL *curl;
  CURLcode res;
  char **words;

  curl = curl_easy_init();
  if(curl) {
    struct string s;
    init_string(&s);
    curl_easy_setopt(curl, CURLOPT_URL, "linkedin-reach.hagbpyjegb.us-west-2.elasticbeanstalk.com/words");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
    res = curl_easy_perform(curl);
    words = ft_strsplt(s.data);
    free(s.data);
    curl_easy_cleanup(curl);
  }
  return words;
}

int main(void)
{
  t_game *game;

  game = (t_game *)malloc(sizeof(t_game));
  game->words = curl_and_split();
  if (pop_the_question())
    setup_game(game);

  int len = ft_array_len(game->words);
  for (int i = 0; i < len; i++)
    free((game->words)[i]);
  free(game->words);
  free(game);
  return 0;
}