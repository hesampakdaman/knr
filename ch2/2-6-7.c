/* Ex. 2-6: Write a function setbits(x,p,n,y) that sets n bits in x
 * starting from position p to the rightmost n bits in y, leaving
 * everything else in x unchanged. */

/* Ex. 2-7: Write a function invert(x,p,n) that inverts all n bits
 * beginning from position p. */

#include <stdio.h>

unsigned getbits(unsigned x, int p, int n);
unsigned intervones(unsigned x, int p, int n);
unsigned invert(unsigned x, int p, int n);
unsigned leftofones(unsigned x, int p);
unsigned onesouterv(unsigned x, int p, int n);
unsigned rightofones(unsigned x, int p);
unsigned setbits(unsigned x, int p, int n, unsigned y);
unsigned zerointerv(unsigned x, int p, int n);

int main(void)
{
     printf("test leftofones:\n");
     {
	  printf("%u", 4294967268  == leftofones(4, 4));
	  printf("%u", 4294966314 == leftofones(42, 9));
	  putchar('\n');
     }

     printf("test rightofones:\n");
     {
	  printf("%u", 43391 == rightofones(43265, 7));
	  printf("%u", 450559 == rightofones(449122, 13));
	  printf("%u", 4203175 == rightofones(4203170, 3));
	  printf("%u", 127 == rightofones(0, 7));

	  putchar('\n');
     }

     printf("test intervones:\n");
     {
	  printf("%u", 1792 == intervones(1792, 10, 3));
	  printf("%u", 1984 == intervones(0, 10, 5));
	  printf("%u", 2004 == intervones(20, 10, 5));
	  printf("%u", 7936 == intervones(3840, 12, 3));
	  putchar('\n');
     }

     printf("test zerointerv:\n");
     {
	  printf("%u", 51 == zerointerv(63, 3, 2));
	  printf("%u", 51 == zerointerv(1843, 10, 3));
	  putchar('\n');
     }

     printf("test onesouterv:\n");
     {
	  printf("%u", 4294967275 == onesouterv(42, 5, 5));
	  printf("%u", 4294959103 == onesouterv(20480, 14, 3));
	  putchar('\n');
     }

     printf("test setbits:\n");
     {
	  printf("%u", 1313  == setbits(1337, 5, 3, 4));
	  printf("%u", 15924 == setbits(564, 13, 4, 15));
	  printf("%u", 2040  == setbits(1792, 7, 5, 63));
	  printf("%u", 1974  == setbits(182, 10, 3, 7));
	  printf("%u", 8190  == setbits(4096, 12, 12, 4095));
	  printf("%u", 512   == setbits(3840, 11, 4, 2));

	  putchar('\n');
     }

     printf("test inverted:\n");
     {
	  printf("%u", 1351 == invert(1337, 6, 6));
	  printf("%u", 7523 == invert(355, 12, 3));
	  printf("%u", 983  == invert(551, 8, 5));
	  printf("%u", 21   == invert(42, 5, 6));
	  putchar('\n');
     }

     return 0;
}

unsigned invert(unsigned x, int p, int n)
{
     unsigned zeroiv;	    /* zero-out the interval to invert in x */
     unsigned flip;         /* flip the interval to invert in x, the rest set to zero */

     zeroiv = zerointerv(x, p, n);
     flip = ~onesouterv(x, p, n);
     return (zeroiv | flip);
}

/* zerointerv: set n bits in x to 0 starting from position p. */
unsigned zerointerv(unsigned x, int p, int n)
{
     return ~intervones(~x, p, n);
}

/* setbits: sets n bits of x beginning at position p to the rightmost
 * n bits in y, leaving the others unchanged. */
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
     unsigned copybits, mask, x_ones_interv;

     copybits = getbits(y, n-1, n) << (p+1 - n);
     mask = onesouterv(copybits, p, n);
     x_ones_interv = intervones(x, p, n);
     return x_ones_interv & mask;
}

/* getbits: get n bits from position p (taken from page 49). */
unsigned getbits(unsigned x, int p, int n)
{
     return (x >> (p+1 - n) & ~(~0 << n));
}

/* leftofones: sets all bits left of position p to 1. */
unsigned leftofones(unsigned x, int p)
{
     return (x | (~0 << (p+1)));
}

/* rightofones: sets all bits right of position p to 1. */
unsigned rightofones(unsigned x, int p)
{
     return (x | getbits(~0, p-1, p));
}

/* intervones: sets n bits in x to 1's starting from position
 * p. Example for x=0000 0101 1011 1100, p=7, n=4 ----------------->
 * 0000 0101 1111 1100.  */
unsigned intervones(unsigned x, int p, int n)
{
     unsigned onbits;

     onbits = rightofones(0, n) << (p+1 - n);
     return (x | onbits);
}

/* onesouterv: sets all bits in x to 1 except n bits starting from
 * position p.  Example for x=0000 0101 1011 1100, p=7, n=4 ------->
 * 1111 1111 1011 1111. */
unsigned onesouterv(unsigned x, int p, int n)
{
     x = leftofones(x, p);
     x = rightofones(x, p+1 - n);
     return x;
}
