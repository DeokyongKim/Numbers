#include <iostream>
#include <vector>
#include <map>

#define MAX_N 110

using namespace std;

typedef struct _COORDINATE {
  int x;
  int y;
} COORDINATE;

typedef struct _VIRUS {
  COORDINATE location;
  int quantity;
  COORDINATE direction;

  void toOppositeDirection() {
    direction.x *= -1;
    direction.y *= -1;
  }
} VIRUS;

typedef struct _NEXT_POSITION {
  COORDINATE location;
  vector<int> virusIndexes;
} NEXT_POSITION;

int n;
vector<VIRUS> viruses;

vector<int> nextPositions[MAX_N][MAX_N];

void printViruses() {
  int board[MAX_N][MAX_N] = {0, };

  for (int i = 0; i < viruses.size(); i++) {
    const VIRUS &virus = viruses[i];
    COORDINATE cur = virus.location;

    board[cur.x][cur.y] = virus.quantity;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << board[i][j] << ' ';
    }
    cout << '\n';
  }
}

void clearNextPositions() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      nextPositions[i][j].clear();
    }
  }
}

void initialize() {
  viruses.clear();

  clearNextPositions();
}

void getViruses(int virusNum) {
  COORDINATE directions[4] = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1},
  };

  for (int i = 0; i < virusNum; i++) {
    VIRUS virus;
    int dirIdx;
    cin >> virus.location.x >> virus.location.y >> virus.quantity >> dirIdx;
    virus.direction = directions[dirIdx - 1];

    viruses.push_back(virus);
  }
}

int getTotalVirusQuantity() {
  int ans = 0;

  for (int i = 0; i < viruses.size(); i++) {
    ans += viruses[i].quantity;
  }

  return ans;
}

void moveVirus(int virusIndex) {
  VIRUS &virus = viruses[virusIndex];

  virus.location = {virus.location.x + virus.direction.x, virus.location.y + virus.direction.y};

  nextPositions[virus.location.x][virus.location.y].push_back(virusIndex);
}

void moveViruses() {
  for (int i = 0; i < viruses.size(); i++) {
    moveVirus(i);
  }
}

bool isBoundary(COORDINATE a) {
  return a.x == 0 || a.y == 0 || a.x == n-1 || a.y == n-1;
}

void medicationTreatment() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      COORDINATE cur = {i, j};
      if (isBoundary(cur)) {
        for (int vi = 0; vi < nextPositions[i][j].size(); vi++) {
          int virusIndex = nextPositions[i][j][vi];

          VIRUS &virus = viruses[virusIndex];
          virus.quantity /= 2;
          virus.toOppositeDirection();
        }
      }
    }
  }
}

vector<VIRUS> newViruses;

void mergeVirus(vector<int> virusIndexes) {
  // merge
  int maxVirusQuantity = -1;

  VIRUS newVirus;
  newVirus.quantity = 0;

  for (int i = 0; i < virusIndexes.size(); i++) {
    int virusIndex = virusIndexes[i];
    const VIRUS &virus = viruses[virusIndex];

    newVirus.quantity += virus.quantity;

    if (maxVirusQuantity < virus.quantity) {
      maxVirusQuantity = virus.quantity;
      newVirus.location = virus.location;
      newVirus.direction = virus.direction;
    }
  }

  newViruses.push_back(newVirus);
}

void mergeViruses() {
  newViruses.clear();

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (nextPositions[i][j].size() > 1) {
        mergeVirus(nextPositions[i][j]);
      } else if (nextPositions[i][j].size() == 1) {
        newViruses.push_back(viruses[nextPositions[i][j][0]]);
      }
    }
  }

  viruses.clear();
  viruses = newViruses;
}

int solve() {
  initialize();

  int testTime, virusNum;
  cin >> n >> testTime >> virusNum;

  getViruses(virusNum);

  // printViruses();

  for (int i = 0; i < testTime; i++) {
    // cout << "TEST TIME: " << i+1 << '\n';
    
    clearNextPositions();
    
    moveViruses();

    medicationTreatment();

    mergeViruses();

    // printViruses();
    // cout << '\n';
  }

  return getTotalVirusQuantity();
}

int run() {
  int testCases;
  cin >> testCases;

  for (int i = 1; i <= testCases; i++) {
    cout << "#" << i << ' ' << solve() << '\n';
  }

  return 0;
}