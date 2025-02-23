import java.util.HashMap;
import java.util.Map;
import java.util.LinkedHashSet;
import java.util.Set;
import java.util.Iterator;

public class alphabet {
	private Set<Character> english_alphabet = new LinkedHashSet<Character>();
	private Map<Character, Map<Character, Character>> map = new HashMap<Character,  Map<Character, Character>>();
	
	public alphabet() {
		// do not edit this method
		fill_english_alphabet();
		fill_map();
	}
	
	private void fill_english_alphabet() {
		// do not edit this method
		for(char c : "ABCDEFGHIJKLMNOPQRSTUVWXYZ".toCharArray()) {
		    english_alphabet.add(c);
		}
	}
	
	private void fill_map() {
		// You must use the "english_alphabet" variable in this method, to fill the "map" variable.
		// You can define 1 or 2 iterators to iterate through the set items.

		// Define a iterator to assign english alphabet as a row
		Iterator<Character> iterator = english_alphabet.iterator();

		int i = 0; // To determine how many letter will pass
		while(iterator.hasNext()) {
			Map<Character, Character> innerMap = new HashMap<>(); // inner map

			// Iterator to assign letters
			Iterator<Character> innerIterator = english_alphabet.iterator();

			// move on until the letter that wanted to be reached
			for(int j=0; j<i; ++j) {
				innerIterator.next();
			}

			// Assign each letter as a key of innerMap, and value of innerMap
			// If innerIterator reaches the end, assign it to beginning
			for(int j=0; j<english_alphabet.size(); ++j) {
				if(!innerIterator.hasNext()) {
					innerIterator = english_alphabet.iterator();
				}

				char innerKey = (char) ('A' + j);
				innerMap.put(innerKey, innerIterator.next());
			}

			// Put the key and value to map
			map.put(iterator.next(), innerMap);
			++i;
		}
	}

	public void print_map() {
		// do not edit this method
		System.out.println("*** Viegenere Cipher ***\n\n");
		System.out.println("    " + english_alphabet);
		System.out.print("    ------------------------------------------------------------------------------");
		for(Character k: map.keySet()) {
			System.out.print("\n" + k + " | ");
			System.out.print(map.get(k).values());
		}
		System.out.println("\n");
		
	}

	public Map get_map() {
		return map;
	}
}