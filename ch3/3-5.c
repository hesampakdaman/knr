/* Ex 3-5 (p. 64): Write a function itob(n,s,b) that converts an
 * (decimal) integer n to its equivalent in base b numeral system. In
 * particular, itob(n,s,16) represents the hexadecimal system.  */

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int iton(int i, int b);
void itob(int n, char s[], int b);
void reverse(char s[]);
void tests(void);

int main(void)
{
     tests();
     return 0;
}

/* iton: integer to ascii numeral. Supports 1-10, 12, 16, 20 numeral
 * systems. */
int iton(int i, int b)
{
     i %= b;
     switch (i) {
     case 10:
	  if (b == 12)
	       return 'X';
	  else
	       return 'A';
     case 11:
	  if (b == 12)
	       return 'E';
	  else
	       return 'B';
     case 12:
	  return 'C';
     case 13:
	  return 'D';
     case 14:
	  return 'E';
     case 15:
	  return 'F';
     case 16:
	  return 'G';
     case 17:
	  return 'H';
     case 18:
	  return 'I';
     case 19:
	  return 'J';
     default:
	  return i + '0';
     }
}

void tests(void)
{
     char s[MAXLINE];

     printf("test quinary:\n");
     {
	  itob(5, s, 5);
	  printf("%d", 0 == strcmp("10", s));

	  itob(25, s, 5);
	  printf("%d", 0 == strcmp("100", s));

	  itob(30, s, 5);
	  printf("%d", 0 == strcmp("110", s));

	  putchar('\n');
     }

     printf("test binary:\n");
     {
	  itob(21, s, 2);
	  printf("%d", 0 == strcmp("10101", s));

	  itob(25, s, 2);
	  printf("%d", 0 == strcmp("11001", s));

	  itob(-500, s, 2);
	  printf("%d", 0 == strcmp("-111110100", s));

	  itob(40, s, 2);
	  printf("%d", 0 == strcmp("101000", s));

	  putchar('\n');
     }

     printf("test hexadecimal:\n");
     {
	  itob(-1337, s, 16);
	  printf("%d", 0 == strcmp("-539", s));

	  itob(2610, s, 16);
	  printf("%d", 0 == strcmp("A32", s));

	  itob(-1375, s, 16);
	  printf("%d", 0 == strcmp("-55F", s));

	  itob(63, s, 16);
	  printf("%d", 0 == strcmp("3F", s));

	  putchar('\n');
     }
}

/* itoa (p. 64): convert n to characters in s, modified to handle
 * largest negative number. */
void itob(int n, char s[], int b)
{
     int i, adjust, sign;

     /* adjust unit with 1 digit since largest negative number does
      * not fit in a two's complement system when multiplied by (-1) */
     adjust = (n == INT_MIN) ? 1 : 0;
     if ((sign = n) < 0) {	          /* record sign */
	  n += adjust;
	  n = -n;		          /* make n positive */
     }
     i = 0;
     do {			          /* generate list in reverse order */
	  s[i++] = iton(n, b);  	  /* get next digit */
     } while ((n /= b) > 0);	          /* delete it */
     if (sign < 0)
     	  s[i++] = '-';
     s[i] = '\0';
     reverse(s);
     if (adjust)
	  ++s[strlen(s) - 1];
}

/* reverse (p. 62-63): reverse order of string s. */
void reverse(char s[])
{
     int c, i, j;

     for (i = 0, j = strlen(s)-1; i < j; ++i, --j)
	  c = s[i], s[i] = s[j], s[j] = c;
}
