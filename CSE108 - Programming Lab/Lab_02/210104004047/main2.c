#include <stdio.h>

int main(){

    float height, weight, BMI;

    /* Getting weight, height from user */
    printf("----------- PART 2 -----------\n\n");
    printf("Enter your weight(kg): ");
    scanf("%f", &weight);

    printf("Enter your height(m): ");
    scanf("%f", &height);

    /* Calculating BMI by using given formula */
    BMI = weight / (height * height);
    printf("BMI is %.1f!\n", BMI);

    /* Printing the result */
    if(BMI < 18.5){
        printf("Underweight\n");
    }
    else if(BMI >= 18.5 && BMI <= 24.9){
        printf("Avarage weight\n");
    }
    else if(BMI >= 25 && BMI <= 29.9){
        printf("Overweight\n");
    }
    else if(BMI >= 30){
        printf("Obese\n");
    }

    return (0);
}