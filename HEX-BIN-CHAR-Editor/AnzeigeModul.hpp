#pragma once
#include "DatenModell.hpp"

// Verantwortlich für die tabellarische Ausgabe in HEX/BIN/CHAR

class AnzeigeModul {
public:
    static constexpr int    COLS = 8;   // Bytes pro Zeile
    static constexpr size_t PAGE_ROWS = 16;  // Zeilen pro Seite

    // Interaktive Seitenansicht (Navigation: n / p / q)

    void view(const DatenModell& model) const;

private:

    // Gibt PAGE_ROWS Zeilen ab startRow aus

    void printTable(const DatenModell& model,
        std::size_t startRow,
        std::size_t rowCount) const;

    // Gibt einen druckbaren Zeichenersatz zurück

    static char printable(unsigned char c);
};
