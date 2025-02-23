#include <stdio.h>
#include <string.h>
#include "util.h"

#define NUM 50

void menu(){
    int operator;

    do{
        printf("*********** WELCOME ***********\n1- File Operations\n2- Query Products\n3- Check Stock Status\n4- Stock Control by Brand\n5- Export Report\n");
        printf("Please enter what you want: ");
        scanf("%d", &operator);

        /* Call appropriate function */
        switch(operator){
            case 1: file_operations(); break;
            case 2: search_product(); break;
            case 3: check_stock_status(); break;
            case 4: list_products_of_brand(); break;
            case 5: break;
            default:
                printf("Please enter appropriate operator!\n");
        }
    }
    while(operator != 5);
}

void file_operations(){
    int file_option;
    int pID[NUM], take_pID[NUM];
    int stock_ID[NUM];
    int current_stock[NUM];
    int *number, order = 0, *times, stock = 0;
    char type[NUM];
    char name[NUM][9];
    char brand[NUM][6];
    char branch[NUM][16];
    char new_feature[NUM][NUM];
    char type_of_variable[NUM] = {0};
    char name_of_feature[NUM][NUM];
    double price[NUM];
    
    number = &order;
    times = &stock;
    
    /* Call read_ptxt() and read_stxt() function to read products.txt and stocks.txt */
    read_ptxt(pID, type, name, brand, price, number, type_of_variable, name_of_feature, new_feature);
    read_stxt(stock_ID, pID, branch, current_stock, times, take_pID);

    do{
        printf("\n1- Add a new product\n2- Delete a product\n3- Update a product\n4- Add feature to products\n5- Add a new stock entry\n6- Delete a stock entry\n7- Update a stock entry\n8- Back to main menu\n");
        printf("Please enter what you want: ");
        scanf(" %d", &file_option);

        /* Call appropriate funciton */
        switch(file_option){
            case 1: add_product(pID, type, name, brand, price, number, type_of_variable, name_of_feature, new_feature); break;
            case 2: delete_product(pID, type, name, brand, price, number, type_of_variable, name_of_feature, new_feature); break;
            case 3: update_product(pID, type, name, brand, price, number, type_of_variable, name_of_feature, new_feature); break;
            case 4: add_feature(pID, type, name, brand, price, number, type_of_variable, name_of_feature); break;
            case 5: add_stock_entry(stock_ID, pID, branch, current_stock, times, take_pID); break;
            case 6: delete_stock_entry(stock_ID, pID, branch, current_stock, times, take_pID); break;
            case 7: update_stocks(stock_ID, pID, branch, current_stock, times, take_pID); break;
            case 8: break;
            default: printf("Please enter appropriate option!\n"); break;
        }
    }
    while(file_option != 8);
    printf("\n");
}

void search_product(){
    int search_option;
    int pID[NUM];
    int *number, order = 0;
    char type[NUM];
    char name[NUM][9];
    char brand[NUM][6];
    double price[NUM];
    
    number = &order;
    do{
       printf("\n1- List all products\n2- Filter products by brand,type,price ,or a user-defined feature\n3- Back to main menu\n");
        printf("Please enter what you want: ");
        scanf(" %d", &search_option);

        /* Call appropriate function */
        switch(search_option){
            case 1: list_product(pID, type, name, brand, price, number); break;
            case 2: filter_product(pID, type, name, brand, price, number); break;
            case 3: break;
            default: printf("Please enter appropriate option!\n"); break;
        }
    }
    while(search_option != 3);
    printf("\n");
}

void check_stock_status(){
    int status_option;
    int stock_ID[NUM], pID[NUM], take_pID[NUM];
    int current_stock[NUM];
    int *counter, status = 0;
    char branch[NUM][16];
    
    counter = &status;

    do{
       printf("\n1- Stock of all product\n2- List the stock of all products\n3- List out-of-stock products\n4- Back to main menu\n");
        printf("Please enter what you want: ");
        scanf(" %d", &status_option);

        /* Call appropriate function */
        switch(status_option){
            case 1: stock_of_product(stock_ID, pID, branch, current_stock, counter, take_pID); break;
            case 2: list_stock(stock_ID, pID, branch, current_stock, counter, take_pID); break;
            case 3: list_out_of_stock(stock_ID, pID, branch, current_stock, counter, take_pID); break;
            case 4: break;
            default: printf("Please enter appropriate option!\n"); break;
        }
    }
    while(status_option != 4);
    printf("\n");
}

