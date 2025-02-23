package hw3.cse222.gtu;

import java.util.Scanner;

public class Main {

    /***
     * Main method to run the program
     * Time complexity O(k*n*m) : Because there is a while loop which runs k times. Then, there are lost of method inside main, but for time complexity we must consider
     * worst-case scenario. Therefore, since there is a method that has time complexity O(n*m), time complexity of main is O(k*n*m).
     * @param args
     */
    public static void main(String[] args) {
        Inventory inventory = new Inventory();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Welcome to the Electronics Inventory Manage System!");

        try {
            while (true) {
                displayMenu();
                int choice = scanner.nextInt();
                scanner.nextLine();

                switch (choice) {
                    case 1:
                        System.out.print("Enter category name: ");
                        String categoryName = scanner.nextLine();

                        System.out.print("Enter device name: ");
                        String deviceName = scanner.nextLine();

                        System.out.print("Enter price: ");
                        double price = scanner.nextDouble();

                        System.out.print("Enter quantity: ");
                        int quantity = scanner.nextInt();

                        boolean succesful = inventory.addNewDevice(categoryName, deviceName, price, quantity);
                        if (succesful)
                            System.out.printf("%s, %s, %.2f$, %d amount added...\n", categoryName, deviceName, price, quantity);

                        break;
                    case 2:
                        System.out.print("Enter device name: ");
                        deviceName = scanner.nextLine();

                        Device device = inventory.removeDevice(deviceName);
                        if (device != null)
                            System.out.printf("%s, %s, %.2f$, %d amount removed...\n", device.getCategory(), device.getName(), device.getPrice(), device.getQuantity());

                        break;
                    case 3:
                        System.out.print("Enter the name of the device to update: ");
                        deviceName = scanner.nextLine();

                        System.out.print("Enter new price (leave blank to keep current price): ");
                        String stringPrice = scanner.nextLine();

                        System.out.print("Enter new quantity (leave blank to keep current quantity): ");
                        String stringQuantity = scanner.nextLine();

                        if (stringPrice.isBlank()) price = -1.0;
                        else price = Double.parseDouble(stringPrice);

                        if (stringQuantity.isBlank()) quantity = -1;
                        else quantity = Integer.parseInt(stringQuantity);

                        device = inventory.updateDevice(deviceName, price, quantity);
                        if (device != null)
                            System.out.printf("%s details updated: Price - %.2f$, Quantity - %d\n", device.getName(), device.getPrice(), device.getQuantity());

                        break;
                    case 4:
                        inventory.displayDevices();

                        break;
                    case 5:
                        Device cheapestDevice = inventory.findCheapestDevice();
                        if (cheapestDevice != null) {
                            System.out.println("The cheapest device is: ");
                            System.out.printf("Category: %s, Name: %s, Price: %.2f$, Quantity: %d\n", cheapestDevice.getCategory(), cheapestDevice.getName(), cheapestDevice.getPrice(), cheapestDevice.getQuantity());
                        }

                        break;
                    case 6:
                        inventory.sortDevice();

                        break;
                    case 7:
                        inventory.calculateTotalPrice();

                        break;
                    case 8:
                        System.out.print("Enter the name of the device to restock: ");
                        deviceName = scanner.nextLine();

                        System.out.print("Do you want to add or remove stock? (Add/Remove): ");
                        String decision = scanner.nextLine();

                        if (decision.equals("Add") || decision.equals("Remove")) {
                            System.out.printf("Enter the quantity to %s: ", decision.toLowerCase());
                            quantity = scanner.nextInt();
                            device = inventory.restockDevice(deviceName, decision, quantity);
                            if (device != null)
                                System.out.printf("%s stock restocked. New quantity: %d\n", device.getName(), device.getQuantity());
                            else
                                System.out.println("Can not restocked. Try again!");
                        } else
                            System.out.println("Invalid decision. Try again!");

                        break;
                    case 9:
                        inventory.displayReport();

                        break;
                    case 0:
                        System.out.println("Program terminating...");
                        break;
                    default:
                        System.out.println("Invalid Input. Please try again!");
                }

                if (choice == 0)
                    break;
            }
        }
        catch (Exception e) {
            System.out.println("Invalid input!");
        }
    }

    /***
     * A method for displaying menu
     * Time complexity O(1) : Because there is no loop or recursion, all statements has O(1) time complexity.
     */
    private static void displayMenu() {
        System.out.println("\nPlease select a option:");
        System.out.println("1. Add a new device");
        System.out.println("2. Remove a device");
        System.out.println("3. Update device details");
        System.out.println("4. List all devices");
        System.out.println("5. Find the cheapest device");
        System.out.println("6. Sort devices by price");
        System.out.println("7. Calculate total inventory value");
        System.out.println("8. Restock a device");
        System.out.println("9. Export inventory report");
        System.out.println("0. Exit");
    }
}

