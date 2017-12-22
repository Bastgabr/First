#include <stdlib.h>
#include <stdio.h>

void main(void)
{
	int iA;
	int iB;


	// iA + iB
	iA = 5;
	iB = 9;
	printf("iA + iB = %d\n", iA + iB);


	// iA - iB
	iA = 10;
	iB = 7;
	printf("iA - iB = %d\n", iA - iB);

	// iA / iB
	iA = 5;
	iB = 9;
	printf("iA / iB = %2.2f\n", (float)iA / iB); // float and %f because the result is a float  // %2.2 to show 2 numbers after the floating point

	// iA / iB
	iA = 12;
	iB = 5;
	printf("iA / iB = %2.2f\n", (float)iA / iB);

	// iA * iB
	iA = 8;
	iB = 7;
	printf("iA * iB = %d\n", iA * iB);

	// iA % iB
	iA = 11;
	iB = 3;
	printf("iA %% iB = %d\n", iA % iB); // modulo operation = rest of the division between the two int


	// iA++
	iA = 5;
	printf("iA ++ = %d\n", iA++); //when ++ is placed after the variable, operation is done after the printf

	// ++iA
	iA = 5;
	printf("++iA  = %d\n", ++iA); //when ++ is placed before the variable, operation is done before the printf

	// iB--
	iB = 10;
	printf("iB -- = %d\n", iB--); //idem 

	// --iB
	iB = 10;
	printf("--iB  = %d\n", --iB); //idem

	getch();

}