void list_products_of_brand(){
    int pID[NUM], take_pID[NUM], stock_ID[NUM], current_stock[NUM], counter_b[NUM];
    char type[NUM], name[NUM][9], brand[NUM][6], branch[NUM][16];
    int *number, order = 0;
    double price[NUM];
    int i, j;
    
    number = &order;
    /* Call brand_control() function to print pID, price and current_stock */
    j = brand_control(pID, type, name, brand, price, number, stock_ID, branch, current_stock, take_pID, counter_b);

    /* print pID, price and current_stock which are allocated in counter_b() array */
    for(i=0; i<j; i++){
        printf("pID,price,current stock: %d,%.1lf,%d\n", pID[counter_b[i]], price[counter_b[i]], current_stock[counter_b[i]]);
    }   
}

void write_ptxt(int pID[NUM], char type[NUM], char name[NUM][9], char brand[NUM][6], double price[NUM], int *number, char type_of_variable[NUM], char name_of_feature[NUM][NUM]){
    FILE *outp = fopen("products.txt", "w+");
    int i, j=0, id;

    if(outp == NULL)
        printf("File could not open!\n");
    else {
        fprintf(outp, "pID,Type,Name,Brand,Price\n");

        /* Print features of products to a file */
        for(i=0;i<(*number); i++){
            fprintf(outp, "%d,%c,%s,%s,%.1lf\n",pID[i], type[i], name[i], brand[i], price[i]);
        }
    }
    fclose(outp);
}

void read_ptxt(int pID[NUM], char type[NUM], char name[NUM][9], char brand[NUM][6], double price[NUM], int *number, char type_of_variable[NUM], char name_of_feature[NUM][NUM], char new_feature[NUM][NUM]){
    FILE *inp = fopen("products.txt", "r");
    char c;
    int i, j=0;
    
    if(inp == NULL)
        printf("File could not open\n");
    else{
        /* Ignore first line of the file */
        while((c=fgetc(inp) != '\n'));
        
        /* Count number of line of the file */
        (*number)=0;
        while((c = fgetc(inp)) != EOF){
            if(c=='\n')
                (*number)++;
        } 

        /* Start to read from begginnig of a file */
        rewind(inp);
        while((c=fgetc(inp) != '\n'));

        /* Take values of products and assign them to appropriate array */
        for(i=0; i<(*number); i++){   
            fscanf(inp, "%d,%c,%[^,],%[^,],%lf", &pID[i], &type[i], name[i], brand[i], &price[i]);
        }
    }
    fclose(inp);
}

void read1(int pID[NUM], char type[NUM], char name[NUM][9], char brand[NUM][6], double price[NUM], int *number){
    FILE *inp = fopen("products.txt", "r");
    char c;
    int i, j=0;
    
    if(inp == NULL)
        printf("File could not open\n");
    else{
        /* Ignore first line of the file */
        while((c=fgetc(inp) != '\n'));
        
         /* Count number of line of the file */
        (*number)=0;
        while((c = fgetc(inp)) != EOF){
            if(c=='\n')
                (*number)++;
        } 

        /* Start to read from begginnig of a file */
        rewind(inp);
        while((c=fgetc(inp) != '\n'));

         /* Take values of products and assign them to appropriate array */
        for(i=0; i<(*number); i++){   
            fscanf(inp, "%d,%c,%[^,],%[^,],%lf", &pID[i], &type[i], name[i], brand[i], &price[i]);
        }
    }
    fclose(inp);
}

