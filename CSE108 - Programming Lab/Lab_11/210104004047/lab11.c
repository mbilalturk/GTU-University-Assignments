#include <stdio.h>
#include <stdlib.h>

typedef struct Order{
    char *customerName;
    int orderID;
    char *items;
    char *orderTime;
    struct Order *next;
} Order;

typedef struct ExamPaper{
    char *studentName;
    int studentNumber;
    int score;
    struct ExamPaper *next;
} ExamPaper;

Order *enqueue(Order *queue, char *customerName, int orderID, char *items, char *orderTime);
Order *dequeue(Order *queue);
void display(Order *queue);

ExamPaper *push(ExamPaper *stack, char *studentName, int studentNumber, int score);
ExamPaper *pop(ExamPaper *stack);
int isEmpty(ExamPaper *stack);
void display2(ExamPaper *queue);

int main(){
    Order *queue = NULL;
    
    queue = enqueue(queue, "Zehra Bilici", 101, "Pizza, Salad, Ice Cream", "12.5");
    queue = enqueue(queue, "Bariş Özcan", 102, "Burger, Fries, Coke", "13.3");
    queue = dequeue(queue);
    queue = enqueue(queue, "Mehmet Burak Koca", 103, "Steak, Mashed Patatoes, Salad", "14.3");
    
    display(queue);

    /* PART 2 */
    ExamPaper *stack = NULL;

    stack = push(stack, "Zehra Bilici", 202200001, 90);
    
    stack = push(stack, "Bariş Özcan", 202200002, 85);
    display2(stack); 
    stack = push(stack, "Mehmet Burak Koca", 202200003, 95);
    
    stack = pop(stack);
    
    
    return (0);
}

Order *enqueue(Order *queue, char *customerName, int orderID, char *items, char *orderTime){
    Order *new;
    new = (Order *)malloc(sizeof(Order));
    new->customerName = customerName;
    new->orderID = orderID;
    new->items = items;
    new->next = NULL;

    if(queue != NULL){
        Order *last;
        last = queue;
        while(last->next != NULL){
            last = last->next;
        }
        last->next = new; 
    } else{
        queue = new;
    }

    return queue;
}

Order *dequeue(Order *queue){
    Order *last, *prev;
    last = queue;

    while(last->next != NULL){
        prev = last;
        last = last->next;
    }
    prev->next = NULL;
    free(last);

    return queue;
}

void display(Order *queue){

    if(queue != NULL){
        while(queue->next != NULL){
            printf("Enqueued Order ID: %d, Customer Name: %s, Items: %s\n",queue->orderID, queue->customerName, queue->items);    
            queue = queue->next;
        }
        printf("Enqueued Order ID: %d, Customer Name: %s, Items: %s\n",queue->orderID, queue->customerName, queue->items);    
    }
}

ExamPaper *push(ExamPaper *stack, char *studentName, int studentNumber, int score){
    ExamPaper *new;
    new = (ExamPaper *)malloc(sizeof(ExamPaper));
    new->studentName = studentName;
    new->studentNumber = studentNumber;
    new->score = score;
    new->next = NULL;

    if(stack == NULL){
        stack = new;
    }else{
        while(stack->next != NULL){
            stack = stack->next;
        }
        stack->next = new;
    }

    return stack; 
}

ExamPaper *pop(ExamPaper *stack){
    ExamPaper *last, *prev;
    last = stack;

    while(last->next != NULL){
        prev = last;
        last = last->next;
    }
    prev->next = NULL;
    free(last);
    
    return stack;
}

int isEmpty(ExamPaper *stack){
    int res;

    if(stack->next == NULL){
        res = 1;
    }else{
        res = 0;
    }
    return res;
}

void display2(ExamPaper *stack){
    if(stack != NULL){
        while(stack->next != NULL){
            printf("%s, Student number: %d, Score: %d\n", stack->studentName, stack->studentNumber, stack->score);    
            stack = stack->next;
        }
        printf("%s, Student number: %d, Score: %d\n", stack->studentName, stack->studentNumber, stack->score); 
    }
}