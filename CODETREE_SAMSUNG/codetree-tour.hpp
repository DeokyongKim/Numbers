// saw answer...

#include <iostream>
#include <vector>
#include <queue>

#define N_MAX 2010
#define ID_MAX 30010
#define INF 0x7fffffff

using namespace std;

struct TRIP {
  int id;
  int revenue;
  int destination;
  int profit;

  struct Comparation {
    bool operator()(const TRIP& a, const TRIP& b) const {
      if (a.profit == b.profit) {
        return a.id > b.id;
      }

      return a.profit < b.profit;
    }
  };
};

priority_queue<TRIP, vector<TRIP>, TRIP::Comparation> trips;

int board[N_MAX][N_MAX], n, costs[N_MAX], isMade[ID_MAX], isCancled[ID_MAX];

int start = 0;

void setOneDimensionArray(int array[N_MAX]) {
  for (int i = 0; i < n; i++) {
    array[i] = INF;
  }
}

void dijkstra() {
  int group[N_MAX] = {0, };

  setOneDimensionArray(costs);

  costs[start] = 0;

  for (int nodeCnt = 1; nodeCnt < n; nodeCnt++) {
    // find closest one
    int target = start, minDist = INF;

    for (int i = 0; i < n; i++) {
      if (!group[i] && minDist > costs[i]) {
        minDist = costs[i];
        target = i;
      }
    }

    group[target] = 1;

    // calculate paths
    for (int i = 0; i < n; i++) {
      if (!group[i] && costs[target] != INF && board[target][i] != INF && costs[i] > costs[target] + board[target][i]) {
        costs[i] = costs[target] + board[target][i];
      }
    }
  }
}

void setBoard() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      board[i][j] = INF;

      if (i == j) board[i][j] = 0;
    }
  }
}

void buildCodtreeLand() {
  int m;
  cin >> n >> m;

  setBoard();

  for (int i = 0; i < m; i++) {
    int v, u, w;

    cin >> v >> u >> w;

    if (board[v][u] > w) {
      board[v][u] = w;
      board[u][v] = w;
    }
  }

  dijkstra();
}

void makeTrip() {
  int id, revenue, destination;

  cin >> id >> revenue >> destination;

  trips.push({
    id,
    revenue,
    destination,
    revenue - costs[destination],
  });
  isMade[id] = 1;
}

void cancleTrip() {
  int id;

  cin >> id;

  if (isMade[id]) isCancled[id] = 1;
}

int bestTrip() {
  while(!trips.empty()) {
    TRIP trip = trips.top();

    if (trip.profit < 0) break;

    trips.pop();

    if (!isCancled[trip.id]) {
      return trip.id;
    }
  }

  return -1;
}

void sellBestTrip() {
  cout << bestTrip() << '\n';
}

void changeStartPoint() {
  int point;

  cin >> point;

  start = point;

  dijkstra();

  vector<TRIP> tmp;

  while(!trips.empty()) {
    tmp.push_back(trips.top());
    trips.pop();
  }

  for (int i = 0; i < tmp.size(); i++) {
    trips.push({
      tmp[i].id,
      tmp[i].revenue,
      tmp[i].destination,
      tmp[i].revenue - costs[tmp[i].destination],
    });
  }
}

void solve() {
  int order;
  cin >> order;

  if (order == 100) buildCodtreeLand();
  if (order == 200) makeTrip();
  if (order == 300) cancleTrip();
  if (order == 400) sellBestTrip();
  if (order == 500) changeStartPoint();
}

int run() {
  int testMax;
  cin >> testMax;

  for (int i = 0; i < testMax; i++) {
    solve();
  }

  return 0;
}