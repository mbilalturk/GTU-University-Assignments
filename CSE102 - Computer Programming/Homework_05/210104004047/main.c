#include <stdio.h>
#include <math.h>

enum Color {RED,GREEN,BLUE,YELLOW,ORANGE};

/* Declarations functions for Part 1 */
void part1();

/* Declaratios functions for Part 2 */
void part2();
void colormixer(enum Color (*mix_color)(enum Color, enum Color, double result_vector[]), enum Color first_color, enum Color second_color);
enum Color mix_color(enum Color, enum Color, double result_vector[]);

/* Declarations functions for Part 3 */
void part3();
int assign_X_or_O(char board[][3], int row, int col, char sign);
int win(char board[][3], char sign1, char sign2);
int fill(char board[][3]);
void clear(char board[][3]);
void conclude(char board[][3], int *full, int *iswinner);


int main(){
    printf("********* PART 1 **********\n\n");
    part1();
    printf("********* PART 2 **********\n\n");
    part2();
    printf("********* PART 3 **********\n\n");
    part3();

    return(0);
}

void part1(){
    char c;
    char filename[20];
    int i, j = 65; 
    int letters[26] = {0}; /* Fill the array with 0 for each letter */
      
    printf("Enter the file name: ");
    scanf("%s", filename);
    
    /* Open file to read */
    FILE *finput = fopen(filename, "r");
    
    if(finput == NULL){
        printf("File could not open to read!\n");
    }
    else{
        /* Take characters from file and implement by 1 */
        while((c = fgetc(finput)) != EOF){
            if(c > 64 && c < 91){
                letters[c-65]++;
            }
            else if(c > 96 && c < 123){
                letters[c-97]++;
            }
        }
        /* Print letter frequency */
        printf("\nLetter Frequency: \n");
        for(i = 0; i < 26; i++){
            printf("%c: %d\n", i+65, letters[i]);
        }
    fclose(finput);
    }
}

void part2(){
    char first_color, second_color;
    enum Color color1, color2;
    enum Color mixed_color;
    
    /* Take color from user */
    printf("Enter color 1 (r,g,b,y,o): ");
    scanf(" %c", &first_color);
    printf("Enter color 2 (r,g,b,y,o): ");
    scanf(" %c", &second_color);
    
    /* Assign appropriate colors to color1 according to color taken by user */
    switch(first_color){
        case 'r': color1 = RED; break;
        case 'g': color1 = GREEN; break;
        case 'b': color1 = BLUE; break;
        case 'y': color1 = YELLOW; break;
        case 'o': color1 = ORANGE; break;
        default: printf("INVALID INPUT!\n");
    }

    /* Assign appropriate colors to color2 according to color taken by user */
    switch(second_color){
        case 'r': color2 = RED; break;
        case 'g': color2 = GREEN; break;
        case 'b': color2 = BLUE; break;
        case 'y': color2 = YELLOW; break;
        case 'o': color2 = ORANGE; break;
        default: printf("INVALID INPUT!\n");
    }

    /* Call colormixer() function */
    colormixer(mix_color, color1, color2);  
}

void colormixer(enum Color (*mix_color)(enum Color, enum Color, double result_vector[]), enum Color first_color, enum Color second_color){
    double result_vector[3];
    enum Color mixed_color;

    /* Call mix_color() function and assign value that returned by mix_color() function to mixed color to print appropriate color */
    mixed_color = mix_color(first_color, second_color, result_vector);
    
    /* Print the color returned by mix_color() function */
    switch(mixed_color){
        case 0:
            printf("Mixed Color: RED "); break;
        case 1:
            printf("Mixed Color: GREEN "); break;
        case 2:
            printf("Mixed Color: BLUE "); break;
        case 3:
            printf("Mixed Color: YELLOW "); break;
        case 4:
            printf("Mixed Color: ORANGE "); break;
        default: break;
    }
    /* Print result vector which is calculated and returned by mix_color() function */
    printf("[%.1lf, %.1lf, %.1lf]\n", result_vector[0], result_vector[1], result_vector[2]);
}

