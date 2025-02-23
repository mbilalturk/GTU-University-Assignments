#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/* Definitions of structures */
typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct {
    char type[20];
    int ivals[1];
    double svals[1];
} Asset1;

typedef struct {
    char type[20];
    int ivals[2];
    double svals[2];
} Asset2;

typedef struct {
    char type[20];
    char string1[50];
    char string2[50];
} Asset3;

typedef struct {
    char type[20];
    double value1;
    float value2;
    double value3;
} Asset4;

/* Definitions of functions */
void fillLinkedList(struct Node **head);
void serializeLinkedList(struct Node *head);
void deserializeLinkedList(struct Node **head);
void insert(struct Node **head, void *data);
void print(struct Node *head);

int main() {
    struct Node *head = NULL;
    struct Node *deserializedHead = NULL;

    /* Fill the linked list, serialize it and print them to a file as a binary form */
    fillLinkedList(&head);
    serializeLinkedList(head);

    /* Print the linked list to terminal */
    printf("******* FILLED LINKED LIST *******\n");
    print(head);

    /* Deserialize the linked list */
    deserializeLinkedList(&deserializedHead);

    /* Print the deserialized linked list to terminal */
    printf("\n******* DESERIALIZED LINKED LIST *******\n");
    print(deserializedHead);

    return (0);
}

void fillLinkedList(struct Node **head){
    int num_asset, det_asset, i, j;

    /* Determine how many assets will be created randomly */
    srand(time(NULL));
    num_asset = (rand() % 10) + 10;

    for(i=0; i<num_asset; i++) {
        /* Determine the type of asset which will be created */
        det_asset = (rand() % 4) + 1;

        switch(det_asset) {
            case 1:
                /* Allocate memory for asset1 */ 
                Asset1 *asset1 = (Asset1 *)malloc(sizeof(Asset1));
                
                /* Assign corresponding values to it randomly */
                strcpy(asset1->type, "Asset1");
                asset1->ivals[0] = rand() % 100;
                asset1->svals[0] = (rand() % 100) / 10.00;

                /* Insert the node into the linked list */
                insert(head, asset1);
                break;
            case 2:
                /* Allocate memory for asset2 */ 
                Asset2 *asset2 = (Asset2 *)malloc(sizeof(Asset2));
                
                /* Assign corresponding values to it randomly */
                strcpy(asset2->type, "Asset2");
                for(j=0; j<2; j++) {
                    asset2->ivals[j] = rand() % 100;
                    asset2->svals[j] = (rand() % 100) / 10.00;
                }

                /* Insert the node into the linked list */
                insert(head, asset2);
                break;
            case 3:
                /* Allocate memory for asset3 */ 
                Asset3 *asset3 = (Asset3 *)malloc(sizeof(Asset3));

                /* Assign corresponding values to it randomly */
                strcpy(asset3->type, "Asset3");
                sprintf(asset3->string1, "String_%d", i); 
                sprintf(asset3->string2, "String_%d", i); 

                /* Insert the node into the linked list */
                insert(head, asset3);
                break;
            case 4:
                /* Allocate memory for asset3 */ 
                Asset4 *asset4 = (Asset4 *)malloc(sizeof(Asset4));

                /* Assign corresponding values to it randomly */
                strcpy(asset4->type, "Asset4");
                asset4->value1 = (rand() % 100) / 10.00;
                asset4->value2 = (rand() % 100) / 10.00;
                asset4->value3 = (rand() % 100) / 10.00;

                /* Insert the node into the linked list */
                insert(head, asset4);
                break;
            default:
        }
    }
} 

void serializeLinkedList(struct Node *head){
    FILE *fp = fopen("linkledlist.bin", "wb");

    if(fp == NULL) {
        printf("File could not open!\n");
    }
    else {
        while(head != NULL){

            /* If the appropriate data type is found, write it to binary file with appropriate values */
            if(strcmp(((Asset1 *)head->data)->type, "Asset1") == 0) {
                fwrite((((Asset1 *)head->data)->type), sizeof((((Asset1 *)head->data)->type)), 1, fp);
                fwrite((((Asset1 *)head->data)->ivals), sizeof(int), 1, fp);
                fwrite((((Asset1 *)head->data)->svals), sizeof(double), 1, fp);
            }
            else if(strcmp(((Asset2 *)head->data)->type, "Asset2") == 0){
                fwrite((((Asset2 *)head->data)->type), sizeof((((Asset3 *)head->data)->type)), 1, fp);
                for(int i=0; i<2; i++){
                    fwrite(&(((Asset2 *)head->data)->ivals[i]), sizeof(int), 1, fp);
                    fwrite(&(((Asset2 *)head->data)->svals[i]), sizeof(double), 1, fp);
                }
            }
            else if(strcmp(((Asset3 *)head->data)->type, "Asset3") == 0){
                fwrite((((Asset3 *)head->data)->type), sizeof((((Asset3 *)head->data)->type)), 1, fp);
                fwrite((((Asset3 *)head->data)->string1), sizeof((((Asset3 *)head->data)->string1)), 1, fp);
                fwrite((((Asset3 *)head->data)->string2), sizeof((((Asset3 *)head->data)->string2)), 1, fp);
            }
            else if(strcmp(((Asset4 *)head->data)->type, "Asset4") == 0){
                fwrite((((Asset4 *)head->data)->type), sizeof((((Asset4 *)head->data)->type)), 1, fp);
                fwrite(&(((Asset4 *)head->data)->value1), sizeof(double), 1, fp);
                fwrite(&(((Asset4 *)head->data)->value2), sizeof(float), 1, fp);
                fwrite(&(((Asset4 *)head->data)->value3), sizeof(double), 1, fp);
            }
            head = head->next;
        }
        fclose(fp);
    }
}

