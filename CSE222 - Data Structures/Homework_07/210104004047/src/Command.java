import java.io.IOException;
import java.io.PrintWriter;
import java.util.Random;

/**
 * The Command class generates a file with a specified number of random commands.
 * Each command is related to stock operations such as ADD, REMOVE, SEARCH, and UPDATE.
 * The commands are written to a specified file.
 */
public class Command {
    private static final String LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    private static final Random RANDOM = new Random();
    private static int size = 1000;

    /**
     * Default constructor that generates 1000 commands and writes them to "input.txt".
     */
    public Command() {
        this("input.txt", 1000);
    }

    /**
     * Constructor that generates a specified number of commands and writes them to "input.txt".
     * @param size the number of commands to generate
     */
    public Command(int size) {
        this("input.txt", size);
    }

    /**
     * Constructor that generates a specified number of commands and writes them to a specified file.
     * If the size is less than or equal to 0, it defaults to 1000.
     * @param fileName the name of the file to write the commands to
     * @param size the number of commands to generate
     */
    public Command(String fileName, int size) {
        if(size <= 1000)
            size = 1000;

        this.size = size;
        try (PrintWriter pw = new PrintWriter(fileName)) {
            generateRandomCommands(pw);
            // System.out.println(size + " lines generated randomly!");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Generates a specified number of random commands and writes them to the provided PrintWriter.
     * @param pw the PrintWriter to write the commands to
     */
    private void generateRandomCommands(PrintWriter pw) {
        for (int i = 0; i < size; ++i) {
            String command = generateCommand();
            pw.println(command);
        }
    }

    /**
     * Generates a random command string.
     * The command can be one of ADD, REMOVE, SEARCH, or UPDATE, followed by a symbol,
     * and random values for price, volume, and market cap.
     * @return the generated command string
     */
    private String generateCommand() {
        int commandNumber = RANDOM.nextInt(7);
        String symbol = generateSymbol();
        String updateSymbol = null;
        String price = String.format("%.1f", RANDOM.nextDouble() * 1000);
        long volume = (long) (RANDOM.nextDouble() * 100000);
        long marketCap = (long) (RANDOM.nextDouble() * 1000000);

        StringBuilder line = new StringBuilder();
        switch (commandNumber) {
            case 0:
            case 1:
            case 2:
                line.append("ADD ");
                line.append(symbol).append(' ');
                break;
            case 3:
            case 4:
                line.append("REMOVE ");
                line.append(symbol).append(' ');
                break;
            case 5:
                line.append("SEARCH ");
                line.append(symbol).append(' ');
                break;
            case 6:
                line.append("UPDATE ");
                updateSymbol = generateSymbol();
                price = String.format("%.1f", RANDOM.nextDouble() * 100);
                volume = (long) (RANDOM.nextDouble() * 100000);
                marketCap = (long) (RANDOM.nextDouble() * 1000000);
                line.append(symbol).append(' ').append(updateSymbol).append(' ');
                break;
            default:
                throw new IllegalStateException("Unexpected value: " + commandNumber);
        }

        line.append(price).append(' ').append(volume).append(' ').append(marketCap);

        return line.toString();
    }

    /**
     * Generates a random three-letter symbol.
     * @return the generated symbol
     */
    private String generateSymbol() {
        StringBuilder symbol = new StringBuilder();
        for (int j = 0; j < 3; ++j) {
            symbol.append(LETTERS.charAt(RANDOM.nextInt(LETTERS.length())));
        }
        return symbol.toString();
    }
}
