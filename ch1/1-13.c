/* Ex. 1-13 (p. 24): Write a program to print a histogram of the
 * lengths of words in its input.. It is easy to to draw the histogram
 * bars horizontally; a vertical orientation is more challenging. */

#include <stdio.h>

#define MAXSIZE 99		/* Max word length that the program handles. */
#define BARBODY "|//|"
#define BARTOP	"...."
#define BARZERO	"____"

/* A word is defined as a sequence of non-whitespace chars */
int main() {
     int c, i;
     int freq[MAXSIZE], maxfreq;         /* frequency and max word lengths */
     int wordlen, minlen, maxlen;        /* length of words, current, minimum and maximum */
     int row, col;                       /* row, column for printing histogram table */

     for (i = 0; i < MAXSIZE; ++i)
	  freq[i] = 0;

     maxfreq = maxlen = wordlen = 0;
     minlen = MAXSIZE;
     while ((c = getchar()) != EOF) {
	  if (c != '\n' && c != '\t' && c != ' ')
	       ++wordlen;
	  else if (wordlen > 0) {
	       ++freq[wordlen];
	       if (freq[wordlen] > maxfreq)
		    maxfreq = freq[wordlen];
	       if (wordlen > maxlen)
		    maxlen = wordlen;
	       if (wordlen < minlen)
		    minlen = wordlen;
	       wordlen = 0;
	  }
     }

     for (i = 0; i < maxlen/2-2; ++i)
	  putchar('\t');
     printf("WORD LENGTH HISTOGRAM\n\n");

     /* We print a BARTOP for each bar, which is not affect the
      * frequency. Since BARTOP consumes one newline, we must start
      * our printing table from maxfreq + 1. The last row in the
      * printing table are word length numbers, which is why the
      * outermost loop stops at row == 1. */
     for (row = maxfreq+1; row > 0; --row) {
	  col = minlen;
     	  for (wordlen = minlen; wordlen <= maxlen; ++wordlen) {
	       while (col < wordlen) {
		    putchar('\t');
		    ++col;
	       }
     	       if (freq[wordlen] > 0) {
		    if (freq[wordlen] >= row)
			 printf(BARBODY);
		    else if (freq[wordlen] + 1 == row)
			 printf(BARTOP);
     	       } else if (row == 1)
		    printf(BARZERO);
     	  }
     	  putchar('\n');
     }

     for (wordlen = minlen; wordlen <= maxlen; ++wordlen)
	  printf("%3d\t", wordlen);
     putchar('\n');
}
