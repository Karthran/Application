#include "Application.h"

auto main() -> int
{
    setlocale(LC_ALL, "");

    Application app;
    app.run();

    return 0;
}