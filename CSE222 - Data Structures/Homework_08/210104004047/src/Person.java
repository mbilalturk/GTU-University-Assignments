import java.text.SimpleDateFormat;
import java.util.*;

/**
 * Represents a person with name, age, hobbies, and timestamp.
 */
public class Person {
    private String name;
    private int age;
    private List<String> hobbies;
    private Date timestamp;

    /**
     * Constructs a new Person object.
     *
     * @param name    the person's name
     * @param age     the person's age
     * @param hobbies the person's hobbies
     */
    public Person(String name, int age, List<String> hobbies) {
        this.name = name;
        this.age = age;
        this.hobbies = new ArrayList<>(hobbies);
        this.timestamp = new Date();
    }

    /**
     * Returns the person's name.
     *
     * @return the person's name
     */
    public String getName() {
        return name;
    }

    /**
     * Returns the person's hobbies.
     *
     * @return the person's hobbies
     */
    public List<String> getHobbies() {
        return hobbies;
    }

    /**
     * Returns the timestamp when the person object was created.
     *
     * @return the timestamp
     */
    public String getTimestamp() {
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        return dateFormat.format(timestamp);
    }

    /**
     * Returns a string representation of the person object.
     *
     * @return a string representation of the person object
     */
    @Override
    public String toString() {
        return name + " (Age: " + age + ", Hobbies: " + hobbies + ")";
    }
}
