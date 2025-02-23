#include <stdio.h>

void menu();
void read_the_sequence_of_shapes();
void write_sequence_of_the_shape();
void draw_square(int size);
void draw_triangle(int size);

int main(){

    menu();
    
    return (0);
}

void menu(){
    int option;
    printf("Welcome to Shaper Reader! Please make your choice to continue: \n");
    printf("1-) Generate a shape file\n");
    printf("2-) Read and draw a shale file\n");
    printf("3-) Terminate the program\n");

    scanf("%d", &option);

    /* Check the option to continue what to do */
    switch(option){
        case 1:
            write_sequence_of_the_shape();
            break;
        case 2:
            read_the_sequence_of_shapes();
            break;
        case 3:
            printf("Goodbye!\n");
            break;
    }
}

void read_the_sequence_of_shapes(){
    int size, n = 1;
    char shape;
    /* Open the file to read */
    FILE *finput = fopen("text.txt", "r");

    /* Get input from file to execute */
    while(n>0){
        n = fscanf(finput,"%c%*c%d\n", &shape, &size);
        printf("%c,%d\n", shape, size);

        /* Check which shape will be display */
        if(shape == 's')
            draw_square(size);
        else if(shape == 't')
            draw_triangle(size);
        else
            printf("Error! Invalid shape!\n");
        
        printf("\n");
    }
}

void write_sequence_of_the_shape(){
    char shape_type;
    int size;
    /* Open the file to apperand */
    FILE *foutput = fopen("text.txt", "a+");

    /* Get the shape and size to print to file */
    printf("Enter shapee type (square: 's', triangle: 't') and size (between 3 - 10): \n");
    scanf(" %c, %d", &shape_type, &size);

    if(size < 3 || size > 10){
        printf("Error ! Invalid numbers!\n");
    }
    else{
    /* Get the shape and size to print to file until typing 'e' */
        while(shape_type != 'e'){
            fprintf(foutput, "%c, %d\n", shape_type, size);
            scanf(" %c, %d", &shape_type, &size);
        }
    }
}

void draw_square(int size){
    int i, j;

    /* Draw a square */
    for(i=0; i<size; i++){
        printf("* ");
    }
    printf("\n");
    for(i=0; i<size-2; i++){
        printf("*");
        for(j=0; j<2*size-3; j++){
            printf(" ");
        }
        printf("*\n");
    }
    for(i=0; i<size; i++){
        printf("* ");
    }

    printf("\n");
}

void draw_triangle(int size){
    int i, j, k;

    /* Draw a triangle */
    for(i=0; i<size; i++){
        for(j=0; j<(2*size-1)-2*i; j++){
            printf(" ");
        }
        printf("*");
        for(j=1; j<=2*i+1; j++){
            printf(" "); 
        }
        printf("*");
        printf("\n");    
    }
}