#include <ctype.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *thread_function(void *arg) {
  // We duplicate the passed string in memory
  char *s = strdup(arg);
  if (s == NULL) {
    perror("strdup");
    exit(EXIT_SUCCESS);
  }

  // Upper case it
  for (char *c = s; *c != '\0'; c++) {
    *c = toupper(*c);
  }

  // Return memory duplicate
  return s;
}

int main(void) {
  // Thread set-up
  int success;

  pthread_t thread_id;
  pthread_attr_t thread_attr;
  success = pthread_attr_init(&thread_attr);
  if (success != 0) {
    perror("pthread_attr_init");
    exit(EXIT_FAILURE);
  }

  // Create thread
  success =
      pthread_create(&thread_id, &thread_attr, thread_function, "hi bro!");
  if (success != 0) {
    perror("thread_create");
    exit(EXIT_FAILURE);
  }

  // Destroy thread
  success = pthread_attr_destroy(&thread_attr);
  if (success != 0) {
    perror("pthread_attr_destroy");
    exit(EXIT_FAILURE);
  }

  void *result;
  success = pthread_join(thread_id, &result);
  if (success != 0) {
    perror("pthread_join");
    exit(EXIT_FAILURE);
  }
  printf("Joined with thread %lu; returned value was '%s'\n", thread_id,
         (char *)result);
  free(result);

  exit(EXIT_SUCCESS);
}
