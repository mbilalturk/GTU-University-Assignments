public class Operator extends Person {
    private int wage;
    private Customer[] customers;
    private int customersLength = 0;

    // Constructor of Operator
    public Operator(String _name, String _surname, String _address, String _phone, int _ID, int _wage){
        super(_name, _surname, _address, _phone, _ID);
        customers = new Customer[100];
        this.wage = _wage;

    }

    public int getWage() {
        return wage;
    }

    // Method printing information about operator
    public void print_operator() {
        System.out.printf("Name & Surname: %s\nAddress: %s\nPhone: %s\nID: %d\nWage: %d\n",
                (getName()+" "+getSurname()), getAddress(), getPhone(), getID(), getWage());
    }

    // Method printing information about customers of this operator
    public void print_customers() {
        if(customersLength == 0) {
            System.out.println("This operator doesn't have any customer.");
            System.out.println("-".repeat(30));
        }

        for(int i=0; i<customersLength; ++i) {
            String type;
            if (customers[i].getClass().getName().equals("Retail_customer"))
                type = "(a retail customer)";
            else
                type = "(a corporate customer)";

            System.out.printf("Customer #%d %s:\n", i + 1, type);
            customers[i].print_customer();
            customers[i].print_orders();
            System.out.println("-".repeat(30));
        }
    }

    // Method defining customers
    public void define_customers(Customer[] _customers) {
        for (Customer customer : _customers) {
            if (customer != null && customer.getOperator_ID() == this.getID()) {
                customers[customersLength] = customer;
                customersLength++;
            }
        }
    }
}
