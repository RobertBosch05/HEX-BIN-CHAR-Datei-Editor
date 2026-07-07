#pragma once
#include <vector>
#include <string>
#include <cstddef>

// Hält die Rohdaten der geöffneten Datei und verwaltet den Änderungszustand

class DatenModell {
public:
    // Daten übernehmen (z.B. nach dem Laden)

    void        setData(const std::vector<unsigned char>& data);

    // Einzelnes Byte lesen

    unsigned char getByte(std::size_t index) const;

    // Einzelnes Byte schreiben – setzt modified-Flag

    bool          setByte(std::size_t index, unsigned char value);

    // Rohdaten für DateiManager und Anzeige

    const std::vector<unsigned char>& getData() const;

    std::size_t size()     const;
    bool        isEmpty()  const;
    bool        isModified() const;
    void        clearModified();

private:
    std::vector<unsigned char> m_data;
    bool                       m_modified = false;
};
