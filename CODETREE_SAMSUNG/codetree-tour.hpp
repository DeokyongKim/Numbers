#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 0x7fffffff

using namespace std;

typedef struct _TRIP {
  int id;
  int revenue;
  int destination;
} TRIP;

int start = 0;

int board[2010][2010], orderNum, n, m, costs[2010];

vector<TRIP> trips;

void printTrips() {
  for (int i = 0; i < trips.size(); i++) {
    cout << trips[i].id << ' ';
  }
  cout << '\n';
}

int visited[2010];
void calculateCosts() {
  for (int i = 0; i < n; i++) costs[i] = 0;
  for (int i = 0; i < n; i++) visited[i] = 0;

  queue<int> q;

  visited[start] = 1;
  q.push(start);

  while(!q.empty()) {
    int cur = q.front();
    q.pop();

    for (int i = 0; i < n; i++) {
      if (!visited[i] && board[cur][i] != INF) {
        visited[i] = 1;
        q.push(i);
        costs[i] = costs[cur] + board[cur][i];
      }
    }
  }

  // for (int i = 0; i < n; i++) cout << costs[i] << ' ';
  // cout << '\n';
}

void changeStartPoint() {
  int point;
  cin >> point;

  start = point;

  calculateCosts();
}

int cancleId;
bool cancleComp(TRIP a, TRIP b) {
  if (b.id == cancleId) return false;
  if (a.id == cancleId) return true;
  return true;
}

void cancleTrip() {
  cin >> cancleId;
  
  sort(trips.begin(), trips.end(), cancleComp);

  if (trips[0].id == cancleId) {
    trips.erase(trips.begin());
  }
}

void makeTrip() {
  int id, revenue, destination;

  cin >> id >> revenue >> destination;

  trips.push_back({id, revenue, destination});
}

void makeCodeTreeLand() {
  cin >> n >> m;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      board[i][j] = INF;
      if (i == j) board[i][j] = 0;
    }
  }

  for (int i = 0; i < m; i++) {
    int from, to, cost;
    cin >> from >> to >> cost;

    if (from != to && board[from][to] > cost) {
      board[from][to] = cost;
      board[to][from] = cost;
    }
  }

  calculateCosts();
}

bool sellComp(TRIP a, TRIP b) {
  return a.revenue - costs[a.destination] > b.revenue - costs[b.destination];
}

void sellBestTrip() {
  sort(trips.begin(), trips.end(), sellComp);
  // printTrips();

  if (trips.size() > 0 && visited[trips[0].destination] && trips[0].revenue - costs[trips[0].destination] >= 0) {
    cout << trips[0].id << '\n';
    trips.erase(trips.begin());
  } else {
    cout << "-1\n";
  }
}

void getOrder() {
  int orderType;
  cin >> orderType;
  // cout << orderType << '\n';

  if (orderType == 100) makeCodeTreeLand();
  if (orderType == 200) makeTrip();
  if (orderType == 300) cancleTrip();
  if (orderType == 400) sellBestTrip();
  if (orderType == 500) changeStartPoint();
}

void solve() {
  for (int i = 0; i < orderNum; i++) {
    getOrder();
  }
}

int run() {
  cin >> orderNum;

  solve();

  return 0;
}