#include <stdio.h>
#include "common_functions.h"

int convert() {
	puts("Input one digit and hit ENTER");
	char input;
	input = getchar();
	if (input > 47 && input < 58) return input - 48;
	return -1;
}

void binary(int x) {
    	int i = x;
	int j = 1;
	while ((i >>= 1) > 0) {
	    j <<= 1;
	}
	printf("Number %d in binary is: 0b", x);
	for (; j > 0; j >>= 1) {
		(x & j) > 0 ? printf("1") : printf("0");
	}
	printf("\n");
}

fraction reduce_fraction(int u, int v, int (*gcd)(int u, int v)) {
	int divider = gcd(u, v);
	fraction fr = { u/divider, v/divider, divider };
	return fr;
}

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

int gcd_three(int u, int v, int w) {
	int result;
	sort(u, v, w);
	result = gcd(u, v);
	if (result == 1) return 1;
	return gcd(result, w);
}

void sort(int u, int v, int w) {
	int tmp;
	if (u < v) { tmp = u; u = v; v = tmp; }
	if (u < w) { tmp = u; u = w; w = v; v = tmp; }
	if (v < w) { tmp = v; v = w; w = tmp; }
}
