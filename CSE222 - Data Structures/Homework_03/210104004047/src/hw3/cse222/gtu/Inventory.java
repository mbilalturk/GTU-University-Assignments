package hw3.cse222.gtu;

import java.io.FileWriter;
import java.io.IOException;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.LinkedList;

public class Inventory {
    private LinkedList<ArrayList<Device>> inventory;

    /***
     * Constructor for inventory, initialize linkedList to inventory fields
     * Time complexity O(n) : Because there is a loop that iterates n times, where n is the number of Arraylist which will be created
     */
    Inventory() {
        inventory = new LinkedList<ArrayList<Device>>();

        for(int i=0; i<5; ++i) {
            inventory.add(new ArrayList<Device>());
        }

        /*
        addNewDevice("TV", "tv1", 350, 5);
        addNewDevice("TV", "tv2", 420, 15);
        addNewDevice("Computer", "computer1", 480, 12);
        addNewDevice("Computer", "computer2", 520, 8);
        addNewDevice("Headphone", "headphone1", 400, 50);
        addNewDevice("Headphone", "headphone2", 580, 40);
        addNewDevice("Keyboard", "keyboard1", 420, 75);
        addNewDevice("Keyboard", "keyboard2", 450, 80);
        addNewDevice("Keyboard", "keyboard3", 500, 100);
        addNewDevice("Smartphone", "smartphone1", 1000, 25);
        addNewDevice("Smartphone", "smartphone2", 800, 30);
        addNewDevice("TV", "tv3", 650, 20);
        addNewDevice("TV", "tv4", 600, 15);
        addNewDevice("TV", "tv4", 650, 20);

        removeDevice("tv2");
        removeDevice("tv1");
        removeDevice("tv7");
        removeDevice("keyboard1");

        updateDevice("tv3", 450, 2);
        updateDevice("headphone2", 1000, 12);
         */

    }

    /***
     * Method for adding new device
     * Time complexity O(n) : Because there is a loop and iterates at most n times in worst-case, where n is the number of the element in the inventory
     *
     * @param categoryName
     * @param deviceName
     * @param price
     * @param quantity
     * @return true if adding new device is successful, otherwise false
     */
    public boolean addNewDevice(String categoryName, String deviceName, double price, int quantity) {
        Device device;
        switch (categoryName) {
            case "Computer":
                device = new Computer(deviceName, price, quantity);
                break;
            case "TV":
                device = new TV(deviceName, price, quantity);
                break;
            case "Smartphone":
                device = new Smartphone(deviceName, price, quantity);
                break;
            case "Headphone":
                device = new Headphone(deviceName, price, quantity);
                break;
            case "Keyboard":
                device = new Keyboard(deviceName, price, quantity);
                break;
            default:
                System.out.println("Category not found. Please try again!");
                return false;
        }

        Device alreadyExist = getDevice(deviceName);
        if(alreadyExist != null) {
            System.out.println(deviceName + " already exist in the inventory!");
            return false;
        }

        int index = 0;
        for (ArrayList<Device> devices : inventory) {
            if(devices.isEmpty()) {
                return devices.add(device);
            }
            else if(devices.get(index).getCategory().equals(categoryName)) {
                boolean successful = devices.add(device);
                if(successful) ++index;
                return successful;
            }
        }

        return false;
    }

    /***
     * Method for removing a device from the list
     * Time complexity O(n*m) : There is a findCategory method whose time complexity is O(n*m). And, there is a loop iterating all element in inventory list in worst-case, where n is the size of the inventory.
     * Then there is a loop inside another loop which iterates all element in devices list in worst-case, where m is the size of the devices.
     * Therefore, in worst-case time complexity is O(n*m)
     *
     * @param deviceName
     * @return device which has just removed successfully, otherwise null
     */
    public Device removeDevice(String deviceName) {
        String categoryName = findCategory(deviceName);
        if(categoryName.isEmpty()) {
            System.out.println("Not found any device");
            return null;
        }

        for (ArrayList<Device> devices : inventory) {
            int index = 0;
            if(devices.isEmpty()) {
                return null;
            }
            else if(devices.get(index).getCategory().equals(categoryName)) {
                for(int i=0; i<devices.size(); ++i) {
                    if(devices.get(i).getName().equals(deviceName)) {
                        Device device = devices.get(i);
                        devices.remove(i);
                        return device;
                    }
                }
                return null;
            }
            ++index;
        }

        return null;
    }

