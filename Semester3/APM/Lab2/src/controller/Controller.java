package controller;

import model.Shape;
import repository.Repository;

public class Controller {
    private Repository repository;

    public Controller(Repository repo) {
        repository = repo;
    }

    public void addShape(Shape shp) {
        this.repository.add(shp);
    }

    public void removeShape(int index) {
        this.repository.remove(index);
    }

    public Shape[] getAllShapes() {
        return this.repository.getAll();
    }

    public Shape[] filterByVolume() {
        Shape[] shapes = this.repository.getAll();
        int size = this.repository.getSize();
        Shape[] filtered = new Shape[size];
        int count = 0;

        for (int i = 0; i < size; i++) {
            if (shapes[i].getVolume() > 25) {
                filtered[count++] = shapes[i];
            }
        }

        Shape[] result = new Shape[count];
        System.arraycopy(filtered, 0, result, 0, count);

        return result;
    }

    public int getRepoSize() {
        return this.repository.getSize();
    }

}
