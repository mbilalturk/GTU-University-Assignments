#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_WORD_COUNT 100
#define MAX_WORD_SIZE 15
#define WORD_ARRAY_SIZE 200000
#define WORD_PER_LINE 500 
#define IGNORED_WORD 100
#define MAX_CHARACTER_SIZE 1200000  
#define NUM_WORD 1100
#define VECTOR_SIZE 400
#define THRESHOLD 5.5  /* Can be changed threshold depending on the case */

/* Declarations of functions */
int read_dict(const char *file_name, char dict[][MAX_WORD_SIZE], double vector[][VECTOR_SIZE]);
int read_text(const char *text_file, const char *ignore_file, char words[][MAX_WORD_SIZE]);
double dissimiliraty(char *w1, const char dict[][MAX_WORD_SIZE], const double vector[][VECTOR_SIZE], float threshold, int *closest_index);
int histogram(const char words[][MAX_WORD_SIZE], const int occurences[], char hist[][MAX_WORD_SIZE+20+5]);
void split_words(char input[WORD_ARRAY_SIZE], char words[][MAX_WORD_SIZE], int *times);
int display(char users_words[][MAX_WORD_SIZE], const char words[][MAX_WORD_SIZE], const char dict[][MAX_WORD_SIZE], double vector[][VECTOR_SIZE], int times, const char *file_name);
void occurences(const char checked_word[][MAX_WORD_SIZE], const char array_in_checked[][MAX_WORD_SIZE], int occ[], int num);

int main(int argc, char *argv[]){
    /* Declarations of variable */
    char users_words[MAX_WORD_COUNT][MAX_WORD_SIZE]; 
    char users_input[WORD_ARRAY_SIZE];
    char words[WORD_ARRAY_SIZE][MAX_WORD_SIZE];
    char dictionary[NUM_WORD][MAX_WORD_SIZE];
    double vector[NUM_WORD][VECTOR_SIZE];
    int times = 0; /* number of words received by the user */ 
    int d_number_read, t_number_read; /* number of words received by the dictionary.txt and input.txt */
    
    /* Take string from user */
    printf("Enter word(s): ");
    fgets(users_input, MAX_WORD_COUNT, stdin);   

    /* Call split_words() functions to split words received by user into users_words array as a index for each of them */
    split_words(users_input, users_words, &times);

    /* Call read_text() function to read input.txt and assign each word to words array */
    t_number_read = read_text("input.txt", "ignore.txt", words);
    
    /* Call read_dict() function to read dictionary.txt. Read name of the words and vector for each and assign them dictionary and vector array respectively */
    d_number_read = read_dict("dictionary.txt", dictionary, vector);

    /* Call display() funciton to print */
    display(users_words, words, dictionary, vector, times, "input.txt");

    return(0);
}

int read_dict(const char *file_name, char dict[][MAX_WORD_SIZE], double vector[][VECTOR_SIZE]){
    FILE *inp = fopen(file_name, "r+");
    char c;
    int i, j, num_word, vector_size, d_number_read;   
    
    if(inp == NULL){
        printf("File could not open!\n");
        return -1;
    }
    /* Read num_word and vector_size from file */
    fscanf(inp, "num_word=%d, vector_size=%d", &num_word, &vector_size);

    /* Ignore first line of the dictionary */
    while((c=fgetc(inp) != '\n'));

    /* Take name of the words and their vectors then assign them to arrays*/
    for(i=0; i<num_word; i++){
        fscanf(inp, "%[^ ]", dict[i]);
        for(j=0; j<vector_size; j++){
            fscanf(inp, "%lf", &vector[i][j]);
        }
        fscanf(inp, "\n");
    }
    /* Assign '-' to last of the array to determine the end of the array */
    dict[i][0] = '-';

    fclose(inp);
    return d_number_read;
}

