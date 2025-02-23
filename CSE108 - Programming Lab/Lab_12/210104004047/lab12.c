#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Customer{
    char *name;
    int age;
    char *pri_name;
    int pri_level;
    struct Customer *prev, *next;
} Customer;

Customer * insertCustomer(Customer * head);
Customer * removeCustomer(Customer * head);
void display(Customer *head);
int searchCustomer(Customer *head, char *name);
void changePriority(Customer *head);

int main(){
    Customer *customer = NULL;
    int option;
    
    do{
        printf("**************************\nWelcome to the ABC Bank\n");
        printf("1. Insert\n2. Remove\n3. Display\n4. Search\n5. Change priority settings\n6. Exit\n");
        printf("Please select an option: ");
        scanf(" %d", &option);

        switch(option){
            case 1: customer = insertCustomer(customer); break;
            case 2: customer = removeCustomer(customer); break;
            case 3: display(customer); break;
            case 4:
                    char *str;
                    str = (char *)malloc(20);
                    printf("Please enter customer's Name: ");
                    scanf("%s", str);
                    searchCustomer(customer, str);
                    break;
            case 5: changePriority(customer); break;
            default: printf("Invalid input\n"); break;
        }
    } while( option != 6);

    printf("Program terminated!\n");

    return(0);
}

Customer * insertCustomer(Customer * head){
    char *str;
    str = (char *)malloc(20);
    Customer *newNode;
    newNode = (Customer *)malloc(sizeof(Customer));

    printf("Please enter customer's Name: ");
    scanf("%s", str);
    newNode->name = (char *)malloc(sizeof(strlen(str)));
    strncpy(newNode->name,str,strlen(str));

    printf("Please enter customer's Age: ");
    scanf(" %d", &newNode->age);
    
    printf("Please enter customer's Priority Group: ");
    scanf("%s", str);
    newNode->pri_name = (char *)malloc(sizeof(strlen(str)));
    strncpy(newNode->pri_name,str,strlen(str));

    newNode->next = NULL;
    newNode->prev = NULL;

    free(str);

    if(strcmp(newNode->pri_name, "NORMAL") == 0){
        newNode->pri_level = 1;
    }
    else if(strcmp(newNode->pri_name, "VETERAN") == 0){
        newNode->pri_level = 2;
    }
    else if(strcmp(newNode->pri_name, "OD") == 0){
        newNode->pri_level = 3;
    }
    else if(strcmp(newNode->pri_name, "VIP") == 0){
        newNode->pri_level = 4;
    }
     int num = 0;
    printf("%d\n", num);
    Customer *t;
   
    t = head;

    while(t!=NULL){
        num++;
        t= t->next;
    }
    printf("%d\n", num);
    if((head == NULL)){
        head = newNode;
    }
    else if(num == 1){
        if(newNode->pri_level > head->pri_level){
            head->prev = newNode;
            newNode->next = head;
            return newNode;
        } 
        else{
            head->next = newNode;
            newNode->prev = head;
            return head; 
        }
    }
    else {
        Customer *temp;
        temp = head;

        while(temp != NULL){
            if(newNode->pri_level > temp->pri_level){
                // temp = temp->next;
                break;
            } 
            temp = temp->next;
        }

        newNode->prev = temp->next;
        temp->prev->next = newNode->prev;
        newNode->next = temp->prev;
        temp->prev = newNode->next; 
    }
    
    return head;
}

Customer * removeCustomer(Customer * head){
    char *str;
    str = (char *)malloc(20);
    printf("Please enter customer's Name: ");
    scanf("%s", str);

    Customer * temp = head;

    while(temp != NULL){
        if(strcmp(temp->pri_name, str) == 0){
            temp->prev->next = temp->next;
            temp->next = temp->prev;
            free(temp);
            free(str);
            return head;
        }
        temp = temp->next;
    }
    return head;
}

void display(Customer *head){
    int i=1;
    while(head != NULL){
        printf("%d. %s - Age: %d - Priority Group: %s - Priority Level: %d\n", i, head->name, head->age, head->pri_name, head->pri_level);
    i++;
    head = head->next;
    }
}

int searchCustomer(Customer *head, char *name){

    if(head == NULL){
        printf("Could not found!\n");
        return 0;
    }
    else if(strcmp(head->name, name) == 0){
        printf("%s - Age: %d - Priority Group: %s - Priority Level: %d\n",head->name, head->age, head->pri_name, head->pri_level);
    }
    else{
        searchCustomer(head->next, name);
    }
}

void changePriority(Customer *head){
    char *str;
    int new_level;
    str = (char *)malloc(20);
    printf("Please enter customer's Name: ");
    scanf("%s", str);

    printf("Please enter new Priority Level: ");
    scanf(" %d", &new_level);

    while(head != NULL){
        if(strcmp(head->name, str) == 0){
            head->pri_level = new_level;
            free(str);
            printf("Priority level changed successfully...\nNew properties are fallowing:\n");
            printf("%s - Age: %d - Priority Group: %s - Priority Level: %d\n", head->name, head->age, head->pri_name, head->pri_level);
        }
        head = head->next;
    }
}
