import java.util.*;

/**
 * Represents a social network graph where people can be added, removed,
 * and friendships can be managed. It also provides functionalities to find
 * the shortest path between two people, count clusters of friends, and suggest friends.
 */
public class SocialNetworkGraph {
    Map<String, Person> people = new HashMap<>();
    Map<Person, List<Person>> friendships = new HashMap<>();

    /**
     * Adds a person to the social network.
     *
     * @param name   the name of the person
     * @param age    the age of the person
     * @param hobbies the list of hobbies of the person
     */
    public void addPerson(String name, int age, List<String> hobbies) {
        Person person = new Person(name, age, hobbies);
        people.put(name, person);
        friendships.put(person, new ArrayList<>());
        System.out.println("Person added: " + person + " (Timestamp: " + person.getTimestamp() + ")");
    }

    /**
     * Removes a person from the social network.
     *
     * @param name the name of the person to be removed
     * @return the removed person, or null if the person was not found
     */
    public Person removePerson(String name) {
        Person person = people.remove(name);
        if(person != null) {
            friendships.remove(person);
            System.out.println("Person removed: " + person);
            return person;
        }
        System.out.println("Person not found: " + name);
        return null;
    }

    /**
     * Adds a friendship between two people.
     *
     * @param name1 the name of the first person
     * @param name2 the name of the second person
     */
    public void addFriendship(String name1, String name2) {
        Person person1 = people.get(name1);
        Person person2 = people.get(name2);
        if (person1 != null && person2 != null) {
            friendships.get(person1).add(person2);
            friendships.get(person2).add(person1);
            System.out.println("Friendship added between " + person1.getName() + " and " + person2.getName());
        } else {
            System.out.println("One or both persons not found in the network.");
        }
    }

    /**
     * Removes a friendship between two people.
     *
     * @param name1 the name of the first person
     * @param name2 the name of the second person
     */
    public void removeFriendship(String name1, String name2) {
        Person person1 = people.get(name1);
        Person person2 = people.get(name2);
        if (person1 != null && person2 != null) {
            boolean areFriend = friendships.get(person1).remove(person2);
            friendships.get(person2).remove(person1);
            if (areFriend)
                System.out.println("Friendship removed between " + person1.getName() + " and " + person2.getName());
            else
                System.out.println("Friendship not found between " + person1.getName() + " and " + person2.getName());
        } else {
            System.out.println("One or both persons not found in the network.");
        }
    }

    /**
     * Finds the shortest path between two people using BFS.
     *
     * @param startName the name of the start person
     * @param endName the name of the end person
     */
    public void findShortestPath(String startName, String endName) {
        Person person1 = people.get(startName);
        Person person2 = people.get(endName);

        if(person1 == null || person2 == null) {
            System.out.println("One or both persons not found in the network.");
            return;
        }

        Map<Person, Person> prev = new HashMap<>();
        Queue<Person> queue = new LinkedList<>();
        queue.add(person1);
        prev.put(person1, null);

        boolean found = false;
        while (!queue.isEmpty() && !found) {
            Person current = queue.poll();
            for (Person neighbor : friendships.get(current)) {
                if (!prev.containsKey(neighbor)) {
                    prev.put(neighbor, current);
                    queue.add(neighbor);
                    if (neighbor.equals(person2)) {
                        found = true;
                        break;
                    }
                }
            }
        }
        if (found) {
            printPath(person1, person2, prev);
        }
        else {
            System.out.println("No path found between " + person1.getName() + " and " + person2.getName());
        }
    }

    /**
     * Prints the shortest path between two people.
     *
     * @param start the start person
     * @param end the end person
     * @param prev the map of previous nodes in the path
     */
    private void printPath(Person start, Person end, Map<Person, Person> prev) {
        List<Person> path = new ArrayList<>();
        for (Person at = end; at!= null; at = prev.get(at)) {
            path.add(at);
        }
        Collections.reverse(path);

        System.out.println("Shortest path: ");
        for (int i = 0; i < path.size(); i++) {
            System.out.print(path.get(i).getName());
            if (i != path.size() - 1)
                System.out.print(" -> ");
        }
        System.out.println();
    }

