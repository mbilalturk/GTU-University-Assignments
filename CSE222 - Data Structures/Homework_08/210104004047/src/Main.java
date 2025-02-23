import java.util.*;

/**
* The main class for the social network analysis program.
*/
public class Main {
    private static final Scanner scanner = new Scanner(System.in);
    private static SocialNetworkGraph network = new SocialNetworkGraph();

    /**
     * The main method that starts the social network analysis application.
     * It continuously displays the menu and prompts the user for input until the user chooses to exit.
     * @param args command-line arguments (not used)
     */
    public static void main(String[] args) {
        boolean countinue = true;
        while(countinue) {
            menu();
            try {
                countinue = prompt();
            }
            catch (Exception e) {
                System.out.println("Invalid input type. Please enter the correct type of input.");
                scanner.nextLine();
            }
        }
        
    }

    /**
     * Displays the main menu for the Social Network Analysis application.
     */
    private static void menu() {
        System.out.println("\n==== Social Network Analysis Menu ====");
        System.out.println("1. Add person");
        System.out.println("2. Remove person");
        System.out.println("3. Add friendship");
        System.out.println("4. Remove friendship");
        System.out.println("5. Find shortest path");
        System.out.println("6. Suggest friends");
        System.out.println("7. Count clusters");
        System.out.println("8. Exit");
        System.out.print("Please select an option: ");
    }

    /**
     * Prompts the user for input and performs actions based on the user's choice.
     * @return true if program will continue, otherwise false
     */
    private static boolean prompt() {
        int choice = scanner.nextInt();
        scanner.nextLine();

        switch (choice) {
            case 1:
                System.out.print("Enter name: ");
                String addName = scanner.nextLine();

                System.out.print("Enter age: ");
                int addAge = scanner.nextInt();
                scanner.nextLine();

                System.out.print("Enter hobbies (comma-separated): ");
                String[] addHhobbies = scanner.nextLine().split(",");
                List<String> hobbyList = Arrays.stream(addHhobbies).toList();

                network.addPerson(addName, addAge, hobbyList);
                break;
            case 2:
                System.out.print("Enter name: ");
                String removeName = scanner.nextLine();

                System.out.print("Enter timestamp: ");
                String removeTimestamp = scanner.nextLine();

                network.removePerson(removeName);
                break;
            case 3:
                System.out.print("Enter first person's name: ");
                String firstPerson = scanner.nextLine();

                System.out.print("Enter first person's timestamp: ");
                String firstPersonTimestamp = scanner.nextLine();

                System.out.print("Enter second person's name: ");
                String secondPerson = scanner.nextLine();

                System.out.print("Enter second person's timestamp: ");
                String secondPersonTimestamp = scanner.nextLine();

                network.addFriendship(firstPerson, secondPerson);
                break;
            case 4:
                System.out.print("Enter first person's name: ");
                String firstName = scanner.nextLine();

                System.out.print("Enter first persons's timestamp: ");
                String firstTimestamp = scanner.nextLine();

                System.out.print("Enter second person's name: ");
                String secondName = scanner.nextLine();

                System.out.print("Enter second person's timestamp: ");
                String secondTimestamp = scanner.nextLine();
                ;

                network.removeFriendship(firstName, secondName);
                break;
            case 5:
                System.out.print("Enter first person's name: ");
                String firstPersonName = scanner.nextLine();

                System.out.print("Enter first persons's timestamp: ");
                String firstPersonsTimestamp = scanner.nextLine();

                System.out.print("Enter second person's name: ");
                String secondPersonName = scanner.nextLine();

                System.out.print("Enter second person's timestamp: ");
                String secondPersonsTimestamp = scanner.nextLine();

                network.findShortestPath(firstPersonName, secondPersonName);
                break;
            case 6:
                System.out.print("Enter person's name: ");
                String personName = scanner.nextLine();

                System.out.print("Enter first persons's timestamp: ");
                String suggestTimestamp = scanner.nextLine();

                System.out.print("Enter maximum number of friends to suggest: ");
                int suggestNumber = scanner.nextInt();
                scanner.nextLine();

                network.suggestFriend(personName, suggestNumber);
                break;
            case 7:
                System.out.println("Counting clusters in the social network...");
                network.countClusters();
                break;
            case 8:
                System.out.println("Program terminated successfully!");
                return false;
            default:
                throw new InputMismatchException();
        }
        return true;
    }
}