void deserializeLinkedList(struct Node **head){
    FILE *fp = fopen("linkledlist.bin", "rb");

    if(fp == NULL) {
        printf("File could not open!\n");
    }
    else {
        char str[20]; /* String to determine data type */
        int i;
        
        /* Read the data type from file until fread() returns 0 */
        while(fread(str, sizeof(str), 1, fp) == 1) {

            /* Determine the appropriate data type by comparing str which was read from file and type of Asset */
            if(strcmp(str,"Asset1") == 0) {
                /* Allocate memory and assign values which are read from file */
                Asset1 *asset1 = (Asset1 *)malloc(sizeof(Asset1));
                strcpy(asset1->type, str);
                fread(&(asset1->ivals[0]), sizeof(int), 1, fp);
                fread(&(asset1->svals[0]), sizeof(double), 1, fp);

                /* Insert the node to the linked list */
                insert(head, asset1);
            }
            else if(strcmp(str,"Asset2") == 0) {
                /* Allocate memory and assign values which are read from file */
                Asset2 *asset2 = (Asset2 *)malloc(sizeof(Asset2));
                strcpy(asset2->type, str);
                for(i=0; i<2; i++){
                    fread(&(asset2->ivals[i]), sizeof(int), 1, fp);
                    fread(&(asset2->svals[i]), sizeof(double), 1, fp);
                }

                /* Insert the node to the linked list */
                insert(head, asset2);
            }
            else if(strcmp(str,"Asset3") == 0) {
                /* Allocate memory and assign values which are read from file */
                Asset3 *asset3 = (Asset3 *)malloc(sizeof(Asset3));
                strcpy(asset3->type, str);
                fread(asset3->string1, sizeof(asset3->string1), 1, fp);
                fread(asset3->string2, sizeof(asset3->string2), 1, fp);

                /* Insert the node to the linked list */
                insert(head, asset3);
            }
            else if(strcmp(str,"Asset4") == 0) {
                /* Allocate memory and assign values which are read from file */
                Asset4 *asset4 = (Asset4 *)malloc(sizeof(Asset4));
                strcpy(asset4->type, str);
                fread(&(asset4->value1), sizeof(double), 1, fp);
                fread(&(asset4->value2), sizeof(float), 1, fp);
                fread(&(asset4->value3), sizeof(double), 1, fp);
                
                /* Insert the node to the linked list */
                insert(head, asset4);
            }
        }
        fclose(fp);
    }
}

void insert(struct Node **head, void *data){

    /* Insert the node to the linked list */
    struct Node *new = (Node *)malloc(sizeof(Node));
    new->data = data;
    new->next = NULL;

    if((*head) == NULL) {
        (*head) = new;
    }
    else {  
        struct Node *temp = (*head);
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = new;
        new->next = NULL;
    }
}

void print(struct Node *head){
    while(head != NULL){

        /* If the appropriate data type is found, print it to terminal with appropriate values */
        if(strcmp(((Asset1 *)head->data)->type, "Asset1") == 0) {
            printf("type: %s, ", ((Asset1 *)head->data)->type);
            printf("ivals[0]: %d, ", ((Asset1 *)head->data)->ivals[0]);
            printf("svals[0]: %.2lf\n", ((Asset1 *)head->data)->svals[0]);
        }
        else if(strcmp(((Asset2 *)head->data)->type, "Asset2") == 0){
            printf("type: %s, ", ((Asset2 *)head->data)->type);
            for(int i=0; i<2; i++){
                printf("ivals[%d]: %d, ", i, ((Asset2 *)head->data)->ivals[i]);    
                printf("svals[%d]: %.2lf, ", i, ((Asset2 *)head->data)->svals[i]);
            }
            printf("\n");
        }
        else if(strcmp(((Asset3 *)head->data)->type, "Asset3") == 0){
            printf("type: %s, ", ((Asset3 *)head->data)->type);
            printf("string1: %s, ", ((Asset3 *)head->data)->string1);
            printf("string2: %s\n", ((Asset3 *)head->data)->string2);
        }
        else if(strcmp(((Asset4 *)head->data)->type, "Asset4") == 0){
            printf("type: %s, ", ((Asset4 *)head->data)->type);
            printf("value1: %.2lf, ", ((Asset4 *)head->data)->value1);
            printf("value2: %.2lf, ", ((Asset4 *)head->data)->value2);
            printf("value3: %.2lf\n", ((Asset4 *)head->data)->value3);
        }
        head = head->next;
    }
}