    /***
     * A method for updating the device by using name of the device
     * Time complexity O(n*m) : There is getDevice method whose time complexity is O(n*m). Therefore, time complexity of this method is O(n*m) too.
     * @param deviceName
     * @param price
     * @param quantity
     * @return if device exist return it, otherwise null
     */
    public Device updateDevice(String deviceName, double price, int quantity) {
        Device device = getDevice(deviceName);
        if(device != null) {
            if(price > 0.0)
                device.setPrice(price);
            if(quantity > 0)
                device.setQuantity(quantity);
        }
        return device;
    }

    /***
     * A method for displaying devices
     * Time complexity O(n*m) : There is a loop iterating all element in inventory list in worst-case, where n is the size of the inventory.
     * Then there is a loop inside another loop which iterates all element in devices list in worst-case, where m is the size of the devices.
     * Therefore, in worst-case time complexity is O(n*m)
     */
    public void displayDevices() {
        int count = 1;
        for (ArrayList<Device> devices : inventory) {
            if(!devices.isEmpty()) {
                for (Device device : devices) {
                    System.out.printf("%d. Category: %s, Name: %s, Price: %.2f$, Quantity: %d\n", count, device.getCategory(), device.getName(), device.getPrice(), device.getQuantity());
                    ++count;
                }
            }
        }
    }

    /***
     * Time complexity O(n*m) : There is a loop iterating all element in inventory list in worst-case, where n is the size of the inventory.
     * Then there is a loop inside another loop which iterates all element in devices list in worst-case, where m is the size of the devices.
     * Therefore, in worst-case time complexity is O(n*m)
     * @return if device exists return cheapest device, otherwise null
     */
    public Device findCheapestDevice() {
        if(inventory.isEmpty()) {
            System.out.println("No device added!");
            return null;
        }
        Device cheapestDevice = inventory.get(0).get(0);

        for (ArrayList<Device> devices : inventory) {
            if(!devices.isEmpty()) {
                for (Device device : devices) {
                    if(device.getPrice() < cheapestDevice.getPrice())
                        cheapestDevice = device;
                }
            }
        }

        return cheapestDevice;
    }

    /***
     * A method for sorting all devices by price
     * Time complexity O(n*m) : There is a loop iterating all element in inventory list in worst-case, where n is the size of the inventory.
     * Then there is a loop inside another loop which iterates all element in devices list in worst-case, where m is the size of the devices.
     * Therefore, in worst-case time complexity is O(n*m)
     */
    public void sortDevice() {
        System.out.println("Devices sorted by price: ");
        ArrayList<Device> allDevices = new ArrayList<Device>();

        for (ArrayList<Device> devices : inventory) {
            if(devices.isEmpty()) {
                return;
            }
            for (Device device : devices) {
                allDevices.add(device);
            }
        }

        Comparator<Device> deviceComparator = Comparator.comparing(Device::getPrice);
        allDevices.sort(deviceComparator);

        int count = 1;
        for(Device device : allDevices) {
            System.out.printf("%d. Category: %s, Name: %s, Price: %.2f$, Quantity: %d\n", count, device.getCategory(), device.getName(), device.getPrice(), device.getQuantity());
            ++count;
        }
    }

    /***
     * A method for calculating total price and displaying it
     * Time complexity O(n*m) : There is a loop iterating all element in inventory list in worst-case, where n is the size of the inventory.
     * Then there is a loop inside another loop which iterates all element in devices list in worst-case, where m is the size of the devices.
     * Therefore, in worst-case time complexity is O(n*m)
     */
    public void calculateTotalPrice() {
        double total = 0.0;
        if(inventory.isEmpty()) {
            System.out.println("Total inventory value: $" + total);
        }

        for (ArrayList<Device> devices : inventory) {
            if(!devices.isEmpty()) {
                for (Device device : devices) {
                    total += device.getPrice() * device.getQuantity();
                }
            }
        }
        System.out.println("Total inventory value: $" + total);
    }

