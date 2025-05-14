#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

char board[3][3];
int playerHP = 10;
int enemyHP = 10;

// Initialize board
void initializeBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = '-';
}

// Print board
void printBoard() {
    cout << "\nGrid:\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        if (i < 2) cout << "\n-----------\n";
    }
    cout << "\n";
}

// Player attacks
void playerTurn() {
    int move;
    cout << "Choose a cell to attack (1-9): ";
    cin >> move;
    int row = (move - 1) / 3;
    int col = (move - 1) % 3;

    if (board[row][col] == '-') {
        board[row][col] = 'X'; // Mark attack
        cout << "?? Hit! Enemy HP -2\n";
        enemyHP -= 2;
    } else {
        cout << "? Already attacked here! Turn skipped.\n";
    }
}

// Enemy attacks randomly
void enemyTurn() {
    int move;
    int row, col;
    do {
        move = rand() % 9 + 1;
        row = (move - 1) / 3;
        col = (move - 1) % 3;
    } while (board[row][col] != '-');

    board[row][col] = 'O';
    cout << "?? Enemy attacked cell " << move << "! You lose 2 HP.\n";
    playerHP -= 2;
}

// Main function
int main() {
    srand(time(0));
    initializeBoard();

    cout << "==== GRID COMBAT GAME ====\n";
    cout << "You (X) vs Enemy (O)\n";
    cout << "Each attack reduces 2 HP. First to 0 HP loses.\n";
    cout << "Choose cells like this:\n";
    cout << " 1 | 2 | 3\n";
    cout << "-----------\n";
    cout << " 4 | 5 | 6\n";
    cout << "-----------\n";
    cout << " 7 | 8 | 9\n";

    while (playerHP > 0 && enemyHP > 0) {
        printBoard();
        cout << "\n?? Your HP: " << playerHP << " | ?? Enemy HP: " << enemyHP << "\n";
        playerTurn();

        if (enemyHP <= 0) break;

        enemyTurn();
    }

    printBoard();
    if (playerHP <= 0 && enemyHP <= 0)
        cout << "?? It's a draw!\n";
    else if (playerHP <= 0)
        cout << "?? You lost!\n";
    else
        cout << "?? You won!\n";

    return 0;
}
