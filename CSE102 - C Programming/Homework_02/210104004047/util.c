#include <stdio.h>
#include <math.h>
#include "util.h"

void leap_year(){
    int year;
    
    /* Get the year from user */
    printf("**************************************\n");
    printf("Please enter a year: ");
    scanf("%d", &year);

    /* Check if the year is leap year or not */
    if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
        printf("%d is a leap year\n", year);
    }
    else{
        printf("%d is not a leap year\n", year);
    }

} /* End of leap_year */

void enhanced_cal(){
    char format;
    int m, n;
    char operation;
    
    /* Get the format from user */
    printf("**************************************\n");
    printf("Enter the format of output (S or I): ");
    scanf(" %c", &format);

    /* Check if the format is appropriate for calculation */
    if(format != 'S' && format != 's' && format != 'I' && format != 'i'){
        printf("Please enter appropriate format!\n");
    }
    /* If user type 'S' or 's' scientific calculation has been selected */
    else if(format == 'S' || format == 's'){
        /* Get m and n values from user */
        printf("Enter m and n values: ");
        scanf("%d %d", &m, &n);
        
        /* Check if n is greater than m */
        if(n > m){
            printf("n can't be greater than m!\n");
        }
        else{
            int count;
            double num1, num2, result;
            
            /* Get the operation from user */
            printf("Enter the operation(+,-,/,*,%%,!,^): ");
            scanf(" %c", &operation);

            /* Get first operand from user */
            printf("Enter the first operand: ");
            scanf("%lf", &num1);
            
            /* Get second operand from user and check if the operand is not factorial because there is no need for second operand to calculate */
            if(operation != '!'){
                printf("Enter the second operand: ");
                scanf("%lf", &num2);
            }

            switch (operation){
                case '+': /* Calculate result and print it by calling print_result function which is made for printing the result */
                        result = num1 + num2;
                        print_result(m, n, result);
                        break;

                case '-':
                        result = num1 - num2;
                        print_result(m, n, result);
                        break;

                case '*':
                        result = num1 * num2;
                        print_result(m, n, result);
                        break;

                case '/': /* Check if denominator is zero because denominator can't be zero */
                        if(num2 == 0){
                            printf("Denominator can't be 0!\n");
                        }
                        else{    
                            result = (num1 * 1.0) / (num2 * 1.0);
                            print_result(m, n, result);
                        }
                        break;

                case '!': /* Calculate factorial calculation by using loop */
                        result = 1;
                        for(count = num1; count > 1; count--){
                            result *= count;
                        }
                        print_result(m, n, result);
                        break;

                case '^': /* Calculate exponential calculation by using loop */
                        result = 1;
                        for(count = 1; count <= num2; count++){
                            result *= num1;
                        }
                        print_result(m, n, result);
                        break;

                case '%': /* Calculate remainder by using loop */
                        result = fmod(num1, num2);
                        print_result(m, n, result);
                        break;
                default: /* If user enter any operator which shouldn't be, print error */
                        printf("Invalid operator!\n");
            }
        }
    }
    /* If user type 'I' or 'i' ınteger format has been selected */
    else if(format == 'I' || format == 'i'){   
        int count;
        int num1, num2;
        double result;

        /* Get the operation from user */
        printf("Enter the operation(+,-,/,*,%%,!,^): ");
        scanf(" %c", &operation);

        /* Get first operand from user */
        printf("Enter the first operand: ");
        scanf("%d", &num1);

        /* Get second operand from user and check if the operand is not factorial because there is no need for second operand to calculate */
       if(operation != '!'){
            printf("Enter the second operand: ");
            scanf("%d", &num2);
        }

        switch (operation){
            case '+': /* Calculate result and print the result */
                    result = num1 + num2;
                    printf("%d + %d = %.0lf\n", num1, num2, result);
                    break;

            case '-':
                    result = num1 - num2;
                    printf("%d - %d = %.0lf\n", num1, num2, result);
                    break;

            case '*':
                    result = num1 * num2;
                    printf("%d * %d = %.0lf\n", num1, num2, result);
                    break;
            case '/': /* Check if denominator is zero because denominator can't be zero and print the result */
                    if(num2 == 0){
                        printf("Denominator can't be 0!\n");
                    }
                    else{
                        result = (num1 * 1.0) / (num2 * 1.0);
                        printf("%d / %d = %.2lf\n", num1, num2, result);
                    }
                    break;

            case '!': /* Calculate factorial calculation by using loop and print the result */
                    result = 1;
                    for(count = num1; count > 1; count--){
                        result *= count;
                    }
                    printf("%d! = %.0lf\n", num1, result);
                    break;

            case '^': /* Calculate exponential calculation by using loop and print the result */                    
                    result = 1;
                    for(count = 1; count <= num2; count++){
                        result *= num1;
                    }
                    printf("%d^%d=%.0lf\n", num1, num2, result);
                    break;

            case '%': /* Calculate remainder by using loop amd print the result */
                    result = num1 % num2;
                    printf("%d %% %d = %.0lf\n", num1, num2, result);
                    break;
            default: /* If user enter any operator which shouldn't be, print error */
                    printf("Invalid operator!\n");
        }
    }   
} /* End of enhanced_cal */

