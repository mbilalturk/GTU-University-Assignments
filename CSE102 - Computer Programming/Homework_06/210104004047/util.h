#ifndef _UTIL_H_
#define _UTIL_H_
#define NUM 50

void menu();
void file_operations();
    void read_ptxt(int pID[NUM], char type[NUM], char name[NUM][9], char brand[NUM][6], double price[NUM], int *number, char type_of_variable[NUM],  char name_of_feature[NUM][NUM], char new_feature[NUM][NUM]);
    void read_stxt(int sID[NUM], int pID[NUM], char branch[NUM][16], int current_stock[NUM], int *times, int take_pID[NUM]);
    void write_ptxt(int pID[NUM], char type[NUM], char name[NUM][9], char brand[NUM][6], double price[NUM], int *number, char type_of_variable[NUM], char name_of_feature[NUM][NUM]);
    void write_stxt(int sID[NUM], int pID[NUM], char branch[NUM][16], int current_stock[NUM], int *times, int take_pID[NUM]);
    void add_product(int pID[NUM], char type[NUM], char name[NUM][9], char brand[NUM][6], double price[NUM], int *number, char type_of_variable[NUM],  char name_of_feature[NUM][NUM], char new_feature[NUM][NUM]);
    void delete_product(int pID[NUM], char type[NUM], char name[NUM][9], char brand[NUM][6], double price[NUM], int *number, char type_of_variable[NUM],  char name_of_feature[NUM][NUM], char new_feature[NUM][NUM]);
    void update_product(int pID[NUM], char type[NUM], char name[NUM][9], char brand[NUM][6], double price[NUM], int *number, char type_of_variable[NUM],  char name_of_feature[NUM][NUM], char new_feature[NUM][NUM]);
    void add_feature(int pID[NUM], char type[NUM], char name[NUM][9], char brand[NUM][6], double price[NUM], int *number, char type_of_variable[NUM], char name_of_feature[NUM][NUM]);
    void add_stock_entry(int sID[NUM], int pID[NUM], char branch[NUM][16], int current_stock[NUM], int *times, int take_pID[NUM]);
    void delete_stock_entry(int sID[NUM], int pID[NUM], char branch[NUM][16], int current_stock[NUM], int *times, int take_pID[NUM]);
    void update_stocks(int sID[NUM], int pID[NUM], char branch[NUM][16], int current_stock[NUM], int *times, int take_pID[NUM]);

void search_product();
    void list_product(int pID[NUM], char type[NUM], char name[NUM][9], char brand[NUM][6], double price[NUM], int *number);
    void filter_product(int pID[NUM], char type[NUM], char name[NUM][9], char brand[NUM][6], double price[NUM], int *number);

void check_stock_status();
    void stock_of_product(int sID[NUM], int pID[NUM], char branch[NUM][16], int current_stock[NUM], int *times, int take_pID[NUM], int id_for_stock[NUM];);
    void list_stock(int sID[NUM], int pID[NUM], char branch[NUM][16], int current_stock[NUM], int *times, int take_pID[NUM]);
    void list_out_of_stock(int sID[NUM], int pID[NUM], char branch[NUM][16], int current_stock[NUM], int *times, int take_pID[NUM]);
    void read_pID(int pID[NUM]);

void list_products_of_brand();
    int brand_control(int pID[NUM], char type[NUM], char name[NUM][9], char brand[NUM][6], double price[NUM], int *number, int sID[NUM], char branch[NUM][16], int current_stock[NUM], int take_pID[NUM], int counter_b[NUM]);
    void read1(int pID[NUM], char type[NUM], char name[NUM][9], char brand[NUM][6], double price[NUM], int *number);
    void read2(int sID[NUM], int pID[NUM], char branch[NUM][16], int current_stock[NUM], int *times, int take_pID[NUM]);

void export_report();
    void stock_report(int pID[NUM], char type[NUM], char name[NUM][9], char brand[NUM][6], double price[NUM], int *number, int sID[NUM], char branch[NUM][16], int current_stock[NUM], int take_pID[NUM], int counter_b[NUM]);

#endif /* _UTIL_H_ */