void read2(int sID[NUM], int pID[NUM], char branch[NUM][16], int current_stock[NUM], int *times, int take_pID[NUM]){
     FILE *inp = fopen("stocks.txt", "r+");
    char c;
    int i;

    if(inp == NULL)
        printf("File could not open\n");
    else{
        /* Ignore first line of the file */
        while((c=fgetc(inp) != '\n'));
        
         /* Count number of line of the file */
        (*times)=0;
        while((c = fgetc(inp)) != EOF){
            if(c=='\n')
                (*times)++;
        } 
        
        /* Start to read from begginnig of a file */
        rewind(inp);
        while((c=fgetc(inp) != '\n'));

         /* Take values of products and assign them to appropriate array */
        for(i=0; i<(*times); i++){   
            fscanf(inp, "%d,%d,%[^,],%d", &sID[i], &take_pID[i], branch[i], &current_stock[i]);
        }
    }
    fclose(inp);
}

void add_product(int pID[], char type[], char name[][9], char brand[][6], double price[], int *number, char type_of_variable[NUM], char name_of_feature[NUM][NUM], char new_feature[NUM][NUM]){
    FILE *outp = fopen("products.txt", "a+");
    int i,j;

    if(outp == NULL)
        printf("File could not open!\n");
    else {
        /* Start pID from 1 */
        pID[*number] = (*number+1);

        /* Take value for add product */
        printf("Enter type: ");
        scanf(" %c", &type[*number]);
        
        printf("Enter name: ");
        for(i=0; i<1; i++)
            scanf("%s", name[*number]);
        
        printf("Enter brand: ");
        for(i=0; i<1; i++)
            scanf("%s", brand[*number]);
        
        printf("Enter price: ");
        scanf(" %lf", &price[*number]);

        /* Print those values from file and print it to terminal */
        printf("%d,%c,%s,%s,%.1lf\n", pID[*number], type[*number], name[*number], brand[*number], price[*number]);
        fprintf(outp, "%d,%c,%s,%s,%.1lf\n", pID[*number], type[*number], name[*number], brand[*number],price[*number]);
        
        /* Implement (*number) by 1 to take value and assign it to index of an aray coming one after */
        (*number)++;
    }
    fclose(outp);
}

void delete_product(int pID[], char type[], char name[][9], char brand[][6], double price[], int *number, char type_of_variable[NUM], char name_of_feature[NUM][NUM], char new_feature[NUM][NUM]){
    FILE *outp = fopen("products.txt", "w+");
    int i, deleted_id;

    if(outp == NULL)
        printf("File could not open!\n");
    else {
        /* Take ıd user want to delete */
        printf("Enter pID that you want to delete: ");
        scanf(" %d", &deleted_id);

        /* Assign null to appropriate index of an array */
        pID[deleted_id-1] = '\0';
        type[deleted_id-1] = '\0';
        for(i=0; i<8; i++){
            name[deleted_id-1][i] = '\0';
        }
        for(i=0; i<5; i++){
            brand[deleted_id-1][i] = '\0';
        }
        price[deleted_id-1] = '\0';
    
        /* Print those values to a file without deleted one */
        fprintf(outp, "pID,Type,Name,Brand,Price\n");
        for(i=0; pID[i] != 0; i++){       
            fprintf(outp, "%d,%c,%s,%s,%.1lf\n",pID[i], type[i], name[i], brand[i], price[i]);        
        }
        for(i +=1; i<(*number); i++){       
            fprintf(outp, "%d,%c,%s,%s,%.1lf\n",i , type[i], name[i], brand[i], price[i]);        
        }  
    }    
    fclose(outp);

    /* Call read_ptxt() function to assign new values to appropriate array */
    read_ptxt(pID, type, name, brand, price, number, type_of_variable, name_of_feature, new_feature);
}

void update_product(int pID[NUM], char type[NUM], char name[NUM][9], char brand[NUM][6], double price[NUM], int *number, char type_of_variable[NUM], char name_of_feature[NUM][NUM], char new_feature[NUM][NUM]){
    FILE *outp = fopen("products.txt", "w+");
    int i, id;

    if(outp == NULL)
        printf("File could not open!\n");
    else {
        printf("Enter pID that you want to update: ");
        scanf(" %d", &id);
        
        printf("Enter your new name:");
        scanf("%s", name[id-1]);

        /* call write_ptxt() function to print new values to file */
        write_ptxt(pID, type, name, brand, price, number, type_of_variable, name_of_feature);
    }
    fclose(outp);
}

