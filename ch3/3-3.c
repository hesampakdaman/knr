/* Ex. 3-3 (p. 63): Write the function expand(s1,s2) that expands
 * shorthand notation like a-z in the string s1 to the complete list
 * abc..xyz in s2. Allow for letters, digits and handle cases like
 * -a-b-c, a-Z0-9 and A-z-. Leading or trailing '-' are to be take
 * literally. */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int chkends(char s, char e);
int chkinterv(char lo, char mid, char hi);
void cpinterv(char s[], int i, int c, int to);
void expand(char s1[], char s2[]);
void tests(void);

int main(void)
{
     tests();
     return 0;
}

/* chkends: check if character s, e make up valid start and end in
 * shorthand notation */
int chkends(char s, char e)
{
     return ((isalpha(s) && isalpha(e)) || (isdigit(s) && isdigit(e)));
}

/* chkinterv: check that s[i], s[i+1] and s[i+2] is a valid
 * interval in shorthand notation. */
int chkinterv(char lo, char mid, char hi)
{
     return (chkends(lo, hi) && mid == '-');
}

/* cpinterv: copy all ascii chars in interval from until to into s
 * beginning at i. */
void cpinterv(char s[], int i, int from, int to)
{
     while (from <= to)
	  s[i++] = from++;
     s[i] = '\0';
}

/* expand: expands shorthand notation and treats leading/trailing '-'
 * literally. */
void expand(char s1[], char s2[])
{
     int i, j;

     i = j = 0;
     if (s1[i] == '-') {
	  s2[j++] = '-';
	  ++i;
     }
     while (i < strlen(s1)-1) {
	  if (chkinterv(s1[i], s1[i+1], s1[i+2])) {
	       cpinterv(s2, j, tolower(s1[i]), tolower(s1[i+2]));
	       j += (tolower(s1[i+2]) - tolower(s1[i]) + 1);
	  }
	  ++i;
     }
     if (s1[strlen(s1)-1] == '-')
	  s2[j++] = '-';
     s2[j] = '\0';
}

void tests(void)
{
     char s[MAXLINE];

     printf("test chkends:\n");
     {
	  printf("%d", 1 == chkends('a', 'b'));
     	  printf("%d", 0 == chkends('a', '5'));
     	  printf("%d", 1 == chkends('5', '3'));

	  putchar('\n');
     }

     printf("test chkinterv:\n");
     {
     	  printf("%d", 1 == chkinterv('a', '-', 'c'));
	  printf("%d", 1 == chkinterv('3', '-', '5'));
     	  printf("%d", 0 == chkinterv('-', '3', '5'));
	  printf("%d", 0 == chkinterv('a', '-', '5'));

     	  putchar('\n');
     }

     printf("%s", "test expand:\n");
     {
	  expand("a-d", s);
	  printf("%d", 0 == strcmp(s, "abcd"));

	  expand("a-b-c", s);
	  printf("%d", 0 == strcmp(s, "abbc"));

	  expand("-a-z", s);
	  printf("%d", 0 == strcmp(s, "-abcdefghijklmnopqrstuvwxyz"));

	  expand("0-9", s);
	  printf("%d", 0 == strcmp(s, "0123456789"));

	  expand("5-8A-D", s);
	  printf("%d", 0 == strcmp(s, "5678abcd"));

	  expand("A-d5-8", s);
	  printf("%d", 0 == strcmp(s, "abcd5678"));

	  expand("-A-f", s);
	  printf("%d", 0 == strcmp(s, "-abcdef"));

	  expand("-a-F-", s);
	  printf("%d", 0 == strcmp(s, "-abcdef-"));

	  expand("u-w-", s);
	  printf("%d", 0 == strcmp(s, "uvw-"));

	  expand("0-3u-wx-z", s);
	  printf("%d", 0 == strcmp(s, "0123uvwxyz"));

	  putchar('\n');
     }
}
