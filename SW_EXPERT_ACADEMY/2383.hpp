#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>

#define INF 0x7fffffff
#define STAIR_MAX 2

using namespace std;

typedef struct _COORDINATE {
  int x;
  int y;

  int getDist(_COORDINATE other) {
    return abs(x - other.x) + abs(y - other.y);
  }
} COORDINATE;

typedef struct _STAIR {
  COORDINATE position;
  int length;
} STAIR;

vector<COORDINATE> people;
vector<STAIR> stairs;

vector<int> choices;
int minTime = INF;

void initialize() {
  people.clear();
  stairs.clear();
  choices.clear();
  minTime = INF;
}

void getInput() {
  int n;
  cin >> n;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int tmp;
      cin >> tmp;

      if (tmp == 1) {
        people.push_back({i, j});
      } else if (tmp > 1) {
        stairs.push_back({{i, j}, tmp});
      }
    }
  }
}

void getTime() {
  vector<int> stairEnterTime[STAIR_MAX];

  for (int personId = 0; personId < choices.size(); personId++) {
    int choice = choices[personId];
    STAIR &stair = stairs[choice];

    int distance = people[personId].getDist(stair.position);

    stairEnterTime[choice].push_back(distance);
  }

  for (int stairId = 0; stairId < STAIR_MAX; stairId++) {
    vector<int> &stair = stairEnterTime[stairId];

    sort(stair.begin(), stair.end());
  }

  for (int stairId = 0; stairId < STAIR_MAX; stairId++) {
    vector<int> &stair = stairEnterTime[stairId];

    for (int i = 0; i < stair.size(); i++) {
      if (i < 3) continue;

      int outTime = stair[i-3] + stairs[stairId].length;

      if (outTime > stair[i]) {
        stair[i] = outTime;
      }
    }
  }

  int minOutTime = -1;

  for (int stairId = 0; stairId < STAIR_MAX; stairId++) {
    if (stairEnterTime[stairId].empty()) continue;

    int outTime = stairEnterTime[stairId].back() + stairs[stairId].length + 1;
    if (minOutTime < outTime) minOutTime = outTime;
  }

  if (minOutTime < minTime) minTime = minOutTime;
}

void getMinTime() {
  if (choices.size() == people.size()) {
    getTime();
    return;
  }

  for (int i = 0; i < STAIR_MAX; i++) {
    choices.push_back(i);
    getMinTime();
    choices.pop_back();
  }
}

int solve() {
  initialize();

  getInput();

  getMinTime();

  return minTime;
}

int run() {
  int testCaseNum;
  cin >> testCaseNum;

  for (int i = 1; i <= testCaseNum; i++) {
    cout << "#" << i << ' ' << solve() << '\n';
  }

  return 0;
}