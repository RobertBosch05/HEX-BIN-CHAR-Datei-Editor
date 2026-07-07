#include "Eingabesteuerung.hpp"
#include <windows.h>

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    Eingabesteuerung controller;
    const std::string path = (argc >= 2) ? argv[1] : "";
    controller.run(path);
    return 0;
}
