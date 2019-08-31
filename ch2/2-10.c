/* Ex. 2-10: Rewrite the function lower that turns an upper case
 * [ascii] character to lower case, with the ternary operator instead
 * of if-else. */

#include <stdio.h>

int lower(char s);

int main(void)
{
     printf("Test lower:\n");
     {
	  printf("%d", 'a' == lower('A'));
	  printf("%d", '!' == lower('!'));
	  printf("%d", 'q' == lower('Q'));
	  printf("%d", 's' == lower('s'));
	  printf("%d", '\n' == lower('\n'));

	  putchar('\n');
     }
     return 0;
}

int lower(char c)
{
     return (('A' <= c && c <= 'Z') ? (c + 'a' - 'A') : c);
}
