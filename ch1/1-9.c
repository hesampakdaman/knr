/* Ex. 1-9 (p. 20): Write a program that copies its input to its
 * output replacing multiple blanks with a single blank.  */

#include <stdio.h>

/* Control whether to putchar BLANK or not. */
#define PUT	1
#define IGNORE	0

int main()
{
     int c, state;

     state = PUT;
     while ((c = getchar()) != EOF) {
	  if (c != ' ') {
	       putchar(c);
	       state = PUT;
	  } else if (state == PUT) {
	       putchar(' ');
	       state = IGNORE;
	  }
     }
}
