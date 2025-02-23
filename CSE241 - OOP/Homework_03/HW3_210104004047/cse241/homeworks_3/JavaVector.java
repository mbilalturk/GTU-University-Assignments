package cse241.homeworks_3;

import java.io.FileWriter;
import java.io.IOException;
import java.util.NoSuchElementException;


/**
 * A generic vector implementation in Java.
 *
 * @param <E> the type of elements in this vector
 */
public class JavaVector<E> implements JavaContainer<E> {
    private E[] data;
    private int capacity;
    private int size;

    /**
     * No parameter JavaVector constructor
     * Calls the other JavaVector constructor with 10 which will be capacity of the set
     */
    public JavaVector() {
        this(10);
    }


    /**
     * JavaVector Constructor with one parameter
     * Constructs a vector with taken capacity, then create some space for this set in the heap
     *
     * @param _capacity : the capacity of the object of JavaVector class
     */
    @SuppressWarnings("unchecked")
    public JavaVector(int _capacity) {
        if(_capacity < 0)
            _capacity = 10;
        this.size = 0;
        this.capacity = _capacity;
        data = (E[]) new Object[getCapacity()];
    }

    /**
     * Add method that adds element to this vector.
     *
     * @param element : The element that will be added to this vector
     */
    @SuppressWarnings("unchecked")
    public void add(E element) {
        if(size() >= getCapacity()) {
            capacity *= 2;
            var temp = (E[]) new Object[getCapacity()];

            for(int i=0; i<size(); ++i)
                temp[i] = data[i];

            data = temp;
        }

        data[size] = element;
        ++size;
    }

    /**
     * Remove method that removes specific element from this vector
     *
     * @param element : The element that will be removed from this vector
     * @throw NoSuchElementException() : If the element that want to be removed is not in this vector, throw noSuchElementException
     */
    @SuppressWarnings("unchecked")
    public void remove(E element) {
        if(!(hasElement(element)))
            throw new NoSuchElementException(element + " not found!");

        var iterator = getIterator();
        var temp = (E[]) new Object[getCapacity()];
        int index = 0;
        boolean hasBeenDeleted = false;

        var current = data[index];
        while(iterator.hasNext()) {
            current = iterator.next();
            if(!current.equals(element) || hasBeenDeleted) {
                temp[index] = current;
                ++index;
            }
            else {
                hasBeenDeleted = true;
            }
        }
        data = temp;
        --size;
    }

    /**
     * Size method that returns size of this vector
     *
     * @return size of this vector as an integer
     */
    public int size() {
        return size;
    }


    /**
     * getIterator method that generates a new iterator via setIterator class
     * @return object of SetIterator
     */
    @Override
    public Iterator<E> getIterator() {
        return new SetIterator();
    }

    /**
     * SetIterator class that derived from Iterator class
     * This class generates a iterator.
     */
    private class SetIterator implements Iterator<E> {
        private int index;

        /**
         * No parameter constructor
         * Initialize index field with 0
         */
        public SetIterator() {
            index = 0;
        }

        /**
         * hasNext method that check if this iterator iterates last element or not
         * @return true if it is not iterating the last element, false otherwise
         */
        public boolean hasNext() {
            return index < size;
        }

        /**
         * next method that implements the iterator by one
         * to move on the next element of this vector if it exists
         *
         * @throw IllegalStateException if try to reach over the last element
         * @return next element of this set via current iterator position
         */
        public E next() {
            if (!hasNext())
                throw new IllegalStateException("No more elements");

            return data[index++];
        }

    }

    /**
     * getCapacity method that returns capacity of the vector
     * @return capacity of this vector
     */
    public int getCapacity() {
        return capacity;
    }

    /**
     * hasElement method that checks if taken element is in this vector or not
     *
     * @param element : that is checked if it is already in this vector
     * @return true if this vector contains element, false otherwise
     */
    private boolean hasElement(E element) {
        Iterator<E> iterator = getIterator();
        while(iterator.hasNext()) {
            E current = iterator.next();
            if (current.equals(element))
                return true;
        }
        return false;
    }

    /**
     * toFile method that writes this vector to file named "vectors.txt"
     *
     * @throw RuntimeException() If any runtime error happen, throw runtimeException
     */
    @Override
    public void toFile() {
        try {
            FileWriter writer = new FileWriter("vectors.txt", true);

            writer.write(toString()+"\n");

            writer.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    /**
     * equals method that checks if this object and taken object are equal or not
     *
     * @param obj : ıt is vector that is taken from user to compare with this vector
     * @return true if this two vector are equal, false otherwise
     */
    @Override
    public boolean equals(Object obj) {
        if(this == obj)
            return true;

        if(obj == null || obj.getClass() != getClass())
            return false;

        JavaVector<?> js = (JavaVector<?>) obj;
        for(int i=0; i<size(); ++i) {
            if(!(data[i].equals(js.data[i])))
                return false;
        }

        return true;
    }

    /**
     * toString method that returns this vector as a string
     *
     * @return this vector as a string
     */
    @Override
    public String toString() {
        String output = "The vector is: [";

        for (int i=0; i<size; ++i) {
            output = output.concat(String.format("%s", data[i]));
            if(i != size-1)
                output = output.concat(", ");
        }

        return output + "]";
    }
}
