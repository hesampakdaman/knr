/* Ex. 1-18: Remove trailing blank and tabs from each line of input
 * and delete blank lines entirely. */

#include <stdio.h>

#define MAXLINE		1000	/* maximum input line size */

/* Name conflict with getline in stdio header forced us to prefix fn
 * name with '_' */
int _getline(char line[], int maxline);
int gettrailidx(char line[], int length);

int main()
{
     int len;			/* current input line length */
     int idx;			/* index to last non-trailing char */
     int i;
     char line[MAXLINE];	/* current input line */

     while ((len = _getline(line, MAXLINE)) > 0) {
	  idx = gettrailidx(line, len);
	  if (idx > 0) {
	       for (i = 0; i <= idx; ++i)
		    putchar(line[i]);
	       if (idx < len)
		    putchar('\n');
	  }
     }
     return 0;
}

/* getline: read a line into s, return length */
int _getline(char s[], int lim)
{
     int c, i;

     for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
	  s[i] = c;
     if (c == '\n') {
	  s[i] = c;
	  ++i;
     }
     s[i] = '\0';
     return i;
}

/* gettrailidx: return the last index of non-whitespace char in the
 * line. */
int gettrailidx(char line[], int len) {
     int i;

     i = len - 2;		/* ignore newline char \n and null char */
     while (line[i] == '\t' || line[i] == ' ')
	  --i;
     return i;
}
