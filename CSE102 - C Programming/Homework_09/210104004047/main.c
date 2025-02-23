#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

/* Definitions of the structures */
typedef struct Point{
    int row, col;
} Point;

typedef struct Board{
    char type;
    int value;
} Board;

/* Definitions of the functions */
Board *** init_board();
void draw_board(Board *** b, Point *s, int *lenght);
void play(Board *** b);
void move(Point *s, char *op_prev_dir, int *move);
Point * update(Board *** b, Point *s, int *lenght, char *op_prev_dir, int *move);
int check_status(Board *** b, Point *s, int *lenght);

int main(){
    /* Definition of the board */
    Board *** board1 = NULL;

    /* Initiliaze the board */
    board1 = init_board();

    /* Call play() function */
    play(board1);

    free(board1);
    return (0);
}

Board *** init_board(){
    Board ***b = NULL;
    int row, col, rand_row, rand_col, rand_num;

    srand(time(NULL));
    
    /* Allocating memory for 2D board, third dimension will be allocated when obstacle generated randomly */
    b = (Board ***)calloc(SIZE,sizeof(Board**));
    for(row=0; row<SIZE; row++){
        b[row]=(Board**)calloc(SIZE,sizeof(Board*));
    }
    for(row=0; row<SIZE; row++){
        for (col=0; col<SIZE; col++){
            b[row][col] = (Board*)malloc(sizeof(Board));
        } 
    }

    /* Initialized each cell as an empty block */
    for(row=0; row<SIZE; row++){
        for(col=0; col<SIZE; col++){
            b[row][col]->type = 'e';
            b[row][col]->value = 0;
        }
    }

    /* Generate bait wtih two rondom number for each dimension and assign 'b' to related index of the board */
    do{
        rand_row = rand() % SIZE;
        rand_col = rand() % SIZE;

        b[rand_row][rand_col]->type = 'b';
    }while(rand_row == 0 && rand_col == 0);

    /* Generate obstacle with three random number last one is for the height of the obstacle,
        generate memory for third dimension and assign 'o' to related index of the board */
    do{
        rand_row = rand() % SIZE;   
        rand_col = rand() % SIZE;
        rand_num = rand() % 8+1;

        b[rand_row][rand_col] = (Board*)realloc(b[rand_row][rand_col],2*sizeof(Board));
        b[rand_row][rand_col]->type = 'o';
        b[rand_row][rand_col]->value = rand_num;
    }while(rand_row == 0 && rand_col == 0);

    return b;
}

void draw_board(Board *** b, Point * s, int *lenght){
    int row, col, i, found;

    /* Draw the board by checking type of the index */
    /* If type is empty and snake is in the board draw O or X */
    for(row=0; row<2*SIZE+2; row++){
        printf("-");
    }
    printf("\n");
    for(row=0; row<SIZE; row++){
        printf("|");
        for(col=0; col<SIZE; col++){
            if(b[row][col]->type == 'e'){
                found=0;
                for(i=1; i<(*lenght); i++){
                    if(row == s[i].row && col == s[i].col){ /* If row and col coincides with the snake, found will be incremented */
                        found = 1;                
                    }
                }
                if(row == s->row && col == s->col){
                    printf("O ");
                }else if(found==1){ /* If found is 1 print 'X', if it is not print ' ' */
                    printf("X ");
                }
                else{
                    printf("  ");
                }
            }
            else if(b[row][col]->type == 'b'){
                printf(". ");
            }
            else if(b[row][col]->type == 'o'){ /* If type of the related index is 'o', print value */
                printf("%d ", b[row][col]->value);
            }
        }
        printf("|\n");
    }

    for(row=0; row<2*SIZE+2; row++){
        printf("-");
    }
}

void play(Board *** b){
    Point *snake;
    int lenght=0, num_moves=0, is_finished;
    char op_prev_dir = 0;
    snake = (Point *)malloc(sizeof(Point)); /* Allocate memory for snake */
    snake->row = 0;
    snake->col = 0;
    lenght = 1; /* Assign 1 to lenght of the snake for head of the snake */

    do{
        draw_board(b, snake, &lenght);
        
        move(snake, &op_prev_dir, &num_moves);
        
        /* Call update() function if game is not over */
        if(check_status(b, snake, &lenght) == 0){
            snake = update(b, snake, &lenght, &op_prev_dir, &num_moves);
        }
        
    }while(!(check_status(b, snake, &lenght))); /* Keep calling these functions until the game is over */

    /* If game is over print end message */
    printf("Terminated the game...\n");
}

