/* Ex. 2-9: Explain why in a two's complement system the operation, x
 * &= (x-1), delets the rightmost 1-bit. Use this to write a faster
 * version of bitcount. */

/* Answer: In two's complement system when 1 is subtracted, we
 * actually add the number 1111 ... 1111, since that is how -1 is
 * represented. When adding ones to the number from right-to-left, we
 * will at some point hit the rightmost 1 bit. Until that time, the
 * result of adding -1 to the number will produce 1's. That is: */

/*   ... 0 0000  */
/* + ... 1 1111  */
/*   ----------  */
/*   ... 1 1111  */

/* This carries on until we hit the rightmost 1-bit. This will cause a
 * carry which in turn will cause carries until the end, since the
 * number -1 is all ones: */

/*   1 ... 1111 1100 ... 000  (carry) */
/*   v ... vvvv vvvv ... vvv   */
/*     ... 0101 0110 ... 0000  */
/* +   ... 1111 1111 ... 1111  */
/*   -----------------------   */
/*   1 ... 0101 0101 ... 1111  */

/* Since the leading 1 is ignored in two's complement, we have created
 * a mask that is made of ones until the rightmost 1-bit, value 0 at
 * the rightmost 1-bit, and then a copy of the number. Hence, the
 * bitwise AND (&) operation will perserve all 0s right of the
 * rightmost 1-bit, set the rightmost bit to 0, and then just leave
 * the rest of the bits unchanged. */

#include <stdio.h>

#define SIGNED_BITS (sizeof(signed) * 8)

int bitcount(signed x);

int main(void)
{
     printf("test: bitcount\n");
     {
	  printf("%d", 0               == bitcount(0));
	  printf("%d", 5               == bitcount(87));
	  printf("%d", SIGNED_BITS - 5 == bitcount(-1337));
	  printf("%d", SIGNED_BITS - 2 == bitcount(-41));
	  printf("%d", SIGNED_BITS     == bitcount(-1));
	  printf("%d", 5               == bitcount(107));

	  putchar('\n');
     }
     return 0;
}

int bitcount(signed x)
{
     int b;

     for (b = 0; x != 0; ++b)
	  x &= (x-1);
     return b;
}
