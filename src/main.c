#include "nucleus_core.h"
#include <stdlib.h>

int main(void) {
    Nucleus_log("Hello, World!");
    Nucleus_FRect* window = malloc(sizeof(Nucleus_FRect));
    *window = (Nucleus_FRect) {.x = 0, .y = 0, .w = 800, .h = 600};
    Nucleus_initWindow(window);
    while (true) {
        Nucleus_log("This is a string!");
        Nucleus_sleepSeconds(3);
    }
    return 0;
}
