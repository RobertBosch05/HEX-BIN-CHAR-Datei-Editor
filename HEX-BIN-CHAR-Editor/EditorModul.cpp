#include "EditorModul.hpp"
#include <iostream>
#include <iomanip>
#include <bitset>

char EditorModul::printable(unsigned char c) {
    return (c >= 32 && c < 127) ? static_cast<char>(c) : '.';
}

bool EditorModul::hexToByte(const std::string& hex, unsigned char& out) {
    if (hex.size() != 2) return false;
    try {
        out = static_cast<unsigned char>(std::stoul(hex, nullptr, 16));
        return true;
    }
    catch (...) { return false; }
}

bool EditorModul::binToByte(const std::string& bin, unsigned char& out) {
    if (bin.size() != 8) return false;
    for (char c : bin)
        if (c != '0' && c != '1') return false;
    out = static_cast<unsigned char>(std::bitset<8>(bin).to_ulong());
    return true;
}

void EditorModul::editByte(DatenModell& model) const {
    if (model.isEmpty()) {
        std::cout << "Datei ist leer – nichts zu bearbeiten.\n";
        return;
    }

    // ── Index abfragen ──────────────────────────────────────────────────────
    std::cout << "Byte-Index (0 – " << model.size() - 1 << "): ";
    std::size_t idx;
    std::cin >> idx;
    if (idx >= model.size()) {
        std::cout << "Ungültiger Index.\n";
        return;
    }

    unsigned char current = model.getByte(idx);
    std::cout << "Aktueller Wert:"
        << "  HEX=" << std::hex << std::uppercase
        << std::setw(2) << std::setfill('0')
        << static_cast<int>(current) << std::dec << std::setfill(' ')
        << "  BIN=" << std::bitset<8>(current)
        << "  CHAR=" << printable(current) << "\n";

    // ── Format abfragen ─────────────────────────────────────────────────────
    std::cout << "Format [hex / bin / char]: ";
    std::string fmt;
    std::cin >> fmt;

    unsigned char newVal = 0;
    bool ok = false;

    if (fmt == "hex") {
        std::cout << "Neuer HEX-Wert (2 Zeichen, z.B. 41): ";
        std::string s; std::cin >> s;
        ok = hexToByte(s, newVal);
    }
    else if (fmt == "bin") {
        std::cout << "Neuer BIN-Wert (8 Zeichen, z.B. 01000001): ";
        std::string s; std::cin >> s;
        ok = binToByte(s, newVal);
    }
    else if (fmt == "char") {
        std::cout << "Neues Zeichen (1 Zeichen): ";
        std::string s; std::cin >> s;
        if (!s.empty()) { newVal = static_cast<unsigned char>(s[0]); ok = true; }
    }
    else {
        std::cout << "Unbekanntes Format.\n";
        return;
    }

    if (ok) {
        model.setByte(idx, newVal);
        std::cout << "Byte " << idx << " auf 0x"
            << std::hex << std::uppercase
            << std::setw(2) << std::setfill('0')
            << static_cast<int>(newVal) << std::dec << std::setfill(' ')
            << " gesetzt.\n";
    }
    else {
        std::cout << "Ungültige Eingabe – keine Änderung.\n";
    }
}