void add_feature(int pID[NUM], char type[NUM], char name[NUM][9], char brand[NUM][6], double price[NUM], int *number, char type_of_variable[NUM], char name_of_feature[NUM][NUM]){
    FILE *outp = fopen("products.txt", "w+");
    int size, i, j, k, filled = 0;
    char users_feature_s[NUM][NUM][8];

    if(outp == NULL){
        printf("File could not open!\n");
    }
    else{
        /* Implement filled by j+1 to use */
        for(j=0; type_of_variable[j] != '\0'; j++){
            filled = j+1;
        }
        
        /* Take the name of the feature from user */
        printf("Enter the name of the new feature: ");
        scanf("%s", name_of_feature[filled]);
        type_of_variable[filled] = 's';

        /* print name of new feature */
        fprintf(outp, "pID,Type,Name,Brand,Price");
        for(i=0; type_of_variable[i] != 0; i++){
            fprintf(outp, ",%s", name_of_feature[i]); 
        }
        fprintf(outp, "\n");

        /* Assing null character to array used before */
        if(type_of_variable[filled] == 's'){
            for(i=0; i<(*number); i++){
                for(j=0; j<8; j++){
                    users_feature_s[filled][i][j] = '\0';
                }
            }
        }

        /* print new values to file */
        for(i=0; i<(*number); i++){
            fprintf(outp, "%d,%c,%s,%s,%.1lf",pID[i], type[i], name[i], brand[i], price[i]);

            for(j=0; j<=filled; j++){
                if(type_of_variable[j] > 0){ 
                    fprintf(outp, ",%s", users_feature_s[filled][i]);
                }
            }
            fprintf(outp, "\n");
        }
    }
    fclose(outp);
}
        
void add_stock_entry(int sID[NUM], int pID[NUM], char branch[NUM][16], int current_stock[NUM], int *times, int take_pID[NUM]){
    FILE *inp_p = fopen("products.txt", "r+");
    FILE *outp_s = fopen("stocks.txt", "a+");
    int match_pID, i;

    if(inp_p == NULL || outp_s == NULL)
        printf("File couldn not open!\n");
    else{
        /* Start sID from 1 */
        sID[*times] = (*times+1);
        
        printf("Enter pID you want to add stock: ");
        scanf(" %d", &take_pID[*times]);

        /* Assign value taken from user to match_pID to print new values later */
        match_pID = pID[take_pID[*times]] - 1;

        printf("Enter branch: ");
        for(i=0; i<1; i++)
            scanf("%s", branch[*times]);
        
        printf("Enter current stock: ");
        scanf(" %d", &current_stock[*times]);

        /* Print new values to file */
        fprintf(outp_s, "%d,%d,%s,%d\n", sID[*times], pID[match_pID]-1, branch[*times], current_stock[*times]);
        (*times)++;
    }
    fclose(inp_p);
    fclose(outp_s);
}

void delete_stock_entry(int sID[NUM], int pID[NUM], char branch[NUM][16], int current_stock[NUM], int *times, int take_pID[NUM]){
    FILE *outp = fopen("stocks.txt", "w+");
    int i, deleted_id;

    if(outp == NULL)
        printf("File could not open!\n");
    else {
        printf("Enter pID that you want to delete: ");
        scanf(" %d", &deleted_id);

        /* Assign null to appropriate index of an array */
        sID[deleted_id-1] = '\0';
        for(i=0; i<8; i++){
            branch[deleted_id-1][i] = '\0';
        }
        current_stock[deleted_id-1] = '\0';
        
        /* Print those values to a file without deleted one */
        fprintf(outp, "sID,pID,branch,current_stock\n");
        for(i=0; sID[i] != 0; i++){    
           fprintf(outp, "%d,%d,%s,%d\n", sID[i], pID[take_pID[i]]-1, branch[i], current_stock[i]);   
        }
        for(i +=1; i<(*times); i++){     
            fprintf(outp, "%d,%d,%s,%d\n", sID[i], pID[take_pID[i]]-1, branch[i], current_stock[i]);   
        }  
    }    
    fclose(outp);

    /* Call read_stxt() function to assign new values to appropriate array */
    read_stxt(sID, pID, branch, current_stock, times,take_pID);
}

