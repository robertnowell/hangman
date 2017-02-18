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

struct game {
  char  *word;
  char  *output_string;
  char  **prev_guesses;
  int   num_incorrect;
};

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
	if (!(res = (char **)malloc(sizeof(char *) * count))){
		return (NULL);
	}
	i = 0;
	while ((current = strsep(&word, "\n"))) {
		if (!(res[i] = (char *)malloc(sizeof(char *) * (ft_strlen(current) + 1))))
			return NULL;
		res[i] = current;
    // printf("current: %s\n", res[i]);
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

void ft_output(char *output_string, int num_incorrect, char **prev_guesses) {
  printf("%s\nGuesses Remaining: %d\nPrevious Guesses: ", output_string, num_incorrect);
  for (int i = 0; i < ft_array_len(prev_guesses); i++){
    printf("%s, ", prev_guesses[i]);
  }
  printf("\n");
}

void play_game(char *word, char *output_string)
{
  char **prev_guesses;
  int num_incorrect = 0;
  bool complete = false;
  char *guess;

  if (!(prev_guesses = (char **)malloc(sizeof(char) * 100)))
    return;
  for(int i = 0; i < 100; i++) {
    if (!(prev_guesses[i] = (char *)malloc(sizeof(char) * 100)))
      return;
    prev_guesses[i] = "\0";
  }
  while (!complete && num_incorrect < 6){
    ft_output(output_string, num_incorrect, prev_guesses);

  }
}

void game_init(char **words)
{
  char answer[100];
  char *word;
  char *output_string;
  printf("Hello, would you like to play a game?\n");
  if (scanf("%s", answer) < 0){
    ft_puterr("error reading user input");
    exit(-1);
  }
  if (ft_strcmp(answer, "no") == 0){
    exit(0);
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
  word = words[r];
  printf("words : (%s)\n", word);
  output_string = ft_strnew(ft_strlen(word)+1);
  printf("len+1=(%lu)\n", (ft_strlen(word)+1));
  for (int i = 0; i < ft_strlen(word); i++)
    output_string[i] = '_';
  printf("output_string: (%s)\n", output_string);
  play_game(word, output_string);
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
  char **words = ft_curl_and_split();
  game_init(words);
  return 0;
}