void print_result(int m, int n, double result){
    /* Declaration for printing scientific format */
    int digit = 0, counter = 0, zero_digit = 0, i;
    int result_int;
    
    /* Assing double result to integer result to calculate number of digit number has */
    result_int = result; 
    
    /* Check if double result equals to integer result */
    if(result_int == result){
        /* Calculate number of digit which is 0 to increment counter which is all digit */
        while(result_int % 10 == 0){
            result_int /= 10;
            zero_digit++;
        }
        
        /* calculate the number of digit by dividing by 10 until i equals to n + zero_digit */
        for(i = 0; i < n + zero_digit; i++){
            result /= 10;
            counter++;
        }
        /* Assign the value of counter to digit to warn user if m is greater than number of digit */
        digit = counter;
    }
    else{
        /* If double result is not equal to integer result, equal them by multiplying 10 */
        while(result != result_int){
            result *= 10;
            counter--; /* Counter get smaller because number which come after e^ deplements */
            result_int = result;                
        }

        /* Calculate number of total digit */
        for(i = 0; result_int > 0; i++){
            result_int /= 10;
            digit++;
        }

        /* Loop to move the number to least significant digit to start from there*/
        for(i = 0; i < n; i++){    
            result /= 10;
            counter++;
        }
    }
    
    /* Check if m is greater than number of digit. If it is, warn user */
    if(m >= digit){
        printf("Result: %0*.*lfe^%d\n", m+1, n, result, counter);
    }
    else{
        printf("m can't be greater than number of digits!\n");
    }
} /* End of print_result */

void grade_cal(){
    int exam1, exam2, exam3;
    int assignment1, assignment2;
    double final;

    /* Get exam results from user */
    printf("**************************************\n");
    printf("Enter 3 exam grades of student: ");
    scanf("%d %d %d", &exam1, &exam2, &exam3);

    /* Check if exam grades are less than 0 */
    if(exam1<0 || exam2<0 || exam3<0){
        printf("Enter positive exam grades!\n");
    }
    /* Check if exam grades are greater than 100 */
    else if(exam1>100 || exam2>100 || exam3>100){
        printf("Enter exam grades out of 100!\n");
    }
    else{
        /* Get assignment grades from user */
        printf("Enter 2 assignment grades of student: ");
        scanf("%d %d", &assignment1, &assignment2);

        /* Check if assignments are less than 0 */
        if(assignment1<0 || assignment2< 0){
            printf("Enter positive assignment grades!\n");
        }
        /* Check if assignments are greater than 100 */
        else if(assignment1>100 || assignment2>100){
            printf("Enter assignment grades out of 100!\n");
        }
        else{
            /* Calculate final grade with grades of students */
            final = ((exam1 + exam2 + exam3) / 3) * 0.6 + ((assignment1 + assignment2) / 2) * 0.4;

            /* Print result by checking if final grade greater than 60 */
            if(final >= 60){
                printf("Final Grade: %.1lf Passed!\n", final);
            }
            else{
                printf("Final Grade: %.1lf Failed!\n", final);
            }
        }
    }
} /* End of grade_cal */