void update_stocks(int sID[NUM], int pID[NUM], char branch[NUM][16], int current_stock[NUM], int *times, int take_pID[NUM]){
     FILE *outp = fopen("stocks.txt", "w+");
    int id;

    if(outp == NULL)
        printf("File could not open!\n");
    else {
        printf("Enter pID that you want to update: ");
        scanf(" %d", &id);
        
        printf("Enter your new branch:");
        scanf("%s", branch[id-1]);

        printf("Enter your new stock:");
        scanf("%d", &current_stock[id-1]);

        /* call write_stxt() function to print new values to file */
        write_stxt(sID, pID, branch, current_stock, times, take_pID);
    }
    fclose(outp);
}

void read_stxt(int sID[NUM], int pID[NUM], char branch[NUM][16], int current_stock[NUM], int *times, int take_pID[NUM]){
    FILE *inp = fopen("stocks.txt", "r+");
    char c;
    int i;

    if(inp == NULL)
        printf("File could not open\n");
    else{
        /* Ignore first line of the file */
        while((c=fgetc(inp) != '\n'));
        
        /* Count number of line of the file */
        (*times)=0;
        while((c = fgetc(inp)) != EOF){
            if(c=='\n')
                (*times)++;
        } 
        
        /* Start to read from begginnig of a file */
        rewind(inp);
        while((c=fgetc(inp) != '\n'));

        /* Take values of products and assign them to appropriate array */
        for(i=0; i<(*times); i++){   
            fscanf(inp, "%d,%d,%[^,],%d", &sID[i], &take_pID[i], branch[i], &current_stock[i]);
        }
    }
    fclose(inp);
}

void write_stxt(int sID[NUM], int pID[NUM], char branch[NUM][16], int current_stock[NUM], int *times, int take_pID[NUM]){
     FILE *outp = fopen("stocks.txt", "w+");
    int i;

    if(outp == NULL)
        printf("File could not open!\n");
    else {
        /* Print features of products to a file */
        fprintf(outp, "sID,pID,branch,current_stock\n");
        for(i=0;i<(*times); i++){
            fprintf(outp, "%d,%d,%s,%d\n",sID[i], take_pID[i], branch[i], current_stock[i]);
        }
    }
    fclose(outp);
}

void list_product(int pID[NUM], char type[NUM], char name[NUM][9], char brand[NUM][6], double price[NUM], int *number){
    FILE *inp = fopen("products.txt", "r");
    char c;
    int i, j=0;
    
    if(inp == NULL)
        printf("File could not open\n");
    else{
        /* Ignore first line of the file */
        while((c=fgetc(inp) != '\n'));
        
        /* Count number of line of the file */
        (*number)=0;
        while((c = fgetc(inp)) != EOF){
            if(c=='\n')
                (*number)++;
        } 

        /* Start to read from begginnig of a file */
        rewind(inp);
        while((c=fgetc(inp) != '\n'));
    
        /* Take values of products and assign them to appropriate array and display them */
        for(i=0; i<(*number); i++){   
            fscanf(inp, "%d,%c,%[^,],%[^,],%lf", &pID[i], &type[i], name[i], brand[i], &price[i]);
            printf("%d,%c,%s,%s,%.1lf\n", pID[i], type[i], name[i], brand[i], price[i]);   
        }
    }
    fclose(inp);
}

