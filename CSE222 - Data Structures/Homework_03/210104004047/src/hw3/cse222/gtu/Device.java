package hw3.cse222.gtu;

public interface Device {
    /***
     *  Interface getter for category
     * @return name of the category
     */
    String getCategory();

    /***
     *  Interface getter for name of the device
     * @return name of the device
     */
    String getName();

    /***
     * Interface setter for name of the device
     * @param _name
     */
    void setName(String _name);

    /***
     * Interface getter for price of the device
     * @return price of the device
     */
    double getPrice();

    /***
     * Interface setter for price of the device
     * @param _price
     */
    void setPrice(double _price);

    /***
     * Interface getter for price of the device
     * @return quantity of the device
     */
    int getQuantity();

    /***
     * Interface setter for price of the device
     * @param _quantity
     */
    void setQuantity(int _quantity);
}
