#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 22
#define INF 0x7fffffff

using namespace std;

typedef struct _COORDINATE {
  int x;
  int y;

  bool operator == (_COORDINATE& other) {
    return x == other.x && y == other.y;
  }
} COORDINATE;

typedef struct _PLAYER {
  COORDINATE position;
  int direction;
  int basicAttack;
  int gun;
  int score;
} PLAYER;

int n, maxRound;

vector<PLAYER> players;

priority_queue<int, vector<int>, less<int> > board[MAX_N][MAX_N];

COORDINATE directions[4] = {
  {-1, 0},
  {0, 1},
  {1, 0},
  {0, -1},
};

int getOppositeDirectionIndex(int directionIndex) {
  return (directionIndex + 2) % 4;
}

bool isOutOfBound(int x, int y) {
  if (x < 0 || x >= n || y < 0 || y >= n) return true;
  return false;
}

void movePlayer(PLAYER& player) {
  int directionIndex = player.direction;

  int x = player.position.x;
  int y = player.position.y;
  int dx = directions[directionIndex].x;
  int dy = directions[directionIndex].y;

  int nx = x + dx;
  int ny = y + dy;

  if (isOutOfBound(nx, ny)) {
    player.direction = getOppositeDirectionIndex(directionIndex);
    directionIndex = player.direction;

    dx = directions[directionIndex].x;
    dy = directions[directionIndex].y;

    nx = x + dx;
    ny = y + dy;

    player.position = {nx, ny};
  } else {
    player.position = {nx, ny};
  }
}

int getOtherPlayerId(int id) {
  COORDINATE cur = players[id].position;

  for (int i = 0; i < players.size(); i++) {
    if (i == id) continue;

    if (cur == players[i].position) return i;
  }

  return -1;
}

bool isGunThere(const PLAYER& player) {
  return !board[player.position.x][player.position.y].empty();
}

bool isGunMorePowerful(const PLAYER& player) {
  if (board[player.position.x][player.position.y].empty()) return false;
  return player.gun < board[player.position.x][player.position.y].top();
}

void dropGun(PLAYER& player) {
  int oldGun = player.gun;
  if (oldGun > 0) board[player.position.x][player.position.y].push(oldGun);
  player.gun = 0;
}

void swapGun(PLAYER& player) {
  int newGun = board[player.position.x][player.position.y].top();
  board[player.position.x][player.position.y].pop();

  dropGun(player);
  player.gun = newGun;
}

void changeGun(PLAYER& player) {
  if (isGunThere(player) && isGunMorePowerful(player)) {
    swapGun(player);
  }
}

vector<PLAYER*> getWinnerAndLoser(PLAYER& a, PLAYER& b) {
  vector<PLAYER*> ans;
  
  if (a.gun + a.basicAttack == b.gun + b.basicAttack) {
    if (a.basicAttack > b.basicAttack) {
      ans.push_back(&a);
      ans.push_back(&b);
    } else {
      ans.push_back(&b);
      ans.push_back(&a);
    }
  } else {
    if (a.gun + a.basicAttack > b.gun + b.basicAttack){
      ans.push_back(&a);
      ans.push_back(&b);
    } else {
      ans.push_back(&b);
      ans.push_back(&a);
    }
  }

  return ans;
}

bool isEmpty(int x, int y) {
  COORDINATE cur = {x, y};

  for (int i = 0; i < players.size(); i++) {
    if (players[i].position == cur) return false;
  }
  return true;
}

void moveLoser(PLAYER& player) {
  int x = player.position.x;
  int y = player.position.y;

  int dx, dy, nx, ny;

  while(true) {
    dx = directions[player.direction].x;
    dy = directions[player.direction].y;

    nx = x + dx;
    ny = y + dy;

    if (isOutOfBound(nx, ny) || !isEmpty(nx, ny)) {
      player.direction = (player.direction + 1) % 4;
    } else {
      break;
    }
  }

  player.position = {nx, ny};
}

void eachRound() {
  for (int i = 0; i < players.size(); i++) {
    PLAYER& player = players[i];

    movePlayer(player);
    
    int otherPlayerId = getOtherPlayerId(i);

    if (otherPlayerId == -1) {
      changeGun(player);
    } else {
      PLAYER& otherPlayer = players[otherPlayerId];

      vector<PLAYER*> winnerAndLoser = getWinnerAndLoser(player, otherPlayer);
      PLAYER& winner = *winnerAndLoser[0];
      PLAYER& loser = *winnerAndLoser[1];

      int score = (winner.basicAttack + winner.gun) - (loser.basicAttack + loser.gun);

      winner.score += score;

      dropGun(loser);

      moveLoser(loser);
      changeGun(loser);

      changeGun(winner);
    }
  }
}

void solve() {
  for (int i = 0; i < maxRound; i++) {
    eachRound();
  }

  for (int i = 0; i < players.size(); i++) {
    cout << players[i].score << ' ';
  }
  cout << '\n';
}

void getInput() {
  int m;

  cin >> n >> m >> maxRound;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int tmp;
      cin >> tmp;

      if (tmp > 0) board[i][j].push(tmp);
    }
  }

  for (int i = 0; i < m; i++) {
    PLAYER player;

    cin >> player.position.x >> player.position.y >> player.direction >> player.basicAttack;

    player.position.x--;
    player.position.y--;

    player.gun = 0;
    player.score = 0;

    players.push_back(player);
  }
}

int run() {
  getInput();

  solve();

  // n = 4;

  // PLAYER a, b;
  // a.position = {0, 0};
  // a.direction = 1;
  // a.basicAttack = 10;
  // a.gun = 20;

  // b.position = {1,1};
  // b.direction = 0;
  // b.basicAttack = 2;
  // b.gun = 1;

  // vector<PLAYER*> winnerAndLoser = getWinnerAndLoser(a, b);

  // PLAYER& winner = *winnerAndLoser[0];
  // cout << "BEFORE: " << winner.position.x << ", " << winner.position.y << " : " << winner.direction << '\n';
  // movePlayer(winner);
  // cout << "AFTER: " << winner.position.x << ", " << winner.position.y << " : " << winner.direction << '\n';

  return 0;
}