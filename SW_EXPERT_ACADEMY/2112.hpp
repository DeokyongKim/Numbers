#include <iostream>
#include <cstring>

#define MAX_W 20
#define MAX_D 15
#define INF 0x7fffffff

using namespace std;

int film[MAX_D][MAX_W], isMedicated[MAX_D];

int depth, width, strength, minMedication;

void initialize() {
  memset(film, 0, sizeof(int) * MAX_D * MAX_W);
  memset(isMedicated, 0, sizeof(int) * MAX_D);
  minMedication = INF; 
}

void getInput() {
  cin >> depth >> width >> strength;

  for (int i = 0; i < depth; i++) {
    for (int j = 0; j < width; j++) {
      cin >> film[i][j];
    }
  }
}

bool isEnough() {
  int board[MAX_D][MAX_W] = {0, };

  for (int i = 0; i < depth; i++) {
    for (int j = 0; j < width; j++) {
      if (isMedicated[i] == 1) {
        board[i][j] = 0;
      } else if (isMedicated[i] == 2) {
        board[i][j] = 1;
      } else if (isMedicated[i] == 0) {
        board[i][j] = film[i][j];
      }
    }
  }

  for (int j = 0; j < width; j++) {
    int len = 0, last = -1;
    bool pass = false;
    for (int i = 0; i < depth; i++) {
      if (board[i][j] != last) {
        if (len >= strength) {
          pass = true;
          break;
        }

        len = 1;
        last = board[i][j];
      } else {
        len++;
      }

      if (len >= strength) {
        pass = true;
        break;
      }
    }
    if (!pass) return false;
  }

  return true;
}

void dfs(int depthIndex, int medicationUsed) {
  if (depthIndex == depth) {
    if (isEnough() && medicationUsed < minMedication) minMedication = medicationUsed;
    return;
  }

  if (medicationUsed >= minMedication) return;

  dfs(depthIndex+1, medicationUsed);

  isMedicated[depthIndex] = 1;
  dfs(depthIndex+1, medicationUsed+1);
  isMedicated[depthIndex] = 2;
  dfs(depthIndex+1, medicationUsed+1);
  isMedicated[depthIndex] = 0;
}

int solve() {
  initialize();

  getInput();

  dfs(0, 0);

  return minMedication;
}

int run() {
  int testCases;
  cin >> testCases;

  for (int i = 1; i <= testCases; i++) {
    cout << "#" << i << ' ' << solve() << '\n';
  }

  return 0;
}