package model;

public class Square implements Shape {
    private int volume;

    public Square(int volume) {
        this.volume = volume;
    }

    @Override
    public int getVolume() {
        return this.volume;
    }

    @Override
    public String toString() {
        return "Square with volume " + this.volume;
    }

}
