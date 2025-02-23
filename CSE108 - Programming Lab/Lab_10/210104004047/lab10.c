#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000

typedef struct Student{
    int ID;
    int age;
    float gpa;
} Student;

int * memory_allocated(int size);
float find_avg();

int main(){
    /* PART 1 */
    printf("******* PART 1 *******\n");
    int *ip;
    int size, min, i;

    printf("Enter the size of the array: ");
    scanf("%d", &size);

    ip = memory_allocated(size);

    min = ip[0];
    for(i=0; i<size; i++){
        if(min>ip[i]){
            min = ip[i];
        }
    }
    printf("Min of the array elements: %d\n", min);

    free(ip);

    /* PART 2 */
    printf("\n******* PART 2 *******\n");
    int *ip2, *ip3;
    int size2, j;

    printf("Enter the number of integers: ");
    scanf("%d", &size2);

    ip2 = memory_allocated(size2);
    ip3 = (int *) calloc(size2, sizeof(int));

    for(i=0; i<size2; i++){
        for(j=0; j<=i; j++){
            ip3[i] += ip2[j]; 
        }
    }

    printf("First array: ");
    for(i=0; i<size2; i++){
        printf("%d ", ip2[i]);
    }
    printf("\nSecond array (cumulative sum): ");
    for(i=0; i<size2; i++){
        printf("%d ", ip3[i]);
    }
    printf("\n");

    free(ip2);
    free(ip3);

    /* PART 3 */
    printf("\n******* PART 3 *******\n");
    float avg_gpa=0;

    srand(time(NULL));

    for(i=0; i<SIZE; i++){
        avg_gpa += find_avg();
    }
    avg_gpa /= SIZE;
    printf("Average GPA of %d x %d students: %.6f\n", SIZE, SIZE, avg_gpa);
    return (0);
}

int * memory_allocated(int size){
    int * ip;
    int i;

    ip = (int *) calloc(size, sizeof(int));

    printf("Enter the elements of the array: ");
    for(i=0; i<size; i++)
        scanf("%d", &ip[i]);

    return ip;
}

float find_avg(){
    Student * students;
    int i;
    float avg_gpa = 0.0;
    
    students = (Student *) calloc(SIZE,sizeof(Student));

    for(i=0; i<SIZE; i++){
        students[i].ID = rand() % SIZE;
        students[i].age = rand() % 10;
        students[i].age += 18;
        students[i].gpa = ((float)rand()/RAND_MAX)*4.0;
    }

    for(i=0; i<SIZE; i++){
        avg_gpa += students[i].gpa;
    }
    avg_gpa /= SIZE;
    
    free(students);
    return avg_gpa;
}