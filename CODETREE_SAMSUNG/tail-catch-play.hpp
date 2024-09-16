#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 25
#define MAX_TEAM 8

using namespace std;

typedef struct _COORDINATE {
  int x;
  int y;
} COORDINATE;

typedef struct _PERSON {
  COORDINATE position;
  int type;
} PERSON;

int board[MAX_N][MAX_N], totalScore, n, teamNum, roundNum;

bool isBackward[MAX_TEAM];

vector<vector<PERSON> > group;

void printBoard() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << board[i][j] << ' ';
    }
    cout << '\n';
  }
  cout << "GROUPS:\n";

  for (int i = 0; i < group.size(); i++) {
    for (int j = 0; j < group[i].size(); j++) {
      cout << '{' << group[i][j].position.x << ", " << group[i][j].position.y << "} : " << group[i][j].type << ", ";
    }
    cout << '\n';
  }

  cout << "IS BACKWARD?: ";
  for (int i = 0; i < group.size(); i++) cout << isBackward[i] << ' ';
  cout << '\n';

  cout << '\n';
}

bool isOutOfBound(COORDINATE position) {
  if (position.x < 0) return true;
  if (position.y < 0) return true;
  if (position.x >= n) return true;
  if (position.y >= n) return true;
  return false;
}

void grouping(COORDINATE position) {
  COORDINATE directions[4] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0},
  };

  int visited[MAX_N][MAX_N] = {0, };

  queue<COORDINATE> q;
  vector<PERSON> team;

  visited[position.x][position.y] = 1;
  q.push(position);

  team.push_back({
    position,
    board[position.x][position.y],
  });

  while (!q.empty()) {
    COORDINATE current = q.front();
    q.pop();

    board[current.x][current.y] = group.size() + 5;

    COORDINATE next = {-1, -1};
    int nextNum = -1;

    for (int i = 0; i < 4; i++) {
      int dx = directions[i].x;
      int dy = directions[i].y;

      int nx = current.x + dx;
      int ny = current.y + dy;

      if (!isOutOfBound({nx, ny}) && !visited[nx][ny] && board[nx][ny] < 4 && board[nx][ny] > 1) {
        if (nextNum == -1) {
          nextNum = board[nx][ny];
          next = {nx, ny};
        } else if (nextNum > board[nx][ny]) {
          nextNum = board[nx][ny];
          next = {nx, ny};
        }
      }
    }

    if (next.x != -1) {
      q.push(next);
      visited[next.x][next.y] = 1;
      team.push_back({
        next,
        board[next.x][next.y],
      });
    }
  }

  group.push_back(team);
}

void identify() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (board[i][j] == 1) {
        grouping({i, j});
      }
    }
  }
}

COORDINATE getNextPosition(COORDINATE position) {
  COORDINATE directions[4] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0},
  };

  for (int i = 0; i < 4; i++) {
    int dx = directions[i].x;
    int dy = directions[i].y;

    int nx = position.x + dx;
    int ny = position.y + dy;

    if (!isOutOfBound({nx, ny}) && board[nx][ny] == 4) return {nx, ny};
  }

  // cout << "SECOND!\n";

  for (int i = 0; i < 4; i++) {
    int dx = directions[i].x;
    int dy = directions[i].y;

    int nx = position.x + dx;
    int ny = position.y + dy;

    int teamId = board[position.x][position.y] - 5;
    int tail = isBackward[teamId] ? 3 : 1;
    int tailIdx = !isBackward[teamId] ? group[teamId].size() - 1 : 0;

    // cout << group[teamId][tailIdx].position.x << " : " << group[teamId][tailIdx].position.y << '\n';

    if (!isOutOfBound({nx, ny}) && group[teamId][tailIdx].position.x == nx && group[teamId][tailIdx].position.y == ny) return {nx, ny};
  }
}

int newBoard[MAX_N][MAX_N] = {0, };

