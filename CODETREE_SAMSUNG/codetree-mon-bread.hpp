#include <iostream>
#include <vector>
#include <queue>

#define INF 0x7fffffff
#define MAX_N 20

using namespace std;

typedef struct _COORDINATE {
  int x;
  int y;

  bool operator == (_COORDINATE& other) {
    return x == other.x && y == other.y;
  }

  bool operator != (_COORDINATE& other) {
    return x != other.x || y != other.y;
  }
} COORDINATE;

typedef struct _PERSON {
  COORDINATE position;
  COORDINATE destination;
  vector<COORDINATE> path;
} PERSON;

int n, unableBoard[MAX_N][MAX_N];

vector<COORDINATE> basecamps;
vector<PERSON> people;

bool isSameCoordi(COORDINATE a, COORDINATE b) {
  return a.x == b.x && a.y == b.y;
}

void getInput() {
  int m;
  cin >> n >> m;
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int tmp;
      cin >> tmp;
      if (tmp) basecamps.push_back({i, j});
    }
  }

  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    people.push_back({{-1, -1}, {x-1, y-1}});
  }
}

bool isOutOfBound(int x, int y) {
  if (x < 0 || x >= n || y < 0 || y >= n) return true;
  return false;
}

bool isEveryoneArrived() {
  for (int i = 0; i < people.size(); i++) {
    if (people[i].position != people[i].destination) return false;
  }
  return true;
}

vector<COORDINATE> getShortestPath(COORDINATE start, COORDINATE end) {
  COORDINATE directions[4] = {
    {-1, 0},
    {0, -1},
    {0, 1},
    {1, 0},
  };

  int visited[MAX_N][MAX_N] = {0, };
  queue<vector<COORDINATE> > q;

  visited[start.x][start.y] = 1;
  q.push({start});

  while(!q.empty()) {
    vector<COORDINATE> path = q.front();
    q.pop();

    COORDINATE cur = path[path.size() - 1];

    if (cur == end) return path;

    int x = cur.x;
    int y = cur.y;

    for (int i = 0; i < 4; i++) {
      int dx = directions[i].x;
      int dy = directions[i].y;

      int nx = x + dx;
      int ny = y + dy;
      if (!isOutOfBound(nx, ny) && !unableBoard[nx][ny] && !visited[nx][ny]) {
        visited[nx][ny] = 1;
        vector<COORDINATE> newPath = path;
        newPath.push_back({nx, ny});
        q.push(newPath);
      }
    }
  }

  return {{-1, -1}};
}

COORDINATE movePerson(PERSON& person) {
  person.path = getShortestPath(person.position, person.destination);

  // if (person.path.size() == 1) cout << "ERROR: PATH\n";

  person.position = person.path[1];

  if (person.position == person.destination) {
    return person.position;
  }

  return {-1, -1};
}

vector<COORDINATE> movePeople(int t) {
  COORDINATE out = {-1, -1};

  vector<COORDINATE> newUnables;
  
  for (int i = 0; i < (t < people.size() ? t : people.size()); i++) {
    PERSON& person = people[i];

    if (person.position == out || person.position == person.destination) continue;

    COORDINATE newUnable = movePerson(person);

    if (newUnable != out) newUnables.push_back(newUnable);
  }

  return newUnables;
}

void markNewUnables(vector<COORDINATE> newUnalbes) {
  for (int i = 0; i < newUnalbes.size(); i++) {
    COORDINATE newUnalbe = newUnalbes[i];

    int x = newUnalbe.x, y = newUnalbe.y;

    unableBoard[x][y] = 1;
  }
}

COORDINATE getClosestBaseCamp(const PERSON& person) {
  int minDistance = INF;
  COORDINATE minBasecamp = {-1, -1}, out = {-1, -1};

  COORDINATE end = person.destination;

  for (int i = 0; i < basecamps.size(); i++) {
    COORDINATE basecamp = basecamps[i];

    if (unableBoard[basecamp.x][basecamp.y]) continue;

    vector<COORDINATE> path = getShortestPath(basecamp, end);

    if (path[0] == out) continue;

    int distance = path.size();

    if (minDistance > distance) {
      minDistance = distance;
      minBasecamp = basecamp;
    } else if (minDistance == distance) {
      if (minBasecamp.x > basecamp.x) {
        minDistance = distance;
        minBasecamp = basecamp;
      } else if (minBasecamp.x == basecamp.x) {
        if (minBasecamp.y  > basecamp.y) {
          minDistance = distance;
          minBasecamp = basecamp;
        }
      }
    }
  }

  return minBasecamp;
}

void getInBaseCamp(int t) {
  if (t >= people.size()) return;

  PERSON& person = people[t];

  COORDINATE basecamp = getClosestBaseCamp(person);

  person.position = basecamp;

  unableBoard[person.position.x][person.position.y] = 1;
}

void printPeople() {
  int board[MAX_N][MAX_N] = {0, };

  for (int i = 0; i < people.size(); i++) {
    PERSON person = people[i];

    int x = person.position.x;
    int y = person.position.y;

    board[x][y] = i + 1;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << board[i][j] << ' ';
    }
    cout << '\n';
  }
  cout << '\n';
}

void solve() {
  int t = 0;

  while (true) {
    // cout << "TIME: " << t+1 << '\n';
     vector<COORDINATE> newUnables = movePeople(t);

    markNewUnables(newUnables);

    getInBaseCamp(t);

    // printPeople();

    if (isEveryoneArrived()) break;

    t++;
  }

  cout << t+1 << '\n';
}

int run() {
  getInput();

  solve();

  return 0;
}