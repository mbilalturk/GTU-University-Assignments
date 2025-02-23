#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book{
    char *isbn;
    char *title;
    char *author;
    int pub_year;
    int reserved;
    struct Book *next;
} Book;

typedef struct Student{
    char *name;
    int ID;
    char *bar_books;
    struct Student *next;
} Student;

/* Declarations of functions */
void barrowed_books_list(struct Student **sl, int ID);
void addBook(struct Book **bl, char *isbn, char *title, char *author, int pub_year, int method);
void deleteBook(struct Book **bl, char *isbn);
void updateBook(struct Book **bl, char *isbn, char *feature, char *value);
void filterAndSortBooks(struct Book **bl, int filterChoice, char *filter, int sortChoice);
void reverseBookList(struct Book **bl);
void searchBooks(struct Book **bl, int searchChoice, char *searchValue);
void borrowBook(struct Book **bl, char *isbn);
void returnBook(struct Book **bl, char *isbn);
void read_books_from_file(struct Book **bl, const char *filename);
void read_students_from_file(struct Student **sl, const char *filename);
void print_to_file(struct Book **bl);
void print_to_screen(struct Book **bl);
void arrangeBook(struct Book *bl, struct Book **fl, int sortChoice);

int main(){    
    struct Book *bl = NULL;
    struct Student *sl = NULL;
    int option;
    char *isbn, *title, *author, *feature, *value, *filter;
    int *pub_year, *reserved, *choice, *choice2, *ID;

    /* Reading data from files */
    read_books_from_file(&bl, "library.txt");
    read_students_from_file(&sl, "student.txt");     

    /* Take input from user what they want until they chooce exit option */
    do{
        printf("***** Welcome to Book Management System *****\n1- Display the list of books\n2- Add Book\n3- Delete Book\n4- Update Book\n5- Filter and Sort Book\n6- Reverse Book\n7- Search Book\n8- Borrow Book\n9- Return Book\n10- Exit\n");
        scanf(" %d", &option);

        /* Take appropriate input from user and call appropriate funciton */
        switch(option){
            case 1: 
                    ID = (int *)malloc(sizeof(int));

                    printf("Enter ID: ");
                    scanf(" %d", ID);

                    barrowed_books_list(&sl, *ID);
                    break;
            case 2: 
                    isbn = (char *)malloc(30);
                    title= (char *)malloc(30);
                    author = (char *)malloc(30);
                    pub_year = (int *)malloc(sizeof(int));
                    reserved = (int *)malloc(sizeof(int));

                    printf("Enter isbn: ");
                    scanf(" %[^\n]s", isbn);

                    printf("Enter title: ");
                    scanf(" %[^\n]s", title);
                    printf("Enter author: ");
                    scanf(" %[^\n]s", author);
                    printf("Enter publication year: ");
                    scanf(" %d", pub_year);
                    printf("Enter method: ");
                    scanf(" %d", reserved);

                    addBook(&bl, isbn, title, author, *pub_year, *reserved);
                    print_to_file(&bl);
                    break;
            case 3:
                    isbn = (char *)malloc(30);

                    printf("Enter isbn: ");
                    scanf(" %[^\n]s", isbn);

                    deleteBook(&bl, isbn);
                    print_to_file(&bl);
                    break;
            case 4:
                    isbn = (char *)malloc(30);
                    feature = (char *)malloc(30);
                    value = (char *)malloc(30);

                    printf("Enter isbn: ");
                    scanf(" %[^\n]s", isbn);
                    printf("Enter feature: ");
                    scanf(" %[^\n]s", feature);
                    printf("Enter  value: ");
                    scanf(" %[^\n]s", value);

                    updateBook(&bl, isbn, title, author);
                    break;
            case 5: 
                    choice = (int *)malloc(sizeof(int));
                    filter = (char *)malloc(30);
                    choice2 = (int *)malloc(sizeof(int));

                    printf("Enter filter choice: ");
                    scanf(" %d", choice);
                    printf("Enter filter: ");
                    scanf(" %[^\n]s", filter);
                    printf("Enter filter choice: ");
                    scanf(" %d", choice);

                    filterAndSortBooks(&bl, *choice, filter, *choice2);
                    break;
            case 6:
                    reverseBookList(&bl);
                    break;
            case 7:
                    choice = (int *)malloc(sizeof(int));
                    value = (char *)malloc(30);

                    printf("Enter search choice: ");
                    scanf(" %d", choice);
                    printf("Enter search value: ");
                    scanf(" %[^\n]s", value);

                    searchBooks(&bl, *choice, value);
                    break;
            case 8:
                    isbn = (char *)malloc(30);

                    printf("Enter isbn: ");
                    scanf(" %[^\n]s", isbn);

                    borrowBook(&bl, isbn);
                    print_to_file(&bl);
                    break;
            case 9:
                    isbn = (char *)malloc(30);
                    printf("Enter isbn: ");
                    scanf(" %[^\n]s", isbn);

                    returnBook(&bl, isbn);
                    print_to_file(&bl);
                    break;
            case 10:
                    printf("Program terminated!\n");
            default: printf("Invalid Input!\n");
        }
        printf("\n");
    }while(option != 10);
    
}

