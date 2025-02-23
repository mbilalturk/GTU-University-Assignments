package cse222.gtu;

import java.sql.Timestamp;

/**
 * Represents an element in a file system, which can be either a file or a directory.
 */
public abstract class FileSystemElement {
    private String name;
    private Timestamp dataCreated;
    private FileSystemElement parent;

    /**
     * Constructs a new FileSystemElement with the specified name and parent.
     *
     * @param name   The name of the file system element.
     * @param parent The parent element in the file system hierarchy.
     */
    public FileSystemElement(String name, FileSystemElement parent) {
        this.name = name;
        this.parent = parent;
        this.dataCreated = new Timestamp(System.currentTimeMillis());
    }

    /**
     * Returns the name of the file system element.
     *
     * @return The name of the element.
     */
    public String getName() {
        return name;
    }

    /**
     * Returns the timestamp when the file system element was created.
     *
     * @return The creation timestamp of the element.
     */
    public Timestamp getDataCreated() {
        return dataCreated;
    }

    /**
     * Returns the parent element of this file system element.
     *
     * @return The parent element.
     */
    public FileSystemElement getParent() {
        return parent;
    }

    /**
     * Sets the parent element of this file system element.
     *
     * @param parent The new parent element to set.
     */
    public void setParent(FileSystemElement parent) {
        this.parent = parent;
    }

    /**
     * Abstract method to print the file system element's details with a prefix.
     *
     * @param prefix The prefix to use when printing the element's details.
     */
    public abstract void print(String prefix);

}
