public class Customer extends Person {
    private Order[] orders;
    private int operator_ID;
    private int orderLength = 0;

    // Constructor of Customer
    Customer(String _name, String _surname, String _address, String _phone, int _ID, int _operator_ID) {
        super(_name, _surname, _address, _phone, _ID);
        this.orders = new Order[100];
        this.operator_ID = _operator_ID;
    }

    public int getOperator_ID() {
        return operator_ID;
    }

    // Method printing information about customer
    public void print_customer() {
        System.out.printf("Name & Surname: %s\nAddress: %s\nPhone: %s\nID: %d\nOperator ID: %d \n",
                (getName()+ " " + getSurname()), getAddress(), getPhone(), getID(), getOperator_ID());
    }

    // Method printing orders of this customer
    public void print_orders() {
        for(int i=0; i<orderLength; ++i) {
            if(orders[i] != null) {
                System.out.printf("Order #%d => ", i+1);
                orders[i].print_order();
            }
        }
    }

    // Method defining orders
    public void define_orders(Order[] _order) {
        for (Order order : _order) {
            if (order != null && order.getCustomer_ID() == this.getID()) {
                orders[orderLength] = order;
                orderLength++;
            }
        }
    }
}