    /***
     * A method for restocking device
     * Time complexity O(n*m) : There is getDevice method whose time complexity is O(n*m). Therefore, time complexity of this method is O(n*m) too.
     * @param deviceName
     * @param decision A field determining stock will be increased or decreased. Decision field can hold only "Add" or "Remove"
     * @param quantity
     * @return if device exist returns it, otherwise null
     */
    public Device restockDevice(String deviceName, String decision, int quantity) {
        Device device = getDevice(deviceName);
        if(device != null) {
            if(decision.equals("Add"))
                device.setQuantity(device.getQuantity()+quantity);
            else if(decision.equals("Remove"))
                device.setQuantity(device.getQuantity()-quantity);
        }

        return device;
    }

    /***
     * A method for displaying all devices with details
     * Time complexity O(n*m) : There is a loop iterating all element in inventory list in worst-case, where n is the size of the inventory.
     * Then there is a loop inside another loop which iterates all element in devices list in worst-case, where m is the size of the devices.
     * Therefore, in worst-case time complexity is O(n*m)
     */
    public void displayReport() {
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append("Electronic Shop Inventory Report\n");
        stringBuilder.append("Generated on: ").append(getCurrentDay()).append("\n");
        stringBuilder.append("-".repeat(65)).append("\n");
        stringBuilder.append(String.format("| %-3s | %-12s | %-20s | %-5s | %-5s |\n", "No.", "Category", "Name", "Price", "Quantity"));
        stringBuilder.append("-".repeat(65)).append("\n");

        int count = 1;
        for (ArrayList<Device> devices : inventory) {
            if(!devices.isEmpty()) {
                for (Device device : devices) {
                    stringBuilder.append(String.format("| %-3d | %-12.12s | %-20.20s | %-5.2f$ | %-5d |\n", count, device.getCategory(), device.getName(), device.getPrice(), device.getQuantity()));
                    ++count;
                }
            }
        }
        stringBuilder.append("-".repeat(65)).append("\n");

        System.out.println(stringBuilder);
        toFile("output.txt", stringBuilder);
    }

    /***
     * A method for writing report to a file
     * Time complexity O(1) : Because there is no loop or recursion
     * @param fileName
     * @param stringBuilder
     */
    public void toFile(String fileName, StringBuilder stringBuilder) {
        try {
            // Create a FileWriter object
            FileWriter writer = new FileWriter(fileName);

            // Write the content to the file
            writer.write(String.valueOf(stringBuilder));

            // Close the writer
            writer.close();

        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
        }

    }

    /***
     * A method for getting device by using name of the device
     * Time complexity O(n*m) : There is a findCategory method whose time complexity is O(n*m). And, there is a loop iterating all element in inventory list in worst-case, where n is the size of the inventory.
     * Then there is a loop inside another loop which iterates all element in devices list in worst-case, where m is the size of the devices.
     * Therefore, in worst-case time complexity is O(n*m)
     * @param deviceName
     * @return if device exist returns it, otherwise null
     */
    private Device getDevice(String deviceName) {
        String categoryName = findCategory(deviceName);
        if(categoryName.isEmpty()) {
            return null;
        }

        for (ArrayList<Device> devices : inventory) {
            int index = 0;
            if(devices.isEmpty()) {
                return null;
            }
            else if(devices.get(index).getCategory().equals(categoryName)) {
                for (Device device : devices) {
                    if (device.getName().equals(deviceName)) {
                        return device;
                    }
                }
                return null;
            }
            ++index;
        }

        return null;
    }

    /***
     * A method for determining name of the category by using name of the device
     * Time complexity O(n*m) : There is a loop iterating all element in inventory list in worst-case, where n is the size of the inventory.
     * Then there is a loop inside another loop which iterates all element in devices list in worst-case, where m is the size of the devices.
     * Therefore, in worst-case time complexity is O(n*m)
     * @param deviceName
     * @return if name of the device exist return name of the category of device, otherwise empty
     */
    private String findCategory(String deviceName) {
        for (ArrayList<Device> devices : inventory) {
            if(!devices.isEmpty()) {
                for (Device device : devices) {
                    if (device.getName().equals(deviceName)) {
                        return device.getCategory();
                    }
                }
            }
        }

        return "";
    }

    /***
     * A method for determining current day
     * Time complexity O(1) : Because there is no loop or recursion
     * @return current day as "dd MMMM yyyy"
     */
    private static String getCurrentDay() {
        LocalDate currentDate = LocalDate.now();
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd MMMM yyyy");
        return currentDate.format(formatter);
    }

}

