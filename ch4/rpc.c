/* Ex. 4-5 (p. 79): Add access to math.h library funs like sin, exp
 * and pow. */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>		/* for atof() */
#include <string.h>		/* strcmp */

#define MAXOP	100		/* max size of operand or operator */
#define NUMBER	'0' 		/* signal that a number was found */
#define MATH	'1' 		/* use math.h lib */

int getop(char[]);
void push(double);
double pop(void);
void print_top(void);
void duplicate_top(void);
void swap(void);
double math_fn(double, char[]);

/* reverse Polish calculator */
int main(void)
{
     int type;
     double op2;
     char s[MAXOP];

     while ((type = getop(s)) != EOF) {
	  switch (type) {
	  case NUMBER:
	       push(atof(s));
	       break;
	  case '+':
	       push(pop() + pop());
	       break;
	  case '*':
	       push(pop() * pop());
	       break;
	  case '-':
	       op2 = pop();
	       push(pop() - op2);
	       break;
	  case '/':
	       op2 = pop();
	       if (op2 != 0.0)
		    push(pop() / op2);
	       else
		    printf("error: zero divisor\n");
	       break;
	  case '%':
	       op2 = pop();
	       if (op2 != 0.0)
		       push((int) pop() % (int) op2);
	       else
		    printf("error: modulu by zero\n");
	       break;
	  case 'p':
	       print_top();
	       break;
	  case 'd':
	       duplicate_top();
	       break;
	  case 's':
	       swap();
	       break;
	  case MATH:
	       push(math_fn(pop(), s));
	       break;
	  case '\n':
	       printf("\t%.8g\n", pop());
	       break;
	  default:
	       printf("error: unknown command %s\n", s);
	       break;
	  }
     }
     return 0;
}

#define MAXVAL	100		/* maximum depth of val stack */

int sp = 0;
double val[MAXVAL];		/* value stack */

/* push: push f onto value stack */
void push(double f)
{
     if (sp < MAXVAL)
	  val[sp++] = f;
     else
	  printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
     if (sp > 0)
	  return val[--sp];
     else {
	  printf("error: stack empty\n");
	  return 0.0;
     }
}

void print_top(void)
{
     extern int sp;

     if (sp > 0)
	  printf("Top of stack is: %g\n" , val[0]);
}

void duplicate_top(void)
{
     extern int sp;
     extern double val[MAXVAL];
     int i;
     double dup[MAXVAL];

     if (sp > 0) {
	  dup[0] = dup[1] = val[0];
	  for (i = 0; i < sp; ++i)
	       dup[i+2] = val[i];
	  sp += 1;
	  for (i = 0; i < sp; ++i)
	       val[i] = dup[i];
     }
}

void swap(void)
{
     extern int sp;
     extern double val[MAXVAL];
     double f;

     if (sp > 1)
	  f = val[0], val[0] = val[1], val[1] = f;
}

double math_fn(double x, char type[])
{
     if (strcmp(type, "sin") == 0)
	  return sin(x);
     else if (strcmp(type, "cos") == 0)
	  return cos(x);
     else if (strcmp(type, "tan") == 0)
	  return tan(x);
     else if (strcmp(type, "exp") == 0)
	  return exp(x);
     else if (strcmp(type, "pow") == 0)
	  return pow(pop(), x);
     else if (strcmp(type, "sqrt") == 0)
	  return sqrt(x);
     else
	  printf("error: unknown operation %s\n", type);
     return 0.0;
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next operator numeric operand */
int getop(char s[])
{
     int i, c, type;
     extern int sp;

     while ((s[0] = c = getch()) == ' ' || c == '\t')
	  ;
     s[1] = '\0';
     if (!isalnum(c) && c != '.' && c != '-')
	  return c;
     else if (c == '-' && sp > 1 && sp % 2 == 0)
	  return c;
     else if(isalpha(c)) {
	  i = 0;
	  while (isalpha(s[++i] = c = getch()))
	       ;
	  if (i == 1) {
	       type = s[0];
	  }
	  else
	       type = MATH;
     } else if (isdigit(c)){
	  type = NUMBER;
	  i = 0;
	  if (isdigit(c) || c == '-')
	       while (isdigit(s[++i] = c = getch()))
		    ;
	  if (c == '.')
	       while (isdigit(s[++i] = c = getch()))
		    ;
     }
     s[i] = '\0';
     if (c != EOF)
	  ungetch(c);
     return type;
}

#define BUFSIZE 100

char buf[BUFSIZE]; 		/* buffer for ungetch */
int bufp = 0;			/* next free position in buf */

int getch(void)			/* get a (possibly pushed back) character */
{
     return (bufp > 0)? buf[--bufp] : getchar();
}

void ungetch(int c)		/* push caracter back on input */
{
     if (bufp >= BUFSIZE)
	  printf("ungetch: too many characters\n");
     else
	  buf[bufp++] = c;
}
