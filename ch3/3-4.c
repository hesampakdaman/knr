/* Ex. 3-4 (p. 64): In two's complement system, our version of itoa
 * does not handle the largest negative number. Explain why. Modify
 * itoa to print the value correctly independent of machine. */

/* Explanation: In two's complement the leftmost bit is used for sign
 * and to represents negative numbers. When the leftmost bit is 0, it
 * is interpreted as a positive number. We get the largest negative
 * number by setting the leftmost bit to 1 and the rest to
 * zero. Setting the leftmost bit to zero and all other bits to 1 will
 * give us the largest positive number. Thus, the largest negative
 * number is one unit digit larger than the largest biggest positive
 * number (disregarding sign, of course). */

#include <stdio.h>
#include <limits.h>
#include <string.h>

void itoa(int n, char s[]);
void tests(void);
void reverse(char s[]);

int main(void)
{
     tests();
     return 0;
}

/* itoa (p. 64): convert n to characters in s, modified to handle
 * largest negative number. */
void itoa(int n, char s[])
{
     int i, sign, adjust;

     /* adjust unit with 1 digit since largest negative number does
      * not fit in a two's complement system when multiplied by (-1) */
     adjust = (n == INT_MIN) ? 1 : 0;
     if ((sign = n) < 0) {	/* record sign */
	  n += adjust;
	  n = -n;		/* make n positive */
     }
     i = 0;
     do {			 /* generate list in reverse order */
	  s[i++] = n % 10 + '0'; /* get next digit */
     } while ((n /= 10) > 0);	 /* delete it */
     if (sign < 0)
	  s[i++] = '-';
     s[i] = '\0';
     reverse(s);
     if (adjust)
	  ++s[strlen(s) - 1];
}

void tests(void)
{
     char s[12];

     itoa(INT_MIN, s);
     printf("%d\n", 0 == strcmp(s, "-2147483648")); /* INT_MIN on my machine */
}


/* reverse p. 62-63: reverse order of string s. */
void reverse(char s[])
{
     int c, i, j;

     for (i = 0, j = strlen(s)-1; i < j; ++i, --j)
	  c = s[i], s[i] = s[j], s[j] = c;
}
