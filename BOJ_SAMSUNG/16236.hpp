// Gold

#include <iostream>
#include <queue>

using namespace std;

typedef struct _SHARK {
  int x;
  int y;
  int size;
  int ate;
} SHARK;

int n, map[25][25], fishes[10], ans;

SHARK shark;

bool isEnd() {
  for (int i = 1; i <= 6; i++)
    if (i < shark.size && fishes[i] > 0) return false;

  return true;
}

void findNextFish() {
  queue<SHARK> q;
  int visited[25][25] = {0, };

  q.push({shark.x, shark.y, 0});
  visited[shark.x][shark.y] = 1;

  while(!q.empty()) {
    SHARK curShark = q.front();
    q.pop();

    int curX = curShark.x;
    int curY = curShark.y;
    int curCnt = curShark.size;

    if (map[curX][curY] > 0 && map[curX][curY] < shark.size) {
      cout << curX << ' ' << curY << '\n';

      map[shark.x][shark.y] = 0;
      shark.x = curX;
      shark.y = curY;
      shark.ate++;
      fishes[map[shark.x][shark.y]]--;
      map[shark.x][shark.y] = 0;

      if (shark.ate == shark.size) {
        shark.size++;
        shark.ate = 0;
      }

      ans += curCnt;
      return;
    } 
    
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, -1, 0, 1};
    for (int dir = 0; dir < 4; dir++) {
      int nx = curX + dx[dir];
      int ny = curY + dy[dir];

      if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
        if (!visited[nx][ny]) {
          if (map[nx][ny] <= shark.size) {
            q.push({nx, ny, curCnt+1});
            visited[nx][ny] = 1;
          }
        }
      }
    }
  }
}

int run() {
  cin >> n;

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      cin >> map[i][j];
      if (map[i][j] == 9) {
        shark.x = i;
        shark.y = j;
        shark.size = 2;
        shark.ate = 0;
      } else {
        fishes[map[i][j]]++;
      }
    }

  while(!isEnd()) {
    findNextFish();
  }

  cout << ans << '\n';

  return 0;
}