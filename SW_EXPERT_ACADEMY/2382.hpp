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
// vector<COORDINATE> positions;
// map<COORDINATE, vector<int> > nextPositions;

vector<int> nextPositions[MAX_N][MAX_N];

void clearNextPositions() {
  for (int i = 0; i <= n+1; i++) {
    for (int j = 0; j <= n+1; j++) {
      nextPositions[i][j].clear();
    }
  }
}

void initialize() {
  viruses.clear();
  // positions.clear();
  // nextPositions.clear();

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

  // cout << nextPositions[virus.location].empty() << '\n';

  // if (nextPositions[virus.location].size()) {
    // nextPositions[virus.location].push_back(virusIndex);
  // } else {
  //   vector<int> tmp;
  //   tmp.push_back(virusIndex);
  //   positions.push_back(virus.location);
  //   nextPositions[virus.location] = tmp;
  // }

  nextPositions[virus.location.x][virus.location.y].push_back(virusIndex);
}

void moveViruses() {
  for (int i = 0; i < viruses.size(); i++) {
    moveVirus(i);
  }
}

bool isBoundary(COORDINATE a) {
  return a.x == 0 || a.y == 0 || a.x == n+1 || a.y == n+1;
}

void medicationTreatment() {
  for (int positionIndex = 0; positionIndex < positions.size(); positionIndex++) {
    if (isBoundary(positions[positionIndex])) {
      vector<int> &virusIndexes = nextPositions[positions[positionIndex]];
      for (int i = 0; i < virusIndexes.size(); i++) {
        int virusIndex = virusIndexes[i];
        
        viruses[virusIndex].quantity /= 2;
        viruses[virusIndex].toOppositeDirection();
      }
    }
  }

  for (int i = viruses.size() - 1; i >= 0; i--) {
    VIRUS &virus = viruses[i];

    if (virus.quantity == 0) {
      viruses.erase(viruses.begin() + i);
    }
  }
}

void mergeVirus(vector<int> virusIndexes) {
  // merge
  // int maxVirusQuantity = -1;

  // VIRUS newVirus;

  // for (int i = 0; i < virusIndexes.size(); i++) {
  //   int virusIndex = virusIndexes[i];
  //   const VIRUS &virus = viruses[virusIndex];

  //   newVirus.quantity += virus.quantity;

  //   if (maxVirusQuantity < virus.quantity) {
  //     maxVirusQuantity = virus.quantity;
  //     newVirus.location = virus.location;
  //     newVirus.direction = virus.direction;
  //   }
  // }

  // delete
  // for (int i = virusIndexes.size() - 1; i >= 0; i--) {
  //   int virusIndex = virusIndexes[i];
    
  //   viruses.erase(viruses.begin() + virusIndex);
  // }
  
  // push new virus
  // viruses.push_back(newVirus);
}

void mergeViruses() {
  // for (int positionIndex = 0; positionIndex < positions.size(); positionIndex++) {
  //   COORDINATE position = positions[positionIndex];

  //   if (nextPositions[position].size() > 1) {
  //     mergeVirus(nextPositions[position]);
  //   }
  // }
}

int solve() {
  initialize();

  int testTime, virusNum;
  cin >> n >> testTime >> virusNum;

  getViruses(virusNum);
  // cout << "GOT\n";

  for (int i = 0; i < testTime; i++) {
    // positions.clear();
    // nextPositions.clear();
    clearNextPositions();

  // cout << "INITIALIZE\n";
    

    moveViruses();
  // cout << "MOVED\n";


    medicationTreatment();
  // cout << "MDIC\n";


    mergeViruses();
  // cout << "MERED\n";

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