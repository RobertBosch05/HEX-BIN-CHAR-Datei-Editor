#include "Eingabesteuerung.hpp"
#include <iostream>
#include <limits>

// ── Hilfsmethoden ────────────────────────────────────────────────────────────

void Eingabesteuerung::printMenu() const {
    std::cout << "--------------------------------\n";
    std::cout << "      HEX / BIN / CHAR  Editor  \n";
    std::cout << "--------------------------------\n";
    std::cout << "  Datei: ";

    std::string label = m_filename.empty() ? "(keine)" : m_filename;
    if (m_model.isModified()) label += " [*]";
    label.resize(29, ' ');
    std::cout << label << "\n";

    std::cout << "--------------------------------\n";
    std::cout << "  [1]  Datei öffnen             \n";
    std::cout << "  [2]  Datei anzeigen           \n";
    std::cout << "  [3]  Byte bearbeiten          \n";
    std::cout << "  [4]  Datei speichern          \n";
    std::cout << "  [5]  Beenden                  \n";
    std::cout << "--------------------------------\n> ";
}


bool Eingabesteuerung::confirmDiscard() const {
    std::cout << "Ungespeicherte Änderungen vorhanden. Trotzdem fortfahren? [j/n]: ";
    std::string ans;
    std::cin >> ans;
    return (ans == "j" || ans == "J");
}

// ── Aktionen ─────────────────────────────────────────────────────────────────

void Eingabesteuerung::actionOpen() {
    if (m_model.isModified() && !confirmDiscard()) return;

    std::cout << "Dateipfad: ";
    std::string path;
    std::cin >> path;

    std::vector<unsigned char> buf;
    if (m_fileMgr.load(path, buf)) {
        m_model.setData(buf);
        m_filename = path;
        std::cout << "Geladen: " << buf.size() << " Bytes.\n";
    }
    else {
        std::cout << "Fehler: Datei konnte nicht geöffnet werden.\n";
    }
}

void Eingabesteuerung::actionView() const {
    if (m_filename.empty()) {
        std::cout << "Keine Datei geöffnet.\n";
        return;
    }
    m_display.view(m_model);
}

void Eingabesteuerung::actionEdit() {
    if (m_filename.empty()) {
        std::cout << "Keine Datei geöffnet.\n";
        return;
    }
    // EditorModul schreibt direkt ins DataModell;
    // das modified-Flag setzt DataModell::setByte() selbst
    m_editor.editByte(m_model);
}

void Eingabesteuerung::actionSave() {
    if (m_filename.empty()) {
        std::cout << "Keine Datei geöffnet.\n";
        return;
    }
    if (m_fileMgr.save(m_filename, m_model.getData())) {
        m_model.clearModified();
        std::cout << "Datei gespeichert.\n";
    }
    else {
        std::cout << "Fehler beim Speichern.\n";
    }
}

// ── Hauptschleife ─────────────────────────────────────────────────────────────

void Eingabesteuerung::run(const std::string& optionalPath) {
    // Datei aus Kommandozeilenargument laden
    if (!optionalPath.empty()) {
        std::vector<unsigned char> buf;
        if (m_fileMgr.load(optionalPath, buf)) {
            m_model.setData(buf);
            m_filename = optionalPath;
            std::cout << "Datei \"" << optionalPath << "\" geladen ("
                << buf.size() << " Bytes).\n";
        }
        else {
            std::cout << "Konnte \"" << optionalPath
                << "\" nicht öffnen.\n";
        }
    }

    while (true) {
        printMenu();

        int choice = 0;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1: actionOpen();  break;
        case 2: actionView();  break;
        case 3: actionEdit();  break;
        case 4: actionSave();  break;
        case 5:
            if (!m_model.isModified() || confirmDiscard()) {
                std::cout << "Auf Wiedersehen!\n";
                return;
            }
            break;
        default:
            std::cout << "Ungültige Auswahl.\n";
        }
    }
}
