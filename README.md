# ifa-sudoku

## Anforgerungen
* Anzeige des Gitters (muss)              [x]
* Auswahl des aktuellen felds (muss)      [x]
* abändern des Wertes (muss)              [x]
* Sichere Verarbeitung der Eingabe (muss) [x]
* auswählen eines Sudoku's (muss)         [x]
* richtiges sudoku erkennen (soll)        [x]
* Zeitmessung (soll)                      [x]
* Einlesen aus Datei (kann)               [ ]
* Abspeichern (kann)                      [ ]
* Hinweis anzeigen (kann)                 [ ]
* Automatische erstellung (kann)          [ ]

# Überprüfung des Programms
Leider ist es uns nicht gelungen rechtzeitig den Build-
vorgang in Code::Blocks zu realisieren. Ich glaube zwar
das die sourcen alle mit drin seien müssten,
aber mit der Funktion: "initscr()" scheint Windows nicht 
klar zu kommen.

Falls Sie dennoch versuchen möchten das Programm zu testen
können sie es unter Linux wie folgt machen:

## Installation unter Debian o. Ableger
sudo apt-get install libncurses5-dev libncursesw5-dev

## Kompilieren
make
