#include <iostream>
#include <cstring>
#include <vector>

#define MAX_N 20
#define MAX_DISERT 110

using namespace std;

typedef struct _COORDINATE {
  int x;
  int y;

  bool operator == (_COORDINATE &other) {
    return x == other.x && y == other.y;
  }

  bool operator != (_COORDINATE &other) {
    return x != other.x || y != other.y;
  }
} COORDINATE;

int n, board[MAX_N][MAX_N], maxAmount = -1;

vector<COORDINATE> points;

void initialize() {
  maxAmount = -1;
  memset(board, 0, sizeof(int) * MAX_N * MAX_N);
  points.clear();
}

void getInput() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> board[i][j];
    }
  }
}

bool isOutOfBound(COORDINATE point) {
  int x = point.x;
  int y = point.y;

  return x < 0 || x >= n || y < 0 || y >= n;
}

vector<COORDINATE> getFUllPoints() {
  COORDINATE two, four;

  int x1 = points[0].x, y1 = points[0].y;
  int x2 = points[1].x, y2 = points[1].y;

  two.x = (y2-y1 + x1+x2) / 2;
  two.y = (y1+y2 + x2-x1) / 2;
  four.x = (y1-y2 + x1+x2) / 2;
  four.y = (y1+y2 + x1-x2) / 2;

  vector<COORDINATE> ans;
  ans.push_back(points[0]);
  ans.push_back(two);
  ans.push_back(points[1]);
  ans.push_back(four);

  return ans;
}

bool isAble() {
  int x1 = points[0].x, y1 = points[0].y;
  int x2 = points[1].x, y2 = points[1].y;

  if (y2 - x2 >= y1 - x1 || y2+x2 <= y1+x1) return false;

  if (x1 == x2) return false;

  if ((y2-y1 + x1+x2) % 2) return false;
  if ((y1+y2 + x2-x1) % 2) return false;
  if ((y1-y2 + x1+x2) % 2) return false;
  if ((y1+y2 + x1-x2) % 2) return false;

  vector<COORDINATE> fullPoints = getFUllPoints();

  for (int i = 0; i < fullPoints.size(); i++) {
    if (isOutOfBound(fullPoints[i])) return false;
  }

  return true;
}

int getScore() {
  int diserts[MAX_DISERT + 1] = {0, };

  int ans = 0;

  for (int i = 0; i < fullPoints.size(); i++) {
    COORDINATE a = fullPoints[i];
    COORDINATE b = fullPoints[(i + 1) % fullPoints.size()];

    COORDINATE direction = {(b.x - a.x) / (b.x - a.x), (b.y - a.y) / (b.y - a.y)};

    COORDINATE constPoint = a;

    for (int d = 0; d <= b.x - a.x; d++) {
      COORDINATE point = {constPoint.x + direction.x * d, constPoint.y + direction.y * d};
      int disert = board[point.x][point.y];

      if (diserts[disert]) return -1;

      diserts[disert] = 1;

      ans++;
    }
  }

  return ans == 0 ? -1 : ans;
}

void dfs(int index) {
  if (points.size() == 4) {
    int score = getScore();

    if (score > maxAmount) {
      maxAmount = score;
      
      cout << "AMOUNT: " << maxAmount << '\n';

      vector<COORDINATE> fullPoints = getFUllPoints();
      cout << "COORDIs: ";
      for (int i = 0; i < fullPoints.size(); i++) {
        cout << "{"<< fullPoints[i].x << ", " << fullPoints[i].y << "}, ";
      }
      cout << '\n';
    }
    return;
  }

  for (int num = index; num < n * n; num++) {
    if (isAble({i, j})) {
      points.push_back({i, j});
      dfs(num + 1);
      points.pop_back();
    }
  }
}

int solve() {
  initialize();

  getInput();

  dfs(0);

  return maxAmount;  
}

int run() {
  int testCases;
  cin >> testCases;

  for (int i = 1; i <= testCases; i++) {
    cout << "#" << i << ' ' << solve() << '\n';
  }

  return 0;
}