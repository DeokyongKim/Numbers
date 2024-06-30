#include <iostream>

using namespace std;

typedef struct _COORDINATE {
  int x;
  int y;
} COORDINATE;

int n, m, baskets[60][60], cloud[60][60];

void printBaskets() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << baskets[i][j] << '\t';
    }
    cout << '\n';
  }
  cout << '\n';
}

void printCloud() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << cloud[i][j] << '\t';
    }
    cout << '\n';
  }
  cout << '\n';
}

int getTotalWater() {
  int ans = 0;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      ans += baskets[i][j];
    }
  }

  return ans;
}

void setCloud() {
  cloud[n-1][0] = 1;
  cloud[n-1][1] = 1;
  cloud[n-2][0] = 1;
  cloud[n-2][1] = 1;
}

void moveCloud(int dir, int dist) {
  int newCloud[60][60] = {0, };

  COORDINATE direction[8] = {
    {0, -1},
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, 1},
    {1, 1},
    {1, 0},
    {1, -1},
  };

  int dx = direction[dir-1].x * dist;
  int dy = direction[dir-1].y * dist;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (!cloud[i][j]) continue;

      int nx = i + dx;
      int ny = j + dy;

      if (nx < 0) nx += ((-1 * nx/n + 1) * n);
      if (ny < 0) ny += ((-1 * ny/n + 1) * n);
      if (nx >= n) nx %= n;
      if (ny >= n) ny %= n;

      newCloud[nx][ny] = 1;
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cloud[i][j] = newCloud[i][j];
    }
  }
}

void removeCloud() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (cloud[i][j]) cloud[i][j] = -1;
    }
  }
}

void rain() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      baskets[i][j] += cloud[i][j];
    }
  }
}

void replicate() {
  COORDINATE direction[4] = {
    {-1, -1},
    {1, -1},
    {-1, 1},
    {1, 1},
  };

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (!cloud[i][j]) continue;

      int cnt = 0;
      for (int dir = 0; dir < 4; dir++) {
        int dx = direction[dir].x;
        int dy = direction[dir].y;

        int nx = i + dx;
        int ny = j + dy;

        if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
          if (baskets[nx][ny]) cnt++;
        }
      }

      baskets[i][j] += cnt;
    }
  }
}

void makeCloud() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (cloud[i][j] == -1) {
        cloud[i][j] = 0;
        continue;
      }

      if (baskets[i][j] >= 2) {
        cloud[i][j] = 1;
        baskets[i][j] -= 2;
      }
    }
  }
}

void solve() {
  setCloud();

  for (int i = 0; i < m; i++) {
    int direction, distance;
    cin >> direction >> distance;

    moveCloud(direction, distance);

    rain();

    replicate();

    removeCloud();

    makeCloud();
  }


  cout << getTotalWater() << '\n';
}

int run() {
  cin >> n >> m;

  for (int i = 0; i < n; i++)  {
    for (int j = 0; j < n; j++) {
      cin >> baskets[i][j];
    }
  }

  solve();

  return 0;
}