#include "Eingabesteuerung.hpp"
#include <windows.h>        // <-- neu

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(65001);   // <-- neu: UTF-8 im Terminal
    SetConsoleCP(65001);         // <-- neu: UTF-8 Eingabe

    Eingabesteuerung controller;
    const std::string path = (argc >= 2) ? argv[1] : "";
    controller.run(path);
    return 0;
}
