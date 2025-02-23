import java.util.Map;

public class encryptor {
	private Map<Character, Map<Character, Character>> map;
	private String key;
	private String keystream = "";
	private String plain_text;
	private String cipher_text = "";
	
	public encryptor(Map<Character, Map<Character, Character>> _map, String _key, String text) {
		this.map = _map;
		this.key = _key;
		this.plain_text = text;
	}
	
	public void encrypt() {
		// do not edit this method
		generate_keystream();
		generate_cipher_text();
	}
	
	private void generate_keystream() {
		// If the text is shorter than the key, the keystream is the first length_of_text letters of the key.
		if(plain_text.length() < key.length()) {
			keystream = key.substring(0, plain_text.length());
		}
		// If the text is longer than the key, we repeatedly add the key to the end of itself to generate the keystream.
		else if(plain_text.length() > key.length()) {
			StringBuilder result = new StringBuilder();

			for(int i=0; i<plain_text.length(); ++i) {
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
	
	private void generate_cipher_text() {
		StringBuilder result = new StringBuilder();

		for(int i=0; i<plain_text.length(); ++i) {
			// assign character in plain_text as a row, and get that row
			char row = plain_text.charAt(i);
			Map<Character, Character> innerMap = map.get(row);

			// assign character in keystream as a column,
			char column = keystream.charAt(i);

			// get the letter from the map
			char letter = innerMap.get(column);
			result.append(letter);
		}
		cipher_text = result.toString();
	}

	public String get_keystream() {
		return keystream;
	}
	
	public String get_cipher_text() {
		return cipher_text;
	}
}
