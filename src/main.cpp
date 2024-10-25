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

int main() {
  int x, y;

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

  do {
    printf("Podaj rząd oraz kolumne\n");
    scanf("%d %d", &x, &y);

    board[x][y].isHidden = false;
    board[x][y].Number = 1;

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

  } while (board[x][y].isMine != true);

  return 0;
}