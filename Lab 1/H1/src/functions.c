#include <stdio.h>
const char *jokes[] = {"Do you know why the programmer quit his job?",
                       "Do you know why C is a good language for kids?",
                       "Do you know why the computer was cold?",
                       "Do you know why computers are so smart?",
                       "Do you know why a byte got married?"};

const char *punchlines[] = {
    "Because he didn't get arrays.", "Because it's easy to C!",
    "Because it left its Windows open.",
    "Because they listen to their motherboards.",
    "Because it needed to be converted into a gig-abyte."};

const char *invalid = "Invalid number. Please enter a number between 1 and 5.";

void TellJoke(int joke_number) { printf("%s", jokes[joke_number - 1]); }

void GivePunchline(int punchline_number) {
  if (punchline_number == 0) {
    printf("%s", invalid);
    return;
  }

  printf("%s", punchlines[punchline_number - 1]);
}
