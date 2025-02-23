public class preprocessor {
	private String initial_string;
	private String preprocessed_string;
		
	public preprocessor(String str) {
		initial_string = str;
	}

	public void preprocess() {
		// do not edit this method
		capitalize();
		clean();
	}
	
	private void capitalize() {
		preprocessed_string = initial_string.toUpperCase();
		preprocessed_string = preprocessed_string.replace('İ', 'I');
	}

	private void clean() {
		StringBuilder result = new StringBuilder();

		// If character is not in this scope which indicates english alphabet in ASCII, does not append
		for(int i=0; i<preprocessed_string.length(); ++i) {
			char ch = preprocessed_string.charAt(i);
			if((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
				result.append(ch);
			}
		}

		// Assign result to preprocessed_string
		preprocessed_string = result.toString();
	}
	
	public String get_preprocessed_string() {
		return preprocessed_string;
	}
}