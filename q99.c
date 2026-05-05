#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pos;
    int speed;
} Car;

// Safe comparator (no overflow issue)
int compare(const void* a, const void* b) {
    Car* c1 = (Car*)a;
    Car* c2 = (Car*)b;

    if (c2->pos > c1->pos) return 1;
    else if (c2->pos < c1->pos) return -1;
    else return 0;
}

int carFleet(int target, int* position, int positionSize, int* speed, int speedSize) {
    Car* cars = (Car*)malloc(positionSize * sizeof(Car));

    // Fill car data
    for (int i = 0; i < positionSize; i++) {
        cars[i].pos = position[i];
        cars[i].speed = speed[i];
    }

    // Sort by position (descending)
    qsort(cars, positionSize, sizeof(Car), compare);

    int fleets = 0;
    double lastTime = -1.0;  // better initialization

    for (int i = 0; i < positionSize; i++) {

        // Avoid division by zero
        if (cars[i].speed == 0) continue;

        double time = (double)(target - cars[i].pos) / cars[i].speed;

        // New fleet condition
        if (time > lastTime) {
            fleets++;
            lastTime = time;
        }
    }

    free(cars);
    return fleets;
}

// Example usage
int main() {
    int target = 12;
    int position[] = {10, 8, 0, 5, 3};
    int speed[] = {2, 4, 1, 1, 3};
    int n = 5;

    int result = carFleet(target, position, n, speed, n);
    printf("Number of fleets: %d\n", result);

    return 0;
}