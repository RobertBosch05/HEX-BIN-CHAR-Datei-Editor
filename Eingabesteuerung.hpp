#pragma once
#include "DatenModell.hpp"
#include "DateiManager.hpp"
#include "AnzeigeModul.hpp"
#include "EditorModul.hpp"
#include <string>

// Steuert den Gesamtablauf: Menü, Benutzereingaben,
// Weiterleitung an Anzeige- und Editor-Modul sowie Datei-Manager

class Eingabesteuerung {
public:

    // Startet die Hauptschleife
    // optionalPath: Dateiname aus argv[1] (kann leer sein)

    void run(const std::string& optionalPath = "");

private:
    DatenModell     m_model;
    DateiManager   m_fileMgr;
    AnzeigeModul m_display;
    EditorModul  m_editor;
    std::string   m_filename;

    void printMenu()       const;
    void actionOpen();
    void actionView()      const;
    void actionEdit();
    void actionSave();
    bool confirmDiscard()  const;   // fragt bei ungespeicherten Änderungen
};
