#include <iostream>
#include <cstring>
#include <vector>
#include <math.h>

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
  vector<COORDINATE> ans;
  ans.clear();
  ans.push_back(points[0]);
  ans.push_back(points[1]);
  ans.push_back(points[3]);
  ans.push_back(points[2]);

  return ans;
}

void printArray(int array[MAX_N][MAX_N]) {
  cout << '\n';

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << array[i][j] << ' ';
    }
    cout << '\n';
  }
}

int getScore() {
  int diserts[MAX_DISERT + 1] = {0, };

  int ans = 0;

  vector<COORDINATE> fullPoints = getFUllPoints();

  int route[MAX_N][MAX_N] = {0, };

  for (int i = 0; i < fullPoints.size(); i++) {
    COORDINATE a = fullPoints[i];
    COORDINATE b = fullPoints[(i + 1) % fullPoints.size()];

    COORDINATE direction = {(b.x - a.x) / abs(b.x - a.x), (b.y - a.y) / abs(b.y - a.y)};

    COORDINATE constPoint = a;

    for (int d = 0; d < abs(b.x - a.x); d++) {
      COORDINATE point = {constPoint.x + direction.x * d, constPoint.y + direction.y * d};
      int disert = board[point.x][point.y];

      route[point.x][point.y] = 1;

      if (diserts[disert]) {
        // cout << "DUPLICATE!\n";
        return -1;
      }

      diserts[disert] = 1;

      ans++;
    }
  }

  // printArray(route);

  return ans == 0 ? -1 : ans;
}

void calculate() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      points.push_back({i, j});
      for (int lenTwo = 1; !isOutOfBound({i + lenTwo, j + lenTwo}); lenTwo++) {
        points.push_back({i + lenTwo, j + lenTwo});
        for (int lenFour = 1; !isOutOfBound({i + lenFour, j - lenFour}); lenFour++) {
          points.push_back({i + lenFour, j - lenFour});
          if (!isOutOfBound({i + lenTwo + lenFour, j + lenTwo - lenFour})) {
            points.push_back({i + lenTwo + lenFour, j + lenTwo - lenFour});
            
            int score = getScore();

            if (score > maxAmount) maxAmount = score;

            points.pop_back();
          }
          points.pop_back();
        }
        points.pop_back();
      }
      points.pop_back();
    }
  }
}

int solve() {
  initialize();

  getInput();

  calculate();

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