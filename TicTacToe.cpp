#include <bits/stdc++.h>
using namespace std;

// Player class
class Player {
private:
    string name;
    char symbol;

public:
    Player(string name, char symbol) {
        this->name = name;
        this->symbol = symbol;
    }

    string getName() const {
        return name;
    }

    char getSymbol() const {
        return symbol;
    }
};

// Board class
class Board {
private:
    char board[3][3];

public:
    Board() {
        resetBoard();
    }

    void resetBoard() {
        char start = '1';
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                board[i][j] = start++;
    }

    void displayBoard() {
        cout << "\n";
        for (int i = 0; i < 3; ++i) {
            cout << " ";
            for (int j = 0; j < 3; ++j) {
                cout << board[i][j];
                if (j != 2) cout << " | ";
            }
            cout << "\n";
            if (i != 2) cout << "---+---+---\n";
        }
        cout << "\n";
    }

    bool makeMove(int cell, char symbol) {
        int row = (cell - 1) / 3;
        int col = (cell - 1) % 3;
        if (cell < 1 || cell > 9 || board[row][col] == 'X' || board[row][col] == 'O')
            return false;

        board[row][col] = symbol;
        return true;
    }

    bool isWin(char symbol) {
        // Check rows & columns
        for (int i = 0; i < 3; ++i)
            if ((board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) ||
                (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol))
                return true;

        // Check diagonals
        if ((board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) ||
            (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol))
            return true;

        return false;
    }

    bool isDraw() {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (board[i][j] != 'X' && board[i][j] != 'O')
                    return false;
        return true;
    }
};

// Game class
class Game {
private:
    Player player1, player2;
    Board board;

public:
    Game(Player p1, Player p2) : player1(p1), player2(p2) {}

    void playGame() {
        int turn = 0;
        board.resetBoard();
        board.displayBoard();

        while (true) {
            Player current = (turn % 2 == 0) ? player1 : player2;

            cout << current.getName() << " (" << current.getSymbol() << ")"
                 << ", enter cell number (1-9): ";
            int cell;
            cin >> cell;

            if (!board.makeMove(cell, current.getSymbol())) {
                cout << "Invalid move. Try again.\n";
                continue;
            }

            board.displayBoard();

            if (board.isWin(current.getSymbol())) {
                cout << "🎉 " << current.getName() << " wins!\n";
                break;
            }

            if (board.isDraw()) {
                cout << "😅 It's a draw!\n";
                break;
            }

            turn++;
        }
    }
};

// MAIN FUNCTION
int main() {
    string name1, name2;
    char symbol1, symbol2;

    cout << "Enter name for Player 1: ";
    getline(cin, name1);

    while (true) {
        cout << "Choose symbol (X or O): ";
        cin >> symbol1;
        symbol1 = toupper(symbol1);
        if (symbol1 == 'X' || symbol1 == 'O') break;
        cout << "Invalid symbol! Try again.\n";
    }

    cin.ignore(); // flush newline
    cout << "Enter name for Player 2: ";
    getline(cin, name2);

    symbol2 = (symbol1 == 'X') ? 'O' : 'X';

    cout << name1 << " is '" << symbol1 << "'\n";
    cout << name2 << " is '" << symbol2 << "'\n";

    Player p1(name1, symbol1);
    Player p2(name2, symbol2);

    Game game(p1, p2);
    game.playGame();

    return 0;
}
