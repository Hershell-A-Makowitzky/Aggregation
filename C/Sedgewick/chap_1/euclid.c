#include <stdio.h>
#include <limits.h>
#include "common_functions.h"

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

    	/*int w = convert();
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
        	printf("Max int value %d\n", INT_MAX);
        	return 0;*/
}
