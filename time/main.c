#include <stdio.h>
#include <time.h>

extern volatile time_t global_time;

// Rename the function to avoid conflict
time_t my_time(time_t *t) {
    return global_time;
}

int main() {
    // Call the renamed function
    printf("time: %ld\n", (long)my_time(NULL));
    return 0;
}
