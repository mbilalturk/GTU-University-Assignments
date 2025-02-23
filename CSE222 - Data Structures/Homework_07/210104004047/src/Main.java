import javax.swing.*;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

/**
 * The Main class contains the main method for executing the program, which performs
 * stock management operations and displays performance graphs.
 */
public class Main {
    // Variables for tracking average times and counters
    private static ArrayList<Long> averageAddTime = new ArrayList<>();
    private static ArrayList<Long> averageRemoveTime = new ArrayList<>();
    private static ArrayList<Long> averageSearchTime = new ArrayList<>();
    private static ArrayList<Long> averageUpdateTime = new ArrayList<>();
    private static long addTime = 0;
    private static long removeTime = 0;
    private static long searchTime = 0;
    private static long updateTime = 0;
    private static int addCounter = 0;
    private static int removeCounter = 0;
    private static int searchCounter = 0;
    private static int updateCounter = 0;

    /**
     * The main method of the program, responsible for executing stock management operations
     * and displaying performance graphs.
     * @param args the command-line arguments
     */
    public static void main(String[] args) {
        // Generate random commands and save them to a file
        new Command(30000);

        // Initialize StockDataManager
        String inputFile = "input.txt";
        StockDataManager manager = new StockDataManager();

        // Process commands from the input file
        try (BufferedReader br = new BufferedReader(new FileReader(inputFile))) {
            String line;
            while ((line = br.readLine()) != null) {
                processCommand(line, manager);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Show performance graphs
        showGraph();


        int[] treeSizes = {1000, 10000, 100000}; // Tree sizes to test

        for (int size : treeSizes) {
            StockDataManager newManager = new StockDataManager();

            System.out.println("*".repeat(100));
            performPerformanceAnalysis(newManager, size);
        }
    }

    /**
     * Processes each command from the input file and performs corresponding stock management operations.
     * @param line the command read from the input file
     * @param manager the StockDataManager object for managing stocks
     */
    private static void processCommand(String line, StockDataManager manager) {
        String[] tokens = line.split(" ");
        String command = tokens[0];

        long startTime, endTime;

        switch (command) {
            case "ADD":
                startTime = System.nanoTime();
                manager.addOrUpdateStock(tokens[1], Double.parseDouble(tokens[2].replace(',', '.')), Long.parseLong(tokens[3]), Long.parseLong(tokens[4]));
                endTime = System.nanoTime();
                addCounter++;
                addTime += (endTime - startTime);
                if (addCounter % 15 == 0) {
                    averageAddTime.add(addTime / 15);
                    addTime = 0;
                }
                break;
            case "REMOVE":
                startTime = System.nanoTime();
                manager.removeStock(tokens[1]);
                endTime = System.nanoTime();
                removeCounter++;
                removeTime += (endTime - startTime);
                if (removeCounter % 15 == 0) {
                    averageRemoveTime.add(removeTime / 15);
                    removeTime = 0;
                }
                break;
            case "SEARCH":
                startTime = System.nanoTime();
                Stock stock = manager.searchStock(tokens[1]);
                endTime = System.nanoTime();
                searchCounter++;
                searchTime += (endTime - startTime);
                if (searchCounter % 15 == 0) {
                    averageSearchTime.add(searchTime / 15);
                    searchTime = 0;
                }
                if (stock != null) {
                    System.out.println(stock);
                } else {
                    System.out.println("Stock not found: " + tokens[1]);
                }
                break;
            case "UPDATE":
                try {
                    startTime = System.nanoTime();
                    manager.updateStock(tokens[1], tokens[2], Double.parseDouble(tokens[3].replace(',', '.')), Long.parseLong(tokens[4]), Long.parseLong(tokens[5]));
                    endTime = System.nanoTime();
                    updateCounter++;
                    updateTime += (endTime - startTime);
                    if (updateCounter % 15 == 0) {
                        averageUpdateTime.add(updateTime / 15);
                        updateTime = 0;
                    }
                } catch (NumberFormatException e) {
                    System.err.println("Invalid number format in UPDATE command: " + line);
                }
                break;
            default:
                System.out.println("Unknown command: " + command);
                break;
        }
    }

    /**
     * Displays performance graphs for ADD, REMOVE, and SEARCH operations.
     */
    private static void showGraph() {
        SwingUtilities.invokeLater(() -> {
            String plotType = "scatter";
            GUIVisualization frame = new GUIVisualization(plotType, averageAddTime, averageAddTime.size(), "Add");
            frame.setVisible(true);
        });

        SwingUtilities.invokeLater(() -> {
            String plotType = "scatter";
            GUIVisualization frame = new GUIVisualization(plotType, averageRemoveTime, averageRemoveTime.size(), "Remove");
            frame.setVisible(true);
        });

        SwingUtilities.invokeLater(() -> {
            String plotType = "scatter";
            GUIVisualization frame = new GUIVisualization(plotType, averageSearchTime, averageSearchTime.size(), "Search");
            frame.setVisible(true);
        });

        SwingUtilities.invokeLater(() -> {
            String plotType = "scatter";
            GUIVisualization frame = new GUIVisualization(plotType, averageSearchTime, averageSearchTime.size(), "Update");
            frame.setVisible(true);
        });
    }

    /**
     * Performs performance analysis by measuring the time taken for ADD, REMOVE, and SEARCH operations.
     * @param manager the StockDataManager object for managing stocks
     * @param size the size of the data for performance analysis
     */
    private static void performPerformanceAnalysis(StockDataManager manager, int size) {
        long startTime, endTime;

        System.out.println("Size = " + size);

        // Measure time for ADD operation
        startTime = System.nanoTime();
        for (int i = 0; i < size; i++) {
            manager.addOrUpdateStock("SYMB" + i, Math.random() * 100, (long) (Math.random() * 1000000), (long) (Math.random() * 1000000000));
        }
        endTime = System.nanoTime();
        System.out.println("Average ADD time for size " + size + ": " + (endTime - startTime) / size + " ns");


        //Measure time for SEARCH operation
        startTime = System.nanoTime();
        for (int i = 0; i < size; i++) {
            manager.searchStock("SYMB" + i);
        }
        endTime = System.nanoTime();
        System.out.println("Average SEARCH time for size " + size + ": " + (endTime - startTime) / size + " ns");


        // Measure time for REMOVE operation
        startTime = System.nanoTime();
        for (int i = 0; i < size; i++) {
            manager.removeStock("SYMB" + i);
        }
        endTime = System.nanoTime();
        System.out.println("Average REMOVE time for size " + size + ": " + (endTime - startTime) / size + " ns");
    }
}
