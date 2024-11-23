package Exception;

public class StackException extends MyException {
    public StackException(String message) {
        super(message);
    }
}

class EmptyStackException extends StackException {
    public EmptyStackException() {
        super("Cannot perform operation on an empty stack.");
    }
}