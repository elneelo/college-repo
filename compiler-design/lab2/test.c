#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


int getCurrentExponent (int n, int exponent) {
	int original = n;
	while (exponent > 1) {
		n *= original;
		printf("\n...n = %d", n);
		exponent--;
	}
	printf("\n***Number = %d", n);
	printf("\n");
	return n;
}


int main () {
	getCurrentExponent(8, 6);
}