#include <iostream>
using namespace std;
const int SIZE = 10;
char playerboard[SIZE][SIZE];
char opponentboard[SIZE][SIZE];
void initializeboard(char board[SIZE][SIZE]);
void displayboard(char board[SIZE][SIZE]);
int main() {
    initializeboard(playerboard);
    displayboard(playerboard);
    initializeboard(opponentboard);
    displayboard(opponentboard);


    
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
   