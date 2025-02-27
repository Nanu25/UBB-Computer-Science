package model;

public class Cylinder implements Shape {
    private int volume;

    public Cylinder(int volume) {
        this.volume = volume;
    }

    @Override
    public int getVolume() {
        return this.volume;
    }

    @Override
    public String toString() {
        return "Cylinder with volume " + this.volume;
    }
}
