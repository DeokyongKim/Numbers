#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef struct _TAXI {
  int x;
  int y;
  int fuel;
  int curCustomer;
} TAXI;

typedef struct _CUSTOMER {
  int fromX;
  int fromY;
  int toX;
  int toY;
} CUSTOMER;

int n, m;

int map[25][25];

TAXI taxi;

CUSTOMER customer[450];

int isGone[450];

bool isCustomerLeft() {
  for (int i = 1; i <= m; i++) {
    if (!isGone[i]) return true;
  } 
  return false;
}

int findClosestCustomer() {
  queue<pair<pair<int, int>, int> > q;
  int visited[25][25] = {0, };

  q.push({{taxi.x, taxi.y}, 0});
  visited[taxi.x][taxi.y] = 1;

  pair<int, int> direction[4] = {
    {-1, 0}, 
    {0, -1},
    {0, 1},
    {1, 0},
  };

  while(!q.empty()) {
    int curX = q.front().first.first;
    int curY = q.front().first.second;
    int curFuelUsed = q.front().second;
    q.pop();

    if (taxi.fuel <= curFuelUsed) return -1;

    if (map[curX][curY] > 0 && !isGone[map[curX][curY]]) {
      // 행과 열이 가장 작은 사람을 찾자

      int targetIndex = map[curX][curY];
      int targetRow = curX;
      int targetCol = curY;
      while(!q.empty()) {
        int cx = q.front().first.first;
        int cy = q.front().first.second;
        int cf = q.front().second;
        q.pop();

        if (map[cx][cy] <= 0) continue;

        if (cf > curFuelUsed) break;

        if (cx == targetRow) {
          if (cy < targetCol) {
            targetIndex = map[cx][cy];
            targetCol = cy;
          }
        } else if (cx < targetRow) {
          targetIndex = map[cx][cy];
          targetRow = cx;
          targetCol = cy;
        }
      }

      taxi.fuel -= curFuelUsed;
      taxi.x = targetRow;
      taxi.y = targetCol;
      isGone[targetIndex] = 1;
      return targetIndex;
    }

    for (int dirIdx = 0; dirIdx < 4; dirIdx++) {
      int dx = direction[dirIdx].first;
      int dy = direction[dirIdx].second;

      int nx = curX + dx;
      int ny = curY + dy;
      if (nx <= 0 || nx > n || ny <= 0 || ny > n) continue;

      if (!visited[nx][ny] && map[nx][ny] >= 0) {
        visited[nx][ny] = 1;
        q.push({{nx, ny}, curFuelUsed+1});
      }
    }
  }

  return -1;
}

void moveCustomer(int customerIndex) {
  queue<pair<pair<int, int>, int> > q;
  int visited[25][25] = {0, };

  q.push({{taxi.x, taxi.y}, 0});
  visited[taxi.x][taxi.y] = 1;

  pair<int, int> direction[4] = {
    {-1, 0}, 
    {0, -1},
    {0, 1},
    {1, 0},
  };

  while(!q.empty()) {
    int curX = q.front().first.first;
    int curY = q.front().first.second;
    int curFuelUsed = q.front().second;
    q.pop();

    if (taxi.fuel < curFuelUsed) {
      taxi.fuel = -1;
      return;
    }

    if (curX == customer[customerIndex].toX && curY == customer[customerIndex].toY) {
      taxi.fuel += curFuelUsed;
      taxi.x = curX;
      taxi.y = curY;
      map[customer[customerIndex].fromX][customer[customerIndex].fromY] = 0;
      return;
    }

    for (int dirIdx = 0; dirIdx < 4; dirIdx++) {
      int dx = direction[dirIdx].first;
      int dy = direction[dirIdx].second;

      int nx = curX + dx;
      int ny = curY + dy;
      if (nx <= 0 || nx > n || ny <= 0 || ny > n) continue;

      if (!visited[nx][ny] && map[nx][ny] >= 0) {
        visited[nx][ny] = 1;
        q.push({{nx, ny}, curFuelUsed+1});
      }
    }
  }

  taxi.fuel = -1;
}

void solve() {
  while(taxi.fuel > 0 && isCustomerLeft()) {
    int customerIndex = findClosestCustomer();

    if (customerIndex == -1) {
      taxi.fuel = -1;
      break;
    }

    // cout << customerIndex << '\n';

    moveCustomer(customerIndex);

    // for (int i = 1; i <= n; i++) {
    //   for (int j = 1; j <= n; j++) {
    //     cout << map[i][j] << '\t';
    //   }
    //   cout << '\n';
    // }
    // cout << '\n';
  }

  if (taxi.fuel >= 0) {
    cout << taxi.fuel << '\n';;
    return;
  }
  cout << -1 << '\n';
}

int run() {
  cin >> n >> m >> taxi.fuel;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> map[i][j];
      map[i][j] *= -1;
    }
  }

  cin >> taxi.x >> taxi.y;

  for (int i = 1; i <= m; i++) {
    CUSTOMER &tmp = customer[i];
    cin >> tmp.fromX >> tmp.fromY >> tmp.toX >> tmp.toY;

    map[tmp.fromX][tmp.fromY] = i;
  }

  solve();

  return 0;
}