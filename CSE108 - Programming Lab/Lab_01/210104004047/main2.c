#include <stdio.h>

int main(){
    
    printf("------------- Part 2 ------------\n\n");

    float x, y, z;
    float max;

    printf("Please type two decimal number: \n");
    printf("x: ");
    scanf("%f", &x);
    printf("y: ");
    scanf("%f", &y);

    if(x > y){
        max = x;
    }
    else{
        max = y;
    }

    if(y == 0.0 || (x == (-1)*y)){
        printf("Undefined\n");
    }
    else{
        z = (x/y) + (max/(x+y)); 
        printf("z = %.2f\n", z);
    }

    return (0);
}