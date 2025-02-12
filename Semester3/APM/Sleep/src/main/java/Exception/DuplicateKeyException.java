package Exception;

public class DuplicateKeyException extends DictionaryException {
    public DuplicateKeyException() {
        super("The key already exists in the dictionary.");
    }
}