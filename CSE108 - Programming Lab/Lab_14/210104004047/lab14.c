#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Order{
    char *customerName;
    int orderID;
    char *items;
    time_t order_time;
    struct Order *next;
} Order;

void enqueue(Order **list, char *customerName, int orderID, char *items, time_t order_time);
void dequeue(Order **list, time_t thresholdTime);
Order *push(Order *list, char *customerName, int orderID, char *items, time_t order_time);
void pop(Order **list);
void serializeFIFO(Order *queue, const char *filename);
Order *deserializeFIFO(const char *filename);
void serializeLIFO(Order *stack, const char *filename);
Order *deserializeLIFO(const char *filename);
void print_order(Order *list);

int main(){

    struct Order *root = NULL;
    struct Order *serialized;
    time_t thresholdTime;

    root = push(root, "Burak", 21, "Ekmek", time(NULL));
    root = push(root, "Baris", 24, "Cay", time(NULL));
    enqueue(&root, "Zehra", 26, "Su", time(NULL));

    thresholdTime = time(NULL) - 500;
    print_order(root);
    // dequeue(&root, thresholdTime);

    print_order(root);
    serializeFIFO(root, "binary.dot");
    serialized = deserializeFIFO("binary.dot");

    serializeLIFO(root, "binary.dot");
    serialized = deserializeLIFO("binary.dot");

    print_order(serialized);
    

    return 0;
}

void enqueue(Order **list, char *customerName, int orderID, char *items, time_t order_time){
    struct Order *new;
    new = (Order *)malloc(sizeof(Order));
    new->customerName = customerName;
    new->orderID = orderID;
    new->items = items;
    new->order_time = order_time;
    new->next = NULL;
    
    if((*list) == NULL){
        (*list) = new;
    }
    else{
        struct Order *temp = *list;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = new;
    }

}

void dequeue(Order **list, time_t thresholdTime){

    if((*list) == NULL){
        return;
    }
    else{
        struct Order *last, *temp = *list;

        while(temp->next != NULL){
            last = temp;
            temp = temp->next;
        }
        last->next = NULL;
        free(temp);

        struct Order *root = NULL;
        struct Order *temp2 = *list;

        while(temp2->next != NULL){
            if(temp2->order_time > thresholdTime){
                enqueue(&root, temp2->customerName, temp2->orderID, temp2->items, temp2->order_time);
            }
            temp2 = temp2->next;
        }
        *list = root;
    }
}

Order *push(Order *list, char *customerName, int orderID, char *items, time_t order_time){
    struct Order *new;
    new = (Order *)malloc(sizeof(Order));
    new->customerName = customerName;
    new->orderID = orderID;
    new->items = items;
    new->order_time = order_time;
    
    if(list == NULL){
        new->next = NULL;
    }
    else{
        new->next = list;
    }
    return new;
}

void pop(Order **list){
    struct Order *temp = *list;
    
    if((*list) != NULL){
        (*list) = (*list)->next;
        free(temp);
    }
}

void serializeFIFO(Order *queue, const char *filename){
    FILE *fp = fopen(filename, "wb");

    if(fp == NULL){
        printf("File could not open!\n");
    }
    else{
        struct Order *temp = queue;
        while(temp != NULL){
            fwrite(temp, sizeof(Order), 1, fp);
            temp = temp->next;
        }
        fclose(fp);
    }
}

Order * deserializeFIFO(const char *filename){
    FILE *fp = fopen(filename, "rw");

    if(fp == NULL){
        printf("File could not open!\n");
    }
    else{
        struct Order *new;
        new = (Order *)malloc(sizeof(Order));

        while(fread(new, sizeof(Order), 1, fp) == 1){
            enqueue(&new, new->customerName, new->orderID, new->items, time(NULL));
        }
        fclose(fp);
        return new;
    }
}

void serializeLIFO(Order *stack, const char *filename){
    FILE *fp = fopen(filename, "wb");

    if(fp == NULL){
        printf("File could not open!\n");
    }
    else{
        struct Order *temp = stack;
        while(temp != NULL){
            fwrite(temp, sizeof(Order), 1, fp);
            temp = temp->next;
        }
        fclose(fp);
    }
}

Order * deserializeLIFO(const char *filename){
    FILE *fp = fopen(filename, "rw");

    if(fp == NULL){
        printf("File could not open!\n");
    }
    else{
        struct Order *new;
        new = (Order *)malloc(sizeof(Order));

        while(fread(new, sizeof(Order), 1, fp) == 1){
            new = push(new, new->customerName, new->orderID, new->items, time(NULL));
        }
        fclose(fp);
        return new;
    }
}

void print_order(Order *list){

    while(list != NULL){
        printf("Customer name: %s, Order ID: %d, Items: %s, Order Time: %ld\n", list->customerName, list->orderID, list->items, list->order_time);
        list = list->next;
    }
}