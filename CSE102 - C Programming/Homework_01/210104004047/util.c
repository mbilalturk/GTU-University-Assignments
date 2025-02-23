#include <stdio.h>
#include "util.h"

void calculate_gcd(){
    int n1, n2, gcd;
    int rem1, rem2; /* Definitions of variables holding numbers to use when calculating gcd*/

    /* Getting numbers from user */
    printf("----- Part 1 ------\n");
    printf("Please type two integers to calculate their GCD:\n");
    scanf("%d %d", &n1, &n2);

    /* Checking if numbers 2 is greater than numbers 1 to begin with greater one */
    if(n1<n2){
        int temp;
        
        temp = n1;
        n1 = n2;
        n2 = temp;
    }

    /* Calculating remainder of numbers that have been gotten from user and assign it into gcd */
    rem1 = n1 % n2;
    gcd = rem1;
    rem1 = n2 % rem1;

    /* Loop to get gcd by calculating remainder of numbers. It takes until rem1 is 0
       and assign previous number in rem2 which is gcd to gcd */
    while(rem1 != 0){
        rem2 = rem1;
        rem1 = gcd % rem1;
        gcd = rem2;
    }

    /* If gcd is negative convert it into positive because gcd can't be negative */
    if(gcd < 0){
        gcd = (-1)*(gcd);
    }  

    /* Printing numbers and gcd */
    printf("GCD of %d and %d is %d.\n", n1, n2, gcd);

}   /* End of calculate_gcd */


void calculate_sum(){
    int n1, n2, result;

    /* Getting numbers from user */
    printf("\n----- Part 2 ------\n");
    printf("First number : ");
    scanf("%d", &n1);

    printf("Second number: ");
    scanf("%d", &n2);

    /* Calculating sum of numbers */
    result = n1 + n2;

    /* Printing numbers an result */
    printf("Result:\n");
    printf("%12d\n%12d\n     +\n     -------\n%12d\n", n1, n2, result);

}   /* End of calculate_sum */


void calculate_multiplication(){
    int n1, n2;
    int units_digit, tens_digit, hundreds_digit; /* Definition of digits to understand how many digits the numbers are */
    int result, result1, result2, result3; /* Definition of results to print result */

    /* Getting numbers from user */
    printf("\n----- Part 3 ------\n");
    printf("First number : ");
    scanf("%d", &n1);

    printf("Second number: ");
    scanf("%d", &n2);
    
    /* Calculating which number is which digits */
    units_digit = n2 % 10;
    tens_digit = (n2 % 100) - units_digit;
    hundreds_digit = (n2 % 1000) - tens_digit - units_digit;

    /* Assigning results which are calculated into result variables to print */
    result1 = units_digit * n1;
    result2 = tens_digit * n1;
    result3 = hundreds_digit * n1;
    result = result1 + result2 + result3;

    /* Printing the multiplication by checking how many digits the numbers are */
    if(tens_digit == 0 && hundreds_digit == 0){
        printf("Result:\n");
        printf("%13d\n%13d\n   *\n   ----------\n%13d\n", n1, n2, result1);
    }
    else if(tens_digit != 0 && hundreds_digit == 0){
        printf("Result:\n");
        printf("%13d\n%13d\n   *\n   ----------\n%13d\n", n1, n2, result1);
        printf("%12d\n", result2 / 10);
        printf("   +\n   ----------\n%13d\n", result);
    }
    else if(tens_digit != 0 && hundreds_digit != 0){
        printf("Result:\n");
        printf("%13d\n%13d\n   *\n   ----------\n%13d\n", n1, n2, result1);
        printf("%12d\n", result2 / 10);
        printf("%11d\n", result3 / 100);
        printf("   +\n   ----------\n%13d\n", result);
    }

} /* End of calculate_multiplication */

void range(){
    int number;

    /* Getting numbers from user */
    printf("\n----- Part 4 ------\n");
    printf("Enter an integer between 1 and 10(inclusive): ");
    scanf("%d", &number);

    /* Checking numbers are in the range to print */
    if(number > 10 || number < 1){
        printf("Invalid input.\n");
    }
    else if(number > 5){
        printf("The integer you entered is greater than 5.\n");
    }
    else if(number <= 5){
        printf("The integer you entered is less or equal 5.\n");
    }

} /* End of range */