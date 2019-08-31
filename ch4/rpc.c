/* Ex. 4-4 (p. 79): Add commands to print top of stack without popping
 * it, to duplicate it and to swap the top two elements. */

#include <stdio.h>
#include <stdlib.h>		/* for atof() */

#define MAXOP	100		/* max size of operand or operator */
#define NUMBER	'0' 		/* signal that a number was found */

int getop(char[]);
void push(double);
double pop(void);
void print_top(void);
void duplicate_top(void);

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

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next operator numeric operand */
int getop(char s[])
{
     int i, c;
     extern int sp;

     while ((s[0] = c = getch()) == ' ' || c == '\t')
	  ;
     s[1] = '\0';
     if (!isdigit(c) && c != '.' && c != '-')
	  return c;
     else if (c == '-' && sp > 1 && sp % 2 == 0)
	  return c;
     i = 0;
     if (isdigit(c) || c == '-')
	  while (isdigit(s[++i] = c = getch()))
	       ;
     if (c == '.')
	  while (isdigit(s[++i] = c = getch()))
	  ;
     s[i] = '\0';
     if (c != EOF)
	  ungetch(c);
     return NUMBER;
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