void barrowed_books_list(struct Student **sl, int ID){
    struct Student *temp = (*sl);

    /* When ID taken from user and one of the student Id is matching, print books */
    while(temp != NULL){
        if(temp->ID == ID){
            printf("%s\n",temp->bar_books);
        }
        temp = temp->next;
    }  
}

void addBook(struct Book **bl, char *isbn, char *title, char *author, int pub_year, int method){
    struct Book *nb;
    nb = (struct Book *)malloc(sizeof(Book));
    nb->isbn = isbn;
    nb->title = title;
    nb->author = author;
    nb->pub_year = pub_year;
    nb->reserved = 0;
    nb->next = NULL;

    /* Insert book to linked list */
    if((*bl) == NULL){
        (*bl) = nb;
    }
    else{
        if(method == 0){ // FIFO
            nb->next = (*bl);
            (*bl) = nb;
        }
        else{ // LIFO
            struct Book *temp = (*bl);
            while((*bl)->next != NULL){
                (*bl) = (*bl)->next;
            }
            (*bl)->next = nb;
            (*bl) = temp;
        }
    }
}

void deleteBook(struct Book **bl, char *isbn){

    /* Delete book from linked list */
    if((*bl) == NULL){
        printf("Library is empty!\n");
        return;
    }
    else{
        struct Book *c, *p;
        c = *bl;
        p = NULL;
        while(c->isbn != isbn && c->next != NULL){
            p = c;
            c = c->next;
        }
        if(p == NULL){ // First entry
           (*bl) = (*bl)->next;
            free(p);
        }
        else{ // Middle or Last entry OR Not Found 
            if(c->isbn != isbn){ // Not Found
                printf("The book whose isbn is '%s' was not found!\n", isbn);
                return;
            }
            else{ // Middle or Last entry
                p->next = c->next;
            }
        }
        printf("The book whose isbn is '%s' was deleted succesfully!\n", isbn);
        free(c);
        print_to_file(bl);
    }
}

void updateBook(struct Book **bl, char *isbn, char *feature, char *value){
    
    /* Update Book from linked list */
    if((*bl == NULL)){
        printf("File is empty!\n");
    }
    else{
        struct Book *temp = (*bl);

        while(temp->isbn != isbn && temp->next != NULL){
            temp = temp->next;
        }
        if(temp->isbn != isbn){ // isbn Not Found
            printf("The book whose isbn is '%s' was not found!\n", isbn);
            return;
        }
        else{ 
            if((strcmp("title",feature)) == 0){
                temp->title = value;
            }
            else if((strcmp("author",feature)) == 0){
                temp->author = value;
            }
            else if((strcmp("publication year",feature)) == 0){
                temp->pub_year = atoi(value);
            }
            else{
                printf("Print enter appropriate feature!\n");
            }
            print_to_file(bl);
        }
    }
}

