import java.util.Map;
import java.util.Iterator;
public class decryptor {
	private Map<Character, Map<Character, Character>> map;
	private String key;
	private String keystream = "";
	private String plain_text = "";
	private String cipher_text;
	
	public decryptor(Map<Character, Map<Character, Character>> _map, String _key, String text) {
		this.map = _map;
		this.key = _key;
		this.cipher_text = text;
	}

	public void decrypt() {
		// do not edit this method
		generate_keystream();
		generate_plain_text();
	}
	
	private void generate_keystream() {
		// If the text is shorter than the key, the keystream is the first length_of_text letters of the key.
		if(cipher_text.length() < key.length()) {
			keystream = key.substring(0, cipher_text.length());
		}
		// If the text is longer than the key, we repeatedly add the key to the end of itself to generate the keystream.
		else if(cipher_text.length() > key.length()) {
			StringBuilder result = new StringBuilder();

			for(int i=0; i<cipher_text.length(); ++i) {
				char ch = key.charAt(i % key.length());
				result.append(ch);
			}
			keystream = result.toString();
		}
		// If the length of the text and the key is equal, then the keystream is the same as key.
		else {
			keystream = key;
		}
	}
	
	private void generate_plain_text() {
		// You must use map.get(x).keySet() with an iterator in this method
		StringBuilder result = new StringBuilder();

		for(int i=0; i<cipher_text.length(); ++i) {
			// get the letter from the keystream as a column
			char column = keystream.charAt(i);
			// get the letter from the cipher_text as a letter
			char letter = cipher_text.charAt(i);

			// create a map for column that is just got
			Map<Character, Character> innerMap = map.get(column);

			// create iterator for row
			Iterator<Character> setIterator = map.get(column).keySet().iterator();;

			// If iterator has next and value of innerKey equals letter, append key to result
			while (setIterator.hasNext()) {
				char innerKey = setIterator.next();
				if(innerMap.get(innerKey).equals(letter)) {
					result.append(innerKey);
					break;
				}
			}

		}
		plain_text = result.toString();
	}

	public String get_keystream() {
		return keystream;
	}
	
	public String get_plain_text() {
		return plain_text;
	}
}
