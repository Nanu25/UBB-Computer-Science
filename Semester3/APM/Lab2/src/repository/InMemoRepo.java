package repository;

import model.Shape;

public class InMemoRepo implements Repository {
    private Shape[] shapes;
    int size;
    public InMemoRepo() {
        shapes = new Shape[5];
        size =  0;
    }

    public void add(Shape shape) {
        if(size == shapes.length)
            throw new RuntimeException("Array is full");

        shapes[size++] = shape;
    }

    public void remove(int index) {
        if(index < 0 || index >= size)
            throw new RuntimeException("Invalid index");

        for(int i = index; i < size - 1; i++)
            shapes[i] = shapes[i + 1];
        size--;
    }

    public Shape[] getAll() {
        return shapes;
    }

    public int getSize() {
        return this.size;
    }
}
