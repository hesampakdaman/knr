/* Ex. 1-16 (p. 30): Edit the __main routine__ to correctly print the
 * length of arbitrarly long input lines and as much as __possible__
 * of the longest line. That is, we are not to modify copy and getline
 * routines. */

#include <stdio.h>
#include <string.h>

#define MAXLINE		10	/* maximum input line size */

/* Name conflict with getline in stdio header forced us to prefix fn
 * name with '_' */
int _getline(char line[], int lim);
int isbigline(char line[]);
void copy(char to[], char from[]);

/* Print longest input line. */
int main()
{
     int len;          	        /* current line length */
     int lengthfin;             /* final length of any line */
     int max;	                /* longest line seen so far */
     char line[MAXLINE];	/* current input line */
     char linefin[MAXLINE];	/* storage for final line wheter tiny or big */
     char longest[MAXLINE];	/* longest line save here */

     max = len = 0;
     lengthfin = 0;
     while ((len = _getline(line, MAXLINE)) > 0) {
	  lengthfin += len;
	  if (lengthfin < MAXLINE)
	       copy(linefin, line);
	  if (lengthfin > max) {
	       max = lengthfin - 1;             /* remove '\n' char from count */
	       copy(longest, linefin);
	  }
	  if (!isbigline(line)) {
	       copy(linefin, "");
	       lengthfin = 0;
	  }
     }
     if (max > 0)
	  printf("%s\n%d\n", longest, max);
     return 0;
}

int isbigline(char line[])
{
     int len;

     len = strlen(line);
     return (len == MAXLINE-1) && (line[len-1] != '\n');
}

/* getline: read a line into s, return its length (including '\n'
 * character) */
int _getline(char s[], int lim)
{
     int c, i;

     for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
	  s[i] = c;
     if (c == '\n')
	  s[i++] = c;
     s[i] = '\0';
     return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough. */
void copy(char to[], char from[])
{
     int i;

     i = 0;
     while ((to[i] = from[i]) != '\0')
	  ++i;
}
