#pragma once
#include <string>
#include <vector>

// Verantwortlich für das Lesen und Schreiben von Binärdateien

class DateiManager {
public:
    // Lädt eine Datei in den übergebenen Puffer
    // Gibt true zurück, wenn erfolgreich

    bool load(const std::string& path, std::vector<unsigned char>& data) const;

    // Schreibt den Puffer zurück in die Datei
    // Gibt true zurück, wenn erfolgreich

    bool save(const std::string& path, const std::vector<unsigned char>& data) const;
};