int read_text(const char *text_file, const char *ignore_file, char words[][MAX_WORD_SIZE]){
    FILE *inp = fopen(text_file, "r+");
    FILE *ign = fopen(ignore_file, "r+");
    char take[WORD_PER_LINE]; /* Array to read each line */
    char store[MAX_CHARACTER_SIZE]; /* Array to store words taken with take array in store array (This array is temporary)*/
    char ignore[IGNORED_WORD][MAX_WORD_SIZE];
    int i, j, t_number_read=0, address=0;

    if(inp == NULL ||  ign == NULL){
        printf("File could not open!\n");
        return -1;
    }

    /* Take words will be ignored from ignore.txt file */
    for(i=0; !feof(ign); i++){
        fscanf(ign, "%s", ignore[i]);
    }

    /* Read each line of input.txt and assign them to store array */
    while(fgets(take, WORD_PER_LINE, inp) != NULL){
        for(i=0; take[i] != '\0'; i++);
        strncpy(&store[address], take, i);
        address += i;
    }    

    /* Split words stored in store array into words. t_number_words will be used to assign '-' to the end of the words array */
    split_words(store, words, &t_number_read);
    
    /* When encountring the words will be ignored assign IGNORED to appropriate index of words */
    for(i=0; ignore[i][0] != '\0'; i++){
        for(j=0; words[j][0] != '\0'; j++){
            if(strcmp(words[j], ignore[i]) == 0){
                strcpy(words[j], "IGNORED");
            }
        }
    }

    fclose(inp);
    fclose(ign);

    return t_number_read;
}

void split_words(char input[WORD_ARRAY_SIZE], char words[][MAX_WORD_SIZE], int *times){
    char seps[] = " !\"#$+_:.;>*<|()={[]}&/,\n\t"; /* Some signs to be ignored */
    char *word, c;
    int i, j;

    /* Strtok() function to ignore some sign */
    word = strtok(input, seps);
    for(i=0; word != NULL; i++){
        strcpy(words[i], word);
        word = strtok(NULL, seps);
        (*times)++;
    }
    
    /* Assign '-' to the end of the words array */
    words[*times][0] = '-';

    /* Count the number of character in input */
    for(j=0; input[j] != '\0'; j++);

    /* Assign NULL character to empty index */
    for(i=0; i<MAX_WORD_COUNT; i++)
        for(j; j<MAX_WORD_SIZE; j++){
            words[i][j] = '\0';
    }
}

