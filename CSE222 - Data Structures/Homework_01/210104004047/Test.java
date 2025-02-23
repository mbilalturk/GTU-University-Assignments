import java.io.File;
import java.util.Scanner;

public class Test {

    private static final int SIZE = 100;
    private static final String filename = "content.txt";

    // Array fields to store objects
    private static Order[] orders = new Order[SIZE];
    private static Customer[] customers = new Customer[SIZE];
    private static Operator[] operators = new Operator[SIZE];

    //Fields to store the length
    private static int orderLength = 0;
    private static int customerLength = 0;
    private static int operatorLength = 0;


    public static void main(String[] args) {
        File file = new File(filename);

        try {
            Scanner scanner = new Scanner(file);

            //Read file if it has line
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                createObjects(line);
            }

            // Prompt input from user
            Scanner input = new Scanner(System.in);

            System.out.println("Please enter your ID...");
            int value = input.nextInt();

            // Display the results
            display(value);

        }
        catch (Exception ignored) {
            // Do nothing
        }

    }

    // Method creating object according to input has been taken from file
    private static void createObjects(String line) {
        // Split line taking from the file into String array
        String[] strings = line.split(";");

        try {
            switch (strings[0]) {
                case "order":
                    // If first word of line is 'order' and its length is 6, create order object
                    if (strings.length == 6) {
                        orders[orderLength] = new Order(strings[1], Integer.parseInt(strings[2]), Integer.parseInt(strings[3]), Integer.parseInt(strings[4]), Integer.parseInt(strings[5]));
                        ++orderLength;
                    }
                    break;
                case "retail_customer":
                case "corporate_customer":
                    // If first word of line is 'retail' or 'corporate' and its length is 7 or 8, create retail_customer or corporate_customer object
                    if (strings.length == 7 || strings.length == 8) {
                        // Check if ID is unique
                        int isUniqueID = 1;
                        int ID = Integer.parseInt(strings[5]);
                        for (int i = 0; i < customerLength; ++i) {
                            if (customers[i].getID() == ID) {
                                isUniqueID = 0;
                                break;
                            }
                        }
                        if (isUniqueID == 1) {
                            if (strings.length == 7) {
                                customers[customerLength] = new Retail_customer(strings[1], strings[2], strings[3], strings[4], Integer.parseInt(strings[5]), Integer.parseInt(strings[6]));
                            } else {
                                customers[customerLength] = new Corporate_customer(strings[1], strings[2], strings[3], strings[4], Integer.parseInt(strings[5]), Integer.parseInt(strings[6]), strings[7]);
                            }

                            customers[customerLength].define_orders(orders);
                            ++customerLength;
                        }
                    }
                    break;
                case "operator":
                    // If first word of line is 'operator' and its length is 7, create operator object
                    if (strings.length == 7) {
                        // Check if ID is unique
                        int isUniqueID = 1;
                        int ID = Integer.parseInt(strings[5]);
                        for (int i = 0; i < operatorLength; ++i) {
                            if (operators[i].getID() == ID) {
                                isUniqueID = 0;
                                break;
                            }
                        }
                        if (isUniqueID == 1) {
                            operators[operatorLength] = new Operator(strings[1], strings[2], strings[3], strings[4], Integer.parseInt(strings[5]), Integer.parseInt(strings[6]));
                            operators[operatorLength].define_customers(customers);
                            ++operatorLength;
                        }
                    }
                    break;
            }
        }
        catch (Exception ignored) {
            // Do nothing
        }
    }

    // Method displaying the operator or customer
    private static void display(int value) {
        int foundOperator = 0, foundCustomer = 0;

        for(int i=0; i<operatorLength;++i) {
            if (operators[i].getID() == value) {
                foundOperator = 1;
                break;
            }
        }

        if(foundOperator == 0) {
            for(int i=0; i<customerLength; ++i) {
                if(customers[i].getID() == value) {
                    foundCustomer = 1;
                    break;
                }
            }
        }

        if(foundOperator == 0 && foundCustomer == 0) {
            System.out.printf("No operator/customer was found with ID %d. Please try again.\n", value);
        }
        else {
            if(foundOperator == 1) {
                System.out.println("*** Operator Screen ***");
                System.out.println("-".repeat(30));
                for(int i=0; i<operatorLength; ++i) {
                    if(operators[i].getID() == value) {
                        operators[i].print_operator();
                        System.out.println("-".repeat(30));
                        operators[i].print_customers();
                    }
                }
            }
            else {
                System.out.println("*** Customer Screen ***");
                System.out.println("-".repeat(30));
                for(int i=0; i<customerLength; ++i) {
                    if(customers[i].getID() == value) {
                        customers[i].print_customer();
                        customers[i].print_orders();
                    }
                }
            }
        }
    }
}
