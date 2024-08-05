#include <iostream>

using namespace std;

typedef struct _KNIGHT {
  int r;
  int c;
  int h;
  int w;
  int k;
} KNIGHT;

typedef struct _COORDINATE {
  int x;
  int y;
} COORDINATE;

int wallLen, knightNum, orderNum, board[50][50], knightBoard[50][50];

int totalDamage[40] = {0, };

KNIGHT knights[40];

int damageTotal = 0;

int knightMoved[50] = {0, };

int newKnightBoard[50][50] = {0, };

bool moveKnight(int id, int dirIdx) {
  COORDINATE direction[4] = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1}
  };

  knightMoved[id] = 1;

  int x = knights[id].r;
  int y = knights[id].c;

  for (int i = 0; i < knights[id].h; i++) {
    for (int j = 0; j < knights[id].w; j++) {
      int nx = x + i + direction[dirIdx].x;
      int ny = y + j + direction[dirIdx].y;

      if (nx <= 0 || nx > wallLen || ny <= 0 || ny > wallLen || board[nx][ny] == 2) {
        return false;
      }

      newKnightBoard[nx][ny] = id;

      if (knightBoard[nx][ny] > 0 && knightBoard[nx][ny] != id) {
        if(!moveKnight(knightBoard[nx][ny], dirIdx)) return false;
      }
    }
  }

  knights[id].r += direction[dirIdx].x;
  knights[id].c += direction[dirIdx].y;

  return true;
}

void clearNewKnightBoard() {
  for (int i = 0; i <= wallLen; i++) {
    for (int j = 0; j <= wallLen; j++) {
      newKnightBoard[i][j] = 0;
    }
  }

  for (int i = 1; i <= knightNum; i++) {
    knightMoved[i] = 0;
  }
}

void putNewKnightBoard() {
  for (int i = 1; i <= wallLen; i++) {
    for (int j = 1; j <= wallLen; j++) {
      knightBoard[i][j] = newKnightBoard[i][j];
    }
  }
}

void eraseKnight(int id) {
  for (int i = 1; i <= wallLen; i++) {
    for (int j = 1; j <= wallLen; j++) {
      if (knightBoard[i][j] == id) knightBoard[i][j] = 0;
    }
  }
}

void damageKnights() {
  int damage[40] = {0, };

  for (int i = 1; i <= wallLen; i++) {
    for (int j = 1; j <= wallLen; j++) {
      if (board[i][j] == 1 && knightBoard[i][j] > 0) {
        damage[knightBoard[i][j]]++;
      }
    }
  }

  for (int i = 1; i <= knightNum; i++) {
    if (!knightMoved[i]) continue;

    knights[i].k -= damage[i];

    if (knights[i].k <= 0) {
      continue;
      eraseKnight(i);
    }

    totalDamage[i] += damage[i];
  }
}

int getTotalDamage() {
  int ans = 0;
  
  for (int i = 1; i <= knightNum; i++) {
    // if (knights[i].k <= 0) continue;
    ans += totalDamage[i];
  }

  return ans;
}

void printKnightBoard() {
  for (int i = 1; i <= wallLen; i++) {
    for (int j = 1; j <= wallLen; j++) {
      cout << knightBoard[i][j] << ' ';
    }
    cout << '\n';
  }
  cout << '\n';
}

void putOldKnightBoard() {
  for (int id = 1; id <= knightNum; id++) {
    if (knightMoved[id] == 0) {
      for (int i = knights[id].r; i < knights[id].r + knights[id].h; i++) {
        for (int j = knights[id].c; j < knights[id].c + knights[id].w; j++) {
          newKnightBoard[i][j] = id;
        }
      }
    }
  }
}

void solve() {
  for (int order_cnt = 0; order_cnt < orderNum; order_cnt++) {
    int knightId, direction;
    cin >> knightId >> direction;

    if (knights[knightId].k <= 0) continue;

    clearNewKnightBoard();

    if (moveKnight(knightId, direction)) {
      putOldKnightBoard();

      putNewKnightBoard();

      knightMoved[knightId] = 0;

      damageKnights();
    }

    // printKnightBoard();
  }

  cout << getTotalDamage() << '\n';
}

int run() {
  cin >> wallLen >> knightNum >> orderNum;

  for (int i = 1; i <= wallLen; i++) {
    for (int j = 1; j <= wallLen; j++) {
      cin >> board[i][j];
    }
  }

  for (int i = 1; i <= knightNum; i++) {
    KNIGHT *tmp = &knights[i];

    cin >> tmp->r >> tmp->c >> tmp->h >> tmp->w >> tmp->k; 
  
    for (int row = 0; row < tmp->h; row++) {
      for (int col = 0; col < tmp->w; col++) {
        knightBoard[tmp->r + row][tmp->c + col] = i;
      }
    }
  }

  solve();

  return 0;
}