int display(char users_words[][MAX_WORD_SIZE], const char words[][MAX_WORD_SIZE], const char dict[][MAX_WORD_SIZE], double vector[][VECTOR_SIZE], int times, const char *file_name){
    int occ[MAX_WORD_COUNT] = {0};
    char hist[MAX_WORD_COUNT][MAX_WORD_SIZE+20+5];
    int index_of_closest, scale, i, j;
    float threshold = THRESHOLD;
    double closest;

    /* times variable stores how many words were entered */
    if(times<1){
        printf("No words were entered!\n");
    }
    else if(times==1){
        /* Calculate the occurences of the first entry of users_word by calling occurences() function */
        occurences(users_words, words, occ, 0);

        /* Print occurence of the first word. */ 
        if(occ[0]>0){
            printf("\"%s\" appears in \"%s\" %d times.\n", users_words[0], file_name, occ[0]);
        }
        else{
            /* If occurence is zero, calculate dissimiliraty and print closest word if it is smaller than threshold */
            closest = dissimiliraty(users_words[0], dict, vector, threshold, &index_of_closest);
            
            if(closest < threshold){
                occurences(dict, words, occ, index_of_closest);
                printf("\"%s\" doesn't appear in \"%s\" but \"%s\" appears in %d times.\n", users_words[0], file_name, dict[index_of_closest], occ[index_of_closest]);
            }
            else{
                printf("\"%s\" doesn't appears in \"%s\".\n", users_words[0], file_name);
            }
        }
    }
    else{
        /* Calculate occurences of the each word taken by the user */
        for(i=0; users_words[i][0] != '-'; i++){
            occurences(users_words, words, occ, i);
        }
        /* Assign -1 as a sentinel value */
        occ[i] = -1;

        /* Calculate scale usign histogram() function */
        scale = histogram(users_words, occ, hist);

        printf("scale: %d\n", scale);
         for(i=0; occ[i] != -1; i++){
            /* If occurence is zero, calculate dissimiliraty. If it is not, print occurence of the word */ 
            if(occ[i]==0){
                /* Print closest word if it is smaller than threshold */
                closest = dissimiliraty(users_words[i], dict, vector, threshold, &index_of_closest);
                if(closest < threshold){
                    occurences(dict, words, occ, index_of_closest);
                    printf("%s->%s\t",users_words[i], dict[index_of_closest]);
                    if((occ[index_of_closest]/scale)>20){
                        for(j=0; j<20; j++){
                            printf("+");
                        }
                        printf("\n");
                    }
                    else{
                        for(j=0; j<(occ[index_of_closest]/2); j++){
                            printf("+");
                        }
                        printf("\n");
                    }
                }
                else{ 
                    /* If closest is greater than threshold print no matches */
                    printf("%-14s", users_words[i]);
                    printf("NO MATCHES\n");
                }  
            }
            else{
                printf("%-14s", users_words[i]);
                if((occ[i]/scale)>20){
                    for(j=0; j<20; j++){
                        printf("*");
                    }
                    printf("\n");
                }
                else{
                    for(j=0; j<(occ[i]/scale); j++){
                        printf("*");
                    }
                    printf("\n");
                }
            }
        }
    }
}

void occurences(const char checked_word[][MAX_WORD_SIZE], const char array_in_checked[][MAX_WORD_SIZE], int occ[MAX_WORD_COUNT], int num){
    int j;
    
    /* When encountering the related words, increment occurence */
    for(j=0; array_in_checked[j][0] != '-'; j++){
        if(strcmp(array_in_checked[j], checked_word[num]) == 0){
            occ[num]++;
        }
    }
}

double dissimiliraty(char *w1, const char dict[][MAX_WORD_SIZE], const double vector[][VECTOR_SIZE], float threshold, int *closest_index){
    int i=0, j=0, first=0;
    int matched;
    double distance=0, closest=0;

    /* Compare first word and dictionary to determine index of the dictionary array that has the word */
    for(i=0; i<NUM_WORD; i++){
        if(strcmp(w1, dict[i]) == 0){
            matched = i;
        }
    }

    /* Assign 1 to first variable to start to calculate with first entry of vector */
    if(matched == 0)
        first=1;

    /* Assign distance of the first word of the dictionary to closest variable */
    for(j=0; j<VECTOR_SIZE; j++){
        distance += pow((vector[matched][j]-vector[first][j]),2);
    }
    closest = sqrt(distance);

    /* Assign 0 to closest_index variable so that determine the index of dictionary which has closest word */
    *closest_index = 0; 
    
    /* Calculte the distance and assign its index to closest_index to determine its occurence using occurences() function */
    for(i=0; i<NUM_WORD; i++){
        /* If i is equal to matched, distance will be 0.0 because they are same. Therefore, ignore this */
        if(i==matched){
        }
        else{
            distance=0;
            for(j=0; j<VECTOR_SIZE; j++){
                distance += pow((vector[matched][j]-vector[i][j]),2);
            }
            distance = sqrt(distance);
            if(distance < closest){
                closest = distance;
                *closest_index = i;
            }
        }
    }

    return closest;
}

int histogram(const char words[][MAX_WORD_SIZE], const int occurences[], char hist[][MAX_WORD_SIZE+20+5]){
    int scale=1, i;

    /* Calculate scale to print occurences of the words */
    for(i=0; words[i][0] != '-'; i++){
        if((occurences[i]/scale) > 20){
            scale = occurences[i] / 20; 
        }
    }    

    return scale;
}