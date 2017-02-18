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

char **ft_strsplt(char *word){
	int count = 0;
	int i = 0;
	char *current;
	char **res;
	int len = ft_strlen(word);



	for (i = 0; i < len; i++) {
		if (word[i] == '\n')
			count++;
	}
	if (!(res = (char **)malloc(sizeof(char *) * (count + 2)))){
		return (NULL);
	}
	i = 0;
  // printf("current:%p\nres:%p\n", current, res);
	while ((current = strsep(&word, "\n"))) {
		res[i] = ft_strnew(ft_strlen(current + 1));
    ft_memset(res[i], 0, ft_strlen(current) + 1);
    // printf("i:%d\nres[i]:%p\n\n", i, res[i]);
		res[i] = current;
		i++;
	}
	res[i] = "\0";
	return res;
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
  printf("%s\nGuesses Remaining: %d\nPrevious Guesses: ", game->output_string, game->num_incorrect);
  for (int i = 0; i < ft_array_len(game->prev_guesses); i++){
    printf("%s, ", (game->prev_guesses)[i]);
  }
  printf("\n");
}

void play_game(t_game *game)
{
  bool complete = false;
  char *guess;

  while (!complete && game->num_incorrect < 6){
    ft_output(game);

  }
}

void game_init(t_game *game)
{
  char *answer;
  char *word;
  char *output_string;
  char **prev_guesses;

  answer = ft_strnew(100);
  ft_memset(answer, 0, 100);
  printf("Hello, would you like to play a game?\n");
  if (scanf("%s", answer) < 0){
    ft_puterr("error reading user input");
    free(answer);
    return;
  }
  if (ft_strcmp(answer, "no") == 0){
    free(answer);
    return;
  }
  if (ft_strcmp(answer, "yes") == 0){
    ft_putendl("yes");
  }
  else {
    ft_putendl("Let's pretend you said 'yes'");
  }
  srand(time(NULL));
  int r = rand() % 162412;
  printf("number: (%d)\n", r);
  game->word = game->words[r];
  printf("words : (%s)\n", game->word);

  game->output_string = ft_strnew(ft_strlen(game->word)+1);
  ft_memset(game->output_string, '_', ft_strlen(word));
  printf("output_string: (%s)\n", game->output_string);

  if (!(game->prev_guesses = (char **)malloc(sizeof(char *) * 100)))
    return;
  for(int i = 0; i < 100; i++) {
    (game->prev_guesses)[i] = ft_strnew(100);
    ft_memset((game->prev_guesses)[i], 0, 100);
  }
  game->num_incorrect = 0;
  play_game(game);

  free(game->words);
  free(game->output_string);
  for(int i = 0; i < 100; i++)
    free((game->prev_guesses)[i]);
  free(game->prev_guesses);
}

char **ft_curl_and_split(void){
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
  game->words = ft_curl_and_split();
  game_init(game);
  free(game);
  return 0;
}
