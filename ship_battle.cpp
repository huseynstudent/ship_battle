#include <iostream>
using namespace std;
const int SIZE = 10;
const char ship = '@';
const char block = 'X';
const char wrecked_ship = '#'; // player's
const char missed = ' ';
const char hit_ship = 'O';     // opponent's
char playerboard[SIZE][SIZE];
char opponentboard[SIZE][SIZE];

void initializeboard(char board[SIZE][SIZE]);
void displayboard(char board[SIZE][SIZE]);
void placeship(char board[SIZE][SIZE], int length);
void markblocks(char board[SIZE][SIZE], int x, int y, int length, char direction);
void markblock1(char board[SIZE][SIZE], int x, int y);


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
	cout << endl;
}
void placeship(char board[SIZE][SIZE], int length) {
	int x;
	int y;
	char direction;
	cout << "Placing a ship of length " << length << ".\n\n";
	cout << "Enter starting coordinates (row and column): ";
	cin >> x >> y;
	cout << endl;
	if (length == 1) {
		for (int i = 0; i < length; i++) {
			if (board[x][y] != '~') {
				cout << "Overlap or blocked area detected. Try again.\n\n";
				placeship(board, length);
				return;
			}
		}
		board[x][y] = ship;
		markblock1(board, x, y);
		displayboard(board);
		return;
	}
	else {
		cout << "Enter direction (h for horizontal, v for vertical): ";
		cin >> direction;
		if (direction == 'h') {
			if (y + length > SIZE) {
				cout << "Ship does not fit horizontally. Try again.\n\n";
				placeship(board, length);
				return;
			}
			for (int i = 0; i < length; i++) {
				if (board[x][y + i] != '~') {
					cout << "Overlap or blocked area detected. Try again.\n\n";
					placeship(board, length);
					return;
				}
			}
			for (int i = 0; i < length; i++) {
				board[x][y + i] = ship;
			}
			markblocks(board, x, y, length, 'h');
		}
		else if (direction == 'v') {
			if (x + length > SIZE) {
				cout << "Ship does not fit vertically. Try again.\n\n";
				placeship(board, length);
				return;
			}
			for (int i = 0; i < length; i++) {
				if (board[x + i][y] != '~') {
					cout << "Overlap or blocked area detected. Try again.\n\n";
					placeship(board, length);
					return;
				}
			}
			for (int i = 0; i < length; i++) {
				board[x + i][y] = ship;
			}
			markblocks(board, x, y, length, 'v');
		}
		else {
			cout << "Invalid direction. Please enter 'h' or 'v'.\n\n";
			placeship(board, length);
			return;
		}
	}
	displayboard(board);
}
void markblocks(char board[SIZE][SIZE], int x, int y, int length, char direction) {
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= length; j++) {
			int newX = x + (direction == 'v' ? j : i);
			int newY = y + (direction == 'h' ? j : i);
			if (newX >= 0 && newX < SIZE && newY >= 0 && newY < SIZE) {
				if (board[newX][newY] == '~') {
					board[newX][newY] = block;
				}
			}
		}
	}
}
void markblock1(char board[SIZE][SIZE], int x, int y) {//just an overload for extra points :)
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			int newX = x + i;
			int newY = y + j;
			if (newX >= 0 && newX < SIZE && newY >= 0 && newY < SIZE) {
				if (board[newX][newY] == '~') {
					board[newX][newY] = block;
				}
			}
		}
	}
}
