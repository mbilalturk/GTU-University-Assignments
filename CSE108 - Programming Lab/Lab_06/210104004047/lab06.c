#include <stdio.h>
#define SENTINEL_VALUE -100
#define SIZE 50

void read_input();
void odd_or_even(int array1[]);
void result(int array1[], char array2[]);

void part2();

int main(){
    read_input();
    printf("\n***** PART 2 *****\n");
    part2();
    return(0);
}

void read_input(){
    int i, array1[SIZE];

    /* Get number from user */
    for(i = 0; array1[i-1] != SENTINEL_VALUE; i++){
        printf("Enter a number: ");
        scanf("%d", &array1[i]);
    }

    /*Call odd_or_even() function */
    odd_or_even(array1);
}

void odd_or_even(int array1[]){
    int i;
    char array2[SIZE];

    /* Check the number if it is even assign 'e' to second array */
    for(i = 0; array1[i] != SENTINEL_VALUE; i++){
        if(array1[i] % 2 == 0){
            array2[i] = 'e';
        }    
        else{
            array2[i] = 'o';
        }
    }
    /* Call result() function */
    result(array1, array2);
}

void result(int array1[], char array2[]){
    int i;

    /* Print value of first array */
    for(i = 0; array1[i] != SENTINEL_VALUE; i++){
        printf("%d\n", array1[i]);
    }

    /* Print -100 which is last value of first array*/
    printf("%d\n", array1[i]);
    
    /* Print numbers with odd or even */
    for(i = 0; array1[i] != SENTINEL_VALUE; i++){
        printf("%d ", array1[i]);
        printf("%c\n", array2[i]);
    }
}

void part2(){
    FILE *filep = fopen("txt.txt", "r");
    /* Get lenght of row from file */
    int num;
    fscanf(filep, "%d", &num);

    int age[num];
    char occupation[num];
    float salary[num];
    char team[num];
    char steam, c;
    float avarage = 0;
    int i, counter = 0;     
    
    /* Get variables from file and assign them to array */
    for(i = 0; i<num; i++){
        fscanf(filep, "%d", &age[i]);
        printf("%d ", age[i]);
        c = fgetc(filep);

        fscanf(filep, "%c", &occupation[i]);
        printf("%c ", occupation[i]);
        c = fgetc(filep);

        fscanf(filep, "%f", &salary[i]);
        printf("%.2f ",salary[i]);
        c = fgetc(filep);

        fscanf(filep, "%c", &team[i]);
        printf("%c ", team[i]);
        printf("\n");
    }

    printf("Please select a team: ");
    scanf(" %c", &steam);  
    
    /* Check if team has been entered exist or not. If it is, implement counter */
    for(i = 0; i<num ;i++){
        if(steam == team[i]){
            avarage += salary[i];
            counter++;
        }
    }
    
    /* Print the result */
    if(counter > 0){
        avarage /= counter;
        printf("Avarage salaries of fans of f: %.1f\n", avarage);
    }
    else{
        printf("There are no fans of %c in the database!\n", steam);
    }
}