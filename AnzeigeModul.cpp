#include "AnzeigeModul.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <bitset>
#include <algorithm>

char AnzeigeModul::printable(unsigned char c) {
    return (c >= 32 && c < 127) ? static_cast<char>(c) : '.';
}

void AnzeigeModul::printTable(const DatenModell& model,
    std::size_t startRow,
    std::size_t rowCount) const
{
    const std::size_t totalRows =
        (model.size() + COLS - 1) / COLS;
    const std::size_t endRow =
        std::min(startRow + rowCount, totalRows);

    // ── Tabellenkopf ───────────────────────────────────────────────────────
    std::cout << "\n"
        << std::setw(10) << std::left << "Offset"
        << std::setw(6) << std::right << "Idx"
        << "  "
        << std::setw(25) << std::left << "HEX"
        << std::setw(73) << std::left << "BIN"
        << "CHAR\n"
        << std::string(122, '-') << "\n";

    // ── Zeilen ─────────────────────────────────────────────────────────────
    for (std::size_t row = startRow; row < endRow; ++row) {
        std::size_t base = row * COLS;
        std::size_t count = std::min(static_cast<std::size_t>(COLS),
            model.size() - base);

        // Offset (hex)
        std::cout << "0x"
            << std::hex << std::uppercase
            << std::setw(6) << std::setfill('0') << base
            << std::dec << std::setfill(' ');

        // Index (dezimal)
        std::cout << std::setw(8) << std::right << base << "  ";

        // HEX-Spalte
        std::string hexCol;
        for (std::size_t i = 0; i < count; ++i) {
            std::ostringstream oss;
            oss << std::hex << std::uppercase
                << std::setw(2) << std::setfill('0')
                << static_cast<int>(model.getByte(base + i));
            hexCol += oss.str() + " ";
        }
        std::cout << std::setw(25) << std::left << hexCol;

        // BIN-Spalte
        std::string binCol;
        for (std::size_t i = 0; i < count; ++i)
            binCol += std::bitset<8>(model.getByte(base + i)).to_string() + " ";
        std::cout << std::setw(73) << std::left << binCol;

        // CHAR-Spalte
        for (std::size_t i = 0; i < count; ++i)
            std::cout << printable(model.getByte(base + i));
        std::cout << "\n";
    }

    std::cout << "\nDateigröße: " << model.size() << " Bytes"
        << "  |  Zeilen gesamt: " << totalRows << "\n";
}

void AnzeigeModul::view(const DatenModell& model) const {
    if (model.isEmpty()) {
        std::cout << "(Datei ist leer)\n";
        return;
    }

    const std::size_t totalRows =
        (model.size() + COLS - 1) / COLS;
    const std::size_t totalPages =
        (totalRows + PAGE_ROWS - 1) / PAGE_ROWS;
    std::size_t page = 0;

    while (true) {
        printTable(model, page * PAGE_ROWS, PAGE_ROWS);
        std::cout << "\nSeite " << page + 1 << " / " << totalPages
            << "  [n = nächste  p = vorherige  q = zurück]\n> ";

        std::string cmd;
        std::cin >> cmd;

        if (cmd == "n" && page + 1 < totalPages) ++page;
        else if (cmd == "p" && page > 0)              --page;
        else if (cmd == "q")                          break;
        else    std::cout << "Unbekannter Befehl.\n";
    }
}
