#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define MAX_N 13
#define MAX_M 13
#define INF 0x7fffffff

using namespace std;

typedef struct _COORDINATE {
  int x;
  int y;

  bool operator==(_COORDINATE& a) {
    return a.x == x && a.y == y;
  }
} COORDINATE;

int n, m, maxTurn, board[MAX_N][MAX_M], lastAttacked[MAX_N][MAX_M], participated[MAX_N][MAX_M];

void resetArray(int array[MAX_N][MAX_M]) {
  memset(array, 0, sizeof(int) * MAX_N * MAX_M);
}

void printArray(int array[MAX_N][MAX_M]) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << array[i][j] << '\t';
    }
    cout << '\n';
  }
}

bool isOutOfBound(int x, int y) {
  if (x < 0) return true;
  if (y < 0) return true;
  if (x >= n) return true;
  if (y >= m) return true;
  return false;
}

COORDINATE getAttacker() {
  COORDINATE attacker = {-1, -1};
  int minAttackForce = INF;
  int maxAttackTime = -1;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (board[i][j] == 0) continue;

      if (minAttackForce >= board[i][j]) {
        if (minAttackForce > board[i][j]) {
          attacker = {i, j};
          minAttackForce = board[i][j];
          maxAttackTime = lastAttacked[i][j];
        } else {
          if (maxAttackTime < lastAttacked[i][j]) {
            attacker = {i, j};
            minAttackForce = board[i][j];
            maxAttackTime = lastAttacked[i][j];
          } else if (maxAttackTime == lastAttacked[i][j]) {
            if (attacker.x + attacker.y < i + j) {
              attacker = {i, j};
              minAttackForce = board[i][j];
              maxAttackTime = lastAttacked[i][j];
            } else if (attacker.x + attacker.y == i + j) {
              if (attacker.y < j) {
                attacker = {i, j};
                minAttackForce = board[i][j];
                maxAttackTime = lastAttacked[i][j];
              }
            }
          }
        }
      }
    }
  }

  return attacker;
}

COORDINATE getDefender() {
  COORDINATE defender = {-1, -1};
  int maxAttackForce = -1;
  int minAttackTime = INF;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (board[i][j] == 0) continue;

      if (board[i][j] > maxAttackForce) {
        defender = {i, j};
        maxAttackForce = board[i][j];
        minAttackTime = lastAttacked[i][j];
      } else if (board[i][j] == maxAttackForce) {
        if (lastAttacked[i][j] < minAttackTime) {
          defender = {i, j};
          minAttackTime = lastAttacked[i][j];
        } else if (lastAttacked[i][j] == minAttackTime) {
          if (i + j < defender.x + defender.y) {
            defender = {i, j};
          } else if (i + j == defender.x + defender.y) {
            if (j < defender.y) defender = {i, j};
          }
        }
      }
    }
  }

  return defender;
}

vector<COORDINATE> getRaserPath(COORDINATE attacker, COORDINATE defender) {
  COORDINATE directions[4] = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
  };
  
  int visited[MAX_N][MAX_M] = {0, };
  queue<vector<COORDINATE> > q;

  vector<COORDINATE> start = {attacker};

  visited[attacker.x][attacker.y] = 1;
  q.push(start);

  while(!q.empty()) {
    vector<COORDINATE> path = q.front();
    q.pop();

    COORDINATE position = path[path.size() - 1];

    if (position == defender) return path;

    int x = position.x;
    int y = position.y;
    // cout << "BFS: " << position.x << position.y << '\n';

    for (int i = 0; i < 4; i++) {
      int dx = directions[i].x;
      int dy = directions[i].y;

      int nx = x + dx;
      int ny = y + dy;

      nx = (nx + n) % n;
      ny = (ny + m) % m;

      COORDINATE nextPosition = {nx, ny};

      if (!visited[nx][ny] && board[nx][ny] != 0) {
        vector<COORDINATE> newPath = path;
        newPath.push_back(nextPosition);
        visited[nx][ny] = 1;
        q.push(newPath);
      }
    }
  }

  return {{-1, -1}};
}

