#include <iostream>
#include <vector>

using namespace std;

typedef struct _FIREBALL {
  int x;
  int y;
  int mass;
  int speed;
  int dirIdx;
} FIREBALL;

typedef struct _DIRECTION {
  int dx;
  int dy;
} DIRECTION;

DIRECTION direction[8] = {
  {-1, 0},
  {-1, 1},
  {0, 1},
  {1, 1},
  {1, 0},
  {1, -1},
  {0, -1},
  {-1, -1}
};

vector<FIREBALL> fireball;

int n, fireBallNum, orderNum;

void moveFireBalls() {
  vector<int> board[55][55];

  // 1
  for (int i = 0; i < fireball.size(); i++) {
    if (fireball[i].mass <= 0) continue;

    int cx = fireball[i].x;
    int cy = fireball[i].y;
    int dx = direction[fireball[i].dirIdx].dx;
    int dy = direction[fireball[i].dirIdx].dy;
    int nx = cx + dx * fireball[i].speed;
    int ny = cy + dy * fireball[i].speed;

    if (nx < 0) {
      nx = nx % n + n;
    } 
    // IMPORTANT!!!!!!
    // IF nx == -4, n == 4 -> nx = n after first if statement!!
    if (nx >= n) {
      nx = nx % n;
    }

    if (ny < 0) {
      ny = ny % n + n;
    } 
    if (ny >= n) {
      ny = ny % n;
    }

    fireball[i].x = nx;
    fireball[i].y = ny;
    board[nx][ny].push_back(i);
  }

  // 2
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (board[i][j].size() >= 2) {
        int massSum = 0;
        int speedSum = 0;
        int cnt = 0;
        int dirStandard = -1;
        bool isDirSame = true;
        for (int k = 0; k < board[i][j].size(); k++) {
          int idx = board[i][j][k];

          massSum += fireball[idx].mass;
          speedSum += fireball[idx].speed;
          cnt++;

          fireball[idx].mass = 0;
          
          if (dirStandard == -1) dirStandard = fireball[idx].dirIdx;
          else {
            if (dirStandard % 2 != fireball[idx].dirIdx % 2) isDirSame = false;
          }
        }

        int newMass = massSum / 5;
        int newSpeed = speedSum / cnt;

        if (newMass > 0) {
          for (int k = 0; k < 4; k++) {
            int newDir = k * 2 + (isDirSame ? 0 : 1);
            fireball.push_back({
              i,
              j,
              newMass,
              newSpeed,
              newDir
            });
          }
        }

      }
      board[i][j].clear();
    }
  }

  // for (int i = 0; i < n; i++) {
  //   for (int j = 0; j < n; j++) {
  //     if (board[i][j].size()) {
  //       cout << board[i][j][0] << '\t' ;
  //     } else {
  //       cout << -1 << '\t';
  //     }
  //   }
  //   cout << '\n';
  // }
  // cout << '\n';

  // for (int i = 0; i < fireball.size(); i++) {
  //   if (fireball[i].mass <= 0) continue;
  //   cout << i << ": " << fireball[i].x << ' ' << fireball[i].y << ' ' << fireball[i].mass << '\n';
  // }
  // cout << '\n';
}

void solve() {
  // for (int i = 0; i < fireball.size(); i++) {
  //   if (fireball[i].mass <= 0) continue;
  //   cout << i << ": " << fireball[i].x << ' ' << fireball[i].y << ' ' << fireball[i].mass << '\n';
  // }
  // cout << '\n';

  for (int moveNum = 0; moveNum < orderNum; moveNum++) {
    moveFireBalls();
  }

  int ans = 0;
  for (int i = 0; i < fireball.size(); i++) {
    if (fireball[i].mass > 0) ans += fireball[i].mass;
  }

  cout << ans << '\n';
}

int run() {
  cin >> n >> fireBallNum >> orderNum;

  for (int i = 0; i < fireBallNum; i++) {
    FIREBALL tmp;
    cin >> tmp.x >> tmp.y >> tmp.mass >> tmp.speed >> tmp.dirIdx;

    fireball.push_back({
      tmp.x-1,
      tmp.y-1,
      tmp.mass,
      tmp.speed,
      tmp.dirIdx
    });
  }

  solve();

  return 0;
}