#include <stdio.h>
#include "max_int_size.h"

typedef struct {
	int numerator;
	int denominator;
	int gcd;
} fraction;

int gcd(int u, int v) {
	int t;
	if (u < 0) u *= -1;
	if (v < 0) v *= -1;
	while (u > 1) {
		if (u < v) {
			t = u; u = v; v = t;		
		}
		printf("%d/%d\n", u,v );
		u = u % v;
	}
	return u == 0 ? v : 1;
}

fraction reduce_fraction(int u, int v, int (*gcd)(int u, int v)) {
	int divider = gcd(u, v);
	fraction fr = { u/divider, v/divider, divider };
	return fr;
}

int convert() {
	puts("Input one digit and hit ENTER");
	char input;
	input = getchar();
	if (input > 47 && input < 58) return input - 48;
	return -1;
}

void binary(int x) {
	int i = 1;
	int j = x / 2 * 2;
	printf("Number %d in binary is: 0b", x);
	for (; x >= i; i *= 2, j >>= 1) {
		(x & j) > 0 ? printf("1") : printf("0");
	}
	printf("\n");
}

int main(void) {
	int w = convert();
	w < 0 ? puts("You didn't follow the instruction!") : printf("You've entered a '%d' digit\n", w);
	binary(65535);
	int u, v;
	int (*fp)(int u, int v) = gcd;
	first_line:
	printf("Insert value for numerator: ");
	if (scanf("%d", &u) <= 0) {
		fpurge(stdin);
		printf("Invalid input\n");
		goto first_line;
	}
	second_line:
	printf("Insert value for denominator: ");
	if (scanf("%d", &v) <= 0) {
		fpurge(stdin);
		printf("Invalid input\n");
		goto second_line;
	}
	fraction result = reduce_fraction(u, v, fp);
	printf("Greatest common divider: %i\n", result.gcd);
	printf("Reduced fraction from %d/%d to %d/%d\n", u, v, result.numerator, result.denominator);
	printf("Max int value %d\n", _int32);
	return 0;
}
