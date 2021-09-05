#ifndef _COMMON_FUNC_H_
#define _COMMON_FUNC_H_

typedef struct {
	int numerator;
	int denominator;
	int gcd;
} fraction;

int convert();

void binary(int x);

fraction reduce_fraction(int u, int v, int (*gcd)(int u, int v));

int gcd(int u, int v);

int gcd_three(int u, int v, int w);

void sort(int u, int v, int w);

#endif