#include <iostream>

using namespace std;

void drawBoard(char *);
int checkWin(char *);

int main() {
	int player = 1;
	int result = 1;
	int choice;
	char mark;

	char board[10] = "123456789";

	do {
		drawBoard(board);
		player = (player % 2) ? 1 : 2;

		cout << "\nPlayer " << player << ", enter number: ";
		cin >> choice;

		mark = (player == 1) ? 'X' : 'O';

		try {
			if (choice < 1 || choice > 9) throw "Out of range!";

			if (board[choice - 1] == choice + '0') {
				board[choice - 1] = mark;
			}
		}
		catch (const char* msg) {
			cout << msg << endl;
			player--;
			getchar();
			cin.ignore();
		}

		result = checkWin(board);

		player++;
	} while (result == -1);
	drawBoard(board);

	if (result == 1) {
		cout << "\n==>\tPlayer " << --player << " win!\t<==";
	}
	else {
		cout << "\n==>\tGame draw!\t<==";
	}

	cin.ignore();
	cin.get();
	return 0;
}

void drawBoard(char *board) {
	system("cls");
	cout << endl << endl << "\tTic Tac Toe" << endl << endl;
	cout << "Player 1 (X)  -  Player 2 (O)" << endl << endl;

	cout << "     |     |     " << endl;
	cout << "  " << board[0] << "  |  " << board[1] << "  |  " << board[2] << endl;
	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;
	cout << "  " << board[3] << "  |  " << board[4] << "  |  " << board[5] << endl;
	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;
	cout << "  " << board[6] << "  |  " << board[7] << "  |  " << board[8] << endl;
	cout << "     |     |     " << endl;
}

int checkWin(char *board) {
	if (board[0] == board[1] == board[2]) return 1;
	else if (board[3] == board[4] && board[4] == board[6]) return 1;
	else if (board[6] == board[7] && board[7] == board[8]) return 1;
	else if (board[0] == board[3] && board[3] == board[6]) return 1;
	else if (board[1] == board[4] && board[4] == board[7]) return 1;
	else if (board[2] == board[5] && board[5] == board[8]) return 1;
	else if (board[0] == board[4] && board[4] == board[8]) return 1;
	else if (board[2] == board[4] && board[4] == board[6]) return 1;
	else if (board[0] != '1' && board[1] != '2' && board[2] != '3' &&
		board[3] != '4' && board[4] != '5' && board[5] != '6' &&
		board[6] != '7' && board[7] != '8' && board[8] != '9') return 0;
	else return -1;
}