#include <iostream>

using namespace std;

typedef struct _COORDI {
  int x;
  int y;
} COORDI;

int n;

int studentsFavorite[420][4];
int studentsOrder[420];

int board[22][22];

bool isFavorite(int orderIndex, COORDI cor) {
  for (int i = 0; i < 4; i++) {
    if (board[cor.x][cor.y] == studentsFavorite[studentsOrder[orderIndex]][i]) return true;
  }
  return false;
}

COORDI getProperPlace(int orderIndex) {
  int favoriteStudentBoard[22][22] = {0, };
  int blankPlaceBoard[22][22] = {0, };

  COORDI direction[4] = {
    {1, 0},
    {0, 1},
    {0, -1},
    {-1, 0}
  };

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (board[i][j] > 0) continue;

      for (int dir = 0; dir < 4; dir++) {
        int dx = direction[dir].x;
        int dy = direction[dir].y;

        int nx = i + dx;
        int ny = j + dy;
        if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
          if (board[nx][ny] == 0) {
            blankPlaceBoard[i][j]++;
          } else if (isFavorite(orderIndex, {nx, ny})) {
            favoriteStudentBoard[i][j]++;
          }
        }
      }
    }
  }

  int maxFav = 0, maxBlank = 0;
  COORDI target;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (board[i][j] > 0) continue;

      if (favoriteStudentBoard[i][j] == maxFav) {
        if (blankPlaceBoard[i][j] > maxBlank) {
          maxBlank = blankPlaceBoard[i][j];
          target.x = i;
          target.y = j;
        } else if (blankPlaceBoard[i][j] == maxBlank) {
          if (i < target.x) {
            target.x = i;
            target.y = j;
          } else if (i == target.x && j < target.y) {
            target.x = i;
            target.y = j;
          }
        }
      } else if (favoriteStudentBoard[i][j] > maxFav) {
        maxFav = favoriteStudentBoard[i][j];
        maxBlank = blankPlaceBoard[i][j];
        target.x = i;
        target.y = j;
      }
    }
  }

  return target;
}

void place(int orderIndex) {
  COORDI coordinate = getProperPlace(orderIndex);

  board[coordinate.x][coordinate.y] = studentsOrder[orderIndex];
}

int getEachSatisfaction(int stIndex, COORDI cur) {
  COORDI direction[4] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1}
  };

  int cnt = 0;

  for (int dir = 0; dir < 4; dir++) {
    int dx = direction[dir].x;
    int dy = direction[dir].y;

    int nx = cur.x + dx;
    int ny = cur.y + dy;

    if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
      for (int i = 0; i < 4; i++) {
        if (board[nx][ny] == studentsFavorite[stIndex][i]) cnt++;
      }
    }
  }

  if (cnt == 1) return 1;
  if (cnt == 2) return 10;
  if (cnt == 3) return 100;
  if (cnt == 4) return 1000;
  return 0;
}

int getSatisfaction() {
  int ans = 0;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      ans += getEachSatisfaction(board[i][j], {i, j});
    }
  }

  return ans;
}

void printBoard() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << board[i][j] << ' ';
    }
    cout << '\n';
  }
  cout << '\n';
}

void solve() {
  for (int i = 0; i < n * n; i++) {
    place(i);
  }

  cout << getSatisfaction() << '\n';
}

int run() {
  cin >> n;

  for (int i = 0; i < n * n; i++) {
    cin >> studentsOrder[i];
    for (int j = 0; j < 4; j++) {
      cin >> studentsFavorite[studentsOrder[i]][j];
    }
  }

  solve();

  return 0;
}