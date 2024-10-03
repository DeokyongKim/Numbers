#include <iostream>
#include <cstring>
#include <vector>

#define MAX_N 10

using namespace std;

typedef struct _COORDINATE {
  int x;
  int y;
} COORDINATE;

int maxLength, n, board[MAX_N][MAX_N], constructionDepth;

int visited[MAX_N][MAX_N];

vector<COORDINATE> highestPoints;

void initialize() {
  maxLength = -1;
  memset(board, 0, sizeof(int) * MAX_N * MAX_N);
  memset(visited, 0, sizeof(int) * MAX_N * MAX_N);
  highestPoints.clear();
}

void getInput() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> board[i][j];
    }
  }
}

int getHighestHeight() {
  int highestHeight = -1;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (highestHeight < board[i][j]) {
        highestHeight = board[i][j];
      }
    }
  }

  return highestHeight;
}

vector<COORDINATE> getHighestPoints() {
  vector<COORDINATE> hps;

  int highestHeight = getHighestHeight();

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (board[i][j] == highestHeight) {
        hps.push_back({i, j});
      }
    }
  }

  return hps;
}

bool isOutOfBound(int x, int y) {
  return x < 0 || x >= n || y < 0 || y >= n;
}

void printArray(int array[MAX_N][MAX_N]) {
  for (int i =0 ; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << array[i][j] << ' ' ;
    }
    cout << '\n';
  }
    cout << '\n';

}

void makeTrail(COORDINATE cur, bool constructed, int length) {
  int currentHeight = board[cur.x][cur.y];

  bool did = false;

  COORDINATE directions[4] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0},
  };

  for (int i = 0; i < 4; i++) {
    int dx = directions[i].x;
    int dy = directions[i].y;

    int nx = cur.x + dx;
    int ny = cur.y + dy;

    if (isOutOfBound(nx, ny) || visited[nx][ny]) continue;

    int newHeight = board[nx][ny];

    if (newHeight < currentHeight) {
      visited[nx][ny] = 1;
      makeTrail({nx, ny}, constructed, length + 1);
      visited[nx][ny] = 0;

      did = true;
    } 
    
    if (!constructed && newHeight >= currentHeight && newHeight - currentHeight < constructionDepth) {
      board[nx][ny] = currentHeight - 1;
      visited[nx][ny] = 1;
      makeTrail({nx, ny}, true, length + 1);
      board[nx][ny] = newHeight;
      visited[nx][ny] = 0;

      did = true;
    }
  }

  if (!did) {
    if (length > maxLength) {
      maxLength = length;
      // printArray(visited);
    }
    return;
  }
}

int solve() {
  initialize();

  cin >> n >> constructionDepth;

  getInput();

  highestPoints = getHighestPoints();

  for (int i = 0; i < highestPoints.size(); i++) {
    visited[highestPoints[i].x][highestPoints[i].y] = 1;
    makeTrail(highestPoints[i], false, 1);
    visited[highestPoints[i].x][highestPoints[i].y] = 0;
  }

  return maxLength;
}

int run() {
  int testCases;
  cin >> testCases;

  for (int i = 1; i <= testCases; i++) {
    cout << "#" << i << ' ' << solve() << '\n';
  }

  return 0;
}