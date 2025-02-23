#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEFT 'a'
#define RIGHT 'd'
#define UP 'w'
#define DOWN 's'

void drawing_the_room();
void the_game();
void gameplay(int size, int d_x_axis, int d_y_axis, int c_x_axis, int c_y_axis);
int control_of_status(int d_x_axis, int d_y_axis, int c_x_axis, int c_y_axis); 

int main(){

    the_game();

    return (0);
} /* End of main */

void drawing_the_room(){
    int size, i,j;
    int d_x_axis, d_y_axis, c_x_axis, c_y_axis;
    
    /* Funciton to create numbers randomly */ 
    srand(time(0));

    /* Get the size of room from user */
    printf("Enter the size of room: ");
    scanf("%d", &size);
    
    /* Check if room's size is between 5 and 10 */ 
    if(size < 5 || size > 10){
        printf("Please enter a number between 5 and 10!\n");
    }
    else{
    /* Create axis of D and C randomly by using rand() function */ 
        d_x_axis = rand() % size + 1;    
        d_y_axis = rand() % size + 1;
        c_x_axis = rand() % size + 1;
        c_y_axis = rand() % size + 1;

    /* Call the gameplay() function */
        gameplay(size, d_x_axis, d_y_axis, c_x_axis, c_y_axis);    
    }
} /* End of drawing_the_room */

void the_game(){
    int option;

    /* Dsiplay the menu */
    do{
        printf("Welcome to the 'D puzzle game!\n");
        printf("1. New Game\n2. Help\n3. Exit\n");

        /* Get number from user to start or quit */
        scanf("%d", &option);

        /* Check what to do with number getting from user */
        switch(option){
            case 1: /* Call drawing_the_room() function to start */
                    drawing_the_room();
                    break;
            case 2: /* Print game's intsruction and rules */               
                    printf("The character is able to move one space in any of the four cardinal directions: up, down, left, and right. Diagonal moves are not allowed. The user will input their desired move using the following keys: 'a' for left, 'd' for right, 'w' for up, and 's' for down. The current state of the room should be printed after each move, except when the character reaches the door. If the character attempts to move through a wall, a warning message should be displayed. The game ends when the character reaches the door, and a message should be displayed to notify the user that the game is over and how many moves were made during the game.\n\n"); 
                    break;
            case 3: /* Print Goodbye message */
                    printf("Goodbye!\n");
                    break;
            default: /* Ask the user to enter the appropriate number */
                    printf("Please enter appropriate option!!\n");
                    break;
        }
    }
    while(option == 1 || option == 2);

} /* End of the_game */

void gameplay(int size, int d_x_axis, int d_y_axis, int c_x_axis, int c_y_axis){
    int i, j, control, counter = 0, flag = 0;
    char direction;

    /* Call control_of_status() function to start if axis are not same */
    control = control_of_status(d_x_axis, d_y_axis, c_x_axis, c_y_axis);         
    
    while(!(control)){
        /* Print top of the room */
        for(i = 1; i <= (2*size+1); i++){
            printf("-");
        }
        /* Print D, C and space by size */
        for(i = size; i > 0; i--){
            printf("\n");
            for(j = 1; j <= size+1; j++){
                printf("|");
                if(d_x_axis == j && d_y_axis == i){
                    printf("D");
                }
                else if(c_x_axis == j && c_y_axis == i){
                    printf("C");
                }
                else{
                    printf(" ");
                }
            }
        }
        /* Print bottom of the room */
        printf("\n");
        for(i = 1; i <= (2*size+1); i++){
            printf("-");
        }
        printf("\n");

        
        /* Get direction from user to move C */
        printf("Move character by entering a (left), d (right), s (down), w (up): \n");   
        //scanf(" %c", &direction);    
        while((getchar()) != '\n');  
        direction = getchar();
        
        /* Determine what to do with direction */
        /* If C attempts to move thruogh a wall, display warning message */
        switch(direction){
            case LEFT:
                    if(c_x_axis > 1)
                        c_x_axis--;
                    else
                        flag = 1;
                    break;
            case RIGHT:
                    if(c_x_axis < size)
                        c_x_axis++;
                    else
                        flag = 1;
                    break;
            case DOWN:
                    if(c_y_axis > 1)
                        c_y_axis--;
                    else
                        flag = 1;
                    break;
            case UP:
                    if(c_y_axis < size)
                        c_y_axis++;
                    else
                        flag = 1;
                    break;
            default:
                    printf("Enter appropriate direction!\n");
                    break;
        }

        if(flag == 1)
            printf("Impassable through the wall!\n");

        counter++;
        /* Check if axis are same using contol_of_status() funtcion */
        control = control_of_status(d_x_axis, d_y_axis, c_x_axis, c_y_axis);     
    }
    /* Display message to end it and print how many times moves were made */
    printf("Congratulations! Made %d moves!\n\n", counter);  
} /* End of gameplay */

int control_of_status(int d_x_axis, int d_y_axis, int c_x_axis, int c_y_axis){

    /* Check if character's location and door's location are same            */
    /* If it is, return 1 and game is over. Otherwise, return 0 and continue */
    if(d_x_axis == c_x_axis && c_y_axis == d_y_axis){
        return 1;
    }
    else{
        return 0;
    }   
} /* End of conrol_of_status */
