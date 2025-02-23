#include <stdio.h>

int main(){

    printf("------------- Part 1 ------------\n\n");

    int num, remainder = 1, range = 0;
    int i;

    printf("Please type a number between 1 and 100: ");
    scanf("%d", &num);

    while(num < 0 || num > 100){
        printf("\nError! This number is not between 1 and 100.\n\n");
        break;
    }

    while(num > 0 && num < 100){
        while(num % 3 == 0){
            remainder = 0;
            break;
        }

        while(num > 5 && num < 50){
            range = 1;

            if(remainder == 0){
                printf("FizzBuzz\n");
            }
            else{
                printf("Buzz\n");
            }
            break;
        }

        if(remainder == 0 && range != 1){
            printf("Fizz\n");
        }
        break;
    }

    return (0);
}