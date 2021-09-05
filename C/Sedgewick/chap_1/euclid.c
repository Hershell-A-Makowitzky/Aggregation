#include <stdio.h>
#include "max_int_size.h"

int gcd(int u, int v) {
	int t;
	if (u < 0) u *= -1;
	if (v < 0) v *= -1;
	while (u > 1) {
		if (u < v) {
			t = u; u = v; v = t;		
		}
		u = u % v;
	}
	return u == 0 ? v : 1;
}

int main(void) {
	int u, v;
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
	printf("Greatest common devider: %i\n", gcd(u, v));
	/*printf("Greatest uint32 value: %u\n", _uint32);*/
	return 0;
}
