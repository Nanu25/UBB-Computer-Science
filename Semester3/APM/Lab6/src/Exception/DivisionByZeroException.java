package Exception;

public class DivisionByZeroException extends MyException {
    public DivisionByZeroException() {
        super("You tried to divide by zero.");
    }
}