void repairTurrets() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (participated[i][j] == 0 && board[i][j] != 0) board[i][j]++;
    }
  }
}

bool isOnlyOneLeft() {
  int cnt = 0;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (board[i][j] > 0) cnt++;
    }
  }

  return cnt <= 1;
}

bool oneTurn(int turnCnt) {
  resetArray(participated);

  COORDINATE attacker = getAttacker();
  COORDINATE defender = getDefender();

  COORDINATE out = {-1, -1};

  if ((attacker == out) || (defender == out) || (attacker == defender)) return false;

  board[attacker.x][attacker.y] += (n + m);
  int attackForce = board[attacker.x][attacker.y];
  participated[attacker.x][attacker.y] = 1;
  lastAttacked[attacker.x][attacker.y] = turnCnt;
  // cout << "ATTACKER: {" << attacker.x << ", " << attacker.y << "}: " << board[attacker.x][attacker.y] << '\n';
  participated[defender.x][defender.y] = 1;
  // cout << "DEFENDER: {" << defender.x << ", " << defender.y << "}: " << board[defender.x][defender.y] << '\n';


  vector<COORDINATE> raserPath = getRaserPath(attacker, defender);

  if (raserPath[0] == out) {
    // cout << "NO RASER\n";
    COORDINATE directions[9] = {
      {1, 0},
      {1, 1},
      {1, -1},
      {-1, 0},
      {-1, 1},
      {-1, -1},
      {0, 1},
      {0, -1},
      {0, 0},
    };

    for (int i = 0; i < 9; i++) {
      int dx = directions[i].x;
      int dy = directions[i].y;

      int nx = defender.x + dx;
      int ny = defender.y + dy;

      nx = (nx + n) % n;
      ny = (ny + m) % m;

      COORDINATE bomb = {nx, ny};

      if (bomb == attacker) {
        continue;
      } else if (bomb == defender) {
        board[defender.x][defender.y] -= attackForce;
        if (board[defender.x][defender.y] < 0) board[defender.x][defender.y] = 0;
      } else {
        board[bomb.x][bomb.y] -= (attackForce / 2);
        if (board[bomb.x][bomb.y] < 0) board[bomb.x][bomb.y] = 0;
        participated[nx][ny] = 1;
      }
    }
  } else {
    // cout << "RASER ATTACK\n";
    for (int i = 0; i < raserPath.size(); i++) {
      // cout << "{" << raserPath[i].x << ", " << raserPath[i].y << "}, ";
    }

    for (int i = 0; i < raserPath.size(); i++) {
      COORDINATE cur = raserPath[i];

      if (cur == attacker) {
        continue;
      } else if (cur == defender) {
        board[defender.x][defender.y] -= attackForce;
        if (board[defender.x][defender.y] < 0) board[defender.x][defender.y] = 0;
      } else {
        board[cur.x][cur.y] -= (attackForce / 2);
        if (board[cur.x][cur.y] < 0) board[cur.x][cur.y] = 0;
        participated[cur.x][cur.y] = 1;
      }
    }
  }
  // cout << "AFTER ATTACK:\n";
  // printArray(board);
  // cout << "\n";

  if (isOnlyOneLeft()) return false;

  repairTurrets();
  // cout << "AFTER REPAIR:\n";
  // printArray(board);
  // cout << "\n";

  return true;
}

void solve() {
  for (int i = 0; i < maxTurn; i++) {
    // cout << "\nTURN " << i+1 << '\n';
    bool success = oneTurn(i+1);

    if (!success) break;
  }

  COORDINATE defender = getDefender(), out = {-1, -1};

  if (defender == out) cout << "0\n";
  else cout << board[defender.x][defender.y] << '\n';
}

int run() {
  cin >> n >> m >> maxTurn;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> board[i][j];
    }
  }

  // cout << "INITIAL BOARD:\n";
  // printArray(board);
  // cout << '\n';

  solve();

  return 0;
}