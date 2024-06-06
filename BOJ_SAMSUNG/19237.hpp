#include <iostream>

#define ENDTURN 1000

using namespace std;

typedef struct _PAIR {
  int first;
  int second;
} PAIR;

typedef struct _SHARK {
  int x;
  int y;
  int curDir;
  int nextDir[4][4] = {0, };
} SHARK;

PAIR direction[4] = {
  {-1, 0},
  {1, 0},
  {0, -1},
  {0, 1}
};

PAIR seaSmell[25][25] = {0, };  // [0~][0~] // first : number, second : smell time left

int n, m, smellTime;

int sea[25][25] = {0, }; // sea[0~][0~] sharkNum

SHARK sharks[420] = {0, }; // [1~]

int isDead[420] = {0, };  // [1~]

bool isSharkEmpty() {
  for (int i = 2; i <= m; i++) {
    if (!isDead[i]) return false;
  }
  return true;
}

void makeCurSeaSmell() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (sea[i][j]) {
        seaSmell[i][j] = {sea[i][j], smellTime};
      }
    }
  }
}

void moveSharks() {
  int tmpSea[25][25] = {0, };

  // move sharks
  for (int sharkNum = 1; sharkNum <= m; sharkNum++) {
    if (isDead[sharkNum]) continue;

    int curDir = sharks[sharkNum].curDir;
    int x = sharks[sharkNum].x;
    int y = sharks[sharkNum].y;

    bool foundNext = false;

    // find no smell dir
    for (int dirIdx = 0; dirIdx < 4; dirIdx++) {
      int nextDirIdx = sharks[sharkNum].nextDir[curDir][dirIdx];
      PAIR dir = direction[nextDirIdx];
      int dx = dir.first;
      int dy = dir.second;

      int nx = x + dx;
      int ny = y + dy;

      if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;

      if (!seaSmell[nx][ny].second) {
        // cout << sharkNum << " FOUND! " << curDir+1 << ' ' << nextDirIdx+1 << '\n';
        if (tmpSea[nx][ny]) {
          if (tmpSea[nx][ny] < sharkNum) {
            isDead[sharkNum] = 1;
            foundNext = true;
            break;
          } else {
            isDead[tmpSea[nx][ny]] = 1;
            tmpSea[nx][ny] = sharkNum;

            sharks[sharkNum].x = nx;
            sharks[sharkNum].y = ny;
            sharks[sharkNum].curDir = nextDirIdx;

            foundNext = true;
            break;
          }
        } else {
          tmpSea[nx][ny] = sharkNum;
          sharks[sharkNum].x = nx;
          sharks[sharkNum].y = ny;
          sharks[sharkNum].curDir = nextDirIdx;
          foundNext = true;
          break;
        }
      }
    }
    if (foundNext) {
      continue;
    }

    // find my smell cell
    for (int dirIdx = 0; dirIdx < 4; dirIdx++) {
      int nextDirIdx = sharks[sharkNum].nextDir[curDir][dirIdx];
      PAIR dir = direction[nextDirIdx];
      int dx = dir.first;
      int dy = dir.second;

      int nx = x + dx;
      int ny = y + dy;

      if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;

      if (seaSmell[nx][ny].first == sharkNum && seaSmell[nx][ny].second) {
        if (tmpSea[nx][ny]) {
          if (tmpSea[nx][ny] < sharkNum) {
            isDead[sharkNum] = 1;
            foundNext = true;
            break;
          } else {
            isDead[tmpSea[nx][ny]] = 1;
            tmpSea[nx][ny] = sharkNum;

            sharks[sharkNum].x = nx;
            sharks[sharkNum].y = ny;
            sharks[sharkNum].curDir = nextDirIdx;

            foundNext = true;
            break;
          }
        } else {
          tmpSea[nx][ny] = sharkNum;
          sharks[sharkNum].x = nx;
          sharks[sharkNum].y = ny;
          sharks[sharkNum].curDir = nextDirIdx;
          foundNext = true;
          break;
        }
      }
    }
  }

  // tmpsea to sea
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      sea[i][j] = tmpSea[i][j];
    }
  }
}

void reduceSmell() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (seaSmell[i][j].first) {
        seaSmell[i][j].second--;
        if (!seaSmell[i][j].second) {
          seaSmell[i][j].first = 0;
        }
      }
    }
  }
}

void printSea() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << sea[i][j] << ' ';
    }
    cout << '\n';
  }
}

void solve() {
  int t = 0;

  makeCurSeaSmell();
  
  // printSea();
  // cout << '\n';

  while (t <= ENDTURN) {
    if (isSharkEmpty()) {
      cout << t << '\n';
      return;
    }

    moveSharks();
    reduceSmell();
    makeCurSeaSmell();

    // printSea();
    // cout << "ISDEAD: ";
    // for (int i = 1; i <= m; i++) {
    //   cout << isDead[i] << ' ' ;
    // }
    // cout << "\n\n";

    t++;
  }

  cout << -1 << '\n';
}

int run() {
  cin >> n >> m >> smellTime;

  // get sea
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> sea[i][j];

      if (sea[i][j]) {
        sharks[sea[i][j]].x = i;
        sharks[sea[i][j]].y = j;
      }
    }
  }

  // get shark current direction 
  for (int sharkNum = 1; sharkNum <= m; sharkNum++) {
    cin >> sharks[sharkNum].curDir;
    sharks[sharkNum].curDir--;
  }

  // get shark direction info
  for (int sharkNum = 1; sharkNum <= m; sharkNum++) {
    for (int curDir = 0; curDir < 4; curDir++) {
      for (int nextDir = 0; nextDir < 4; nextDir++) {
        cin >> sharks[sharkNum].nextDir[curDir][nextDir];
        sharks[sharkNum].nextDir[curDir][nextDir]--;
      }
    }
  }

  solve();

  return 0;
}