#include <iostream> 
#include <conio.h>
#pragma warning(disable:4996);

using namespace std;
const int SIZE = 10;
const char sea = '~';
const char ship = '@';
const char block = 'X';
const char missed = 'M';
const char hit_ship = 'O';

char playerboard[SIZE][SIZE];
char opponentboard[SIZE][SIZE];
char hiddenboard_opponent[SIZE][SIZE];
char hiddenboard_player[SIZE][SIZE];
char attackboard_opponent[SIZE][SIZE];
char attackboard_player[SIZE][SIZE];

int dice_roll();
void displaywinner(int player);
void initializeboard(char board[SIZE][SIZE]);
void displayboard(char board[SIZE][SIZE]);
void placeship(char board[SIZE][SIZE], int length, char hidden[SIZE][SIZE]);
void markblocks(char board[SIZE][SIZE], int x, int y, int length, char direction);
void markblock1(char board[SIZE][SIZE], int x, int y);
void attackplayer(char attackboard[SIZE][SIZE], char hidden[SIZE][SIZE], int& count, bool secondplayer, int cursorX = 0, int cursorY = 0);
int main() {
	srand(time(NULL));
	int players_ship_count = 14;
	int opponents_ship_count = 14;
	int shiplength = 4;
	int x1 = 0; int y1 = 0; int x2 = 0; int y2 = 0;
	initializeboard(playerboard);
	initializeboard(hiddenboard_opponent);
	initializeboard(hiddenboard_player);
	initializeboard(opponentboard);
	initializeboard(attackboard_opponent);
	initializeboard(attackboard_player);
	cout << "\tplayer1\n";
	displayboard(playerboard);
	cout << "\tplayer2\n";
	displayboard(opponentboard);
	cout << "\t\tplayer 1 places ships:\n";
	placeship(playerboard, shiplength--, hiddenboard_player);
	placeship(playerboard, shiplength--, hiddenboard_player);
	placeship(playerboard, shiplength, hiddenboard_player);
	placeship(playerboard, shiplength--, hiddenboard_player);
	placeship(playerboard, shiplength, hiddenboard_player);
	placeship(playerboard, shiplength, hiddenboard_player);
	cout << "\x1B[2J\x1B[H";
	cout << "give keyboard to player 2";
	cout << endl;
	displayboard(opponentboard);
	cout << "\nplayer 2 places ships:\n";
	shiplength = 4;
	placeship(opponentboard, shiplength--, hiddenboard_opponent);
	placeship(opponentboard, shiplength--, hiddenboard_opponent);
	placeship(opponentboard, shiplength, hiddenboard_opponent);
	placeship(opponentboard, shiplength--, hiddenboard_opponent);
	placeship(opponentboard, shiplength, hiddenboard_opponent);
	placeship(opponentboard, shiplength, hiddenboard_opponent);
	cout << "\x1B[2J\x1B[H";
	cout << "both players have 6 ships(14 pieces).first to eliminate all of other's wins.use arrows and space to navigate\n\npress enter to roll the dice(odd-player1,even-player 2 starts)";
	cin.get();
	int dice = dice_roll();
	cout << "dice rolled and result is:" << dice;
	if (dice % 2 == 0) {
		cout << "\n\teven,player 2 starts\n";
		attackplayer(attackboard_opponent, hiddenboard_player, players_ship_count,true,x2,y2);
	}
	else cout << "\n\todd,player 1 starts";
	while (players_ship_count > 0 && opponents_ship_count > 0) {
		attackplayer(attackboard_player, hiddenboard_opponent, opponents_ship_count,false,x1,y1);

		attackplayer(attackboard_opponent, hiddenboard_player, players_ship_count,true);

	}
	if (players_ship_count == 0)
		displaywinner(2);
	else displaywinner(1);
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

int dice_roll() {
	int dice = 1 + rand() % 6;
	return dice;
}

void displaywinner(int player) {
	cout << "\x1B[2J\x1B[H";
	if (player == 1) {
		cout << "\033[32m"; //green
		cout << "\t****************************\n";
		cout << "\t*     PLAYER 1 WINS!       *\n";
		cout << "\t****************************\n";
	}
	else if (player == 2) {
		cout << "\033[31m"; //red
		cout << "\t****************************\n";
		cout << "\t*     PLAYER 2 WINS!       *\n";
		cout << "\t****************************\n";
	}
	cout << "\033[33m";
	cout << "thanks for playing,this was all";
	cout << "\033[0m";
}

void placeship(char board[SIZE][SIZE], int length, char hidden[SIZE][SIZE]) {
	int x; int y; char confirm;
	char direction;
	cout << "\nPlacing a ship of length " << length << ".\n";
	cout << "\nEnter starting coordinates (row): ";
	cin >> x;
	cout << "\nEnter starting coordinates (column): ";
	cin >> y;
	cout << endl;
	if (x >= 0 && x <= 9 || y >= 0 && y <= 9) {
		if (length == 1) {
			for (int i = 0; i < length; i++) {
				if (board[x][y] != '~') {
					cout << "Overlap or blocked area detected. Try again.\n\n";
					placeship(board, length, hidden);
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
				cout << "\ncurrent ship placement will be like this.\tpress enter to confirm(press anything else to decline)";
				confirm = _getch();
				if (confirm == 13) {
					for (int i = 0; i < length; i++) {
						board[x][y + i] = ship;
					}
					markblocks(board, x, y, length, direction);
				}
				else {
					for (int i = 0; i < length; i++) {
						hidden[x][y + i] = sea;
					}
					placeship(board, length, hidden);
					return;
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
					hidden[x + i][y] = ship;
				}
				displayboard(hidden);
				cout << "\ncurrent ship placement will be like this.\tpress enter to confirm(press anything else to decline)";
				confirm = _getch();
				if (confirm == 13) {
					for (int i = 0; i < length; i++) {
						board[x + i][y] = ship;
					}
					markblocks(board, x, y, length, direction);
				}
				else {
					for (int i = 0; i < length; i++) {
						hidden[x + i][y] = sea;
					}
					placeship(board, length, hidden);
					return;
				}
			}
			else {
				cout << "Invalid direction. Try again.\n\n";
				placeship(board, length, hidden);
				return;
			}
		}
	}
	else {
		cout << "Invalid coordinates. Please enter a number(0-9)\n\n";
		placeship(board, length, hidden);
		return;
	}
}

void attackplayer(char attackboard[SIZE][SIZE], char hidden[SIZE][SIZE], int& count, bool secondplayer,int cursorX ,int cursorY ){
	char input;
	char prevchar = attackboard[cursorX][cursorY];
	bool validMove = false;

	while (!validMove) {
		displayboard(attackboard); 
		attackboard[cursorX][cursorY] = '*'; 
		cout << "\n\t" << (secondplayer ? "player 2" : "player 1") << endl<< "Remaining Ships: " << count << "\nUse arrow keys to move the cursor. Press space to attack.\n";
		input = _getch(); 

		switch (input) {
		case 72: // Up arrow
			if (cursorX > 0) {
				attackboard[cursorX][cursorY] = prevchar; 
				--cursorX;
				prevchar = attackboard[cursorX][cursorY]; 
			}
			break;
		case 80: // Down arrow
			if (cursorX < SIZE - 1) {
				attackboard[cursorX][cursorY] = prevchar;
				++cursorX;
				prevchar = attackboard[cursorX][cursorY];
			}
			break;
		case 75: // Left arrow
			if (cursorY > 0) {
				attackboard[cursorX][cursorY] = prevchar;
				--cursorY;
				prevchar = attackboard[cursorX][cursorY];
			}
			break;
		case 77: // Right arrow
			if (cursorY < SIZE - 1) {
				attackboard[cursorX][cursorY] = prevchar;
				++cursorY;
				prevchar = attackboard[cursorX][cursorY];
			}
			break;
		case 32: // Space to attack
			if (hidden[cursorX][cursorY] == ship) {
				cout << "Hit!\n";
				hidden[cursorX][cursorY] = sea;
				attackboard[cursorX][cursorY] = hit_ship;
				count--;
			}
			else {
				cout << "Miss!\n";
				attackboard[cursorX][cursorY] = missed;
			}
			validMove = true;
			break;
		case 99: // Enable cheat to see opponent's board
			displayboard(hidden);
			cout << "\nPress Enter to return to attack phase.";
			cin.get();
			cout << "\x1B[2J\x1B[H";
			break;
		default:
			break;
		}
		attackboard[cursorX][cursorY] = '*'; 
		cout << "\x1B[2J\x1B[H";
	}
}

