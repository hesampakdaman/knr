/* Ex. 4-2 (p. 73): Extend atof to handle scientific notation, such as
 * 1.2e5 or 1.2E5. */

#include <stdio.h>
#include <ctype.h>

void tests(void);
double atof(char s[]);

int main(void)
{
     tests();
     return 0;
}

/* atof (p. 71): convert string s to double */
double atof(char s[])
{
     double val, power;
     int i, j, sign;

     for (i = 0; isspace(s[i]); i++) /* skip white space */
	  ;
     sign = (s[i] == '-') ? -1 : 1;
     if (s[i] == '+' || s[i] == '-')
	  i++;
     for (val = 0.0; isdigit(s[i]); i++)
	  val = 10.0 * val + (s[i] - '0');
     if (s[i] == '.')
	  i++;
     for (power = 1.0; isdigit(s[i]); i++) {
	  val = 10.0 * val + (s[i] - '0');
	  power *= 10.0;
     }
     if (tolower(s[i]) == 'e') {
	  ++i;
	  if (s[i] == '-') {
	       ++i;
	       for (j = 0; j < (s[i] - '0'); j++)
		    power *= 10.0;
	  } else {
	       for (j = 0; j < (s[i] - '0'); j++)
		    power /= 10.0;
	  }

     }
     return sign * val / power;
}

void tests(void)
{
     printf("test (extended) atof:\n");
     {
	  printf("%d", atof("1e2") == 100.0);
	  printf("%d", atof("123.45e-6") == 0.00012345);
	  printf("%d", atof("  1337E3  ") == 1337000.0);
	  printf("%d", atof("0.00243") == 0.00243);
	  printf("%d", atof("243E-5") == 0.00243);

	  putchar('\n');
     }
}
