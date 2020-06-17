#include<iostream>
#include <cstdlib>

using namespace std;
const int MAX_SIZE = 9;
char board[MAX_SIZE][MAX_SIZE];
int N;
int choice;

void generateGrid() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = ' ';
        }
    }
}

void printGrid()//draw the board
{
    for (int i = 0; i < N; i++)//can add numbers for the col and row
    {
        for (int j = 0; j < N; j++) {
            cout << "[" << board[i][j] << "]";
        }
        cout << endl;
    }
}

bool generateRand() {
    int v = rand();
    return v % 2 == 0;
}

void playerMove(char player, int x, int y) {
    if (board[x][y] != ' ') {
        cout << "That cell is not empty. Try another one.";
    } else {
        board[x][y] = player;
    }
}


void computerMove(char player) {
    int row, col;
    do {
        row = rand() % N;
        col = rand() % N;
    } while (board[row][col] != ' ');
    board[row][col] = player;
}

bool isValid(int x, int y) {
    return x >= 0 && y >= 0 && x < N && y < N;
}


bool hasWon() {
    int counterRows = 0, counterCols = 0, counterLeftDiag = 0, counterRightDiag = 0;
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1; j++) {
            if (board[i][j] == board[i][j + 1] && board[i][j] != ' ') {
                counterRows++;
            }
            if (board[j][i] == board[j + 1][i] && board[i][j] != ' ') {
                counterCols++;
            }
            if (i == j && board[i][j] == board[i + 1][j + 1] && board[i][j] != ' ') {
                counterLeftDiag++;
            }
            if (i + j == N - 1 && board[i][j] == board[i + 1][j - 1] && board[i][j] != ' ') {
                counterRightDiag++;
            }
        }
        if (counterRows == N - 1 || counterCols == N - 1) {
            return true;
        }
        counterCols = 0;
        counterRows = 0;
    }
    return counterLeftDiag == N - 1 || counterRightDiag == N - 1;
}

void playGame() {
    int x, y;
    int count = 0;
    char player1 = 'X';
    char player2 = 'O';
    char currPlayer = player1;
    printGrid();
    cout << endl;
    while (count != N * N) {
        if (choice == 1 || (choice == 2 && currPlayer == player1)) {
            cin >> x >> y;
            x -= 1;
            y -= 1;
            if (!isValid(x, y)) {
                cout << "Try again" << endl;
                continue;
            }
            playerMove(currPlayer, x, y);
        } else {
            computerMove(currPlayer);
        }
        printGrid();
        cout << endl;
        if (hasWon()) {
            if (currPlayer == player1) {
                cout << "Player 1 won!" << endl;
                break;
            } else {
                cout << "Player 2 won!" << endl;
                break;
            }
        }
        count++;
        if (currPlayer == player1) {
            currPlayer = player2;
        } else {
            currPlayer = player1;
        }
    }
    if (count == N * N) {
        cout << "No winner" << endl;
    }
}

int main() {
    do {
        cout << "If you want to play user vs computer: enter 1" << endl;
        cout << "if you want to play user vs user: enter 2" << endl;
        cout << "if you want to play computer vs computer: enter 3" << endl;
        cin >> choice;
    } while (choice < 1 || choice > 3);

    do {
        cout << "Enter grid size: ";
        cin >> N;
    } while (N < 3 || N > 9);
    generateGrid();
    playGame();

    return 0;
}
