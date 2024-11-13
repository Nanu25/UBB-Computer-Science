package repository;

import model.Shape;

public interface Repository {

    void add(Shape shape);
    void remove(int index);
    Shape[] getAll();
    int getSize();
}
