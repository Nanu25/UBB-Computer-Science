#include <stdio.h>
#include <math.h>

/* DSL equivalent:
float a;
read(a);
float b;
read(b);
write("Hypotenuse is: ");
write(pythagoras(a, b));
write("Area of triangle is: ");
write(area_triangle(a, b));
*/

/* Compute the hypotenuse of a right triangle given its two legs. */
static double pythagoras(double leg_a, double leg_b) {
    return sqrt(leg_a * leg_a + leg_b * leg_b);
}

/* Compute the area of a right triangle given base and height. */
static double area_triangle(double base, double height) {
    return 0.5 * base * height;
}

/* Helper to read one double value with a descriptive name. */
static int read_double(const char *name, double *value) {
    if (scanf("%lf", value) != 1) {
        fprintf(stderr, "Failed to read %s\n", name);
        return 0;
    }
    return 1;
}

int main(void) {
    double leg_a = 0.0;
    double leg_b = 0.0;

    /* read(a); -> read first leg of the right triangle */
    if (!read_double("leg_a", &leg_a)) {
        return 1;
    }

    /* read(b); -> read second leg of the right triangle */
    if (!read_double("leg_b", &leg_b)) {
        return 1;
    }

    /* write("Hypotenuse is: "); */
    printf("Hypotenuse is: ");
    /* write(pythagoras(a, b)); */
    printf("%.2f\n", pythagoras(leg_a, leg_b));

    /* write("Area of triangle is: "); */
    printf("Area of triangle is: ");
    /* write(area_triangle(a, b)); */
    printf("%.2f\n", area_triangle(leg_a, leg_b));

    return 0;
}

