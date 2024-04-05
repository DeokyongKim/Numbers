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

bool doing = true;

void findNextFish() {
  queue<SHARK> q;
  int visited[25][25] = {0, };
  doing = false;

  int minX, minY;

  q.push({shark.x, shark.y, shark.size, 0});
  visited[shark.x][shark.y] = 1;

  while(!q.empty()) {
    SHARK curShark = q.front();
    q.pop();

    int curX = curShark.x;
    int curY = curShark.y;
    int curCnt = curShark.ate;

    if (map[curX][curY] > 0 && map[curX][curY] < shark.size) {
      minX = curX;
      minY = curY;
      
      while(!q.empty()) {
        SHARK tmp = q.front();
        q.pop();
        if (tmp.ate != curCnt) break;
        if (map[tmp.x][tmp.y] == 0 || map[tmp.x][tmp.y] >= shark.size) continue;

        if (minX > tmp.x) {
          minX = tmp.x;
          minY = tmp.y;
        } else if (minX == tmp.x && minY > tmp.y) {
          minX = tmp.x;
          minY = tmp.y;
        }
      }

      map[shark.x][shark.y] = 0;
      shark.x = minX;
      shark.y = minY;
      shark.ate++;
      fishes[map[shark.x][shark.y]]--;
      map[shark.x][shark.y] = 0;

      if (shark.ate == shark.size) {
        shark.size++;
        shark.ate = 0;
      }

      doing = true;
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
            visited[nx][ny] = 1;
            q.push({nx, ny, shark.size, curCnt+1});
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
        map[i][j] = 0;
      } else {
        fishes[map[i][j]]++;
      }
    }

  while(doing) {
    findNextFish();
  }

  cout << ans << '\n';

  return 0;
}