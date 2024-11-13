package model;

public class Sphere implements Shape {
    private int volume;

    public Sphere(int volume) {
        this.volume = volume;
    }

    @Override
    public int getVolume() {
        return this.volume;
    }

    @Override
    public String toString() {
        return "Spehere with volume " + this.volume;
    }
}
