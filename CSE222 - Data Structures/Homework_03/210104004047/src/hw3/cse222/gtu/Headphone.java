package hw3.cse222.gtu;

public class Headphone implements Device {
    private final String category = "Headphone";
    private String name;
    private double price;
    private int quantity;

    /***
     * Constructor for headphone
     * Time complexity O(1) : Constant time because there is no loop or recursion
     * @param _name
     * @param _price
     * @param _quantity
     */
    Headphone(String _name, double _price, int _quantity) {
        this.name = _name;
        this.price = _price;
        this.quantity = _quantity;
    }

    /***
     * Getter for category
     * Time complexity O(1) : Constant time because there is no loop or recursion
     * @return category
     */
    @Override
    public String getCategory() {
        return category;
    }

    /***
     * Getter for name
     * Time complexity O(1) : Constant time because there is no loop or recursion
     * @return name
     */
    @Override
    public String getName() {
        return name;
    }

    /***
     * Setter for name
     * Time complexity O(1) : Constant time because there is no loop or recursion
     * @param _name
     */
    @Override
    public void setName(String _name) {
        this.name = _name;
    }

    /***
     * Getter for price
     * Time complexity O(1) : Constant time because there is no loop or recursion
     * @return price
     */
    @Override
    public double getPrice() {
        return price;
    }

    /***
     * Setter for price
     * Time complexity O(1) : Constant time because there is no loop or recursion
     * @param _price
     */
    @Override
    public void setPrice(double _price) {
        if(_price < 0)
            _price = 0;
        this.price = _price;
    }

    /***
     * Getter for quantity
     * Time complexity O(1) : Constant time because there is no loop or recursion
     * @return quantity
     */
    @Override
    public int getQuantity() {
        return quantity;
    }

    /***
     * Setter for quantity
     * Time complexity O(1) : Constant time because there is no loop or recursion
     * @param _quantity
     */
    @Override
    public void setQuantity(int _quantity) {
        if(_quantity < 0)
            _quantity = 0;
        this.quantity = _quantity;
    }
}

