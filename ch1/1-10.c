/* Ex. 1-10 (p. 20): Write a program that copies its input to its
 * output and replaces the whitespace characters tab, backspace and
 * backslash with \t, \b and \\ respectively. */

#include <stdio.h>

int main()
{
     int c;

     while ((c = getchar()) != EOF) {
	  if (c == '\t')
	       printf("\\t");
	  else if (c == '\b')
	       printf("\\b");
	  else if (c == '\\')
	       printf("\\");
	  else
	       putchar(c);
     }
}