enum Color mix_color(enum Color color1, enum Color color2, double result_vector[]){
    /* Declarations of variables */
    enum Color result_color;
    double first_vector[3];
    double second_vector[3];
    double red[3] = {1,0,0};
    double green[3] = {0,1,0};
    double blue[3] = {0,0,1};
    double yellow[3] = {0.5,0.5,0};
    double orange[3] = {0.5,0.4,0.2};
    double distance[5];
    double min;
    int i;

    /* Assign color's vectors to first vector and second vector to calculate avarage color */
    for(i=0; i<3; i++){
        switch(color1){
            case RED:
                first_vector[i] = red[i]; break;
            case GREEN:
                first_vector[i] = green[i]; break;
            case BLUE:
                first_vector[i] = blue[i]; break;
            case YELLOW:
                first_vector[i] = yellow[i]; break;
            case ORANGE:
                first_vector[i] = orange[i]; break;
            default: break;           
        }
        switch(color2){
            case RED:
                second_vector[i] = red[i]; break;
            case GREEN:
                second_vector[i] = green[i]; break;
            case BLUE:
                second_vector[i] = blue[i]; break;
            case YELLOW:
                second_vector[i] = yellow[i]; break;
            case ORANGE:
                second_vector[i] = orange[i]; break;   
            default: break;         
        }
    }

    /* Calculate result vector */
    for(i = 0; i < 3; i++){
        result_vector[i] = (first_vector[i] + second_vector[i]) / 2;
    }
    
    /* Calculate distances for each color and assign them to distance array to determine closest one */
    distance[0] = sqrt(pow(result_vector[0]-red[0],2) + pow(result_vector[1]-red[1],2) + pow(result_vector[2]-red[2],2));
    distance[1] = sqrt(pow(result_vector[0]-green[0],2) + pow(result_vector[1]-green[1],2) + pow(result_vector[2]-green[2],2));
    distance[2] = sqrt(pow(result_vector[0]-blue[0],2) + pow(result_vector[1]-blue[1],2) + pow(result_vector[2]-blue[2],2));
    distance[3] = sqrt(pow(result_vector[0]-yellow[0],2) + pow(result_vector[1]-yellow[1],2) + pow(result_vector[2]-yellow[2],2));
    distance[4] = sqrt(pow(result_vector[0]-orange[0],2) + pow(result_vector[1]-orange[1],2) + pow(result_vector[2]-orange[2],2));  

    /* Determine closest color */
    min = distance[0];    
    for(i=0; i<5; i++){
        if(min > distance[i]){
            min = distance[i];    
        }
    }

    /* Assign color to result color to print */
    if(min == distance[0]){
        result_color = RED;
    }
    else if(min == distance[1]){
        result_color = GREEN;
    }
    else if(min == distance[2]){
        result_color = BLUE;
    }
    else if(min == distance[3]){
        result_color = YELLOW;
    }
    else if(min == distance[4]){
        result_color = ORANGE;
    }
    
    return result_color;
}

void part3(){
    char board[3][3] = {{'_', '_', '_'}, {'_', '_', '_'}, {'_', '_', '_'}};
    int row, col, iswinner, full, already_filled;
    int i, j;

    do{
        /* Take row and col number from user for empty place for first user */
        already_filled = 1;
        while(already_filled == 1){
            printf("Player 1 (X), enter your move (row, col): ");
            scanf("%d %d", &row, &col);
            already_filled = assign_X_or_O(board, row, col, 'X'); /* Assign X or O to given place via function check if it is empty */
        }
       
       /* Print board */
        for(i=0; i<3; i++){
            for(j=0; j<3; j++){
                printf("%c ", board[i][j]);
            }
            printf("\n");
        }

        /* Check if board is full via function and if it is, return 1. If it is not, return 0 */
        full = fill(board);

        /* Check if there is a winner via function.
            If player1 win, return 1. If player2 win, return 2 */
        iswinner = win(board, 'X', 'O');

        /* If there is a winner, ask to users want to play again */
        conclude(board, &full, &iswinner);

        /* If users don't want to play again, quit */
        if(iswinner == 1 || full == 1)
            break;

        /* Take row and col number from user for empty place for second user */
        already_filled = 1;
        while(already_filled == 1){
            printf("Player 2 (O), enter your move (row, col): ");
            scanf("%d %d", &row, &col);
            already_filled = assign_X_or_O(board, row, col, 'O');
        }

        /* Print board */
        for(i=0; i<3; i++){
            for(j=0; j<3; j++){
                printf("%c ", board[i][j]);
            }
            printf("\n");
        }
        
        /* Check if board is full via function and if it is, return 1. If it is not, return 0 */
        full = fill(board);

        /* Check if there is a winner via function.
            If player1 win, return 1. If player2 win, return 2 */
        iswinner = win(board, 'X', 'O');

        /* If there is a winner, ask to users want to play again */
        conclude(board, &full, &iswinner);
    }
    while(full == 0 && (iswinner != 1 && iswinner != 2));
} 

