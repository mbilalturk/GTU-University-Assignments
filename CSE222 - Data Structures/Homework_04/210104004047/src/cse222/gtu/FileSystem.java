package cse222.gtu;

import java.util.Collections;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;

/**
 * FileSystem represents a simple file system with directories and files.
 * It provides functionalities to create, delete, move, and list directories and files.
 */
public class FileSystem {
    private Directory root;

    /**
     * Constructs a new FileSystem with a root directory.
     */
    public FileSystem() {
        this.root = new Directory("/", null);
    }

    /**
     * Creates a new file with the given name and adds it to the specified parent directory.
     *
     * @param name   the name of the file to be created
     * @param parent the parent directory where the file will be created
     */
    public void createFile(String name, Directory parent) {
        if(search(name, parent)) {
            System.out.println("File named " + name + " already exist!");
        }
        else {
            File newFile = new File(name, parent);
            parent.addElement(newFile);
            System.out.println("File created: " + name);
        }
    }

    /**
     * Creates a new directory with the given name and adds it to the specified parent directory.
     *
     * @param name   the name of the directory to be created
     * @param parent the parent directory where the directory will be created
     */
    public void createDirectory(String name, Directory parent) {
        if(search(name, parent)) {
            System.out.println("Directory named " + name + " already exist!");
        }
        else {
            Directory newDirectory = new Directory(name, parent);
            parent.addElement(newDirectory);
            System.out.println("Directory created: " + name);
        }
    }

    /**
     * Deletes the file with the given name from the specified parent directory.
     *
     * @param name   the name of the file to be deleted
     * @param parent the parent directory from which the file will be deleted
     */
    public void deleteFile(String name, Directory parent) {
        FileSystemElement fileToRemove = searchRecursive(name, parent);
        if(!(fileToRemove instanceof File)) {
            System.out.println("File named " + name + " not found!");
        }
        else {
            parent.removeElement(fileToRemove);
            System.out.println("File deleted: " + name);
        }
    }

    /**
     * Deletes the directory with the given name from the specified parent directory.
     *
     * @param name   the name of the directory to be deleted
     * @param parent the parent directory from which the directory will be deleted
     */
    public void deleteDirectory(String name, Directory parent) {
        Directory directoryToDelete = (Directory) searchRecursive(name, parent);

        if (directoryToDelete != null) {
            deleteDirectoryRecursive(directoryToDelete);
            parent.removeElement(directoryToDelete);
            System.out.println("Directory deleted: " + name);
        } else {
            System.out.println("Directory named " + name + " not found!");
        }
    }

    /**
     * Recursively deletes the specified directory and all its contents (files and subdirectories).
     * This method is called internally to delete directories in a recursive manner.
     *
     * @param directory the directory to be deleted recursively
     */
    private void deleteDirectoryRecursive(Directory directory) {
        for (FileSystemElement element : directory.getChildren()) {
            if (element instanceof Directory) {
                deleteDirectoryRecursive((Directory) element);
            } else {
                // If element is a file, delete it
                directory.removeElement(element);
            }
        }
    }

    /**
     * Moves the file or directory with the given name to the specified path.
     * If the destination directory does not exist, the element remains in its original location.
     *
     * @param name   the name of the file or directory to be moved
     * @param path   the destination path to which the file or directory will be moved
     * @param parent the parent directory from which the file or directory will be moved
     */
    public void moveElement(String name, String path, Directory parent) {
        FileSystemElement foundElement = null;

        LinkedList<FileSystemElement> childrens = parent.getChildren();
        for(int i=0; i<childrens.size(); ++i) {
            FileSystemElement element = childrens.get(i);
            if(element.getName().equals(name)) {
                foundElement = childrens.remove(i);
            }
        }

        if(foundElement == null) {
            System.out.println(name + " not found!");
            return;
        }

        Directory newParent = getDirectory(path);

        if(newParent == null) {
            System.out.println("Destination directory '" + path + "' not found!");
            parent.getChildren().add(foundElement);
        }
        else {
            newParent.addElement(foundElement);
            foundElement.setParent(newParent);
            System.out.println("Element '" + name + "' moved to '" + path + "'");
        }
    }

    /**
     * Retrieves the directory specified by the given path within the file system.
     *
     * @param path the path of the directory to retrieve
     * @return the directory specified by the path, or null if the directory does not exist
     */
    private Directory getDirectory(String path) {
        Directory newParent = getRoot();
        String[] directories = path.split("/");

        for (String directory : directories) {
            if (!directory.isEmpty()) {
                boolean found = false;
                for (FileSystemElement element : newParent.getChildren()) {
                    if (element instanceof Directory && element.getName().equals(directory)) {
                        newParent = (Directory) element;
                        found = true;
                        break;
                    }
                }
                if(!found)
                    newParent = null;
            }
        }
        return newParent;
    }

