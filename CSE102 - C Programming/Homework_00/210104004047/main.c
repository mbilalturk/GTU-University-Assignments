#include <stdio.h>
#include "util.h"


int main() {

    /* A fractional number: 13/7 */
    int num1 = 13, den1 = 7;
    /* A second fractional number: 30/11 */
    int num2 = 30, den2 = 11;
    /* An unitilized fractional number */
    int num3, den3;
    /* Declaration for numbers which will be got */
    int fnum, fden, snum, sden;

    printf("First number: ");
    fraction_print(num1, den1);
    printf("\n");

    printf("Second number: ");
    fraction_print(num2, den2);
    printf("\n");

    printf("Addition: ");
    fraction_add(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Subtraction: ");
    fraction_sub(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Multiplication: ");
    fraction_mul(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Division: ");
    fraction_div(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n\n");

    /* etting input from user */
    printf("Please enter numerator of first number: ");
    scanf("%d", &fnum);

    printf("Please enter denominator of first number: ");
    scanf("%d", &fden);

    printf("Please enter numerator of second number: ");
    scanf("%d", &snum);

    printf("Please enter denominator of second number: ");
    scanf("%d", &sden);
    printf("\n");

    /* Denominator cannot be zero. Checking if denominator is 0 */
    if(fden == 0 || sden == 0){
        printf("Please enter a number other than 0 for the denominator!\n");
    }
    else{
        /* Displaying the results */
        printf("First number: ");
        fraction_print(fnum, fden);
        printf("\n");

        printf("Second number: ");
        fraction_print(snum, sden);
        printf("\n");

        printf("Addition: ");
        fraction_add(fnum, fden, snum, sden, &num3, &den3);
        fraction_print(num3, den3);
        printf("\n");

        printf("Subtraction: ");
        fraction_sub(fnum, fden, snum, sden, &num3, &den3);
        fraction_print(num3, den3);
        printf("\n");

        printf("Multiplication: ");
        fraction_mul(fnum, fden, snum, sden, &num3, &den3);
        fraction_print(num3, den3);
        printf("\n");

        printf("Division: ");
        fraction_div(fnum, fden, snum, sden, &num3, &den3);
        fraction_print(num3, den3);
        printf("\n");
    }
    
    return(0);
}
