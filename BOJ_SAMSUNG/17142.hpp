#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef struct _VIRUS {
  int x;
  int y;
  int t;
} VIRUS;

int n, m, board[60][60], ans = -1;

int selected[15] = {0, };

vector<VIRUS> virus;

int getTimeForInfection() {
  int tmpBoard[60][60] = {0, };
  int notInfected = 0;
  
  queue<VIRUS> q;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      tmpBoard[i][j] = board[i][j];
      if (board[i][j] == 0) notInfected++;
    }
  }

  if (notInfected == 0) return 0;

  for (int i = 0; i < virus.size(); i++) {
    if (selected[i]) {
      q.push({virus[i].x, virus[i].y, 0});
      tmpBoard[virus[i].x][virus[i].y] = 3;  
    }
  }

  // infect
  while (!q.empty()) {
    int i = q.front().x;
    int j = q.front().y;
    int curTime = q.front().t;
    q.pop();

    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};

    for (int dir = 0; dir < 4; dir++) {
      int nx = i + dx[dir];
      int ny = j + dy[dir];

      if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
        if (tmpBoard[nx][ny] == 0 || tmpBoard[nx][ny] == 2) {
          q.push({nx, ny, curTime+1});
          if (tmpBoard[nx][ny] == 0) notInfected--;
          tmpBoard[nx][ny] = 3;
        }
      }
    }

    if (notInfected == 0) {
      return curTime + 1;
    }
  }

  return -1;
}

void solve(int check, int lastNum) {
  if (check == m) {
    int t = getTimeForInfection();

    if (t >= 0) {
      if (ans == -1) ans = t;
      else if (ans > t) ans = t;
    }
  } else {
    for (int i = lastNum + 1; i < virus.size(); i++) {
      selected[i] = 1;
      solve(check + 1, i);
      selected[i] = 0;
    }
  }
}

int run() {
  // input
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> board[i][j];
      if (board[i][j] == 2) {
        virus.push_back({i, j, 0});
      }
    }
  }

  solve(0, -1);

  cout << ans << '\n';

  return 0;
}