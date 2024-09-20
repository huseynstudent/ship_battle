#include <iostream>

using namespace std;

const int SIZE = 10;
char playerBoard[SIZE][SIZE];
char opponentBoard[SIZE][SIZE];
void initializeBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = '~';  
}

void displayBoard(char board[SIZE][SIZE]) {
    cout << "  0 1 2 3 4 5 6 7 8 9\n";
    for (int i = 0; i < SIZE; i++) {
        cout << i << " ";
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
}

int main() {
    

}
