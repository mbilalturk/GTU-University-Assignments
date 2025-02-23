#include <stdio.h>
#include <string.h>

#define SIZE 50

void part1();
void part3();
void foo_min_max(int arr[], int n);


int main(){

    part1();
    part3();

    return(0);
}

void part1(){
    char str[SIZE], ch, del_ch;
    int counter, times = 0, i,j, lenght=0;

    printf("Please enter a string: ");
    scanf("%s", str);
    printf("%s\n", str);

    while (strlen(str) > 1){
        /* Determine which character will be removed */
        printf("Which character will be removed: ");
        scanf(" %c", &del_ch);

        counter = 0;
        /* Count and check sequence of character */
        for(i=0; i<strlen(str); i++){
            if(del_ch == str[i]){
                counter++;
            }
            else{
                str[i-counter] = str[i];
            }
        }
        str[strlen(str)-counter] = '\0';
        printf("%s\n", str);
        /* Implement how many times deleted */
        times++;
    }
    printf("It is deleted in %d times!\n", times);
}

void part3(){
    int size, i;

    /* Take size of array */
    printf("How many number will you enter: ");
    scanf("%d", &size);
    int arr[size];
    
    /* Take numbers */
    printf("Enter number: ");
    for(i=0; i<size; i++){
        scanf("%d", &arr[i]);
    }    
    
    foo_min_max(arr, size);
}

void foo_min_max(int arr[], int n){
    int i;
    int max, min;
 
    max = arr[0];
    min = arr[0];
    for(i = 1; i < n ;i++){
        if(max < arr[i])
            max = arr[i];

        if(min > arr[i])
            min = arr[i];
    }

    printf("Min: %d\n", min);
    printf("Max: %d\n", max);
}

