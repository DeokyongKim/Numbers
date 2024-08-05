#include <iostream>
#include <queue>

using namespace std;

typedef struct _KNIGHT {
  int row;
  int col;
  int height;
  int width;
  int health;
} KNIGHT;

typedef struct _COORDINATE {
  int x;
  int y;
} COORDINATE;

int L, N, Q, board[50][50], knightBoard[50][50];

KNIGHT knights[40];

int totalDamage[40];

void move(int id, int dir) {
  COORDINATE direction[4] = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1},
  };

  int visited[40] = {0, };

  int newKnightBoard[50][50] = {0, };

  queue<int> q;

  q.push(id);
  visited[id] = 1;

  int dx = direction[dir].x;
  int dy = direction[dir].y;

  while(!q.empty()) {
    int curId = q.front();
    q.pop();

    for (int i = 0; i < knights[curId].height; i++) {
      for (int j = 0; j < knights[curId].width; j++) {
        int x = knights[curId].row + i;
        int y = knights[curId].col + j;

        int nx = x + dx;
        int ny = y + dy;

        if (nx <= 0 || ny <= 0 || nx > L || ny > L || board[nx][ny] == 2) {
          return;
        }

        if (knightBoard[nx][ny] > 0 && !visited[knightBoard[nx][ny]]) {
          visited[knightBoard[nx][ny]] = 1;
          q.push(knightBoard[nx][ny]);
        }

        newKnightBoard[nx][ny] = curId;
      }
    }
  }

  for (int i = 1; i <= N; i++) {
    if (visited[i]) {
      knights[i].row += dx;
      knights[i].col += dy;
    }
  }

  
  for (int i = 1; i <= L; i++) {
    for (int j = 1; j <= L; j++) {
      if (!visited[knightBoard[i][j]] && knightBoard[i][j] > 0) {
        newKnightBoard[i][j] = knightBoard[i][j];
      } 
    }
  }

  for (int i = 1; i <= L; i++) {
    for (int j = 1; j <= L; j++) {
      knightBoard[i][j] = newKnightBoard[i][j];
    }
  }

  // get damage
  visited[id] = 0;

  int eachDamage[40] = {0, };

  for (int i = 1; i <= L; i++) {
    for (int j = 1; j <= L; j++) {
      eachDamage[knightBoard[i][j]] += (board[i][j] == 1);
    }
  }

  for (int i = 1; i <= N; i++) {
    if (visited[i]) {
      totalDamage[i] += eachDamage[i];
    
      knights[i].health -= eachDamage[i];

      if (knights[i].health <= 0) {
        for (int row = knights[i].row; row < knights[i].row + knights[i].height; row++) {
          for (int col = knights[i].col; col < knights[i].col + knights[i].width; col++) {
            knightBoard[row][col] = 0;
          }
        }
      }
    }
  }

  // for (int i = 1; i <= L; i++) {
  //   for (int j = 1; j <= L; j++) {
  //     cout << knightBoard[i][j] << ' ' ;
  //   }
  //   cout << '\n';
  // }
  // cout << '\n';
}

void order() {
  int id, dir;
  cin >> id >> dir;

  if (knights[id].health <= 0) return;

  move(id, dir);
}

int getTotalDamage() {
  int ans = 0;

  for (int i = 1; i <= N; i++) {
    if (knights[i].health > 0) ans += totalDamage[i];
  }

  return ans;
}

int run() {
  cin >> L >> N >> Q;

  for (int i = 1; i <= L; i++) {
    for (int j = 1; j <= L; j++) {
      cin >> board[i][j];
    }
  }

  for (int id = 1; id <= N; id++) {
    cin >> knights[id].row >> knights[id].col >> knights[id].height >> knights[id].width>> knights[id].health;
  
    for (int i = 0; i < knights[id].height; i++) {
      for (int j = 0; j < knights[id].width; j++) {
        knightBoard[knights[id].row + i][knights[id].col + j] = id;
      }
    }
  }

  for (int order_num = 0; order_num < Q; order_num++) {
    order();
  }

  cout << getTotalDamage() << '\n';

  return 0;
}