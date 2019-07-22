/* Write a function squeeze(s1, s2) that will delete any character in
 * s1 that is in s2. */

#include <stdio.h>

#define MAXLEN 100

int compstr(const char s1[], const char s2[]);
int cinstr(const char c, const char s[]);
void copystr(const char from[], char to[]);
void squeeze(char s1[], const char s2[]);

int main(void)
{
     char s1[MAXLEN], s2[MAXLEN];

     printf("test compstr:\n");
     {
	  printf("%d", 1 == compstr("th is", "th is"));
	  printf("%d", 1 == compstr("!234@", "!234@"));
	  printf("%d", 0 == compstr("erqwrwer", "erqwrw"));
	  printf("%d", 0 == compstr("hello", "elloh"));

	  putchar('\n');
     }

     printf("test copystr:\n");
     {
	  copystr("this", s1);
	  printf("%d", 1 == compstr("this", s1));

	  copystr("this", s2);
	  printf("%d", 1 == compstr(s1, s2));

	  copystr("hello world", s1);
	  copystr("world", s2);
	  printf("%d", 0 == compstr(s1, s2));

	  copystr("foo", s1);
	  copystr("bar", s2);
	  printf("%d", 0 == compstr(s1, s2));


	  putchar('\n');
     }

     printf("test cinstr:\n");
     {
	  printf("%d", 1 == cinstr('\0', "heo"));
	  printf("%d", 1 == cinstr('s', "string"));
	  printf("%d", 0 == cinstr('l', "going"));
	  printf("%d", 0 == cinstr(' ', "direct"));


	  putchar('\n');
     }

     printf("test squeeze:\n");
     {
	  copystr("hello world", s1);
	  copystr("world", s2);
	  squeeze(s1, s2);
	  printf("%d", 1 == compstr(s1, "he "));

	  copystr("hello world", s1);
	  copystr("", s2);
	  squeeze(s1, s2);
	  printf("%d", 1 == compstr(s1, "hello world"));

	  copystr("hello world", s1);
	  copystr("eo ", s2);
	  squeeze(s1, s2);
	  printf("%d", 1 == compstr(s1, "hllwrld"));

	  copystr("123!", s1);
	  copystr("1!", s2);
	  squeeze(s1, s2);
	  printf("%d", 1 == compstr(s1, "23"));


	  putchar('\n');
     }
}

/* compstr: compare to strings up to the first null character. */
int compstr(const char s1[], const char s2[])
{
     int i, eq;

     i = 0;
     while (s1[i] != '\0' || s2[i] != '\0') {
	  eq = ((s1[i] == s2[i]) == 1);
	  ++i;
     }
     return eq;
}

/* copystr: copy strings until null character is found in
 * from. Assumes to[] is big enough.  */
void copystr(const char from[], char to[])
{
     int i;

     i = 0;
     while ((to[i] = from[i]) != '\0')
	  ++i;
}

/* squeeze: removes characters in s1 that exists in s2. */
void squeeze(char s1[], const char s2[])
{
     int i, j;

     i = j = 0;
     while (s1[i] != '\0') {
	  if (! cinstr(s1[i], s2)) {
	       s1[j++] = s1[i];
	  }
	  ++i;
     }
     s1[j] = '\0';
}

/* cinstr: looks if the character c is in the string s. */
int cinstr(const char c, const char s[])
{
     int j, in;

     j = 0;
     while ((in = (c == s[j])) == 0 && s[j++] != '\0')
	  ;
     return in;
}