    /**
     * Counts the number of clusters of friends using BFS.
     */
    public void countClusters() {
        Set<Person> visited = new HashSet<>();
        List<List<Person>> clusters = new ArrayList<>();

        for (Person person : people.values()) {
            if (!visited.contains(person)) {
                List<Person> cluster = new ArrayList<>();
                bfs(person, visited, cluster);
                clusters.add(cluster);
            }
        }

        System.out.println("Number of clusters: " + clusters.size());
        for (int i = 0; i < clusters.size(); i++) {
            System.out.println("\nCluster " + (i + 1) + ": ");
            for (Person person : clusters.get(i)) {
                System.out.println(person.getName());
            }
        }
    }

    /**
     * Suggests friends for a person based on mutual friends and common hobbies.
     *
     * @param name the name of the person
     * @param suggestNumber the number of friends to suggest
     */
    public void suggestFriend(String name, int suggestNumber) {
        Person person = people.get(name);

        if (person == null) {
            System.out.println(name + " not found in the network.");
            return;
        }

        System.out.println("Suggested friends for " + name + ":\n");
        Map<Person, Double> suggestMap = new HashMap<>();
        Set<Person> visited = new HashSet<>();

        Queue<Person> queue = new LinkedList<>();
        queue.add(person);
        visited.add(person);

        while (!queue.isEmpty()) {
            Person current = queue.poll();

            for (Person neighbor : friendships.get(current)) {
                if (!visited.contains(neighbor)) {
                    if (neighbor!= person && !friendships.get(person).contains(neighbor)) {
                        double score = calculateScore(person, neighbor)[0];
                        suggestMap.put(neighbor, score);
                    }
                    queue.add(neighbor);
                    visited.add(neighbor);
                }
            }
        }
        
        List<Map.Entry<Person, Double>> friendsList = new ArrayList<>(suggestMap.entrySet());
        friendsList.sort(Map.Entry.comparingByValue(Comparator.reverseOrder()));

        for (int i = 0; i < Math.min(friendsList.size(), suggestNumber); i++) {
            Person p = friendsList.get(i).getKey();
            double[] scores = calculateScore(person, p);
            System.out.println(p.getName() + " (Score: " + scores[0] + ", " + (int) scores[1] + " mutual friends, " + (int) scores[2] + " common hobbies)");
        }
    }

    /**
     * Calculates the score for suggesting friends based on mutual friends and common hobbies.
     *
     * @param person1 the first person
     * @param person2 the second person
     * @return an array with the score, number of mutual friends, and number of common hobbies
     */
    public double[] calculateScore(Person person1, Person person2) {
        double mutualFriend = 0.0;
        double commanHobbies = 0.0;

        for (Person friend : friendships.get(person1)) {
            if (friendships.get(friend).contains(person2)) {
                ++mutualFriend;
            }
        }
        
        for (String hobby : person2.getHobbies()) {
            if (person1.getHobbies().contains(hobby)) {
                ++commanHobbies;
            }
        }

        double score = (mutualFriend * 1.0) + (commanHobbies * 0.5);
        return new double[] {score, mutualFriend, commanHobbies};
    }

    /**
     * Performs a BFS to find all connected people starting from a given person.
     *
     * @param start the starting person
     * @param visited the set of visited people
     * @param cluster the list to store the current cluster
     */
    private void bfs(Person start, Set<Person> visited, List<Person> cluster) {
        Queue<Person> queue = new LinkedList<>();
        queue.add(start);
        visited.add(start);

        while (!queue.isEmpty()) {
            Person current = queue.poll();
            cluster.add(current);

            for (Person neighbor : friendships.get(current)) {
                if (!visited.contains(neighbor)) {
                    queue.add(neighbor);
                    visited.add(neighbor);
                }
            }
        }
    }
}
