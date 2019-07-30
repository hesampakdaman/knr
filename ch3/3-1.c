/* Ex. 3-1: Modifiy binsearch such that the number of tests inside the
 * loop is 1 with the price of added tests outside the loop. */

#include <stdio.h>
#include <stdlib.h>

#define MAXNUM  1000000
#define MAXLINE 1000000

int binsearch(int x, int v[], int n);
int fetchline(char line[]);
void tests(void);

int main(void)
{
     char line[MAXLINE];
     int v[MAXNUM];
     int n;

     n = 0;
     while ((n = fetchline(line)) > 0) {
     	  v[n++] = atoi(line);
     }
     return 0;
}

/* fetchline: read line from stdin, copy it to input array and return
 * its length. */
int fetchline(char line[])
{
     int i, c;

     i = 0;
     while ((c = getchar()) != '\n' && c != EOF)
	  line[i++] = c;
     if (c == '\n')
	  line[i++] = '\n';
     line[i] = '\0';
     return i;
}

/* binsearch: finds x in a vector v of integers in increasing order. */
int binsearch(int x, int v[], int n)
{
     int low, mid, high;

     low = 0;
     high = n - 1;
     while (low < high) {
	  mid = (low + high) / 2;
	  if (x <= v[mid])
	       high = mid;
	  else
	       low = mid + 1;
     }
     if (x == v[mid])
	  return mid;
     else if(x == v[high])
	  return high;
     else
	  return -1;
}

void tests(void)
{
     printf("test binsearch:\n");
     {
                    /* 0  1  2   3   4   5 */
	  int v[] = {-13, 0, 55, 78, 93, 99};

	  printf("%d", 2 == binsearch(55, v, 6));
	  printf("%d", 4 == binsearch(93, v, 6));
	  printf("%d", 0 == binsearch(-13, v, 6));
	  printf("%d", -1 == binsearch(77, v, 6));
	  printf("%d", -1 == binsearch(-1337, v, 6));
     }

     {
                    /* 0     1    2    3    4    5  6 */
	  int v[] = {-101, -99, -93, -78, -55, -13, 0};

	  printf("%d", 4 == binsearch(-55, v, 7));
	  printf("%d", -1 == binsearch(101, v, 7));
	  printf("%d", 6 == binsearch(0, v, 7));
	  printf("%d", -1 == binsearch(78, v, 7));
	  printf("%d", 5 == binsearch(-13, v, 7));
     }
     putchar('\n');
}
