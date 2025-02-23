package cse222.gtu;

/**
 * Represents a file in a file system.
 */
public class File extends FileSystemElement {
    /**
     * Constructs a new File with the specified name and parent.
     *
     * @param name   The name of the file.
     * @param parent The parent element of the file.
     */
    public File(String name, FileSystemElement parent) {
        super(name, parent);
    }

    /**
     * Prints the name of the file.
     *
     * @param prefix The prefix to print before the name.
     */
    @Override
    public void print(String prefix) {
        System.out.println(this.getName());
    }
}
