#include <iostream>
#include <conio.h>
#pragma warning(disable:4996);

using namespace std;
const int SIZE = 10;
const char sea = '~';
const char ship = '@';
const char block = 'X';
const char wrecked_ship = '#'; // player's
const char missed = 'M';
const char hit_ship = 'O';     // opponent's

char playerboard[SIZE][SIZE];
char opponentboard[SIZE][SIZE];
char hiddenboard_opponent[SIZE][SIZE];
char hiddenboard_player[SIZE][SIZE];

void initializeboard(char board[SIZE][SIZE]);
void displayboard(char board[SIZE][SIZE]);
void placeship(char board[SIZE][SIZE], int length, char hidden[SIZE][SIZE]);
void markblocks(char board[SIZE][SIZE], int x, int y, int length, char direction);
void markblock1(char board[SIZE][SIZE], int x, int y);


int main() {
	initializeboard(playerboard);
	initializeboard(hiddenboard_opponent);
	initializeboard(hiddenboard_player);
	displayboard(playerboard);
	cout << endl << endl;
	initializeboard(opponentboard);
	displayboard(opponentboard);
	int shiplength = 4;
	placeship(playerboard, shiplength--, hiddenboard_player);
	placeship(playerboard, shiplength--, hiddenboard_player);
	placeship(playerboard, shiplength, hiddenboard_player);
	placeship(playerboard, shiplength--, hiddenboard_player);
	placeship(playerboard, shiplength, hiddenboard_player);
	placeship(playerboard, shiplength, hiddenboard_player);
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
void placeship(char board[SIZE][SIZE], int length, char hidden[SIZE][SIZE]) {
	int x; int y; char confirm;
	char direction;
	cout << "Placing a ship of length " << length << ".\n\n";
	cout << "Enter starting coordinates (row and column): ";
	cin >> x;
	cin >> y;
	cout << endl;
	if (length == 1) {
		for (int i = 0; i < length; i++) {
			if (board[x][y] != '~') {
				cout << "Overlap or blocked area detected. Try again.\n\n";
				placeship(board, length, hidden);
				return;
			}
		}
		hidden[x][y] = ship;
		displayboard(hidden);
		cout << "\ncurrent ship placement will be like this.\tconfirm(c is confirm and rest is not confirm)";
		cin >> confirm;
		if (confirm == 'c' || confirm == 'C') {
			board[x][y] = ship;
			markblock1(board, x, y);
		}
		else {
			hidden[x][y] = sea;
			placeship(board, length, hidden);
			return;
		}
	}
	else {
		cout << "Enter direction (h for horizontal, v for vertical): ";
		cin >> direction;
		if (direction == 'h') {
			if (y + length > SIZE) {
				cout << "Ship does not fit horizontally. Try again.\n\n";
				placeship(board, length, hidden);
				return;
			}
			for (int i = 0; i < length; i++) {
				if (board[x][y + i] != '~') {
					cout << "Overlap or blocked area detected. Try again.\n\n";
					placeship(board, length, hidden);
					return;
				}
			}
			for (int i = 0; i < length; i++) {
				hidden[x][y + i] = ship;
			}
			displayboard(hidden);
			cout << "\ncurrent ship placement will be like this.\tconfirm(c is confirm and rest is not confirm)";
			cin >> confirm;
			if (confirm == 'c' || confirm == 'C') {
				for (int i = 0; i < length; i++) {
					board[x][y + i] = ship;
				}
				markblocks(board, x, y, length, 'h');
			}
			else {
				for (int i = 0; i < length; i++) {
					hidden[x][y + i] = sea;
				}
				cout << "\n\tconfirm denied\n";
				placeship(board, length, hidden);
			}
		}
		else if (direction == 'v') {
			if (x + length > SIZE) {
					cout << "Ship does not fit vertically. Try again.\n\n";
					placeship(board, length, hidden);
					return;
			}
			for (int i = 0; i < length; i++) {
					if (board[x + i][y] != '~') {
						cout << "Overlap or blocked area detected. Try again.\n\n";
						placeship(board, length, hidden);
						return;
					}
			}
			for (int i = 0; i < length; i++) {
				hidden[x+i][y] = ship;
			}
			displayboard(hidden);
			cout << "\ncurrent ship placement will be like this.\tconfirm(c is confirm and rest is not confirm)";
			cin >> confirm;
			if (confirm == 'c' || confirm == 'C') {
				for (int i = 0; i < length; i++) {
					board[x+i][y] = ship;
				}
				markblocks(board, x, y, length, 'v');
			}
			else {
				for (int i = 0; i < length; i++) {
					hidden[x+i][y] = sea;
				}
				cout << "\n\tconfirm denied\n";
				placeship(board, length, hidden);
			}
		}
		else {
			cout << "Invalid direction. Please enter 'h' or 'v'.\n\n";
			placeship(board, length, hidden);
			return;
		}
	}
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
void markblock1(char board[SIZE][SIZE], int x, int y) {
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














void attack_player() {
	int cursor_x = 0;
	int cursor_y = 0;

	while (true) {
		displayboard(opponentboard);
		char key = _getch();
		switch (key) {
		case 72: // Up 
			if (cursor_y > 0) cursor_y--;
			break;
		case 80: // Down
			if (cursor_y < SIZE - 1) cursor_y++;
			break;
		case 75: // Left 
			if (cursor_x > 0) cursor_x--;
			break;
		case 77: // Right
			if (cursor_x < SIZE - 1) cursor_x++;
		}
	}
}