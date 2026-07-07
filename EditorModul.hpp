#pragma once
#include "DatenModell.hpp"

// Verantwortlich für das Bearbeiten einzelner Bytes in HEX/BIN/CHAR

class EditorModul {
public:

    // Fragt Benutzer nach Index + neuem Wert und schreibt ihn ins DataModel

    void editByte(DatenModell& model) const;

private:

    // Konvertierungshilfen

    static bool hexToByte(const std::string& hex, unsigned char& out);
    static bool binToByte(const std::string& bin, unsigned char& out);
    static char printable(unsigned char c);
};