void move(Point *s, char *op_prev_dir, int *move){
    char dir;

    /* Prompt the direction from the user to move the snake */
    do{
        printf("\nEnter a direction (w,a,s,d): ");
        scanf(" %c", &dir);
    } while(!(dir == 'w' || dir == 'a' || dir == 's' || dir == 'd' || dir != *op_prev_dir));

    /* Rearrange head of the snake and assign opposite direction to op_prev_dir variable */
    switch(dir){
        case 'w': s->row -= 1;
                *op_prev_dir = 's';
                break;  
        case 'a': s->col -= 1;
                *op_prev_dir = 'd';
                break;
        case 's': s->row += 1;
                *op_prev_dir = 'w';
                break;
        case 'd': s->col += 1;
                *op_prev_dir = 'a';
    }
    (*move)++; /* Increment move by 1 for counting the number of the move */
}

int check_status(Board *** b, Point *s, int *lenght){
    int res=0, temp=0, i, j;

    /* If head of the snake and body of the snake coincide, assign 1 to temp variable */
    for(i=1; i<(*lenght); i++){
        if(s[0].row == s[i].row && s[0].col == s[i].col ){
            temp = 1;
        }
    }

    if(temp == 1){
        res = 1;
    }
    /* If head of the snake collide the wall, assign 1 to res variable */
    else if(s->row < 0 || s->row > 9 || s->col < 0 || s->col > 9){
        res = 1;
    }
    /* If the value of the obstacle is greather than body of the snake, assign 1 to res variable */
    else if(b[s->row][s->col]->type == 'o' && b[s->row][s->col]->value >= (*lenght-1)){
        res = 1;
    }

    return res;
}

