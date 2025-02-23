#include <stdio.h>
#include "util.h"

void median_number(){
    int num1, num2, num3;
    int median;
    
    /* Get numbers from user */
    printf("Enter 3 integers: ");
    scanf("%d %d %d", &num1, &num2, &num3);

    /* Check which number is greter than others */
    if(num1 > num2){
        if(num2 > num3){
            median = num2;
        }
        else if(num1 < num3){
            median = num1;
        }
        else{
            median = num3;
        }
    }
    else{ 
        if(num1 > num3){
            median = num1;
        }
        else if(num2 < num3){
            median = num2;
        }
        else{
            median = num3;
        }
    }
    
    /* Print the median number */
    printf("Median number is %d\n", median);
}

void grade(){
    int grade1, grade2, grade3;
    char score1_1, score1_2, score2_1, score2_2, score3_1, score3_2; /* Declaratian for letter score */
    double grade_avg;

    /* Get grades from user */
    printf("Enter your scores: ");
    scanf("%d %d %d", &grade1, &grade2, &grade3);

    /* Calculate average grade */
    grade_avg = (grade1 + grade2 + grade3) / 3.0;

    /* Assign letter score into appropriate score variable to print them later for first grade */      
    switch(grade1){
        case 100:
        case 99:
        case 98:
        case 97:
        case 96:
        case 95:
        case 94:
        case 93:
        case 92:
        case 91:
        case 90:
                score1_1 = 'A';
                score1_2 = '+';
                break;
        case 89:
        case 88:
        case 87:
        case 86:
        case 85:
        case 84:
        case 83:
        case 82:
        case 81:
        case 80:
                score1_1 = 'A';
                break;
        case 79:
        case 78:
        case 77:
        case 76:
        case 75:
        case 74:
        case 73:
        case 72:
        case 71:
        case 70:
                score1_1 = 'B';
                score1_2 = '+';
                break;
        case 69:
        case 68:
        case 67:
        case 66:
        case 65:
        case 64:
        case 63:
        case 62:
        case 61:
        case 60:
                score1_1 = 'B';
                break;
        case 59:
        case 58:
        case 57:
        case 56:
        case 55:
        case 54:
        case 53:
        case 52:
        case 51:
        case 50:
                score1_1 = 'C';
                break;
        case 49:
        case 48:
        case 47:
        case 46:
        case 45:
        case 44:
        case 43:
        case 42:
        case 41:
        case 40:
                score1_1 = 'D';
                break;
        case 39:
        case 38:
        case 37:
        case 36:
        case 35:
        case 34:
        case 33:
        case 32:
        case 31:
        case 30:
        case 29:
        case 28:
        case 27:
        case 26:
        case 25:
        case 24:
        case 23:
        case 22:
        case 21:
        case 20:
        case 19:
        case 18:
        case 17:
        case 16:
        case 15:
        case 14:
        case 13:
        case 12:
        case 11:
        case 10:
        case 9:
        case 8:
        case 7:
        case 6:
        case 5:
        case 4:
        case 3:
        case 2:
        case 1:
        case 0:
                score1_1 = 'F';
                break;
    }

    /* Assign letter score into appropriate score variable to print them later for second grade */      
    switch(grade2){
        case 100:
        case 99:
        case 98:
        case 97:
        case 96:
        case 95:
        case 94:
        case 93:
        case 92:
        case 91:
        case 90:
                score2_1 = 'A';
                score2_2 = '+';
                break;
        case 89:
        case 88:
        case 87:
        case 86:
        case 85:
        case 84:
        case 83:
        case 82:
        case 81:
        case 80:
                score2_1 = 'A';
                break;
        case 79:
        case 78:
        case 77:
        case 76:
        case 75:
        case 74:
        case 73:
        case 72:
        case 71:
        case 70:
                score2_1 = 'B';
                score2_2 = '+';
                break;
        case 69:
        case 68:
        case 67:
        case 66:
        case 65:
        case 64:
        case 63:
        case 62:
        case 61:
        case 60:
                score2_1 = 'B';
                break;
        case 59:
        case 58:
        case 57:
        case 56:
        case 55:
        case 54:
        case 53:
        case 52:
        case 51:
        case 50:
                score2_1 = 'C';
                break;
        case 49:
        case 48:
        case 47:
        case 46:
        case 45:
        case 44:
        case 43:
        case 42:
        case 41:
        case 40:
                score2_1 = 'D';
                break;
        case 39:
        case 38:
        case 37:
        case 36:
        case 35:
        case 34:
        case 33:
        case 32:
        case 31:
        case 30:
        case 29:
        case 28:
        case 27:
        case 26:
        case 25:
        case 24:
        case 23:
        case 22:
        case 21:
        case 20:
        case 19:
        case 18:
        case 17:
        case 16:
        case 15:
        case 14:
        case 13:
        case 12:
        case 11:
        case 10:
        case 9:
        case 8:
        case 7:
        case 6:
        case 5:
        case 4:
        case 3:
        case 2:
        case 1:
        case 0:
                score2_1 = 'F';
                break;
    }

    /* Assign letter score into appropriate score variable to print them later for third grade */      
    switch(grade3){
        case 100:
        case 99:
        case 98:
        case 97:
        case 96:
        case 95:
        case 94:
        case 93:
        case 92:
        case 91:
        case 90:
                score3_1 = 'A';
                score3_2 = '+';
                break;
        case 89:
        case 88:
        case 87:
        case 86:
        case 85:
        case 84:
        case 83:
        case 82:
        case 81:
        case 80:
                score3_1 = 'A';
                break;
        case 79:
        case 78:
        case 77:
        case 76:
        case 75:
        case 74:
        case 73:
        case 72:
        case 71:
        case 70:
                score3_1 = 'B';
                score3_2 = '+';
                break;
        case 69:
        case 68:
        case 67:
        case 66:
        case 65:
        case 64:
        case 63:
        case 62:
        case 61:
        case 60:
                score3_1 = 'B';
                break;
        case 59:
        case 58:
        case 57:
        case 56:
        case 55:
        case 54:
        case 53:
        case 52:
        case 51:
        case 50:
                score3_1 = 'C';
                break;
        case 49:
        case 48:
        case 47:
        case 46:
        case 45:
        case 44:
        case 43:
        case 42:
        case 41:
        case 40:
                score3_1 = 'D';
                break;
        case 39:
        case 38:
        case 37:
        case 36:
        case 35:
        case 34:
        case 33:
        case 32:
        case 31:
        case 30:
        case 29:
        case 28:
        case 27:
        case 26:
        case 25:
        case 24:
        case 23:
        case 22:
        case 21:
        case 20:
        case 19:
        case 18:
        case 17:
        case 16:
        case 15:
        case 14:
        case 13:
        case 12:
        case 11:
        case 10:
        case 9:
        case 8:
        case 7:
        case 6:
        case 5:
        case 4:
        case 3:
        case 2:
        case 1:
        case 0:
                score3_1 = 'F';
                break;
    }

    /* Print letter grade with an average */
    printf("Your letters are %c%c, %c%c, and %c%c with an %.1lf average.\n", score1_1, score1_2, score2_1, score2_2, score3_1, score3_2, grade_avg);
}

void calculator(){
    char operation;
    int num1, num2;
    double user_result, result; /* Declaration of real result and result will be got from user */

    /* Get operation from user */
    printf("Enter an aritmetic operation (+, -, *, /): ");
    scanf("%c", &operation);

    /* Get two numbers from user */
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);

    /* Get result from user */
    printf("Result: ");
    scanf("%lf", &user_result);

    /* Check operation which had got from user to calculate result */
    switch(operation){
        case '+':
                result = num1 + num2;
                break;
        case '-': 
                result = num1 - num2;
                break;
        case '*': 
                result = num1 * num2;
                break;
        case '/':
                if(num2 == 0){
                        print("Denominator can't be zero!\n");
                }
                else{
                result = num1 / num2;
                }
                break;
        default : 
                printf("Invalid operation!\n");
    }

    /* Check if result getting from user is equal to real result and print a message */
    if(user_result == result){
        printf("Bravo, correct answer!\n");
    }
    else{
        printf("Wrong answer, try again.\n");
    }
}