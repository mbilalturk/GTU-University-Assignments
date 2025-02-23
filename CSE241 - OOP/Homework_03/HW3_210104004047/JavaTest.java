import cse241.homeworks_3.*;

import java.io.FileWriter;
import java.io.IOException;
import java.util.NoSuchElementException;
import java.util.Scanner;

/**
 * The JavaTest class provides a simple interactive console-based interface for testing the JavaSet
 * and JavaVector classes. It allows users to add, remove, and display elements in either a set or a vector,
 * and writes the output to files.
 */
public class JavaTest {
    /**
     * The main method that serves as the entry point for the JavaTest application.
     * It has an interactive console interface for testing the JavaSet and JavaVector classes.
     *
     * @param args command-line arguments (not used)
     */
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        boolean start = true;

        while (true) {
            try {
                // If program starts, empty file and test
                if(start) {
                    emptyFile("sets.txt");
                    emptyFile("vectors.txt");
                    testSetAndVector();
                    start = false;
                }

                System.out.println("------------------------------------------");
                System.out.print("Type exit to terminate the program: ");
                System.out.print("Enter which type of variable you will store (int, double, String): ");
                char typeofVariableInput = scanner.nextLine().toLowerCase().charAt(0);
                if (typeofVariableInput == 'e')
                    break;

                System.out.print("Enter which type container you want to create (set/vector): ");
                char containerType = scanner.nextLine().toLowerCase().charAt(0);

                System.out.print("Enter capacity: ");
                int capacity = Integer.parseInt(scanner.nextLine());

                System.out.print("Enter elements with comma: ");
                String elementsInput = scanner.nextLine();
                String[] elements = elementsInput.split(",");

                JavaSet<Object> set = new JavaSet<>(capacity);
                JavaVector<Object> vector = new JavaVector<>(capacity);

                addToSetOrVector(set, vector, elements, typeofVariableInput, containerType);
                display(set, vector, containerType);

                System.out.print("Enter element that you want to remove:");
                String removeInput = scanner.nextLine();

                removeFromSetOrVector(set,vector,removeInput,typeofVariableInput,containerType);
                display(set, vector, containerType);

            }
            catch(IllegalArgumentException illegalArgumentException){
                System.out.println(illegalArgumentException.getMessage());
            }
            catch(IllegalStateException illegalStateException){
                System.out.println(illegalStateException.getMessage());
            }
            catch(NoSuchElementException noSuchElementException){
                System.out.println(noSuchElementException.getMessage());
            }
            catch(ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException){
                System.out.println(arrayIndexOutOfBoundsException.getMessage());
            }
            catch(RuntimeException runtimeException) {
                System.out.println(runtimeException.getMessage());
            }
        }
    }


    /**
     * Tests some methods of the JavaSet and JavaVector classes by performing various operations
     * such as adding, removing, and comparing elements.
     */
    public static void testSetAndVector() {
        JavaSet<Integer> intSet = new JavaSet<>(5);
        intSet.add(1);
        intSet.add(2);
        intSet.add(3);

        JavaSet<Integer> intSet2 = new JavaSet<>();
        intSet2.add(1);
        intSet2.add(3);
        intSet2.add(2);

        System.out.println(intSet);
        System.out.println(intSet2);

        System.out.println("equals: " + intSet.equals(intSet2));
        System.out.println("*******************");

        intSet.remove(3);

        System.out.println(intSet);
        System.out.println(intSet2);
        intSet.toFile();
        intSet2.toFile();

        System.out.println("equals: " + intSet.equals(intSet2));
        System.out.println("*******************\n");

        JavaSet<Double> doubleSet = new JavaSet<>();
        doubleSet.add(1.5);
        doubleSet.add(2.5);
        doubleSet.add(3.5);

        JavaSet<Double> doubleSet2 = new JavaSet<>(5);
        doubleSet2.add(1.5);
        doubleSet2.add(3.5);
        doubleSet2.add(2.5);

        System.out.println(doubleSet);
        System.out.println(doubleSet2);

        System.out.println("equals: " + doubleSet.equals(doubleSet2));
        System.out.println("*******************");

        doubleSet.remove(3.5);

        System.out.println(intSet);
        System.out.println(intSet2);

        System.out.println("equals: " + intSet.equals(intSet2));
        System.out.println("*******************\n");
        doubleSet.toFile();
        doubleSet2.toFile();


        JavaVector<Integer> intVector = new JavaVector<>(5);
        intVector.add(1);
        intVector.add(2);
        intVector.add(3);
        intVector.add(1);
        intVector.add(3);

        JavaVector<Integer> intVector2 = new JavaVector<>();
        intVector2.add(1);
        intVector2.add(2);
        intVector2.add(3);
        intVector2.add(1);
        intVector2.add(3);

        System.out.println(intVector);
        System.out.println(intVector2);

        System.out.println("equals: " + intVector.equals(intVector2));
        System.out.println("*******************");

        intVector.remove(3);

        System.out.println(intVector);
        System.out.println(intVector2);

        System.out.println("equals: " + intVector.equals(intVector2));
        System.out.println("*******************\n");
        intVector.toFile();
        intVector2.toFile();
    }

    /**
     * Adds user input elements to either a set or a vector based on the specified type of variable
     * and container type.
     *
     * @param set                the JavaSet object to add elements to
     * @param vector             the JavaVector object to add elements to
     * @param elements           the elements to be added
     * @param typeOfVariableInput the type of variable input (int, double, String)
     * @param containerType      the type of container (set or vector)
     */
    public static void addToSetOrVector(JavaSet<Object> set, JavaVector<Object> vector, String[] elements, char typeOfVariableInput, char containerType) {
        for (var e : elements) {
            switch (typeOfVariableInput) {
                case 'i':
                    int intValue = Integer.parseInt(e);
                    if (containerType == 's') {
                        set.add(intValue);
                    } else if (containerType == 'v') {
                        vector.add(intValue);
                    }
                    break;
                case 'd':
                    double doubleValue = Double.parseDouble(e);
                    if (containerType == 's') {
                        set.add(doubleValue);
                    } else if (containerType == 'v') {
                        vector.add(doubleValue);
                    }
                    break;
                case 's':
                    if (containerType == 's') {
                        set.add(e);
                    } else if (containerType == 'v') {
                        vector.add(e);
                    }
                    break;
                default:
                    throw new IllegalArgumentException("Invalid Input");
            }
        }
    }

    /**
     * Removes user input element from either a set or a vector based on the specified type of variable
     * and container type.
     *
     * @param set                the JavaSet object to remove element from
     * @param vector             the JavaVector object to remove element from
     * @param removeInput        the element to be removed
     * @param typeOfVariableInput the type of variable input (int, double, String)
     * @param containerType      the type of container (set or vector)
     */
    public static void removeFromSetOrVector(JavaSet<Object> set, JavaVector<Object> vector, String removeInput, char typeOfVariableInput, char containerType) {
        switch (typeOfVariableInput) {
            case 'i':
                int intValue = Integer.parseInt(removeInput);
                if (containerType == 's') {
                    set.remove(intValue);
                } else if (containerType == 'v') {
                    vector.remove(intValue);
                }
                break;
            case 'd':
                double doubleValue = Double.parseDouble(removeInput);
                if (containerType == 's') {
                    set.remove(doubleValue);
                } else if (containerType == 'v') {
                    vector.remove(doubleValue);
                }
                break;
            case 's':
                if (containerType == 's') {
                    set.remove(removeInput);
                } else if (containerType == 'v') {
                    vector.remove(removeInput);
                }
                break;
            default:
                throw new IllegalArgumentException("Invalid Input");
        }
    }

    /**
     * Displays the contents of either a set or a vector and writes the output to a file.
     *
     * @param set          the JavaSet object to display
     * @param vector       the JavaVector object to display
     * @param containerType the type of container (set or vector)
     */
    public static void display(JavaSet<Object> set, JavaVector<Object> vector, char containerType) {
        if (containerType == 's') {
            System.out.println(set);
            set.toFile();
        } else if (containerType == 'v') {
            System.out.println(vector);
            vector.toFile();
        }
    }

    /**
     * Empties the contents of a file by truncating it.
     *
     * @param fileName the name of the file to be emptied
     */
    public static void emptyFile(String fileName) {
        try {
            FileWriter writer = new FileWriter(fileName);
            writer.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

}
