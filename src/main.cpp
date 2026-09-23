#include "cstdlib"

#include "application.hpp"

int main() {
    Application app;

    if (!app.init()) {
        return EXIT_FAILURE;
    }

    app.run();

    return 0;
}
