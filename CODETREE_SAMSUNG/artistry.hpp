#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef struct _COORDINATE {
  int x;
  int y;
} COORDINATE;

typedef struct _GROUP {
  COORDINATE position;
  int number;
} GROUP;

int n, board[35][35], groupBoard[35][35], visited[35][35];

int newBoard[35][35] = {0, };

vector<GROUP> groups;

void getInput() {
  cin >> n;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> board[i][j];
    }
  }
}

bool isOutOfBoundary(COORDINATE point) {
  return (point.x < 1 || point.x > n || point.y < 1 || point.y > n);
}

void makeGroup(COORDINATE initialPoint) {
  queue<COORDINATE> q;
  int howMany = 0;

  COORDINATE direction[4] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0},
  };

  int color = board[initialPoint.x][initialPoint.y];

  visited[initialPoint.x][initialPoint.y] = 1;
  q.push(initialPoint);
  groupBoard[initialPoint.x][initialPoint.y] = groups.size() + 1;
  howMany++;

  while(!q.empty()) {
    int x = q.front().x;
    int y = q.front().y;
    q.pop();

    for (int i = 0; i < 4; i++) {
      int dx = direction[i].x;
      int dy = direction[i].y;

      int nx = x + dx;
      int ny = y + dy;

      if (!isOutOfBoundary({nx, ny}) && !visited[nx][ny] && board[nx][ny] == color) {
        visited[nx][ny] = 1;
        groupBoard[nx][ny] = groups.size() + 1;
        q.push({nx, ny});
        howMany++;
      }
    }
  }

  groups.push_back({initialPoint, howMany});
}

void grouping() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      visited[i][j] = 0;
    }
  }

  groups.clear();

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (!visited[i][j]) {
        makeGroup({i, j});
      }
    }
  }
}

int getSide(COORDINATE now, int target) {
  int side = 0;

  COORDINATE direction[4] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0},
  };

  int x = now.x;
  int y = now.y;

  for (int i = 0; i < 4; i++) {
    int dx = direction[i].x;
    int dy = direction[i].y;

    int nx = x + dx;
    int ny = y + dy;

    if (!isOutOfBoundary({nx, ny}) && groupBoard[nx][ny] == target) {
      side++;
    }
  }

  return side;
}

int getSides(int id1, int id2) {
  COORDINATE direction[4] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0},
  };

  int sides = 0;

  int sideVisited[35][35] = {0, };

  int target = id2 + 1;
  int sameSide = id1 + 1;

  queue<COORDINATE> q;

  q.push(groups[id1].position);
  sideVisited[groups[id1].position.x][groups[id1].position.y] = 1;

  sides += getSide(groups[id1].position, target);

  while (!q.empty()) {
    int x = q.front().x;
    int y = q.front().y;
    q.pop();

    for (int i = 0; i < 4; i++) {
      int dx = direction[i].x;
      int dy = direction[i].y;

      int nx = x + dx;
      int ny = y + dy;

      if (!isOutOfBoundary({nx, ny}) && !sideVisited[nx][ny] && groupBoard[nx][ny] == sameSide) {
        sideVisited[nx][ny] = 1;
        q.push({nx, ny});
        sides += getSide({nx, ny}, target);
      }
    }
  }

  return sides;
}

int getArtistyScore(int id1, int id2) {
  int aNum = groups[id1].number;
  int bNum = groups[id2].number;

  int aColor = board[groups[id1].position.x][groups[id1].position.y];
  int bColor = board[groups[id2].position.x][groups[id2].position.y];

  int sides = getSides(id1, id2);

  int score = (aNum + bNum) * aColor * bColor * sides;

  return score > 0 ? score : 0;
}

int getArtistyScores() {
  int totalScore = 0;
  
  for (int firstGroupId = 0; firstGroupId < groups.size(); firstGroupId++) {
    for (int secondGroupId = firstGroupId + 1; secondGroupId < groups.size(); secondGroupId++) {
      totalScore += getArtistyScore(firstGroupId, secondGroupId);
    }
  }

  return totalScore;
}

void rotateCross() {
  int middle = (n+1) / 2;

  for (int i = 1; i <= n; i++) {
    newBoard[middle][i] = board[i][middle];
  }

  for (int i = 1; i <= n; i++) {
    newBoard[i][middle] = board[middle][n - i + 1];
  }
}

void rotateBox(COORDINATE start) {
  int len = (n-1) / 2;

  for (int i = 0; i < len; i++) {
    for (int j = 0; j < len; j++) {
      newBoard[start.x + i][start.y + j] = board[start.x + len - j - 1][start.y + i];
    }
  }
}

void printBoard() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cout << board[i][j] << ' ';
    }
    cout << '\n';
  }
  cout << '\n';
}

void rotateFullBoard() {
  rotateCross();

  int middle = (n+1) / 2;

  rotateBox({1, 1});
  rotateBox({1, middle + 1});
  rotateBox({middle + 1, 1});
  rotateBox({middle + 1, middle + 1});

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      board[i][j] = newBoard[i][j];
    }
  }

  // printBoard();
}

void solve() {
  int totalScore = 0;

  for (int i = 0; i < 4; i++) {
    grouping();

    totalScore += getArtistyScores();

    rotateFullBoard();
  }

  cout << totalScore << '\n';
}

int run() {
  getInput();

  solve();

  return 0;
}