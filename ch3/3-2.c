/* Ex. 3-2: Write escape(s,t) that will copy the string t to string s
 * and make newline and tabstop visible while copying. Use
 * switch. Write another function that does the reverse. */

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void escape(char s[], char t[]);
void reverse_esc(char s[], char t[]);
void tests(void);

int main(void)
{
     tests();
     return 0;
}

/* escape: copy string t to string s making escaped characters '\n'
 * and '\t' visible */
void escape(char s[], char t[])
{
     int i, j;

     i = j = 0;
     while (t[i] != '\0') {
	  switch (t[i]) {
	  case '\n':
	       s[j++] = '\\';
	       s[j++] = 'n';
	       break;
	  case '\t':
	       s[j++] = '\\';
	       s[j++] = 't';
	       break;
	  default:
	       s[j++] = t[i];
	       break;
	  }
	  ++i;
     }
     s[j] = '\0';
}

/* reverse_esc: copy string t to string s by turning visible escape
 * character sequences of newline and tabstop to real characters. */
void reverse_esc(char s[], char t[])
{
     int i, j;

     i = j = 0;
     while (t[i] != '\0') {
	  switch (t[i]) {
	  case '\\':
	       switch (t[++i]) {
	       case 'n':
		    s[j++] = '\n';
		    break;
	       case 't':
		    s[j++] = '\t';
		    break;
	       default:
		    s[j++] = '\\';
		    s[j++] = t[i];
		    break;
	       }
	       break;
	  default:
	       s[j++] = t[i];
	       break;
	  }
	  ++i;
     }
     s[j] = '\0';
}

void tests(void)
{
     char s[MAXLINE];

     printf("%s", "test escape:\n");
     {
	  escape(s, "	tabs");
	  printf("%d", 0 == strcmp(s, "\\ttabs"));

	  escape(s, "ta	\b  s");
	  printf("%d", 0 == strcmp(s, "ta\\t\b  s"));
	  putchar('\n');
     }

     printf("%s", "test reverse_esc:\n");
     {
	  escape(s, "tab	s");
	  reverse_esc(s, s);
	  printf("%d", 0 == strcmp(s, "tab	s"));

	  escape(s, "t\a	bs");
	  reverse_esc(s, s);
	  printf("%d", 0 == strcmp(s, "t\a	bs"));

	  putchar('\n');
     }
}
