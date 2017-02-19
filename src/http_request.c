#include "hangman.h"

/*
  init_string:
      -initialize struct of type string
*/
void init_string(struct string *s) {
  s->len = 0;
  if (!(s->data = malloc(s->len+1)))
    exit(EXIT_FAILURE);
  s->data[0] = '\0';
}

/*
  write_func:
      -this function is created to interact with the curl api
      -received data from http request and returns an integer
      -instructs program how to store data receieved from http request
*/
size_t write_func(void *data, size_t size, size_t nmemb, struct string *s)
{
  size_t new_len = s->len + size*nmemb;

  if (!(s->data = realloc(s->data, new_len+1)))
    exit(EXIT_FAILURE);
  memcpy(s->data+s->len, data, size*nmemb);
  s->data[new_len] = '\0';
  s->len = new_len;

  return (size*nmemb);
}

/*
	ft_strsplt takes in a null terminated string and returns a null terminated array of null terminated strings
	relies on strsep, which is a builtin function that finds the next instance of a specified separator character
	and reutrns a pointer to that location in the original string.
*/
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
  while ((current = strsep(&data, "\n")))
    res[i++] = ft_strdup(current);
  res[i] = "\0";
  return res;
}




/*curl_and_split(void)
  call to curl_easy_init() which sets up a few things needed for an http request
  declare and initialize a string struct (has a field for string length, which is useful for receiving http request)
  set a few operations to be performed.
        -we're going to send our request to CURLOPT_URL.
        -we're going to use write_func when we receive the information retrieved
        -we're going to to send the output of write_func to string struct s;
  -we call to curl function, which returns variable of type CURLcode;
  -use ft_strsplt() to split the resulting very long string into an array of strings, one string for each word.
  -free memory and call to curl_easy_cleanup()
  return words, the array of strings.
-questions:
  -what is CURLcode type // what is return value of curl_easy_perform();
*/
char **curl_and_split(void){
  CURL *curl;
  CURLcode res;
  char **words;

  curl = curl_easy_init();
  if(curl) {
    struct string s;
    init_string(&s);
    curl_easy_setopt(curl, CURLOPT_URL, "linkedin-reach.hagbpyjegb.us-west-2.elasticbeanstalk.com/words");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_func);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
    res = curl_easy_perform(curl);
    words = ft_strsplt(s.data);
    free(s.data);
    curl_easy_cleanup(curl);
  }
  return words;
}
