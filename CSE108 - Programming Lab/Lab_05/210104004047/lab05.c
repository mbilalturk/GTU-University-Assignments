#include <stdio.h>

/* Part 1 */
void menu();
int choice();
void celsius_conversion(double fahrenheit);
void fahrenheit_conversion(double celsius);

/* Part 2 */
void reverse();

/* Part 3 */
void calculator();

int main(){

    /* Part 1 */
    menu();
    
    /* Part 2*/
    reverse();

    /* Part 3 */
    calculator();

    return(0);
}

void menu(){
    int times;
    
    /* Print menu */
    do{
        printf("Temperature Conversion Menu\n");
        printf("1. Convert Celsius to Fahrenheit\n");
        printf("2. Convert Fahrenheit to Celsius\n");
        printf("3. Quit\n");

        times = choice();
        printf("\n");
    }
    while(times != 3);
}

int choice(){
    int choice;
    double temperature;

    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);

    /* Call appropriate funtions */
    if(choice == 1 || choice == 2){
        printf("Enter the temperature value to convert: ");
        scanf("%lf", &temperature);
        if(choice == 1)
            fahrenheit_conversion(temperature);
        
        if(choice == 2)    
            celsius_conversion(temperature);
    }
    else if(choice == 3){
        printf("Goodbye!\n");
    }
    else
        printf("Invalid number!\n");

    return choice;
}

void celsius_conversion(double fahrenheit){
    double celsius;

    /* Calculate conversion and print */
    celsius = 5 * (fahrenheit-32) / 9;
    printf("%.2lf Fahrenheit = %.2lf Celsius\n", fahrenheit, celsius);

}

void fahrenheit_conversion(double celsius){
    double fahrenheit;

    /* Calculate conversion and print */
    fahrenheit = (celsius * 9) / 5 + 32;
    printf("%.2lf Celsius = %.2lf Fahrenheit\n", celsius, fahrenheit);

}

void reverse(){
    int number, digit = 0, i;
    int unit, ten, hundread, thousand, ten_thousand;

    /* Get number from user */
    printf("Enter a number (3, 4, or 5): ");
    scanf("%d", &number);

    /* Calculate number in digits to reverse */
    unit = number % 10;
    ten = (number % 100) / 10;
    hundread = (number % 1000) / 100;
    thousand = (number % 10000) / 1000;
    ten_thousand = (number % 100000) / 10000;

    /* Calculate number of digit to print */
    while (number > 0){
        number /= 10;
        digit++;
    } 

    /* Print the result by checking number of digit */
    if(digit == 5)
        printf("Reversed number: %d%d%d%d%d\n", unit, ten, hundread, thousand, ten_thousand);
    else if(digit == 4)
        printf("Reversed number: %d%d%d%d\n", unit, ten, hundread, thousand);
    else if(digit == 3)
        printf("Reversed number: %d%d%d\n", unit, ten, hundread);
    else
        printf("Invalid number!\n");

}

void calculator(){
    int choice, number, decimal, binary, octal, hexadecimal;

    /* Print the menu */
    printf("Menu:\n");
    printf("1. Convert a nmber to decimal, binary, octal, and hexadecimal\n");
    printf("2. Quit\n");

    /* Get choice from the user*/
    printf("Enter your choice: ");
    scanf("%d", &choice);

    /* Print the results */
    if (choice == 1){
        printf("Enter a number: ");
        scanf("%d", &number);

        printf("Decimal equivalent: %d\n", number);
        printf("Octal equivalent: %o\n", number);
        printf("Hexadecimal equivalent: %x\n", number);
        printf("\n");
    }
    else if( choice == 2){
        printf("Goodbye!\n");
    }
    else{
        printf("Invalid number!\n");
    }
}
