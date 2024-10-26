#include <conio.h>
#include <iostream>
#include <random>
#include <stdio.h>

#define MAXSIDES 25

int sides, mines;
bool gameRunning = true;

class Field {
public:
  bool isMine = false;
  bool isHidden = true;
  int Number = 0;
};

Field board[MAXSIDES][MAXSIDES];

bool isValid(int row, int col) {
  return ((row >= 0) && (row < sides) && (col >= 0) && (col < sides));
}

void chooseLevel() {
  int level;
  printf("Wybierz poziom trudności\n");
  printf("Łatwy - wciśnij 0\n");
  printf("Normlany - wciśnij 1\n");
  printf("Trudny - wciśnij 2\n");
  scanf("%d", &level);
  switch (level) {
  case 0:
    sides = 9;
    mines = 10;
    break;
  case 1:
    sides = 16;
    mines = 40;
    break;
  case 2:
    sides = 25;
    mines = 99;
    break;
  default:
    printf("Wybrałeś zły numer, wybierz ponownie");
    chooseLevel();
  }
}

void placeMines() {

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, sides);

  for (int i = 0; i < mines; i++) {
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

  for (int i = 0; i < sides; i++) {
    for (int j = 0; j < sides; j++) {
      if (board[i][j].isHidden == true) {
        std::cout << "-";
      } else if (board[i][j].isMine == true) {
        std::cout << "*";
      } else {
        std::cout << board[i][j].Number;
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
  if (board[x][y].isMine == true) {
    for (int i = 0; i < sides; i++) {
      for (int j = 0; j < sides; j++) {
        board[i][j].isHidden = false;
      }
    }
    printBoard();
    printf("Trafiłeś na bombę, gameover\n");
    gameRunning = false;
  }
  if (gameRunning == true) {
    showZeros(x, y);
  }
}

int main() {

  chooseLevel();

  placeMines();

  for (int i = 0; i < sides; i++) {
    for (int j = 0; j < sides; j++) {
      assignNumbers(i, j);
    }
  }

  do {
    printBoard(); // TODO Liczby rzędów, kolumn oraz wyrównanie
    makeMove();
  } while (gameRunning == true);

  return 0;
}