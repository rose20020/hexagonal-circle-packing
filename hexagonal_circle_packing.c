#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_CIRCLES 200

typedef struct {
    double x;
    double y;
} Circle;

/* w for width
   h for height
   r for radius*/
int place_circles_hexagonal(double w, double h, double r, Circle circles[]) {
    // d -> diameter of the circles
    double d = 2*r;
    double dx = d;
    double dy = d*sqrt(3)/2;

    int count=0;
    double y=r;
    int row=0;

    while (y <= h-r) {
        double x=(row%2==0) ? r : r + dx/2;
        while(x <= w-r) {
            circles[count].x = x;
            circles[count].y = y;
            count++;
            x += dx;
            if(count >= MAX_CIRCLES) return count;
        }
        y += dy;
        row++;
    }
    return count;
}

int main() {
    double width, height, radius;
    Circle circles[MAX_CIRCLES];

    printf("Enter rectangle width: ");
    scanf("%lf", &width);
    printf("Enter rectangle height: ");
    scanf("%lf", &height);
    printf("Enter circle radius: ");
    scanf("%lf", &radius);

    // Input validation
    if (width <= 0  || height <= 0 || radius <= 0 || 2 *radius > fmin(width, height)) {
        printf("Invalid input. Try again !\n");
        return 1;
    }

    // Placing circles
    int num_circles = place_circles_hexagonal(width, height, radius, circles);

    // Output
    printf("Number of circles placed in the rectangle is : %d\n", num_circles);
    printf("Circle positions (x, y):\n");
    for (int i = 0; i < num_circles; i++) {
        printf("Circle %d: (%.2f, %.2f)\n", i+1, circles[i].x, circles[i].y);
    }
    // Calculating fill density
    double rec_area = width*height;
    // M_PI = 3.14159265358979323846
    double cir_area = num_circles * M_PI * radius * radius;
    double density = (cir_area/rec_area)*100;

    printf("Fill density: %.2f%%\n", density);

    return 0;
}
