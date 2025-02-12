package Exception;

public class KeyNotFoundException extends DictionaryException {
    public KeyNotFoundException() {
        super("The key does not exist in the dictionary.");
    }
}