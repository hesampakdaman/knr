/* Ex. 2-3: Write a function htoi that converts a hexadecimal string
 * of to its decimal equivalent */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

int atoh(const char s);
int hexlen(const char s[]);
int htoi(const char h[]);
int power(const int base, int exp);
void stoh(const char from[], char to[], int hexlen);

/* main: tests converting hexadecimal to decimal using htoi()
 * function. */
int main(void)
{
     printf("Test: power\n");
     printf("%d", 1  == power(16, 0));
     printf("%d", 256  == power(16, 2));
     printf("%d\n", -27 == power(-3, 3));

     printf("Test: hexlen\n");
     printf("%d", 5 == hexlen("0x22345"));
     printf("%d", 3 == hexlen("344"));
     printf("%d\n", 2 == hexlen("0x43"));

     printf("Test: atoh (ascii to hex)\n");
     printf("%d", 10 == atoh('a'));
     printf("%d", 15 == atoh('F'));
     printf("%d\n", 2 == atoh('2'));

     printf("Test: htoi\n");
     printf("%d", 10995  == htoi("2AF3"));
     printf("%d", 1337   == htoi("0x539"));
     printf("%d\n", 1989 == htoi("0X7c5"));
}

/* htoi: converts a hex string its 10-decimal equivalent. */
int htoi(const char s[])
{
     int i, res;
     int len = hexlen(s); /* length of significant hex values in input string */
     char hex[len];

     stoh(s, hex, len);
     res = 0;
     for (i = 0; i < len; ++i)
	  res += hex[i] * power(16, len-(i+1));
     return res;
}

/* power: computes int power of base with positive exponent n */
int power(const int base, int n)
{
     int p;

     for (p = 1; n > 0; --n)
	  p *= base;
     return p;
}

/* hexlen: returns the length of a hex string counting only
 * significant digits */
int hexlen(const char s[])
{
     int i;

     i = strlen(s);
     if (s[0] == '0' && tolower(s[1]) == 'x')
	  i -= 2;
     return i;
}

/* atoh: ascii to hex value, respects null character. */
int atoh(char h)
{
     int i;
     if (isdigit(h))
	  i = h - '0';
     else if (tolower(h) >= 'a' && tolower(h) <= 'h')
	  i = tolower(h) - 'a' + 10;
     else if (h == '\0')
	  i = '\0';
     else
	  i = 0;
     return i;
}

/* stoh: input string to hex string */
void stoh(const char from[], char to[], int hexlen)
{
     int i;
     int fstart;	 /* index where hex values begin (excl. 0x) */

     i = 0;
     fstart = strlen(from) - hexlen;
     while ((to[i] = atoh(from[i+fstart])) != '\0')
	  ++i;
}
