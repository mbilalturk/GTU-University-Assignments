#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 3
#define COL 3

/* Definition of puzzle struct */
typedef struct {
    int board[ROW][COL];
} puzzle;

/* Definitions of functions */
void clean_puzzle(puzzle *board);
int print_puzzle(puzzle *board, char *text_file);
void generate_puzzle(puzzle *board);
void users_selection(puzzle *board);
int movement(puzzle *board, char *direction, int *num, int *num_x, int *num_y, int *emp_x, int *emp_y);
int is_finished(puzzle *board);
int read_score(char *text_file);
int write_score(int *score, char *text_file);
int auto_finish(puzzle *board, int n, int *pn);
int is_solvable(puzzle *board);

int main(){
    int option, move=0, pn=0;
    puzzle board1;
    
    srand(time(0));

    do{
        printf("Welcome to the 8-Puzzle Game!\n");
        printf("Please select an option:\n1. Play game as a user\n2. Finish the game with PC\n3. Show the best score\n4. Exit\n> ");
        scanf("%d", &option);

        switch(option){
            case 1: do{
                        clean_puzzle(&board1); /* Function to clean each index of the board before generating */
                        generate_puzzle(&board1); /* Function to generate random puzzle board */
                    }
                    while(!(is_solvable(&board1))); /* Function to check if generated board is solvable */
                    print_puzzle(&board1, "8_puzzle.txt"); /* Function to print the board */
                    users_selection(&board1); /* Function to take input from user */
                    break;
            case 2: do{
                        clean_puzzle(&board1); 
                        generate_puzzle(&board1);
                    }
                    while(!(is_solvable(&board1)));
                    print_puzzle(&board1, "8_puzzle.txt");
                    move = auto_finish(&board1, is_finished(&board1), &pn); /* Function to move randomly */
                    printf("Computer finished the game.\nTotal number of computer moves: %d\n\n", move); 
                    break;
            case 3: read_score("score.txt"); break; /* Function to read the best score from file for printing */
            case 4: printf("Good Bye!\n"); break; 
            default: printf("Invalid Input!\n");
        }
    }
    while(option != 4);

    return (0);
}

/* Function to print current puzzle to the terminal and the file */
int print_puzzle(puzzle *board, char *text_file){
    FILE *fout = fopen(text_file, "a+");
    int i, j;

    if(fout == NULL){
        printf("File could not open!\n");
        return -1;
    }
    for(i=0; i<ROW; i++){
        for (j=0; j<COL; j++){
            fprintf(fout, "%d ", board->board[i][j]);
            printf("%d ", board->board[i][j]);
        }
        fprintf(fout, "\n");
        printf("\n");
    }
    fprintf(fout, "\n");
    fclose(fout);
}

/* Function to clean each index of the puzzle */
void clean_puzzle(puzzle *board){
    int i, j;
    for(i=0; i<ROW; i++){
        for (j=0; j<COL; j++){
            board->board[i][j] = 0;
        }
    }
}

/* Function to generate puzzle randomly by selecting random two numbers for index of the puzzle and checking if that index is 0 */
void generate_puzzle(puzzle *board){
    int r, c, i=1;
    while(i<=8){
        r = rand() % 3;
        c = rand() % 3;
        if(board->board[r][c] == 0){
            board->board[r][c] = i;
            i++;
        }
    }
}

/* Function to take input from user */
void users_selection(puzzle *board){
    char sel[5], dir;
    int i, j, nx, ny, ex, ey, num, valid, score, moves=0;
   
   do{
        /* Take number and direction from user to the array */
        printf("Enter your move (number-direction, e.g., 2-R): ");
        scanf("%s", sel);
        
        /* Determine the number and direction from array and assign them into num variable and dir variable respectively */
        sscanf(sel, "%d", &num);
        dir = sel[2];

        /* Determine the index of the number that taken and the index of the zero */
        for(i=0; i<ROW; i++){
            for(j=0; j<COL; j++){
                if(board->board[i][j] == num){
                    nx=i; ny=j;
                }
                if(board->board[i][j] == 0){
                    ex=i; ey=j;
                }
            }
        }

        /* Check if the movement is legal */
        valid = movement(board, &dir, &num, &nx, &ny, &ex, &ey);
        print_puzzle(board, "8_puzzle.txt");

        /* If movement is legal, increment number of movement */
        if(valid == 1)
            moves++;

   }while(!(is_finished(board))); /* Check if board is finished, if it is not keep taking input from user */

    /* Calculate score and print the moves and score to the terminal and the file */
    score = 1000-(moves*10);
    printf("Total number of moves: %d\nYour score: %d\n\n", moves, score); 
    write_score(&score, "score.txt");
}