Point * update(Board *** b, Point *s, int *lenght, char *op_prev_dir, int *move){
    int rand_row, rand_col, exist=0, i, j, k;
    Point *prev_s;
    Board *temp;
    /* Allocate memory for previous state of the snake */
    prev_s = (Point *)calloc((*lenght),sizeof(Point));  

    /* Assign current snake to previous snake and
        rearrange head of the previous snake by checking last move for the head of the body */
    for(i=0; i<(*lenght); i++){
        prev_s[i].row = s[i].row;
        prev_s[i].col = s[i].col;
        
        if(i==0){
            switch(*op_prev_dir){
                case 'w': prev_s[i].row--; break;
                case 'a': prev_s[i].col--; break;
                case 's': prev_s[i].row++; break;
                case 'd': prev_s[i].col++; break;
            }
        }
    }
    
    srand(time(NULL));

    /* If head of the snake coinside with 'b', reallocate memory to increment lenght of the snake */
    if(b[s->row][s->col]->type == 'b'){
        s = (Point *)realloc(s,(*lenght+1)*sizeof(Point));        
        
        (*lenght)++;
        b[s->row][s->col]->type = 'e'; /* Assign 'e' to related index of the board */

        /* Generate new bait randomly */
        do{
            exist=0;
            rand_row = rand() % SIZE;
            rand_col = rand() % SIZE;

            /* If body of the snake and bait coincide, increment by 1 exist variable */
            for(i=0; i<(*lenght); i++){
                if(s[i].row == rand_row && s[i].col == rand_col)
                    exist = 1;
            }

            /* If exist 0 and type of the related index of the board is empty,
                assign 'b' to related index of the board */
            if(exist == 0 && b[rand_row][rand_col]->type == 'e')
                b[rand_row][rand_col]->type = 'b';

        }while(b[rand_row][rand_col]->type != 'b'); /* Keep generating bait, if type is not 'b' */
    }

   /* Update the obstacles every 5 moves */
    if((*move) % 5 == 0){
        int rand_obs, val_obs;

        rand_obs = rand() % 3+1; /* Determine how many obstacles will be exist */

        for(i=0; i<rand_obs; i++){

            /* Generate index of the obstacle */
            do{
                exist = 0;
                rand_row = rand() % 8 + 1;
                rand_col = rand() % 8 + 1;
                val_obs = rand() % 8 + 1;

                /* If body of the snake and bait coincide, increment by 1 exist variable */
                for(j=0; j<(*lenght); j++){
                    if(s[j].row == rand_row && s[j].col == rand_col)
                        exist = 1;
                }
                
            }while(b[rand_row][rand_col]->type == 'b' || exist == 1);
            
            /* If type of the place where new obstacle will be exist is not 'o' */
            if(b[rand_row][rand_col]->type != 'o'){
                int prev_row, prev_col, flag = 0, rand_index;

                /* Determine which obstacle will be delete randomly */
                rand_index = rand() % 2+1;

                /* Determine the index of the obstacle that will be deleted */
                for(j=0; j<SIZE; j++){
                    for(k=0; k<SIZE; k++){
                        if(b[j][k]->type == 'o'){
                            if(flag == rand_index){
                                prev_row = j;
                                prev_col = k;
                            }
                            flag++; 
                        }
                    }
                }
                
                /* Free obstacle that will be deleted and reallocate to assign 'e' and 0 */
                if(flag != 1 && flag != 2){
                    free(b[prev_row][prev_col]);
                    b[prev_row][prev_col] = (Board *)malloc(sizeof(Board));
                    b[prev_row][prev_col]->type = 'e';
                    b[prev_row][prev_col]->value = 0;
                }
                
                /* Generate new obstacle */
                b[rand_row][rand_col]->value = val_obs;
                b[rand_row][rand_col] = (Board *)realloc(b[rand_row][rand_col], b[rand_row][rand_col]->value*sizeof(Board));
                b[rand_row][rand_col]->type = 'o'; 
                
            }
            else{
                /* If value of the obstacle is smaller than 9
                    assign value that is generated randomly to  value of the obstacle and reallocate */
                if((b[rand_row][rand_col]->value + val_obs) <= 9){
                    b[rand_row][rand_col]->value += val_obs;
                    b[rand_row][rand_col] = (Board *)realloc(b[rand_row][rand_col], b[rand_row][rand_col]->value*sizeof(Board));
                }else{
                    /* If value of the obstacle is greater than 9 */
                    /* Determine index of the obstacle whose value is greater than 9*/
                    int prev_row, prev_col, flag=0;
                    for(j=0; j<SIZE; j++){
                        for(k=0; k<SIZE; k++){
                            if(b[j][k]->type == 'o'){
                                prev_row = j;
                                prev_col = k;
                                flag = 1;
                                break;
                            }
                        }
                        if(flag == 1)
                            break;
                    }
                    /* Free obstacle that will be deleted and reallocate to assign 'e' and 0 */
                    free(b[prev_row][prev_col]);
                    b[prev_row][prev_col] = (Board *)malloc(sizeof(Board));
                    b[prev_row][prev_col]->type = 'e';
                    b[prev_row][prev_col]->value = 0;

                    /* Generate new obstacle */
                    b[rand_row][rand_col]->value = val_obs;
                    b[rand_row][rand_col] = (Board *)realloc(b[rand_row][rand_col], b[rand_row][rand_col]->value*sizeof(Board));
                    b[rand_row][rand_col]->type = 'o'; 
                }
            }
        }
    }

    /* Assign indexes of previous snake to current snake starting with second index of the current snake */
    for(i=0; i<(*lenght-1); i++){
        s[i+1] = prev_s[i];
    }

    /* If head of the snake and one of the obstacle coincide AND
        lenght of the snake is greater than value of the obstacle free current obstacle,
        allocate memory the related index of the board,
        assign 'e' to type of the related index of the board,
        assign 0 to value of the related index of the board*/
    if(b[s->row][s->col]->type == 'o' && (*lenght-1) > b[s->row][s->col]->value){
        free(b[s->row][s->col]);
        b[s->row][s->col] = (Board *)malloc(sizeof(Board));    
        b[s->row][s->col]->type = 'e';
        b[s->row][s->col]->value = 0;

    }
    
    /* Free previous snake */
    free(prev_s);

    return s;
}
