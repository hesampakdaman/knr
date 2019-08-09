/* Ex. 4-1 (p. 71): Write the function strrindex(s,t), which returns the
 * position of the /rightmost/ occurrence of t in s, or -1 if there is
 * none. */

#include <stdio.h>
#include <string.h>

void tests(void);
int strrindex(char s[], char t[]);

int main(void)
{
     tests();
     return 0;
}

/* strrindex: Find the rightmost occurrence of pattern t in s. Returns
 * index in s if there is a match, otherwise -1. */
int strrindex(char s[], char t[])
{
     int i, j, k;

     for (i = strlen(s)-1; i >= 0; --i) {
	  for (j=i, k=strlen(t)-1; j>0 && k>0 && s[j]==t[k]; --j, --k)
	       ;
	  if (k == 0 && s[j] == t[k])
	       return j;
     }
     return -1;
}

void tests(void)
{
     printf("test strrindex:\n");
     {
	  printf("%d",  7 == strrindex("banana banana", "banana"));
	  printf("%d",  0 == strrindex("living large", "living"));
	  printf("%d",  5 == strrindex("moon bandits", "band"));
	  printf("%d",  0 == strrindex("driven", "drive"));
	  printf("%d",  10 == strrindex("driven to drive", "drive"));
	  printf("%d",  0 == strrindex("a b", "a"));
	  printf("%d", -1 == strrindex("no match", "none"));
	  printf("%d", -1 == strrindex("empty string", ""));
	  printf("%d", -1 == strrindex("bird", "birds"));

	  putchar('\n');
     }
}