/* Function for movement, if movement is legal return 1 if it is not return 0 */
int movement(puzzle *board, char *direction, int *num, int *num_x, int *num_y, int *emp_x, int *emp_y){
    /* Declaraton of temporary variable to store previous number */
    int temp_x = *num_x;
    int temp_y = *num_y;
    int valid;

    /* Increment or dicrement temporary variable for appropriate direction */
    switch(*direction){
        case 'U': temp_x--; break;
        case 'D': temp_x++; break;
        case 'L': temp_y--; break;
        case 'R': temp_y++; break;
        default: printf("Invalid Input!\n");
            return 0;
    }

    /* If index of the empty block and temporary variable are same, swap the number and zero */
    if(board->board[temp_x][temp_y] == board->board[*emp_x][*emp_y]){
        board->board[*emp_x][*emp_y] = *num;
        board->board[*num_x][*num_y] = 0;
        valid = 1;
    }
    else{
        printf("%d-%c is an illegal move!!! Make a legal move!!!\n", *num, *direction);
        valid = 0;
    }

    /* Return valid to determine if movement is legal or not */
    return valid;
}

/* Function to determine if the puzzle finish. If it is finished return 1, if it is not return 0 */
int is_finished(puzzle *board){
    int i, j, over=1, num=1;

    for(i=0; i<ROW; i++){
        for(j=0; j<COL; j++){
            if(board->board[i][j] != num)
                over = 0;
            num++;
            if(i==2 && j==1)
                num=0;
        }
    }

    /* Normally over is 1, if the all number is ordered over variable becomes zero */
    return over;
}

/* Function to read the best score from the file */
int read_score(char *text_file){
    FILE *fin = fopen(text_file, "r+");
    int best;

    if(fin == NULL){
        printf("File could not open!\n");
        return -1;
    }
    fscanf(fin, "%d", &best);
    printf("The best score is %d...\n\n", best);

    fclose(fin);
}

/* Function to read the previous score from the file and write the current score if it is higher than previous one */
int write_score(int *score, char *text_file){
    FILE *fin = fopen(text_file, "r+");
    int best;

    if(fin == NULL){
        printf("File could not open!\n");
        return -1;
    }
    fscanf(fin, "%d", &best);

    /* Check if current score is higher than previous score, If it is write current score to the file */
    if((*score)>best){
        FILE *fout = fopen(text_file, "w+");
        if(fout == NULL){
            printf("File could not open!\n");
        return -1;
        }
        fprintf(fout, "%d", *score);
        fclose(fout);
    }
    fclose(fin);
}

/* Function to move randomly */
int auto_finish(puzzle *board, int n, int *pn){    
    if(n==1){
        return 0;
    }
    else{
        int i, j, nx, ny, ex, ey, num;
        char dir=0;

        do{
            /* If the previous number and current number are same, generate any other number */
            do{
                num = rand()%8 + 1;
            }while(num == *pn);

            /* Determine the index of the number and the index of the zero */
            for(i=0; i<ROW; i++){
                for(j=0; j<COL; j++){
                    if(board->board[i][j] == num){
                        nx=i; ny=j;
                    }
                    if(board->board[i][j] == 0){
                        ex=i; ey=j;
                    }
                }
            }

            /* Check the index of the number and the index of the zero. If they are in suitable place assign appropriate direction and swap them */
            if(ex == nx+1 && ny == ey){ 
                dir = 'D';
                board->board[ex][ey] = num;
                board->board[nx][ny] = 0;
            }else if(ex == nx-1 && ny == ey){ 
                dir = 'U';
                board->board[ex][ey] = num;
                board->board[nx][ny] = 0;
            }else if(nx == ex && ey == ny+1){ 
                dir = 'R';
                board->board[ex][ey] = num;
                board->board[nx][ny] = 0;
            }else if(nx == ex && ey == ny-1){ 
                dir = 'L';
                board->board[ex][ey] = num;
                board->board[nx][ny] = 0;
            }
        }while(dir == 0); /* Keep generating number and determining appropriate direction until dir variable is not null */

        /* Print the movement and current puzzle board */
        printf("Computer move: %d-%c\n", num, dir);
        print_puzzle(board, "8_puzzle.txt");

        /* Call auto_finish() function with incrementing by 1 for each movement */
        return 1 + auto_finish(board, is_finished(board), &num);
    }
}

/* Function to determine generated board is solvable or not */
int is_solvable(puzzle *board){
    int a[9], i, j, flag, k=0, count=0;

    /* Assign numbers of board into a array respectively */
    for(i=0; i<ROW; i++){
        for(j=0; j<COL; j++){
            a[k]= board->board[i][j];
            k++;
        }    
    }

    /* Count the number of the smaller numbers for each numbers coming after */
    for(i=0; i<8; i++){
        for(j=i+1; j<=8; j++){
            if(a[j]!=0){
                if(a[i] > a[j])
                    count++;
            }
        }
    }    

    /* If the counter is even return 1 which means board is solvable, if it is odd return 0 which means board is unsolvable.*/
    if(count%2 == 0)
        flag = 1;
    else
        flag = 0;

    return flag;
}