void moveTeam(int id) {
  int start = !isBackward[id] ? 0 : group[id].size() - 1;
  int end = isBackward[id] ? -1 : group[id].size();
  int plus = !isBackward[id] ? 1 : - 1;


  vector<PERSON> team;
  PERSON person = {
    getNextPosition(group[id][start].position),
    group[id][start].type,
  };
  // cout << "START: " << group[id][start].position.x << ", "<< group[id][start].position.y<< '\n';

  // cout << person.position.x << ' ' << person.position.y << '\n';

  for (int i = start; i != end; i += plus) {
    PERSON tmp = group[id][i];
    int teamId = board[group[id][i].position.x][group[id][i].position.y];
    team.push_back({
      person.position,
      group[id][i].type,
    });
    newBoard[person.position.x][person.position.y] = teamId;
    person = tmp;
  }

  group[id].clear();
  group[id] = team;
}

void moveTeams() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      newBoard[i][j] = board[i][j];

      if (newBoard[i][j] > 0) newBoard[i][j] = 4;
    }
  }

  for (int i = 0; i < group.size(); i++) {
    moveTeam(i);
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      board[i][j] = newBoard[i][j];
    }
  }
}

COORDINATE getBallDirection(int roundCnt) {
  COORDINATE directions[4] = {
    {0, 1},
    {-1, 0},
    {0, -1},
    {1, 0},
  };

  // cout << roundCnt << ", " << n << ", " << roundCnt / n << '\n';

  return directions[roundCnt / n];
}

COORDINATE getBallStartPoint(int roundCnt) {
  if (roundCnt / n == 0) return {roundCnt % n, 0};
  if (roundCnt / n == 1) return {n-1, roundCnt % n};
  if (roundCnt / n == 2) return {n-1 - roundCnt % n, n-1};
  if (roundCnt / n == 3) return {0, n-1 - roundCnt % n};
}

void addPoint(COORDINATE point) {
  int teamId = board[point.x][point.y] - 5;

  int start = !isBackward[teamId] ? 0 : group[teamId].size() - 1;
  int end = isBackward[teamId] ? -1 : group[teamId].size();
  int plus = !isBackward[teamId] ? 1 : - 1;

  int cnt = 1;

  // cout << point.x << ", " << point.y << '\n';

  for (int i = start; i != end; i += plus) {
    if (group[teamId][i].position.x == point.x && group[teamId][i].position.y == point.y) {
      totalScore += (cnt * cnt);
      // cout << cnt << '\n';
      // cout << totalScore << '\n';
    }
    cnt++;
  }

  isBackward[teamId] = true;
}

void throwBall(int roundCnt) {
  COORDINATE ballDirection = getBallDirection(roundCnt);
  COORDINATE ballStartPoint = getBallStartPoint(roundCnt);

  // cout << "BALL START: " << ballStartPoint.x << ", " << ballStartPoint.y << '\n';
  // cout << "BALL DIRECTION: " << ballDirection.x << ", " << ballDirection.y << '\n';
  
  for (COORDINATE point = ballStartPoint; !isOutOfBound(point); point = {point.x + ballDirection.x, point.y + ballDirection.y}) {
    if (board[point.x][point.y] > 4) {
      // cout << point.x << ", " << point.y << '\n';
      // cout << "HIT: " << board[point.x][point.y] << '\n';
      addPoint(point);
      break;
    }
  }
}

void round(int roundCnt) {
  moveTeams();

  for (int i = 0; i < group.size(); i++) isBackward[i] = false;

  throwBall(roundCnt % (4 * n));
  // printBoard();
}

void solve() {
  // printBoard();

  for (int i = 0; i < roundNum; i++) {
    // cout << "+++++++++++++++ROUND " << i+1 << "+++++++++++++++++\n";
    round(i);
  }

  cout << totalScore << '\n';
}

int run() {
  cin >> n >> teamNum >> roundNum;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> board[i][j];
    }
  }

  identify();

  solve();

  return 0;
}