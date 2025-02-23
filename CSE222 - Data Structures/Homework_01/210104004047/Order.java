public class Order {
    private String product_name;
    private int count;
    private int total_price;
    private int status;
    private int customer_ID;

    // Constructor of Order
    public Order(String _product_name, int _count, int _total_price, int _status, int _customer_ID) {
        try {
            setProduct_name(_product_name);
            setCount(_count);
            setTotal_price(_total_price);
            setStatus(_status);
            setCustomer_ID(_customer_ID);
        }
        catch (Exception ignored) {
            // Do nothing
        }
    }

    public String getProduct_name() {
        return product_name;
    }
    private void setProduct_name(String _product_name) throws Exception {
        if(_product_name == null || _product_name.isEmpty())
            throw new Exception("String cannot be empty!");
        this.product_name = _product_name;
    }

    public int getCount() {
        return count;
    }
    private void setCount(int _count) throws Exception {
        if(_count <= 0 || _count >= 100)
            throw new Exception("Count cannot be less than or equal to zero!");
        this.count = _count;
    }

    public int getTotal_price() {
        return total_price;
    }
    private void setTotal_price(int _total_price) throws Exception {
        if(_total_price <= 0 || _total_price >= 1000000)
            throw new Exception("Total price cannot be negative!");
        this.total_price = _total_price;
    }

    public String getStatus() {
        String _status = "";

        if(status == 0) _status = "Initialized";
        else if(status == 1) _status = "Processing";
        else if(status == 2) _status = "Completed";
        else if(status == 3) _status = "Cancelled";

        return _status;
    }
    private void setStatus(int _status) throws Exception {
        if(_status < 0 || _status > 3)
            throw new Exception("Status cannot be less than 0 or greater than 3!");
        this.status = _status;
    }

    public int getCustomer_ID() {
        return customer_ID;
    }
    private void setCustomer_ID(int _customer_ID) throws Exception {
        if(_customer_ID <= 0 || _customer_ID >= 100000)
            throw  new Exception("Invalid customer ID!");
        this.customer_ID = _customer_ID;
    }

    public void print_order() {
        System.out.printf("Product name: %s - Count: %d - Total Price: %d - Status: %s.\n", getProduct_name(), getCount(), getTotal_price(), getStatus());
    }
}
