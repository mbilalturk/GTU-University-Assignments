public class Corporate_customer extends Customer {
    private String company_name;

    // Corporate_customer constructor calling super class to create object
    public Corporate_customer(String _name, String _surname, String _address, String _phone, int _ID, int _operator_ID, String _company_name) {
        super(_name, _surname, _address, _phone, _ID, _operator_ID);
        this.company_name = _company_name;
    }

    public String getCompany_name() {
        return company_name;
    }

    // Method printing the information about customer
    public void print_customer() {
        super.print_customer();
        System.out.printf("Company name: %s\n", getCompany_name());
    }
}