void filterAndSortBooks(struct Book **bl, int filterChoice, char *filter, int sortChoice){
    struct Book *temp = (*bl);
    struct Book *fl = NULL;

    if((*bl) == NULL){
        printf("File is empty!\n");
    }
    else{
        while(temp != NULL){
            switch(filterChoice){
                case 0: /* If filter and autor or filter and publication year coincide, call arrangeBook() funciton to sort */
                        if(strcmp(temp->author,filter) == 0){
                            arrangeBook(temp, &fl, sortChoice);
                        }
                        break;    
                case 1:
                        if(temp->pub_year == atoi(filter)){
                            arrangeBook(temp, &fl, sortChoice);
                        }
                        break;
                default:
                        printf("Enter appropriate filter choice!\n"); return;
            }
            temp = temp->next;
        }
        print_to_screen(&fl);
        free(fl);
    }
}

void reverseBookList(struct Book **bl){
    struct Book *prev = NULL;
    struct Book *curr = (*bl);
    struct Book *next = NULL;

    /* Reverse books */
    if((*bl) == NULL){
        printf("File is empty!\n");
    }
    else{
        while(curr != NULL){
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }   
        (*bl) = prev;
    }
    print_to_screen(bl);
    print_to_file(bl);
}

void searchBooks(struct Book **bl, int searchChoice, char *searchValue){
    struct Book *temp = (*bl);
    int counter=1;

    /* When search value and one of the book's isbn, author or title coincide, print */
    if((*bl) == NULL){
        printf("File is empty!\n");
    }
    else{
        while(temp != NULL){
            switch(searchChoice){
                case 0:
                        if(strcmp(temp->isbn,searchValue) == 0){
                            printf("ISBN: %s, Title: %s, Author: %s, Publication Year: %d, Reserved Status: %d\n", temp->isbn, temp->title, temp->author, temp->pub_year, temp->reserved);
                            counter++;
                        }
                        break;
                case 1:
                        if(strcmp(temp->author,searchValue) == 0){
                            printf("%d-) ISBN: %s, Title: %s, Author: %s, Publication Year: %d, Reserved Status: %d\n", counter, temp->isbn, temp->title, temp->author, temp->pub_year, temp->reserved);
                            counter++;
                        }
                        break;
                case 2:
                        if(strcmp(temp->title,searchValue) == 0){
                            printf("%d-) ISBN: %s, Title: %s, Author: %s, Publication Year: %d, Reserved Status: %d\n", counter, temp->isbn, temp->title, temp->author, temp->pub_year, temp->reserved);
                            counter++;
                        }
                        break;
                default:
                        printf("Enter appropriate search choice!\n"); return;
            }
            temp = temp->next;
        }

        if(counter == 1){
            printf("No books found!\n");
        }
    }
}

void borrowBook(struct Book **bl, char *isbn){
    struct Book *temp = (*bl);

    if((*bl) == NULL){
        printf("File is empty!\n");
    }
    else{
        while(temp->next != NULL){
            if(strcmp(temp->isbn, isbn) == 0){
                temp->reserved = 1;
                return;
            }
            temp = temp->next;
        }
    }
}

void returnBook(struct Book **bl, char *isbn){
    struct Book *temp = (*bl);

    if((*bl) == NULL){
        printf("File is empty!\n");
    }
    else{
        while(temp->next != NULL){
            if(strcmp(temp->isbn, isbn) == 0){
                temp->reserved = 0;
                return;
            }
            temp = temp->next;
        }
    }
}

void read_books_from_file(struct Book **bl, const char *filename){
    FILE *fp = fopen(filename, "r+");
    char *isbn, *title, *author, *ignore;
    int *pub_year, *reserved;
    int num = 0, i;
    char ch;

    /* Fill linked list by taken input from file */
    if(fp == NULL){
        printf("File could not open!\n");
    }
    else{
        while((ch = getc(fp)) != EOF){
            if(ch == '\n')
                num++;
        }

        rewind(fp);

        for(i=0; i<num; i++){
            isbn = (char *)malloc(30);
            title= (char *)malloc(30);
            author = (char *)malloc(30);
            ignore = (char *)malloc(sizeof(char));
            pub_year = (int *)malloc(sizeof(int));
            reserved = (int *)malloc(sizeof(int));

            fscanf(fp, " %[^,],", isbn);
            fscanf(fp, " %[^,],", title);
            fscanf(fp, " %[^,],", author);
            fscanf(fp, " %d,", pub_year);
            fscanf(fp, " %d\n", reserved);

            addBook(bl, isbn, title, author, *pub_year, *reserved);
        }

        fclose(fp);
    }
}

