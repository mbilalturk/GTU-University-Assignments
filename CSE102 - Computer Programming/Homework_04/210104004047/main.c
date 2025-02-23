#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void write_menu();
void read_menu();
void ask_the_user();
void calculate_price(double total);
void read_receipt();

void rock_paper_scissors();

int main(){
    
    write_menu();   /* Part 1 */
    
    rock_paper_scissors(); /* Part 2 */
    
    return(0);
} /* End of the main() */

void write_menu(){
    FILE *fwrite = fopen("text.txt", "w+"); /* Open file to write */

    if(fwrite == NULL){ /* Check if the file is open, else warn user */
        printf("File could not open to write!\n");
    }
    else{ /* Print menu to text.txt file */
        fprintf(fwrite, "Product       Price(TL)\n");
        fprintf(fwrite, "1. Kebap          75.99\n");
        fprintf(fwrite, "2. Lahmacun       21.50\n");
        fprintf(fwrite, "3. Pide           40.00\n");
        fprintf(fwrite, "4. Döner          55.60\n");
        fprintf(fwrite, "5. Kola           15.00\n");
        fprintf(fwrite, "6. Çay            10.00\n");
        fprintf(fwrite, "7. Su             5.00\n");
        fprintf(fwrite, "8. Kemalpaşa      27.50\n");
        fprintf(fwrite, "9. Künefe         60.00\n");
        fprintf(fwrite, "10. Sütlaç        32.50\n");
    }

    fclose(fwrite); /* Close the file */
    
    read_menu(); /* Call read_menu() function to read the menu from a file to display */
} /* End of the write_menu() */

void read_menu(){
    
    FILE *fread1 = fopen("text.txt", "r"); /* Open file to read */
    char c;
    int counter = 0, line = 0;

    if(fread1 == NULL){ /* Check if the file is open, else warn user */
        printf("File could not open to read!\n");
    }
    else{ /* Read the menu from file and print to terminal */
        while(c = fgetc(fread1) != '\n'); /* Ignore the first line of the text.txt */

        printf("Yemek Listesi: ");
        while((c = fgetc(fread1)) != EOF){ 
            if(counter < 13 && line == 0){ /* Check the current line */
                line = 1;
                printf("\n");
            }
        
            if(c == '\n'){ /* If c reaches the end of the line, assign 0 to counter and line */
                counter = 0;
                line = 0;
            }
            else if(counter < 13){ /* If counter less than 13, print current character to terminal */
                printf("%c", c);
                counter++;
            }
        }
        printf("\n");
    }

    fclose(fread1); /* Close the file */

    ask_the_user(); /* Call ask_the_user() function to get input from user */
} /* End of the read_menu() */

void ask_the_user(){ 
    FILE *fwrite2 = fopen("receipt.txt", "w+"); /* Open file to write */
    double total, price;
    int product, times = 1;
    time_t t; /* data type for displaying current time */

    time(&t); 
    
    if(fwrite2 == NULL){ /* Check if the file is open, else warn user */
        printf("File could not open to write!\n");
    }
    else{   /* Print some text for bill to a file */
        fprintf(fwrite2, "\n210104004047    %s", ctime(&t)); /* Print number and time via ctime() function to a file */
        fprintf(fwrite2, "----------------------------------------\n");
        fprintf(fwrite2, "Product                       Price (TL)\n");
        fprintf(fwrite2, "----------------------------------------\n");

        while(times){           
            
            printf("Please choose a product (1-10): "); /* Get users choice */
            scanf("%d", &product);

            printf("How many servings do you want? "); /* Get how many servings user wants */
            scanf("%d", &times);

            switch(product){ /* Switch case to get price and print it with prdocuct name to a file */
                case 0:     
                    price = 0;         
                    break;
                case 1:
                    price = 75.99;
                    fprintf(fwrite2, "%d* Kebap                         %.2lf\n", times, (times*price));
                    break;
                case 2:   
                    price = 21.50;
                    fprintf(fwrite2, "%d* Lahmacun                      %.2lf\n", times, (times*price));
                    break;
                case 3:   
                    price = 40.00;
                    fprintf(fwrite2, "%d* Pide                          %.2lf\n", times, (times*price));
                    break; 
                case 4: 
                    price = 55.60;
                    fprintf(fwrite2, "%d* Döner                         %.2lf\n", times, (times*price));
                    break;
                case 5:
                    price = 15.00;
                    fprintf(fwrite2, "%d* Kola                          %.2lf\n", times, (times*price));
                    break;
                case 6:
                    price = 10.00;
                    fprintf(fwrite2, "%d* Çay                           %.2lf\n", times, (times*price));
                    break;
                case 7:
                    price = 5.00;
                    fprintf(fwrite2, "%d* Su                            %.2lf\n", times, (times*price));
                    break;
                case 8:
                    price = 27.50;
                    fprintf(fwrite2, "%d* Kemalpaşa                     %.2lf\n", times, (times*price));
                    break;
                case 9:
                    price = 60.00;
                    fprintf(fwrite2, "%d* Künefe                        %.2lf\n", times, (times*price));
                    break;
                case 10:  
                    price = 32.50;
                    fprintf(fwrite2, "%d* Sütlaç                        %.2lf\n", times, (times*price));
                    break; 
                default:
                    printf("Invalid input!\n");
                    price = 0;
                    break;
            }  
            total += price*times;   /* Calculate total price */
        }
    }
    fclose(fwrite2); /* Close the file */

    calculate_price(total);    
} /* End of the ask_the_user() */

