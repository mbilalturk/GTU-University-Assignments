package cse241.homeworks_3;

/**
 * The JavaContainer interface is a generic container that can hold elements of type E.
 * It defines methods for adding and removing elements, retrieving the size of the container,
 * obtaining an iterator over its elements, and writing its contents to a file.
 *
 * @param <E> the type of elements in the container
 */
public interface JavaContainer<E> {

    /**
     * Adds the specified element to this container if it does not exist.
     *
     * @param element the element to be added to this container
     */
    void add(E element);

    /**
     * Removes the specified element from this container.
     *
     * @param element the element to be removed from this container
     */
    void remove(E element);

    /**
     * Returns the number of elements in this container.
     *
     * @return the number of elements in this container
     */
    int size();

    /**
     * Returns an iterator over the elements in this container.
     *
     * @return an iterator over the elements in this container
     */
    Iterator<E> getIterator();

    /**
     * Iterator interface that has hasNext method and next method
     * This class generates a iterator.
     * @param <E> the type of elements in the container
     */
    interface Iterator<E> {
        /**
         * Returns true if the iteration has more elements.
         *
         * @return true if the iteration has more elements, false otherwise
         */
        boolean hasNext();

        /**
         * Iterates next element if exists, throw exception otherwise
         * @return next element over the iterator
         */
        E next();
    }

    /**
     * Writes the string representation of this container to a file.
     * This method may throw a runtime exception if any I/O error occurs.
     */
    void toFile();
}
