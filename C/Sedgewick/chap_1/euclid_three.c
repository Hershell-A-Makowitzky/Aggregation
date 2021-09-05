#include <stdio.h>

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

void sort(int u, int v, int w) {
	int tmp;
	if (u < v) { tmp = u; u = v; v = tmp; } 
	if (u < w) { tmp = u; u = w; w = v; v = tmp; }
	if (v < w) { tmp = v; v = w; w = tmp; }
}

int gcd_three(int u, int v, int w) {
	int result;
	sort(u, v, w);
	result = gcd(u, v);
	if (result == 1) return 1;
	return gcd(result, w);
}

int main(void) {
	int u, v, w;
	first_line:
	printf("Insert value for first number: ");
	if (scanf("%d", &u) <= 0) {
		fpurge(stdin);
		printf("Invalid input\n");
		goto first_line;
	}
	second_line:
	printf("Insert value for second number: ");
	if (scanf("%d", &v) <= 0) {
		fpurge(stdin);
		printf("Invalid input\n");
		goto second_line;
	}
	third_line:
	printf("Insert value for third number: ");
	if (scanf("%d", &w) <= 0) {
		fpurge(stdin);
		printf("Invalid input\n");
		goto third_line;
	}
	printf("Greatest common divider: %i\n", gcd_three(u, v, w));
	return 0;
}
