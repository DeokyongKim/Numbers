#include <iostream>
#include <cstring>
#include <vector>

#define MAX_N 12
#define MAX_WORKER 2

using namespace std;

typedef struct _COORDINATE {
  int x;
  int y;

  bool operator == (_COORDINATE& other) {
    return x == other.x && y == other.y;
  }
} COORDINATE;

int n, board[MAX_N][MAX_N], maxBenefit, scores[MAX_N][MAX_N], maxLength, maxQuantity;

vector<COORDINATE> workers;

void initialize() {
  memset(board, 0, sizeof(int) * MAX_N * MAX_N);
  memset(scores, 0, sizeof(int) * MAX_N * MAX_N);

  maxBenefit = -1;
  workers.clear();
}

void getInput() {
  cin >> n >> maxLength >> maxQuantity;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> board[i][j];
    }
  }
}

int getMaximumBenefit(COORDINATE start, int length, int quantity) {
  if (length == maxLength) return 0;

  COORDINATE cur = {start.x, start.y + length};
  int honey = board[cur.x][cur.y];

  int a = -1, b;

  if (quantity + honey <= maxQuantity) {
    a = getMaximumBenefit(start, length+1, quantity + honey) + honey * honey;
  }

  b = getMaximumBenefit(start, length+1, quantity);

  return a > b ? a : b;
}

bool isOutOfBound(int x, int y) {
  return x < 0 || x >= n || y < 0 || y >= n;
}

bool isAble(int x, int y) {
  int nx = x, ny = y + maxLength - 1;

  return !isOutOfBound(nx, ny);
}

void printArray(int array[MAX_N][MAX_N]) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << array[i][j] << ' ';
    }
    cout << '\n';
  }
  cout << '\n';
}

void dfs(int cur) {
  if (workers.size() == MAX_WORKER) {
    if (workers[0] == workers[1]) return;
    if (workers[0].x == workers[1].x && workers[0].y + maxLength - 1 >= workers[1].y) return;

    int ans = scores[workers[0].x][workers[0].y] + scores[workers[1].x][workers[1].y];
  
    if (ans > maxBenefit) {
      // cout << "WORKERS: " << workers[0].x << ", " << workers[0].y << " and " << workers[1].x << ", " << workers[1].y << '\n';
      maxBenefit = ans;
    }

    return;
  }

  for (int num = cur; num < n * n; num++) {
    int i = num / n;
    int j = num % n;

    if (scores[i][j] <= 0 || j > n - maxLength) continue;

    workers.push_back({i, j});
    dfs(cur+1);
    workers.pop_back();
  }
}

int solve() {
  initialize();

  getInput();

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (isAble(i, j)) {
        scores[i][j] = getMaximumBenefit({i, j}, 0, 0);
      }
    }
  }

  dfs(0);
  // printArray(scores);

  return maxBenefit;
}

int run() {
  int testCases;
  cin >> testCases;

  for (int i = 1; i <= testCases; i++) {
    cout << "#" << i << ' ' << solve() << '\n';
  }

  return 0;
}