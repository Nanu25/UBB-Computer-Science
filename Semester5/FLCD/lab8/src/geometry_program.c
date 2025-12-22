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

static float pythagoras(float x, float y) {
    return sqrtf(x * x + y * y);
}

static float area_triangle(float base, float height) {
    return 0.5f * base * height;
}

int main(void) {
    float a;
    float b;

    /* read(a); */
    if (scanf("%f", &a) != 1) {
        fprintf(stderr, "Failed to read a\n");
        return 1;
    }

    /* read(b); */
    if (scanf("%f", &b) != 1) {
        fprintf(stderr, "Failed to read b\n");
        return 1;
    }

    /* write("Hypotenuse is: "); */
    printf("Hypotenuse is: ");
    /* write(pythagoras(a, b)); */
    printf("%f\n", pythagoras(a, b));

    /* write("Area of triangle is: "); */
    printf("Area of triangle is: ");
    /* write(area_triangle(a, b)); */
    printf("%f\n", area_triangle(a, b));

    return 0;
}


