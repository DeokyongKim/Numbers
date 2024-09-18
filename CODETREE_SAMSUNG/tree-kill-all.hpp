#include <iostream>
#include <vector>

#define MAX_N 25
#define WALL -20

using namespace std;

int n, eradicationYear, herbicideRange, herbicideRemainYear;

int map[MAX_N][MAX_N], totalKilled, herbicideMap[MAX_N][MAX_N];

typedef struct _COORDINATE {
  int x;
  int y;
} COORDINATE;

void printMap(int array[MAX_N][MAX_N]) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (array[i][j] == WALL) cout << 'W' << '\t';
      else cout << array[i][j] << '\t';
    }
    cout << "\n\n";
  }
  cout << '\n';
}

bool isOutOfBound(int x, int y) {
  if (x < 0) return true;
  if (y < 0) return true;
  if (x >= n) return true;
  if (y >= n) return true;

  return false;
}

int getNumberOfTreesNearby(int x, int y) {
  COORDINATE directions[4] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0},
  };

  int ans = 0;

  for (int i = 0; i < 4; i++) {
    int dx = directions[i].x;
    int dy = directions[i].y;

    int nx = x + dx;
    int ny = y + dy;

    if (!isOutOfBound(nx, ny) && map[nx][ny] > 0) {
      ans++;
    }
  }

  return ans;
}

void grow() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (map[i][j] > 0) {
        map[i][j] += getNumberOfTreesNearby(i, j);
      }
    }
  }
}

vector<COORDINATE> getBlanksNearby(int x, int y) {
  COORDINATE directions[4] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0},
  };

  vector<COORDINATE> ans;

  for (int i = 0; i < 4; i++) {
    int dx = directions[i].x;
    int dy = directions[i].y;

    int nx = x + dx;
    int ny = y + dy;

    if (!isOutOfBound(nx, ny) && map[nx][ny] == 0 && herbicideMap[nx][ny] == 0) {
      ans.push_back({nx, ny});
    }
  }

  return ans;
}

void breed() {
  int newMap[MAX_N][MAX_N] = {0, };

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      newMap[i][j] = map[i][j];
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (map[i][j] > 0) {
        vector<COORDINATE> blanksNearby = getBlanksNearby(i, j);

        int numberOfBlanksNearby = blanksNearby.size();

        for (int k = 0; k < blanksNearby.size(); k++) {
          COORDINATE cur = blanksNearby[k];

          newMap[cur.x][cur.y] += (map[i][j] / numberOfBlanksNearby);
        }
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      map[i][j] = newMap[i][j];
    }
  }
}

int getEradicationNumber(int x, int y, bool erase, int year) {
  COORDINATE directions[4] = {
    {1, 1},
    {-1, 1},
    {1, -1},
    {-1, -1},
  };

  int ans = 0;

  int tmp = map[x][y];

  ans += map[x][y];
  if (erase) {
    map[x][y] = 0;
    herbicideMap[x][y] = year;
  }

  if (tmp == 0) return 0;

  for (int i = 0; i < 4; i++) {
    int dx = directions[i].x;
    int dy = directions[i].y;

    int nx = x;
    int ny = y;

    for (int range = 0; range < herbicideRange; range++) {
      nx += dx;
      ny += dy;

      if (isOutOfBound(nx, ny) || map[nx][ny] == WALL) break;

      int mapNum = map[nx][ny];

      ans += map[nx][ny];
      if (erase) {
        map[nx][ny] = 0;
        herbicideMap[nx][ny] = year;
      }
      if (mapNum == 0) break;
    }
  }

  return ans;
}

COORDINATE getMostEradicatingPosition(int year) {
  COORDINATE maxPosition = {-1, -1};
  int maxEradication = -1;
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (map[i][j] > 0) {
        int eradicationNumber = getEradicationNumber(i, j, false, year);

        if (maxEradication < eradicationNumber) {
          maxEradication = eradicationNumber;

          maxPosition = {i, j};
        }
      } else if (map[i][j] == 0) {
        if (maxEradication < 0) {
          maxEradication = 0;

          maxPosition = {i, j};
        }
      }
    }
  }
  // cout << "KILLED: " << maxEradication << '\n';

  return maxPosition;
}

void eradicate(int year) {
  COORDINATE mostEradicatingPosition = getMostEradicatingPosition(year);

  if (mostEradicatingPosition.x == -1) return;

  totalKilled += getEradicationNumber(mostEradicatingPosition.x, mostEradicatingPosition.y, true, year);
}

void deherbicide(int year) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (herbicideMap[i][j] + herbicideRemainYear < year) herbicideMap[i][j] = 0;
    }
  }
}

void spendYear(int year) {
  deherbicide(year);
  // printMap(map);

  grow();
  // printMap(map);

  breed();
  // printMap(map);

  eradicate(year);
  // printMap(map);

}

void solve() {
  for (int year = 0; year < eradicationYear; year++) {
    // cout << "YEAR: " << year + 1 << "=============\n";
    spendYear(year+1);
  }

  cout << totalKilled << '\n';
}

int run() {
  cin >> n >> eradicationYear >> herbicideRange >> herbicideRemainYear;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> map[i][j];

      if (map[i][j] == -1) map[i][j] = WALL;
    }
  }

  solve();

  return 0;
}