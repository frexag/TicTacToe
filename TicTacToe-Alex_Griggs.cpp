#include <iostream>
using namespace std;

class TicTacToe {
private:
    char board[3][3];   // 3x3 board
    char currentPlayer; // 'X' or 'O'
    int movesCount;     // Count of moves made

public:
    TicTacToe() { // Constructor
        currentPlayer = 'X'; // X starts first
        movesCount = 1; //start move count at 1 to make it match UI
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                board[i][j] = ' '; // Start board with empty spaces
    }

    void displayBoard() { // Display the board
        cout << "  1 2 3\n";
        for (int i = 1; i <= 3; ++i) { // Use 1-based for display
            cout << i << " ";
            for (int j = 1; j <= 3; ++j) {
                cout << board[i - 1][j - 1]; // Use i-1 and j-1 for 0-based storage
                if (j < 3) cout << "|";
            }
            cout << "\n";
            if (i < 3) cout << "  -----\n";
        }
    }

    bool isValidMove(int row, int col) { // Check if move is valid
        // bounds check for 1–3
        if (row < 1 || row > 3) return false;
        if (col < 1 || col > 3) return false;

        int r = row - 1; // Convert to 0-based index for actual board access
        int c = col - 1; // Same thing here

        // Check if square is already used
        if (board[r][c] != ' ')
            return false;

        return true;
    }

    void makeMove(int row, int col) { // Actually place the mark
        int r = row - 1;
        int c = col - 1;
        board[r][c] = currentPlayer;
        ++movesCount; // track the move count
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    bool checkWin() { // Check for a win
        // rows if any row has all same marks in all 3 columns
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] == currentPlayer &&
                board[i][1] == currentPlayer &&
                board[i][2] == currentPlayer)
                return true;
        }

        // columns
        for (int j = 0; j < 3; ++j) {
            if (board[0][j] == currentPlayer &&
                board[1][j] == currentPlayer &&
                board[2][j] == currentPlayer)
                return true;
        }

        // diagonals
        if (board[0][0] == currentPlayer &&
            board[1][1] == currentPlayer &&
            board[2][2] == currentPlayer)
            return true;

        if (board[0][2] == currentPlayer &&
            board[1][1] == currentPlayer &&
            board[2][0] == currentPlayer)
            return true;

        return false;
    }

    bool checkDraw() { // Check for a draw
        return movesCount == 10; // 9 moves + 1 initial count
    }

    char getCurrentPlayer() const {
        return currentPlayer;
    }

    int getMovesCount() const {
        return movesCount;
    }

    void resetBoard() {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                board[i][j] = ' ';
        currentPlayer = 'X';
        movesCount = 1;
    }

    void play() {
        char again = 'y';

        while (again == 'y' || again == 'Y') {
            resetBoard();
            displayBoard();

            while (true) {
                int row, col;
                cout << "(Turn: " << movesCount << ") Enter row then column ie '1 3': ";
                cin >> row >> col;

                if (!isValidMove(row, col)) {
                    cout << "Invalid move. Try again.\n";
                    continue;
                }

                makeMove(row, col);
                displayBoard();

                if (checkWin()) {
                    cout << "Player " << getCurrentPlayer() << " wins!\n";
                    break;
                }

                if (checkDraw()) {
                    cout << "It's a draw!\n";
                    break;
                }

                switchPlayer();
            }

            cout << "Play again? (y/n): ";
            cin >> again;
        }
    }
};

int main() {
    TicTacToe game;
    game.play();
    return 0;
}