/* Function to assign X and O to board */
int assign_X_or_O(char board[][3], int row, int col, char sign){
    int already_filled;

    if(sign == 'X'){
        if(board[row][col] == '_'){
            board[row][col] = 'X';
            already_filled = 0;
        }
        else{
            printf("Try again for another place!\n\n");
            already_filled = 1;
        }
    }
    else if(sign == 'O'){ 
        if(board[row][col] == '_'){
            board[row][col] = 'O';
            already_filled = 0;
        }
        else{
            printf("Try again for another place!\n\n");
            already_filled = 1;
        }
    }
    return already_filled;
} 

/* Function to check if there is a winner */
int win(char board[][3], char sign1, char sign2){
    int i, j, res = 0;
    char play;

    /* Check row and column to check if there is a winner */
    for(i=0; i<3; i++){
        if(board[i][0] == sign1 && board[i][1] == sign1 && board[i][2] == sign1)
            res = 1;
        else if(board[i][0] == sign2 && board[i][1] == sign2 && board[i][2] == sign2)
            res = 2;
        else if(board[0][i] == sign1 && board[1][i] == sign1 && board[2][i] == sign1)
            res = 1;
        else if(board[0][i] == sign2 && board[1][i] == sign2 && board[2][i] == sign2)
            res = 2;
    }

    /* Check dioganol to check if there is a winner */
    if(board[0][0] == sign1 && board[1][1] == sign1 && board[2][2] == sign1)
        res = 1;
    else if(board[0][0] == sign2 && board[1][1] == sign2 && board[2][2] == sign2)
        res = 2;
    else if(board[0][2] == sign1 && board[1][1] == sign1 && board[2][0] == sign1)
        res = 1;
    else if(board[0][2] == sign2 && board[1][1] == sign2 && board[2][0] == sign2)
        res = 2;
    
    return res; 
} 

/* Function to check if board is full. If it is full, return 1 */
int fill(char board[][3]){
    int c, r, fill;
    char play;

    fill = 1;
    for(r=0; r<3; r++){
        for(c=0; c<3; c++){
            if(board[r][c] == '_')
                fill = 0;
        }
    }
    return fill;
} 

/* Function to clean the board up to start a new game */
void clear(char board[][3]){ 
    int r, c;
    for(r=0; r<3; r++){
        for(c=0; c<3; c++){
            board[r][c] = '_';
        }
    }
    printf("\n");
}

/* Function to conclude game and ask to users if they want to play again  */
void conclude(char board[][3], int *full, int *iswinner){
    char play;

     if(*full == 1)
        printf("Draw!\n");

    if(*iswinner == 1)
        printf("Player1 Win!\n");
    else if(*iswinner == 2)
        printf("Player2 Win!\n");
    
    if(*full == 1 || *iswinner == 1 || *iswinner == 2){
        printf("Do you want to play again (Y/N): ");
        scanf(" %c", &play);

        if(play == 'Y'){
            *full = 0;
            *iswinner = 0;
            clear(board);
        }
        else if(play == 'N'){
            printf("Goodbye!\n");
        }else{
            printf("Invalid input!\n");
        }
    }
}