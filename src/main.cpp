#include <iostream>
#include <random>
#include <stdio.h>

class Field {
public:
  bool isMine = false;
  bool isHidden = true;
  int Number = 0;
};

Field board[9][9];

bool isValid(int row, int col) {
  return ((row >= 0) && (row < 9) && (col >= 0) && (col < 9));
}

void placeMines() {

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, 8);

  for (int i = 0; i < 10; i++) {
    int j = distrib(gen);
    int k = distrib(gen);
    if (board[j][k].isMine == true) {

      i--;

    } else {
      (board[j][k].isMine = true);
    }
  }
}

void printBoard() {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (board[i][j].isHidden == false) {
        if (board[i][j].isMine == false) {
          std::cout << board[i][j].Number;
        } else {
          std::cout << "*";
        }
      } else {
        std::cout << "#";
      }
    }
    std::cout << "\n";
  }
}

void assignNumbers(int row, int col) {
  int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

  for (int d = 0; d < 8; d++) {
    int newRow = row + dx[d];
    int newCol = col + dy[d];

    if (isValid(newRow, newCol) == true) {
      if (board[newRow][newCol].isMine == true) {
        board[row][col].Number++;
      }
    }
  }
}

void showZeros(int row, int col) {
  if (board[row][col].isHidden == true) {
    board[row][col].isHidden = false;
    if (board[row][col].Number == 0) {
      int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
      int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

      for (int d = 0; d < 8; d++) {
        int newRow = row + dx[d];
        int newCol = col + dy[d];

        if (isValid(newRow, newCol) == true) {

          if (board[newRow][newCol].Number == 0) {
            showZeros(newRow, newCol);
          }
          board[newRow][newCol].isHidden = false;
        }
      }
    }
  }
}
void makeMove() {
  int x, y;
  printf("Podaj rząd oraz kolumne\n");
  scanf("%d %d", &x, &y);
  showZeros(x, y);
}

int main() {

  placeMines();
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      assignNumbers(i, j);
    }
  }
  printBoard();

  makeMove();
  printBoard();
  makeMove();
  printBoard();
  makeMove();
  printBoard();
  makeMove();
  printBoard();

  return 0;
}