#include <stdio.h>
#include <string.h>

typedef struct {
    char name[20];
    char color[20];
    double price;
    int serial_number;
    int quantity;
} furniture;

int read_text(furniture furnitures[]);
int add_item(furniture furnitures[]);
int remove_item(furniture furnitures[]);
int search_name(furniture furnitures[]);
int search_color(furniture furnitures[]);

int main(){
    int option, property, line, i;
    furniture furnitures[10];
    
    do{
        printf("***************\n");
        printf("Welcome to database of furniture shop\n");
        printf("1-See all furnitures\n2-Add a new furniture\n3-Remove a furniture\n4-Search furniture\n5-Exit\n");
        scanf(" %d", &option);

        switch(option){
            case 1: line = read_text(furnitures);
                    for(i=0; i<line; i++){
                        printf("Name: %s\n", furnitures[i].name);
                        printf("Color: %s\n", furnitures[i].color);
                        printf("Price: $%.2lf\n", furnitures[i].price);
                        printf("Serial Number: %d\n", furnitures[i].serial_number);
                        printf("Quantity: %d\n", furnitures[i].quantity);
                        printf("\n");
                    } 
            break;
            case 2: add_item(furnitures); break;
            case 3: remove_item(furnitures); break;
            case 4:
                    printf("Select a property to make search:\n\n1-Name\n2-Color\n");
                    scanf(" %d", &property);
                    do{
                        if(property==1)
                            search_name(furnitures);
                        if(property==2)
                            search_color(furnitures);
                        else{
                            printf("Invalid Input!\n");
                        }
                    }while(property != 1 && property != 2);

                    break;
            case 5: printf("Good Bye!\n"); break;
            default: printf("Invalid Input!\n"); break; 
        }
    }while(option != 5);   

    return (0);
}

int read_text(furniture furnitures[]){
    FILE *filep = fopen("furniture_database.txt", "r");
    int i;
    char c;
    int line=1;
    
    if(filep == NULL){
        printf("File could not open!\n");
        return -1;
    }
    while((c=fgetc(filep)) != EOF){
        if(c=='\n')
           line++;
    }

    rewind(filep);
    for(i=0; i<line; i++){
        fscanf(filep, "%[^,],%[^,],%lf,%d,%d\n", furnitures[i].name, furnitures[i].color, &furnitures[i].price, &furnitures[i].serial_number, &furnitures[i].quantity);
    } 
    fclose(filep);
    return line;
}

int add_item(furniture furnitures[]){
    FILE *filep = fopen("furniture_database.txt", "a+");
    int line;

    line = read_text(furnitures);

    printf("Please enter the proporties of new furniture: \n");
    printf("Name: ");
    scanf("%s", furnitures[line].name);
    printf("Color: ");
    scanf("%s", furnitures[line].color);
    printf("Price: ");
    scanf("%lf", &furnitures[line].price);
    printf("Serial number: ");
    scanf("%d", &furnitures[line].serial_number);
    printf("Quantity: ");
    scanf("%d", &furnitures[line].quantity);
    
    printf("\nFollowing furniture is added to the database:\n");
    printf("Name: %s\n", furnitures[line].name);
    printf("Color: %s\n", furnitures[line].color);
    printf("Price: $%.2lf\n", furnitures[line].price);
    printf("Serial Number: %d\n", furnitures[line].serial_number);
    printf("Quantity: %d\n", furnitures[line].quantity);
    printf("\n");

    fprintf(filep, "\n%s,%s,%.2lf,%d,%d", furnitures[line].name, furnitures[line].color, furnitures[line].price, furnitures[line].serial_number, furnitures[line].quantity);
    fclose(filep);
}   

int remove_item(furniture furnitures[]){
    FILE *finp = fopen("furniture_database.txt", "r+");
    int line, i;
    int option;

    if(finp == NULL){
        printf("File could not open!\n");
        return -1;
    }

    line = read_text(furnitures);
    printf("Please enter the index of you want to remove: ");
    scanf("%d", &option);
    
    printf("\nFallowing furniture is removed from the database:\n");
    printf("Name: %s\n", furnitures[option].name);
    printf("Color: %s\n", furnitures[option].color);
    printf("Price: $%.2lf\n", furnitures[option].price);
    printf("Serial Number: %d\n", furnitures[option].serial_number);
    printf("Quantity: %d\n", furnitures[option].quantity);
    printf("\n");

    for(i=0; i<20; i++){
        furnitures[option].name[i] = '\0';
        furnitures[option].color[i] = '\0';
    }
    furnitures[option].price = '\0';
    furnitures[option].serial_number = '\0';
    furnitures[option].quantity = '\0';

    fclose(finp);

    FILE *foutp = fopen("furniture_database.txt", "w+");
    
    if(foutp == NULL){
        printf("File could not open!\n");
        return -1;
    }
    
    for(i=0; i<line; i++){
        if(i==option){

        }
        else{
            fprintf(foutp, "%s,%s,%.2lf,%d,%d\n", furnitures[i].name, furnitures[i].color, furnitures[i].price, furnitures[i].serial_number, furnitures[i].quantity);
        }
    }
    fclose(foutp);
}

int search_name(furniture furnitures[]){
    FILE *filep = fopen("furniture_database.txt", "r");
    char c;
    int line=1, i;
    char name[20];
    
    if(filep == NULL){
        printf("File could not open!\n");
        return -1;
    }
    while((c=fgetc(filep)) != EOF){
        if(c=='\n')
           line++;
    }

    rewind(filep);
    for(i=0; i<line; i++){
        fscanf(filep, "%[^,],%[^,],%lf,%d,%d\n", furnitures[i].name, furnitures[i].color, &furnitures[i].price, &furnitures[i].serial_number, &furnitures[i].quantity);
    } 

    printf("Enter the name of product: ");
    scanf(" %[^\n]", name);

    for(i=0; i<line; i++){
        if(strcmp(furnitures[i].name, name) == 0){
            printf("Name: %s\n", furnitures[i].name);
            printf("Color: %s\n", furnitures[i].color);
            printf("Price: $%.2lf\n", furnitures[i].price);
            printf("Serial Number: %d\n", furnitures[i].serial_number);
            printf("Quantity: %d\n", furnitures[i].quantity);
            printf("\n");
        }
    }

    fclose(filep);
}

int search_color(furniture furnitures[]){
     FILE *filep = fopen("furniture_database.txt", "r");
    char c;
    int line=1, i;
    char color[20];
    
    if(filep == NULL){
        printf("File could not open!\n");
        return -1;
    }
    while((c=fgetc(filep)) != EOF){
        if(c=='\n')
           line++;
    }

    rewind(filep);
    for(i=0; i<line; i++){
        fscanf(filep, "%[^,],%[^,],%lf,%d,%d\n", furnitures[i].name, furnitures[i].color, &furnitures[i].price, &furnitures[i].serial_number, &furnitures[i].quantity);
    } 

    printf("Enter the color of product: ");
    scanf(" %[^\n]", color);

    for(i=0; i<line; i++){
        if(strcmp(furnitures[i].color, color) == 0){
            printf("Name: %s\n", furnitures[i].name);
            printf("Color: %s\n", furnitures[i].color);
            printf("Price: $%.2lf\n", furnitures[i].price);
            printf("Serial Number: %d\n", furnitures[i].serial_number);
            printf("Quantity: %d\n", furnitures[i].quantity);
            printf("\n");
        }
    }

    fclose(filep);
}