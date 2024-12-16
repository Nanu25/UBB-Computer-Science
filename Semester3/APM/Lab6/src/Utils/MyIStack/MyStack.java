package Utils.MyIStack;

import java.util.*;

import Exception.StackException;

public class MyStack<T> implements MyIStack<T> {
    private Stack<T> stack;

    public MyStack() {
        stack = new Stack<T>();
    }

    @Override
    public T pop() {
        if(this.stack.size() == 0)
            throw new EmptyStackException();
        return this.stack.pop();
    }

    @Override
    public void push(T v) {
        this.stack.push(v);
    }

    @Override
    public String toString() {
        return this.stack.toString();
    }

    @Override
    public boolean isEmpty() {
        return this.stack.isEmpty();
    }

    @Override
    public List<T> getReversed() {
        List<T> reversed = Arrays.asList((T[]) stack.reversed().toArray());
        return reversed;
    }

}
