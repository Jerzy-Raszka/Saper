#include <conio.h>
#include <iostream>
#include <random>
#include <stdio.h>

uint8_t sides, mines;
int moves;
bool gameRunning = true;
const int8_t dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int8_t dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

class Field {
public:
  bool isMine = false;
  bool isHidden = true;
  int number = 0;
};

std::vector<std::vector<Field>> board;

bool isFieldOnBoard(int row, int col) {
  return row >= 0 && row < sides && col >= 0 && col < sides;
}

void chooseLevel() {
  int level;

  printf("Wybierz poziom trudności\n");
  printf("Łatwy - wciśnij 0\n");
  printf("Normlany - wciśnij 1\n");
  printf("Trudny - wciśnij 2\n");

  if (scanf(" %d", &level) == 1 && level != '\n') {
    switch (level) {
      case 0:
        sides = 9;
        mines = 10;
        moves = 71;
        break;
      case 1:
        sides = 16;
        mines = 216;
        moves = 71;
        break;
      case 2:
        sides = 25;
        mines = 99;
        moves = 526;
        break;
      default:
        printf("Wybrałeś zły numer, wybierz ponownie\n");
        chooseLevel();
    }
  } else {
    printf("Wprowadź numer poprawnie\n");
    fseek(stdin, 0, SEEK_END);
    chooseLevel();
  }
}

void placeMines() {

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, sides - 1);

  for (int i = 0; i < mines; i++) {
    uint8_t j = distrib(gen);
    uint8_t k = distrib(gen);
    if (board[j][k].isMine) {
      i--;
    } else {
      board[j][k].isMine = true;
    }
  }
}

void printBoard() {

  for (int i = -1; i < sides; i++) {
    for (int j = -1; j < sides; j++) {
      if (i == -1) {
        for (int i = 0; i < sides; i++) {
          if (i == 0) {
            printf(" X ");
          }
          printf(" %d ", i);
        }
        printf("\n");
        i++;
      }
      if (j == -1) {
        printf(" %d ", i);
        j++;
      }
      if (board[i][j].isHidden) {
        printf(" - ");
      } else if (board[i][j].isMine) {
        printf(" * ");
      } else {
        printf(" %d ", board[i][j].number);
      }
    }
    printf("\n");
  }
}

void assignNumbers(int row, int col) {

  for (int d = 0; d < 8; d++) {
    int8_t newRow = row + dx[d];
    int8_t newCol = col + dy[d];

    if ((isFieldOnBoard(newRow, newCol)) && (board[newRow][newCol].isMine)) {
      board[row][col].number++;
    }
  }
}

void showZeros(int row, int col) {
  if (board[row][col].isHidden) {

    board[row][col].isHidden = false;
    moves--;

    if (board[row][col].number == 0) {
      for (int d = 0; d < 8; d++) {
        int8_t newRow = row + dx[d];
        int8_t newCol = col + dy[d];
        if (isFieldOnBoard(newRow, newCol)) {
          if (board[newRow][newCol].number == 0) {
            showZeros(newRow, newCol);
          }
          if (board[newRow][newCol].isHidden) {
            board[newRow][newCol].isHidden = false;
            moves--;
          }
        }
      }
    }
  }
}

void makeMove() {
  int x, y;
  printf("Podaj rząd oraz kolumne\n");
  scanf("%d %d", &x, &y);
  if (isFieldOnBoard(x, y)) {
    if (board[x][y].isMine) {
      for (int i = 0; i < sides; i++) {
        for (int j = 0; j < sides; j++) {
          board[i][j].isHidden = false;
        }
      }
      printBoard();
      printf("Trafiłeś na bombę, gameover\n");
      gameRunning = false;
    }
    if (gameRunning) {
      showZeros(x, y);
      if (moves == 0) {
        printf("Wygrałes gratulacje\n");
        gameRunning = false;
      }
    }
  } else {
    printf("Podaj poprawny numer wiersza i kolumny\n");
    fseek(stdin, 0, SEEK_END);
    makeMove();
  }
}

int main() {

  chooseLevel();

  board.resize(sides);
  for (int i = 0; i < sides; i++) {
    board[i].resize(sides);
  }
  placeMines();

  for (int i = 0; i < sides; i++) {
    for (int j = 0; j < sides; j++) {
      assignNumbers(i, j);
    }
  }

  do {
    printBoard();
    makeMove();

  } while (gameRunning);

  return 0;
}