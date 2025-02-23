package cse222.gtu;

import java.util.LinkedList;

/**
 * Represents a directory in a file system which can contain other file system elements.
 */
public class Directory extends FileSystemElement {
    /**
     * A list of file system elements that are children of this directory.
     */
    private LinkedList<FileSystemElement> children;

    /**
     * Constructs a new Directory with the specified name and parent.
     *
     * @param name   The name of the directory.
     * @param parent The parent element of the directory.
     */
    public Directory(String name, FileSystemElement parent) {
        super(name, parent);
        children = new LinkedList<>();
    }

    /**
     * Adds a file system element to the beginning of the list of children.
     *
     * @param element The file system element to add.
     */
    public void addElement(FileSystemElement element) {
        children.addFirst(element);
    }

    /**
     * Removes a file system element from the list of children.
     *
     * @param element The file system element to remove.
     */
    public void removeElement(FileSystemElement element) {
        children.remove(element);
    }

    /**
     * Returns the list of file system elements that are children of this directory.
     *
     * @return The list of children file system elements.
     */
    public LinkedList<FileSystemElement> getChildren() {
        return children;
    }

    /**
     * Prints the name of the directory with the specified prefix.
     *
     * @param prefix The prefix to print before the name.
     */
    @Override
    public void print(String prefix) {
        System.out.println(prefix + " " + getName());
    }
}
