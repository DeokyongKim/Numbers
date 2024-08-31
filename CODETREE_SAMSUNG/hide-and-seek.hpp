#include <iostream>
#include <vector>

using namespace std;

typedef struct _COORDINATE {
  int x;
  int y;
} COORDINATE;

typedef struct _RUNNER {
  COORDINATE position;
  int type;
  int direction;
} RUNNER;

typedef struct _TAGGER {
  COORDINATE position;
  COORDINATE direction;
  bool backward;
} TAGGER;

COORDINATE runnerDirection[2][2] = {
  {{0, 1}, {0, -1}},
  {{1, 0}, {-1, 0}},
};

int n, runnerNum, treeNum, maxTurn;

int snailBoard[110][110], treeBoard[110][110];

vector<int> board[110][110], nextBoard[110][110];

RUNNER runners[10010];

TAGGER tagger;

int score = 0;

int abs(int a) {
  if (a >= 0) return a;
  else return -1 * a;
}

void setTagger() {
  tagger.position = {(n+1) / 2, (n+1) / 2};
  tagger.backward = false;
  tagger.direction = {-1, 0};
}

void printSnailBoard() {
  for (int i = 1; i <= n; i++) {
    for (int j= 1; j <= n; j++) {
      cout << snailBoard[i][j] << '\t';
    }
    cout << '\n';
  }
  cout << '\n';
}

void setSnailBoard() {
  int x = (n+1) / 2;
  int y = (n+1) / 2;

  int cnt = 1;

  int dir = -1;

  snailBoard[x][y] = cnt++;

  for (int len = 1; len < n; len++) {
    for (int i = 0; i < len; i++) {
      x += dir;
      
      snailBoard[x][y] = cnt++;
    }

    dir *= -1;

    for (int i = 0; i < len; i++) {
      y += dir;
      snailBoard[x][y] = cnt++;
    }
  }

  for (int i = 1; i < n; i++) {
    x--;
    snailBoard[x][y] = cnt++;
  }
}

void getInput() {
  cin >> n >> runnerNum >> treeNum >> maxTurn;

  for (int i = 1; i <= runnerNum; i++) {
    cin >> runners[i].position.x >> runners[i].position.y >> runners[i].type;
    runners[i].direction = 0;
    runners[i].type--;
    board[runners[i].position.x][runners[i].position.y].push_back(i);
  }

  for (int i = 0; i < treeNum; i++) {
    COORDINATE tmp;
    cin >> tmp.x >> tmp.y;
    treeBoard[tmp.x][tmp.y] = 1;
  }
}

bool isRunnerInTaggerRange(int id) {
  COORDINATE rp = runners[id].position;
  COORDINATE tp = tagger.position;

  return (abs(rp.x - tp.x) + abs(rp.y - tp.y) <= 3);
}

bool isRunnerNextMoveOutOfBoarder(int id) {
  int dx = runnerDirection[runners[id].type][runners[id].direction].x;
  int dy = runnerDirection[runners[id].type][runners[id].direction].y;

  int x = runners[id].position.x;
  int y = runners[id].position.y;

  int nx = x + dx;
  int ny = y + dy;

  if (nx < 1 || nx > n || ny < 1 || ny > n) return true;
  return false;
}

void moveRunnerIfRunnerCan(int id) {
  int dx = runnerDirection[runners[id].type][runners[id].direction].x;
  int dy = runnerDirection[runners[id].type][runners[id].direction].y;

  int x = runners[id].position.x;
  int y = runners[id].position.y;

  int nx = x + dx;
  int ny = y + dy;

  if (!(nx == tagger.position.x && ny == tagger.position.y)) {
    runners[id].position = {nx, ny};
    nextBoard[nx][ny].push_back(id);
  } else {
    nextBoard[x][y].push_back(id);
  }
}

void moveRunner(int id) {
  bool outOfBoarder = isRunnerNextMoveOutOfBoarder(id);
  if (outOfBoarder) {
    runners[id].direction = (runners[id].direction + 1) % 2;
    moveRunnerIfRunnerCan(id);
  } else {
    moveRunnerIfRunnerCan(id);
  }
}

void moveRunners() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (board[i][j].size() > 0) {
        for (int k = board[i][j].size()-1; k >= 0 ; k--) {
          if (isRunnerInTaggerRange(board[i][j][k])) {
            moveRunner(board[i][j][k]);
          } else {
            nextBoard[i][j].push_back(board[i][j][k]);
          }
        }
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      board[i][j].clear();
      board[i][j] = nextBoard[i][j];
      nextBoard[i][j].clear();
    }
  }
}

COORDINATE getNextTaggerPosition(bool predict) {
  COORDINATE direction[4] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0},
  };

  int curNum = snailBoard[tagger.position.x][tagger.position.y];
  int nextNum = tagger.backward ? curNum - 1 : curNum + 1;

  if (!predict) {
    if (tagger.backward && nextNum == 1) tagger.backward = false;
    else if (!tagger.backward && nextNum == n * n) tagger.backward = true;
  }

  for (int dir = 0; dir < 4; dir++) {
    int nx = tagger.position.x + direction[dir].x;
    int ny = tagger.position.y + direction[dir].y;

    if (nx < 1 || nx > n || ny < 1 || ny > n) continue;

    if (snailBoard[nx][ny] == nextNum) return {nx, ny};
  }
}

COORDINATE getNextTaggerDirection() {
  if (!tagger.backward && snailBoard[tagger.position.x][tagger.position.y] == n * n) {    return {1, 0};
  }

  if (tagger.backward && snailBoard[tagger.position.x][tagger.position.y] == 1) {
    return {-1, 0};
  }

  COORDINATE nextTaggerPosition = getNextTaggerPosition(true);

  return {
    nextTaggerPosition.x - tagger.position.x,
    nextTaggerPosition.y - tagger.position.y
  };
}

void printTagger() {
  int tmpBoard[110][110] = {0, };

  int x = tagger.position.x;
  int y = tagger.position.y;

  for (int i = 0; i < 3; i++) {
    tmpBoard[x][y] = 1;
    x += tagger.direction.x;
    y += tagger.direction.y;
    if (x < 1 || x > n || y < 1 || y > n) break;
  }
  tmpBoard[tagger.position.x][tagger.position.y] = 2;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cout << tmpBoard[i][j] << ' ' ;
    }
    cout << '\n';
  }
  cout << '\n';
}

void moveTagger() {
  tagger.position = getNextTaggerPosition(false);

  tagger.direction = getNextTaggerDirection();
}

void printBoardSize() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cout << board[i][j].size() << ' ' ;
    }
    cout << '\n';
  }
  cout << '\n';
}

void tagRunners(int turn) {
  int x = tagger.position.x;
  int y = tagger.position.y;

  int dx = tagger.direction.x;
  int dy = tagger.direction.y;

  for (int i = 0; i < 3; i++) {

    if (!treeBoard[x][y] && board[x][y].size()) {
      score += board[x][y].size() * turn;
      board[x][y].clear();
    }

    x += dx;
    y += dy;

    if (x < 1 || x > n || y < 1 || y > n) break;
  }
}

void playOneTurn(int turn) {
  moveRunners();

  moveTagger();

  // printBoardSize();

  tagRunners(turn);

  // cout << "SCORE: " << score << '\n';
}

void playHideAndSeek() {
  for (int i = 0; i < maxTurn; i++) {
    // cout << "TURN : " << i+1 << '\n';
    playOneTurn(i+1);
  }
}

int run() {
  getInput();

  setSnailBoard();

  setTagger();

  playHideAndSeek();

  cout << score << '\n';

  return 0;
}