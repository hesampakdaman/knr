/* Ex. 2-4: Write the function any(s1, s2) that returns the first
 * position j in s1 where s1[j] == c for some character c in s2,
 * otherwise return -1. */

#include <stdio.h>

int any(const char s1[], const char s2[]);
int cinstr(const char c, const char s[]);

int main(void)
{
     printf("Test any():\n");
     {
	  printf("%d", 1 == any("abc", "123b"));
	  printf("%d", 0 == any("hello, world!", "here you go!"));
	  printf("%d", 5 == any("!1234a", "a"));
	  printf("%d", 2 == any("!1a324", "a"));
	  printf("%d", -1 == any("12345", "characters"));
	  printf("%d", -1 == any("gibberish", "!@#$(&#)"));
	  printf("%d", -1 == any("", ""));
	  printf("%d", 1 == any("h ", "     "));
	  putchar('\n');
     }
}

/* any: returns the first position in s1 which matches any character
 * in s2.  */
int any(const char s1[], const char s2[])
{
     int i, res;

     i = 0;
     while (cinstr(s1[i], s2) == 0 && s1[i++] != '\0')
	  ;
     if (s1[i] != '\0')
	  return i;
     else
	  return -1;
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
