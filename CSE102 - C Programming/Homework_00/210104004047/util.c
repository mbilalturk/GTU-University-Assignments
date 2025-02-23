#include <stdio.h>
#include "util.h"

void fraction_print(int numerator, int denominator) {
    printf("%d//%d", numerator, denominator);
}  /* end fraction_print */

void fraction_add(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2 + n2*d1;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_add */

void fraction_sub(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2 - n2*d1;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_sub */

void fraction_mul(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*n2;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_mul */

void fraction_div(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2;
    *d3 = d1*n2;
    fraction_simplify(n3, d3);
} /* end fraction_div */

/* Simplify the given fraction such that they are divided by their GCD */
void fraction_simplify(int * n, int * d) {

    int i = 2, gcd = 1;

    /* Checking if numerator of the result is negative so that the result of the fraction will be siplified. */
    /* If numerator of the result is negative, converts it into positive and simplify by dividing their gcd. */
    /* Then converts it into negative number. */
    if(*n < 0){
        *n = (-1)*(*n);

        while(i<=*n){
            if(*n % i == 0 && *d % i == 0){
                gcd *= i; 
                *n = *n / i;
                *d = *d / i;
            }
            else{
                i++;
            }
        }
        *n = (-1)*(*n);
    }

    /* Checking both the numerator and denominator are 0 to understand the result is undefined. */
    else if(*n == 0 && *d == 0){
        printf("Undefined ");
    }

    /* Checking both the numerator and denominator are equal to simplify easily. */
    // else if(*n == *d){
    //     *n = 1;
    //     *d = 1;
    // }
    
    /* If the numerator of the result is greater than 0, simplify the numerator and denominator by dividing their gcd. */
    else{
        while(i<=*n){
            if(*n % i == 0 && *d % i == 0){
                gcd *= i;
                *n = *n / i;
                *d = *d / i;
            }
            else{
                i++;
            }
        }
    }

    /* If both the numerator and denominator are negative, convert them into positive number. */
    if(*n < 0 && *d < 0){
        *n = (-1)*(*n);
        *d = (-1)*(*d);
    }
}
