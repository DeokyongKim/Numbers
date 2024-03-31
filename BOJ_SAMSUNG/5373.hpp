// Gold

#include <cstring>
#include <iostream>

using namespace std;

char cube[6][3][3];

void initialize() {
  char val[10] = {'w', 'y', 'r', 'o', 'g', 'b'};
  for (int i = 0; i < 6; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 3; k++)
        cube[i][j][k] = val[i];
}

void rotatePlain(char plain, char dir) {
  int plainNum;

  if (plain == 'U')
    plainNum = 0;
  if (plain == 'D')
    plainNum = 1;
  if (plain == 'F')
    plainNum = 2;
  if (plain == 'B')
    plainNum = 3;
  if (plain == 'L')
    plainNum = 4;
  if (plain == 'R')
    plainNum = 5;

  if (dir == '+') {
    char tmp[3][3] = {
        {cube[plainNum][2][0], cube[plainNum][1][0], cube[plainNum][0][0]},
        {cube[plainNum][2][1], cube[plainNum][1][1], cube[plainNum][0][1]},
        {cube[plainNum][2][2], cube[plainNum][1][2], cube[plainNum][0][2]},
    };

    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        cube[plainNum][i][j] = tmp[i][j];
  }

  if (dir == '-') {
    char tmp[3][3] = {
        {cube[plainNum][0][2], cube[plainNum][1][2], cube[plainNum][2][2]},
        {cube[plainNum][0][1], cube[plainNum][1][1], cube[plainNum][2][1]},
        {cube[plainNum][0][0], cube[plainNum][1][0], cube[plainNum][2][0]},
    };

    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        cube[plainNum][i][j] = tmp[i][j];
  }
}

void rotateSide(char plain) {
  if (plain == 'U') {
    char tmp[3] = {cube[2][0][0], cube[2][0][1], cube[2][0][2]};
    for (int i = 0; i < 3; i++)
      cube[2][0][i] = cube[5][0][i];
    for (int i = 0; i < 3; i++)
      cube[5][0][i] = cube[3][0][i];
    for (int i = 0; i < 3; i++)
      cube[3][0][i] = cube[4][0][i];
    for (int i = 0; i < 3; i++)
      cube[4][0][i] = tmp[i];
  }
  if (plain == 'D') {
    char tmp[3] = {cube[2][2][0], cube[2][2][1], cube[2][2][2]};
    for (int i = 0; i < 3; i++)
      cube[2][2][i] = cube[4][2][i];
    for (int i = 0; i < 3; i++)
      cube[4][2][i] = cube[3][2][i];
    for (int i = 0; i < 3; i++)
      cube[3][2][i] = cube[5][2][i];
    for (int i = 0; i < 3; i++)
      cube[5][2][i] = tmp[i];
  }
  if (plain == 'F') {
    char tmp[3] = {cube[0][2][0], cube[0][2][1], cube[0][2][2]};
    for (int i = 0; i < 3; i++)
      cube[0][2][i] = cube[4][2 - i][2];
    for (int i = 0; i < 3; i++)
      cube[4][i][2] = cube[1][0][i];
    for (int i = 0; i < 3; i++)
      cube[1][0][i] = cube[5][2 - i][0];
    for (int i = 0; i < 3; i++)
      cube[5][i][0] = tmp[i];
  }
  if (plain == 'B') {
    char tmp[3] = {cube[0][0][0], cube[0][0][1], cube[0][0][2]};
    for (int i = 0; i < 3; i++)
      cube[0][0][i] = cube[5][i][2];
    for (int i = 0; i < 3; i++)
      cube[5][i][2] = cube[1][2][2 - i];
    for (int i = 0; i < 3; i++)
      cube[1][2][i] = cube[4][i][0];
    for (int i = 0; i < 3; i++)
      cube[4][i][0] = tmp[2 - i];
  }
  if (plain == 'R') {
    char tmp[3] = {cube[0][0][2], cube[0][1][2], cube[0][2][2]};
    for (int i = 0; i < 3; i++)
      cube[0][i][2] = cube[2][i][2];
    for (int i = 0; i < 3; i++)
      cube[2][i][2] = cube[1][i][2];
    for (int i = 0; i < 3; i++)
      cube[1][i][2] = cube[3][2 - i][0];
    for (int i = 0; i < 3; i++)
      cube[3][i][0] = tmp[2 - i];
  }
  if (plain == 'L') {
    char tmp[3] = {cube[0][0][0], cube[0][1][0], cube[0][2][0]};
    for (int i = 0; i < 3; i++)
      cube[0][i][0] = cube[3][2 - i][2];
    for (int i = 0; i < 3; i++)
      cube[3][i][2] = cube[1][2 - i][0];
    for (int i = 0; i < 3; i++)
      cube[1][i][0] = cube[2][i][0];
    for (int i = 0; i < 3; i++)
      cube[2][i][0] = tmp[i];
  }
}

void cubing(char plain, char dir) {
  rotatePlain(plain, dir);

  if (dir == '+')
    rotateSide(plain);
  else if (dir == '-')
    for (int i = 0; i < 3; i++)
      rotateSide(plain);
}

int main() {
  freopen("input.txt", "r", stdin);

  int test_case;
  cin >> test_case;
  for (int t = 0; t < test_case; t++) {
    initialize();

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
      char order[4];
      cin >> order;

      cubing(order[0], order[1]);
    }

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        cout << cube[0][i][j];
      }
      cout << '\n';
    }
  }
}