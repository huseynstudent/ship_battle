#include <iostream>
using namespace std;
const int SIZE = 10;
char playerboard[SIZE][SIZE];
char opponentboard[SIZE][SIZE];
void initializeboard(char board[SIZE][SIZE]);
void displayboard(char board[SIZE][SIZE]);
void placeship(char board[SIZE][SIZE], int length);
int main() {
    initializeboard(playerboard);
    displayboard(playerboard);
    cout << endl << endl;
    initializeboard(opponentboard);
    displayboard(opponentboard);
    int shiplength = 4;
    placeship(playerboard, shiplength);
    shiplength--;
    placeship(playerboard, shiplength);
    shiplength--;
    placeship(playerboard, shiplength);
    placeship(playerboard, shiplength);
    shiplength--;
    placeship(playerboard, shiplength);
    placeship(playerboard, shiplength);
}




void initializeboard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = '~';  
}
void displayboard(char board[SIZE][SIZE]) {
    cout << "  0 1 2 3 4 5 6 7 8 9\n";
    for (int i = 0; i < SIZE; i++) {
        cout << i << " ";
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
}
void placeship(char board[SIZE][SIZE], int length) {
    int x, y;
    char direction;
    cout << "Placing a ship of length " << length << ".\n";
    cout << "Enter starting coordinates (row and column): ";
    cin >> x >> y;
    if (length==1)
        board[x][y] = '@';
    else {
        cout << "Enter direction (h for horizontal, v for vertical): ";
        cin >> direction;
        if (direction == 'h') {
            if (y + length > SIZE) {
                cout << "Ship does not fit horizontally. Try again.\n";
                placeship(board, length);
                return;
            }
            for (int i = 0; i < length; i++) {
                if (board[x][y + i] != '~') {
                    cout << "Overlap detected. Try again.\n";
                    placeship(board, length);
                    return;
                }
            }
            for (int i = 0; i < length; i++) {
                board[x][y + i] = '@';
            }
        }
        else if (direction == 'v') {
            if (x + length > SIZE) {
                cout << "Ship does not fit vertically. Try again.\n";
                placeship(board, length);
                return;
            }
            for (int i = 0; i < length; i++) {
                if (board[x + i][y] != '~') {
                    cout << "Overlap detected. Try again.\n";
                    placeship(board, length);
                    return;
                }
            }
            for (int i = 0; i < length; i++) {
                board[x + i][y] = '@';
            }
        }
        else {
            cout << "Invalid direction. Please enter 'h' or 'v'.\n";
            placeship(board, length);
            return;
        }
    }
    displayboard(board);
}