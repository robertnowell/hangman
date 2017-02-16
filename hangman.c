//dependencies
//libcurl: install libcurl from https://curl.haxx.se/download.html
// in untarred directory, run ./configure
						// then run: make
						// then: make install
// from https://curl.haxx.se/libcurl/c/libcurl-tutorial.html


#include "libft.h"

#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>

struct string {
  char *data;
  size_t len;
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
		ft_putendl(res[i]);
		i++;
	}
	res[i] = "\0";
	return res;
}

int main(void)
{
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

    // printf("%s\n", s.data);
    // char *token;
	// while ((token = strsep(&s.data, ","))) ft_putendl(token);
    ft_strsplt(s.data);
    // ft_putstr(words[43]);
    free(s.data);

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return 0;
}