void filter_product(int pID[NUM], char type[NUM], char name[NUM][9], char brand[NUM][6], double price[NUM], int *number){
    char apply[NUM];
    char determinate[NUM][16];
    int i=0, j=0, k=0, comma = 1, counter=0;
    char c;

    printf("Enter type of filter you want to (brand,type,price,user-defined): ");
    scanf("%s", apply);

    /* Count comma to determinate how many times assign will be done */
    for(i=0; apply[i] != '\0'; i++){
        if (apply[i] == ','){
            comma++;
        }
    }

    /* Assign users input to determinate array */
    for(i=0; i<comma; i++){
        while(apply[j] != ',' && apply[j] != '\0'){
            determinate[i][k] = apply[j];
            j++; 
            k++;
        }
        j++;
        k=0;
    }

    /* Print index of determinate */
    for(i=0; i<comma; i++){
        printf("determine[%d]: %s\n", i, determinate[i]);
    }
}

void stock_of_product(int sID[NUM], int pID[NUM], char branch[NUM][16], int current_stock[NUM], int *times, int take_pID[NUM]){
    int entered_id = 0, i, counter;

    /* Call read_stxt() function to read values from file */
    read_stxt(sID, pID, branch, current_stock, times, take_pID);
    
    printf("Enter pID you want to check stock: ");
    scanf(" %d", &entered_id);

    /* Assing number of id taken from user to counter to use it to print later */
    for(i=0; i<*times; i++){
        if(take_pID[i] == entered_id)
        counter = i;
    }
    
    printf("pID: %d, branch: %s, Current stock: %d\n", take_pID[counter], branch[counter], current_stock[counter]);
}

void list_stock(int sID[NUM], int pID[NUM], char branch[NUM][16], int current_stock[NUM], int *times, int take_pID[NUM]){
    char entered_name[16];
    int counter, i, j=0, matched[NUM];

    /* Call read_stxt() function to read values from file */
    read_stxt(sID, pID, branch, current_stock, times, take_pID);

    printf("Enter branch name: ");
    for(i=0; i<1; i++){
        scanf("%s", entered_name);
    }

    /* Compare branch name and entered name, If they are same implement matched array by one */
    for(i=0; i<*times; i++){
        counter = strcmp(entered_name, branch[i]);
        if(counter == 0){
            matched[j] = i;
            j++;
        }
    }

    for(i=0; i<j; i++){
        printf("pID: %d, current_stock: %d\n",take_pID[matched[i]], current_stock[matched[i]]);
    }
}

void list_out_of_stock(int sID[NUM], int pID[NUM], char branch[NUM][16], int current_stock[NUM], int *times, int take_pID[NUM]){
    char entered_name[16];
    int counter, i, j=0, matched[NUM];

    /* Call read_stxt() function to read values from file */
    read_stxt(sID, pID, branch, current_stock, times, take_pID);

    printf("Enter branch name: ");
    for(i=0; i<1; i++){
        scanf(" %s", entered_name);
    }

    /* Compare branch name and entered name, If they are same implement matched array by one */
    for(i=0; i<*times; i++){
        counter = strcmp(entered_name, branch[i]);
        if(counter == 0){
            matched[j] = i;
            j++;
        }
    }

    /* Print appropriate index of an array checking current_stock is 0 */
    for(i=0; i<j; i++){
        if(current_stock[matched[i]] == 0){
            printf("pID: %d\n",take_pID[matched[i]]);
        }
    }
}

int brand_control(int pID[NUM], char type[NUM], char name[NUM][9], char brand[NUM][6], double price[NUM], int *number, int sID[NUM], char branch[NUM][16], int current_stock[NUM], int take_pID[NUM], int counter_b[NUM]){
    char entered_brand[16];
    int counter, i, j=0;

    /* Call read1() function and read2() function to read values from file */
    read1(pID, type, name, brand, price, number);
    read2(sID, pID, branch, current_stock, number, take_pID);

    /* Assign 1 to counter_b array to protect index of it generate randomly */
    for(i=0; i<*number; i++){
        counter_b[i] = 1;
    }

    printf("Enter brand: ");
    scanf("%s", entered_brand);

    /* Compare brand name and entered name, If they are same implement counter_b array by one */
    for(i=0; i<*number; i++){
        counter = strcmp(entered_brand, brand[i]);
        if(counter == 0){
            counter_b[j] = i;
            j++;
        }
    }  
    /* return j to determinate how many times printing will be done */
    return j;
}