void calculate_price(double total){
    FILE *fwrite3 = fopen("receipt.txt", "a+"); /* Open file to append */
    char student;
    double student_discount, additional_discount, price_payable;

    if(fwrite3 == NULL){ /* Check if the file is open, else warn user */
        printf("File could not open to write!\n");
    }
    else{
        do{ /* Ask the user if he or she is student to apply discount until enter a valid answer */
            printf("Are you student? (Y/N): ");
            scanf(" %c", &student);

            if(student == 'Y'){ 
                student_discount = (total * 12.50) / 100;
            }
            else if(student == 'N')
                student_discount = 0;
            else
                printf("Please enter a valid answer!\n");
            }
        while(student != 'Y' && student != 'N');

        if(total >= 150){ /* If total is greater than 150, apply discount */
            additional_discount = (total * 10) / 100;
        }
        else{
            additional_discount = 0;
        }
        
        /* Calculate price payable and add VAT */
        price_payable = total-student_discount-additional_discount;
        price_payable = (price_payable * 118) / 100;

        /* Print total, discounts and price payable to a file */
        fprintf(fwrite3, "Total:                           %.2lf\n", total);  

        if(student_discount > 0)
            fprintf(fwrite3, "Student Discount:               -%.2lf\n", student_discount);
        
        if(additional_discount > 0)
            fprintf(fwrite3, "Additional Discount:            -%.2lf\n", additional_discount);
        
        fprintf(fwrite3, "---------------------------------------\n");
        fprintf(fwrite3, "Price Payable:                   %.2lf\n", price_payable);   
    }

    fclose(fwrite3); /* Close the file */

    read_receipt(); /* Call read_receipt() function to display receipt */
} /* End of the calculate_price() */

void read_receipt(){
    FILE *fread2 = fopen("receipt.txt", "r"); /* Open file to read */
    char c;

    if(fread2 == NULL){ /* Check if the file is open, else warn user */
        printf("File could not open to read!\n");
    }
    else{
        while((c = fgetc(fread2)) != EOF){ /* Display receipt to terminal */
            printf("%c", c);
        }
    }

    fclose(fread2); /* Close the file */
} /* End of the read_receipt() */

void rock_paper_scissors(){
    int users_choice, comp_choice;
    char play;

    /* Function to create number randomly for each times */
    srand(time(0));

    do{
        printf("\n\n*********** PART 2 ***********\n\n");
        /* Get input from user */
        printf("Please make a choice!\n");
        printf("1: Stone, 2: Paper, 3: Scissor\n");
        scanf(" %d", &users_choice);

        /* Create number randomly */
        comp_choice = rand() % 3 + 1;

        /* Print user's choice by checking gotten input */
        switch(users_choice){
            case 1: printf("You chose Stone. ");
                    break;
            case 2: printf("You chose Paper. ");
                    break;
            case 3: printf("You chose Scissors. ");
                    break;
            default: printf("Please enter appropriate number!\n");
                    break;
        }

        /* Print computer's choice by checking created number randomly */
        switch(comp_choice){
            case 1: printf("I chose Stone. ");
                    break;
            case 2: printf("I chose Paper. ");
                    break;
            case 3: printf("I chose Scissors. ");
                    break;
        }

        /* Print the result by checking given input */
        if(users_choice > comp_choice)
            printf("You won!\n");
        else if(users_choice == comp_choice)
            printf("It's a tie! \n");
        else
            printf("I won!\n");

        /* Ask the user want to play again */
        printf("Do you want to play again? (Y/N): ");
        scanf(" %c", &play);
        printf("\n");
    }
    while(play == 'Y' || play == 'y');

    printf("Goodbye!\n");
} /* End of the rock_paper_scissors() */