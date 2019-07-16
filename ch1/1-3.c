/* Ex 1-3 (p. 13): Modify the Farenheit to Celsius program to print a
 * heading above the table. */

#include <stdio.h>

int main() {
     float fahr, celsius;
     int lower, upper, step;

     lower = 0;
     upper = 300;
     step = 20;
     printf("|-------------------|\n");
     printf("| %s | %s |\n", "Farenh.", "Celsius");
     printf("|-------------------|\n");
     fahr = lower;
     while (fahr <= upper) {
	  celsius = 5.0 / 9.0 * (fahr - 32.0);
	  printf("|%7.0f  | %7.1f |\n", fahr, celsius);
	  fahr += step;
     }
     printf("|_________|_________|\n");
}
