package cse222.gtu;

import java.util.InputMismatchException;
import java.util.Scanner;

/**
 * The Main class contains the main method to run the file system management program.
 * It provides a menu-based interface to interact with the file system.
 */
public class Main {

    private static FileSystem fs = new FileSystem();
    private static Scanner scanner = new Scanner(System.in);
    private static Directory currentDirectory;

    /**
     * The main method to run the file system management program.
     *
     * @param args command line arguments (not used)
     */
    public static void main(String[] args) {
        currentDirectory = fs.getRoot();


        while (true) {
            try{
                System.out.print("Current directory: ");
                System.out.println(fs.getCurrentPath(currentDirectory));
                System.out.print(
                        "==== File System Management Menu ====\n" +
                                "1. Change directory\n" +
                                "2. List directory contents\n" +
                                "3. Create file\n" +
                                "4. Create directory\n" +
                                "5. Delete file\n" +
                                "6. Delete directory\n" +
                                "7. Move file/directory\n" +
                                "8. Search file/directory\n" +
                                "9. Print directory tree\n" +
                                "10. Sort contents by date\n" +
                                "11. Exit\n" +
                                "Please select an option: ");

                int choice = scanner.nextInt();
                scanner.nextLine();

                switch (choice) {
                    case 1:
                        changeDirectory(); // Not implemented yet
                        break;
                    case 2:
                        listContents();
                        break;
                    case 3:
                        createFile();
                        break;
                    case 4:
                        createDirectory();
                        break;
                    case 5:
                        deleteFile();
                        break;
                    case 6:
                        deleteDirectory();
                        break;
                    case 7:
                        moveElement(); // Not implemented yet
                        break;
                    case 8:
                        search();
                        break;
                    case 9:
                        printDirectoryTree();
                        break;
                    case 10:
                        sortDirectoryByDate();
                        break;
                    case 11:
                        scanner.close();
                        System.exit(0);
                        break;
                    default:
                        System.out.println("Invalid option. PLease try again!");
                }
                System.out.println();
            }
            catch (InputMismatchException e) {
                scanner.nextLine();
                System.out.println("Invalid input! Please try again!");
            }
            catch (Exception e) {

            }

        }
    }

    /**
     * Changes the current directory based on user input.
     */
    private static void changeDirectory() {
        System.out.print("Current directory: ");
        System.out.println(fs.getCurrentPath(currentDirectory));
        System.out.print("Enter new directory path: ");
        String newPath = scanner.nextLine();
        Directory successful = fs.changeDirectory(newPath);
        if(successful != null)
            currentDirectory = successful;
    }

    /**
     * Lists the contents of the current directory.
     */
    private static void listContents() {
        fs.listContents(currentDirectory);
    }

    /**
     * Creates a new file in the current directory.
     */
    private static void createFile() {
        System.out.print("Enter file name to create: ");
        String name = scanner.nextLine();
        fs.createFile(name, currentDirectory);
    }

    /**
     * Creates a new directory in the current directory.
     */
    private static void createDirectory() {
        System.out.print("Enter directory name to create: ");
        String name = scanner.nextLine();
        fs.createDirectory(name, currentDirectory);
    }

    /**
     * Deletes a file in the current directory.
     */
    private static void deleteFile() {
        System.out.print("Enter file name to delete: ");
        String name = scanner.nextLine();
        fs.deleteFile(name, currentDirectory);
    }

    /**
     * Deletes a directory in the current directory.
     */
    private static void deleteDirectory() {
        System.out.print("Enter directory name to delete: ");
        String name = scanner.nextLine();
        fs.deleteDirectory(name, currentDirectory);
    }

    /**
     * Moves a file or directory to a new location.
     */
    private static void moveElement() {
        System.out.print("Current directory: ");
        System.out.println(fs.getCurrentPath(currentDirectory));
        System.out.print("Enter the name of file/directory to move: ");
        String name = scanner.nextLine();
        System.out.print("Enter new directory path: ");
        String path = scanner.nextLine();
        fs.moveElement(name, path, currentDirectory);
    }

    /**
     * Searches for a file or directory.
     */
    private static void search() {
        System.out.print("Search query: ");
        String name = scanner.nextLine();
        Directory root = fs.getRoot();
        System.out.println("Searching from root...");
        FileSystemElement found = fs.searchRecursive(name, root);
        if(found == null)
            System.out.println(name + " not found! ");
        else
            System.out.println("Found: " + fs.getCurrentPath(found));
    }

    /**
     * Prints the directory tree structure.
     */
    private static void printDirectoryTree() {
        fs.printDirectoryTree(currentDirectory);
    }

    /**
     * Sorts the contents of the current directory by date.
     */
    private static void sortDirectoryByDate() {
        fs.sortDirectoryByDate(currentDirectory);
    }

}