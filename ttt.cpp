#include <iostream>
#include <cstdio>

using namespace std;

char board[3][3];

void init_board() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void print_board() {
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "---+---+---" << endl;
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "---+---+---" << endl;
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
}

int game_over() {
    // check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return 1;
        }
    }
    for (int j = 0; j < 3; j++) {
        if (board[0][j] != ' ' && board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
            return 1;
        }
    }
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return 1;
    }
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return 1;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 2; 
}

void get_move(int player, int &row, int &col) {
    cout << "Player " << player << "'s turn (row, col): ";
    cin >> row >> col;
}

int main() {
    int player = 1; 
    int row, col;

    init_board();

    while (true) {
        print_board(); 
        get_move(player, row, col);
        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
            cout << "Invalid move, try again." << endl;
            continue;
        }
        board[row][col] = (player == 1) ? 'X' : 'O';
        int result = game_over();
        if (result == 1) {
            cout << "Player " << player << " wins!" << endl;
            break;
        } else if (result == 2) {
            cout << "Tie game!" << endl;
            break;
        }
        player = (player == 1) ? 2 : 1;
    }

    print_board();

    return 0;
}
