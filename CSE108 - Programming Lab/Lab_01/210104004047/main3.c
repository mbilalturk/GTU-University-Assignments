#include <stdio.h>

int main(){
    
    printf("------------- Part 3 ------------\n\n");

    int age, exp, salary;

    printf("Age: ");
    scanf("%d", &age);

    printf("Years of experience: ");
    scanf("%d", &exp);

    if(age < 20 && (exp > 0 && exp < 10)){
        printf("Salary: 10.000\n");
    }
    else if(age < 20 && exp > 10){
        printf("Error\n");
    }    
    else if((age > 20 && age < 50) && (exp > 0 && exp < 10)){
        printf("Salary: 15.000\n");
    }    
    else if((age > 20 && age < 50) && exp > 10){
        printf("Salary: 20.000\n");
    }
    else if(age > 50 && (exp > 0 && exp < 10)){
        printf("Salary: 20.000\n");
    }
    else if(age > 50 && exp > 10){
        printf("Salary: 25.000\n");
    }
    
    return (0);
}