    /**
     * Searches for an element (file or directory) with the given name within the specified parent directory.
     *
     * @param name   the name of the element to search for
     * @param parent the parent directory in which the search will be conducted
     * @return true if the element is found, false otherwise
     */

    public boolean search(String name, Directory parent) {
        return searchRecursive(name, parent) != null;
    }

    /**
     * Recursively searches for an element (file or directory) with the given name within the specified parent directory.
     *
     * @param name   the name of the element to search for
     * @param parent the parent directory in which the recursive search will be conducted
     * @return the found element if it exists, null otherwise
     */
    public FileSystemElement searchRecursive(String name, Directory parent) {
        for (FileSystemElement element : parent.getChildren()) {
            if (element.getName().equals(name)) {
                return element;
            }
            if (element instanceof Directory) {
                FileSystemElement found = searchRecursive(name, (Directory) element);
                if (found != null) {
                    return found;
                }
            }
        }
        return null;
    }

    /**
     * Prints the directory tree structure starting from the specified directory.
     *
     * @param currentDirectory the directory from which the directory tree will be printed
     */
    public void printDirectoryTree(Directory currentDirectory) {
        String[] strings = getCurrentPath(currentDirectory).split("/");

        for(int i=0 ; i<strings.length; ++i)
            System.out.println(" ".repeat(i) + "* " + strings[i] + "/");

        for(FileSystemElement element : currentDirectory.getChildren()) {
            System.out.print(" ".repeat(strings.length+1));
            if(element instanceof File)
                element.print("");
            else
                element.print("*");
        }
    }

    /**
     * Lists the contents (files and directories) of the specified directory.
     *
     * @param dir the directory whose contents will be listed
     */
    public void listContents(Directory dir) {
        System.out.println("Listing contents of " + getCurrentPath(dir) + ":");
        if(dir != null) {
            for (FileSystemElement element : dir.getChildren()) {
                if (element instanceof Directory)
                    element.print("*");
                else
                    System.out.println(element.getName());
            }
        }
    }

    /**
     * Sorts the contents of the specified directory by date created and prints them.
     *
     * @param dir the directory whose contents will be sorted and printed
     */
    public void sortDirectoryByDate(Directory dir) {
        System.out.println("Sorted contents of " + getCurrentPath(dir) + " by date created: ");

        List<FileSystemElement> children = dir.getChildren();
        Collections.sort(children, Comparator.comparing(FileSystemElement::getDataCreated));


        for (FileSystemElement element : children) {
            if (element instanceof Directory)
                System.out.println("* " + element.getName() + " (" + element.getDataCreated() + ")");
            else
                System.out.println(element.getName() + " (" + element.getDataCreated() + ")");
        }
    }

    /**
     * Constructs and returns the current path of the given FileSystemElement.
     *
     * @param element the file or directory whose path will be constructed
     * @return the current path of the element
     */
    public String getCurrentPath(FileSystemElement element) {
        StringBuilder pathBuilder = new StringBuilder();
        constructPath(element, pathBuilder);
        return pathBuilder.toString();
    }

    /**
     * Recursively constructs the path of the given FileSystemElement within the file system.
     * The path includes all parent directories leading to the element.
     *
     * @param element     the file or directory whose path will be constructed
     * @param pathBuilder a StringBuilder to append the path components
     */
    private void constructPath(FileSystemElement element, StringBuilder pathBuilder) {
        if(element == null)
            return;

        if(element.getParent() == null) {
            pathBuilder.append("/");
            return;
        }

        constructPath(element.getParent(), pathBuilder);
        pathBuilder.append(element.getName());

        if (element instanceof Directory) {
            pathBuilder.append("/");
        }
    }

    /**
     * Changes the current directory to the one specified by the given path.
     *
     * @param path the path of the directory to change to
     * @return the new current directory if the change is successful, null otherwise
     */
    public Directory changeDirectory(String path) {
        Directory currentDirectory = root;
        String[] directories = path.split("/");

        for (String directory : directories) {
            if (!directory.isEmpty()) {
                boolean found = false;

                for (FileSystemElement element : currentDirectory.getChildren()) {
                    if (element instanceof Directory && element.getName().equals(directory)) {
                        currentDirectory = (Directory) element;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    System.out.println("Directory '" + directory + "' not found.");
                    return null;
                }
            }
        }

        return currentDirectory;
    }

    /**
     * Returns the root directory of the file system.
     *
     * @return the root directory
     */
    public Directory getRoot() {
        return root;
    }
}