void read_students_from_file(struct Student **sl, const char *filename){
    FILE *fp = fopen(filename, "r+");
    char *name, *barrowed;
    int *ID;
    int num = 0, i;
    char ch;

    /* Fill linked list by taken input from file */
    if(fp == NULL){
        printf("File could not open!\n");
    }
    else{
        while((ch = getc(fp)) != EOF){
            if(ch == '\n')
                num++;
        }

        rewind(fp);

        for(i=0; i<num; i++){
            struct Student *ns;
            ns = (Student *)malloc(sizeof(Student));

            name = (char *)malloc(30);
            ID = (int *)malloc(sizeof(int));
            barrowed = (char *)malloc(30);

            
            fscanf(fp, " %[^,],", name);
            fscanf(fp, " %d,", ID);
            fscanf(fp, " %[^\n]", barrowed);

            ns->name = name;
            ns->ID = *ID;
            ns->bar_books = barrowed;

            /* Insert linked list at the end */
            if((*sl) == NULL){
                (*sl) = ns;
            }
            else{
                struct Student *temp = (*sl);
                while((*sl)->next != NULL){
                    (*sl) = (*sl)->next;
                }
                (*sl)->next = ns;
                (*sl) = temp;
            }
        }
        fclose(fp);
    }
}

void print_to_file(struct Book **bl){
    FILE *fp = fopen("library.txt", "w");

    if(fp == NULL){
        printf("File could not open!\n");
        return;
    }
    else{
        struct Book *temp = *bl;

        while(temp != NULL){
            fprintf(fp, "%s,%s,%s,%d,%d\n", temp->isbn, temp->title, temp->author, temp->pub_year, temp->reserved);
            temp = temp->next;
        }
        fclose(fp);
    }
}

void print_to_screen(struct Book **bl){
    struct Book *temp = *bl;

    while(temp != NULL){
        printf("%s,%s,%s,%d,%d\n", temp->isbn, temp->title, temp->author, temp->pub_year, temp->reserved);
        temp = temp->next;
    }   
}

void arrangeBook(struct Book *bl, struct Book **fl, int sortChoice){
    int counter=0;
    struct Book *nb;
    nb = (struct Book *)malloc(sizeof(Book));
    nb->isbn = bl->isbn;
    nb->title = bl->title;
    nb->author = bl->author;
    nb->pub_year = bl->pub_year;
    nb->reserved = bl->reserved;
    nb->next = NULL;

    if ((*fl) == NULL) {
        (*fl) = nb;
    } else {
        struct Book *prev = NULL;
        struct Book *current = (*fl);
        int counter = 0;

        switch (sortChoice) {
            case 0: // Sort by title
                while (current != NULL && strcmp(current->title, nb->title) <= 0) {
                    prev = current;
                    current = current->next;
                    counter++;
                }
                break;
            case 1: // Sort by author
                while (current != NULL && strcmp(current->author, nb->author) <= 0) {
                    prev = current;
                    current = current->next;
                    counter++;
                }
                break;
            case 2: // Sort by publication year
                while (current != NULL && current->pub_year <= nb->pub_year) {
                    prev = current;
                    current = current->next;
                    counter++;
                }
                break;
            default:
                printf("Enter appropriate sort choice!\n");
                return;
        }

        if (prev == NULL) { // Insert at the beginning
            nb->next = (*fl);
            (*fl) = nb;
        } else if (current == NULL) { // Insert at the end
            prev->next = nb;
        } else { // Insert in the middle
            prev->next = nb;
            nb->next = current;
        }
    }
}