#include <iostream>
#include <vector>

// Erstellung des Spielfeldes in Form eines Vectors
std::vector<std::vector<char>> create_game_field() {
    std::vector<std::vector<char>> game_field{
    {' ',' ',' '},
    {' ',' ',' '},
    {' ',' ',' '}
    };
// Array: Fixe Größe, manuelle Speicherverwaltung, weniger Funktionalität, effizienter in bestimmten Situationen.
// Vector: Dynamische Größe, automatische Speicherverwaltung, reichhaltige Funktionalität, etwas mehr Overhead.

// Rueckgabe des Spielfeldes
    return game_field;
}

// Konsolen ausgabe des Spielfeld
void print_game_field(std::string player, std::vector<std::vector<char>>game_field) {
    std::cout << "Your turn: " << player << std::endl;
    std::cout << "-------------\n";
    // For schleife zur ausgabe des Spielfeldes mit dem Vector inhalt
    for (int i = 0; i < 3; i++) {
        std::cout << "| ";
        for (int j = 0; j < 3; j++) {
            std::cout << game_field[i][j] << " | ";
        }
        std::cout << "\n-------------\n";
    }
/*
-------------
|   |   |   |
-------------
|   |   |   |
-------------
|   |   |   |
-------------
*/
}

// Ueberpruefung des Gewinners
bool check_win(char player, std::vector<std::vector<char>>game_field) {

/* Horizontale Ueberpruefung
-------------   -------------   -------------
| X | X | X |   |   |   |   |   |   |   |   |
-------------   -------------   -------------
|   |   |   |   | X | X | X |   |   |   |   |
-------------   -------------   -------------
|   |   |   |   |   |   |   |   | X | X | X |
-------------   -------------   -------------
*/
    for (int i = 0; i < 3; i++) {
        if (game_field[i][0] == player && game_field[i][1] == player
            && game_field[i][2] == player)
            return true;

/* Verticale Ueberpruefung
-------------   -------------   -------------
| X |   |   |   |   | X |   |   |   |   | X |
-------------   -------------   -------------
| x |   |   |   |   | X |   |   |   |   | X |
-------------   -------------   -------------
| x |   |   |   |   | X |   |   |   |   | X |
-------------   -------------   -------------
*/
        if (game_field[0][i] == player && game_field[1][i] == player
            && game_field[2][i] == player)
            return true;
    }
/* Diagonale Ueberpruefung
-------------   -------------
| X |   |   |   |   |   | X |
-------------   -------------
|   | X |   |   |   | X |   |
-------------   -------------
|   |   | X |   | X |   |   |
-------------   -------------
*/
    if (game_field[0][0] == player && game_field[1][1] == player
        && game_field[2][2] == player)
        return true;
    if (game_field[0][2] == player && game_field[1][1] == player
        && game_field[2][0] == player)
        return true;
    return false;
}

int main() {
    // Erstellung der Variablen
    std::string player_1 = "";
    std::string player_2 = "";
    bool player_win = false;
    bool lets_play = true;

    // Fuellen mit Daten
    std::cout << "Please enter Name Player 1:" << std::endl;
    std::cin >> player_1;
    std::cout << "Please enter Name Player 2:" << std::endl;
    std::cin >> player_2;
    // Status welcher spieler aktuell aktiv ist.
    std::string current_player = player_1;

    // Spiel start
    while (lets_play==true) {
        int turn = 9;
        // Erstellen und speicher des leeren spielfeldes
        std::vector<std::vector<char>>field = create_game_field();
        // Spiel auf Max. 9 zuege begrenzen
        for (int i = 0; i < 9; i++) {
            bool player_turn = false;
            // Konsole aufraeumen
            system("CLS");
            // Spielfeld ausgabe mit Aktuellen daten
            print_game_field(current_player,field);

            // Spieler zug, mit ueberpruefung der zugelassen Nummern 0-2
            // und dazu ob dieses Feld was gewaehlt wurde, leer ist
            while (player_turn == false) {
                int row = 0;
                int col = 0;
                std::cout << "enter row (1-3) and column (1-3): \n";
                std::cin >> row;
                std::cin >> col;
                if (row >=1 && row <4 && col >=1 && col <4 && field[row-1][col-1]==' ') {
                    // Setzen der Spieler Zeichen
                    if (current_player == player_1) {
                        field[row-1][col-1] = 'X';
                    }
                    else {
                        field[row-1][col-1] = 'O';
                    }
                    // Current_player_char ist ein X oder O um den vector einfacher zu ueberpruefen
                    char current_player_char = current_player != player_1 ? 'O' : 'X';
                    // Ueberpruefung ob Spieler gewonnen hat
                    player_win = check_win(current_player_char ,field);

                    // unterbrechen while schleife, wenn Spieler gewonnen hat
                    if (player_win == true) {                      break;
                    }
                    // Spieler Wechsel
                    current_player = current_player != player_1 ? player_1 : player_2;
                    player_turn = true;
                }
            }
            // Konsolen ausgabe wenn Spieler gewonnen inkl. Spielfeld.
            if (player_win == true) {
                system("CLS");
                print_game_field(current_player, field);
                std::cout << "Congratulations " << current_player << "!" << std::endl;
                current_player = current_player != player_1 ? player_1 : player_2;
                break;
            }
            turn--;
        }
        // Nach 9 Zuege und niemand gewonnen, Unendschieden
        if (turn == 0) {
            std::cout << "Draw!" << std::endl;
        }
        // Frage ob Spiel erneut gespielt werden soll, mit Selben Spieler.
        char next_try = ' ';
        std::cout << "Next Try? " << std::endl;
        std::cout << "Y for Yes | N for No" << std::endl;
        std::cin >> next_try;
        // Bei N/n wird das programm beendet durch die while schleife.
        if (next_try == 'N' || next_try == 'n') {
            lets_play = false;
        }
    }
}
