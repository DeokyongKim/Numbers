#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_PEOPLE 10
#define MAX_STAIR 2
#define INF 0x7fffffff

using namespace std;

int abs(int a) {
  return a < 0 ? -1 * a : a;
}

typedef struct _COORDINATE {
  int x;
  int y;
} COORDINATE;

typedef struct _STAIR {
  COORDINATE location;
  int length;
  vector<int> entered;
  vector<int> waitings;
} STAIR;

vector<STAIR> stairs;
typedef struct _PERSON {
  int id;
  COORDINATE location;

  int dist(int stairId) {
    COORDINATE cur = {location.x, location.y};
    return abs(cur.x - stairs[stairId].location.x) + abs(cur.y - stairs[stairId].location.y);
  }
} PERSON;

int n;
vector<PERSON> people;

void initialize() {
  people.clear();
  stairs.clear();
}

void getInput() {
  cin >> n;

  int cnt = 0;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int tmp;
      cin >> tmp;

      if (tmp == 1) {
        PERSON person;
        person.id = cnt++;
        person.location = {i, j};
        people.push_back(person);
      } else if (tmp > 1) {
        STAIR stair;
        stair.location = {i, j};
        stair.length = tmp;
        stairs.push_back(stair);
      }
    }
  }
}

int minTime = INF;

bool isAllVisited(int visited[MAX_PEOPLE]) {
  for (int i = 0; i < people.size(); i++) {
    if (!visited[i]) return false;
  }
  return true;
}

bool isPassed(int curTime, int visited[MAX_PEOPLE]) {
  for (int i = 0; i < people.size(); i++) {
    if (!visited[i] && people[i].dist(0) < curTime && people[i].dist(1) < curTime) {
      return true;
    }
  }
  return false;
}

vector<pair<int, int> > getMinPersonAndStairs(int curTime, int visited[MAX_PEOPLE]) {
  vector<pair<int, int> > ans;

  for (int i = 0; i < people.size(); i++) {
    PERSON &person = people[i];
    
    if (!visited[i]) {
      if (person.dist(0) == curTime) {
        ans.push_back({i, 0});
      }
      if (person.dist(1) == curTime) {
        ans.push_back({i, 1});
      }
    }
  }

  return ans;
}

void dp(int curTime, int visited[MAX_PEOPLE], int lastOutTime) {
  if (isPassed(curTime, visited)) {
    cout << "AT " << curTime << " ALL PASSED\n";
    
    return;
  }

  if (isAllVisited(visited)) {
    cout << "AT " << curTime << " ALL VISITED\n";
    if (minTime > lastOutTime) minTime = lastOutTime;
    return;
  }

  for (int stairId = 0; stairId < MAX_STAIR; stairId++) {
    STAIR &stair = stairs[stairId];

    for (int i = stair.entered.size() - 1; i >= 0; i--) {
      if (stair.entered[i] + stair.length >= curTime) {
      cout << "ENTERED OUT AT " << curTime << "\n";
        stair.entered.erase(stair.entered.begin() + i);
      }
    }

    for (int i = stair.waitings.size() - 1; i >= 0; i--) {
      if (stair.entered.size() < 3) {
      cout << "WAITING: " << stair.waitings[i] << " ENTERED AT " << curTime << "\n";
        stair.entered.push_back(curTime);
        stair.waitings.erase(stair.waitings.begin() + i);

        if (curTime + stair.length > lastOutTime) {
          lastOutTime = curTime + stair.length;
        }
      }
    }
  }

  vector<pair<int, int> > minPersonAndStairs = getMinPersonAndStairs(curTime, visited);
  for (int index = 0; index < minPersonAndStairs.size(); index++) {
    cout << "DOING\n";
    int peopleId = minPersonAndStairs[index].first;
    int minStairId = minPersonAndStairs[index].second;

    PERSON &person = people[peopleId];
    STAIR &stair = stairs[minStairId];

    if (person.dist(minStairId) == curTime) {
      cout << "PUSHED " << peopleId << " TO " << minStairId << '\n';
      visited[peopleId] = 1;
      stair.waitings.push_back(peopleId);
      dp(curTime + 1, visited, lastOutTime);
      visited[peopleId] = 0;
      stair.waitings.pop_back();
    }

    dp(curTime + 1, visited, lastOutTime);
  }
  
}

int getShortestTime() {
  int visited[MAX_PEOPLE] = {0, };

  dp(0, visited, -1);

  return minTime;
}

int solve() {
  initialize();

  getInput();

  return getShortestTime();
}

int run() {
  int maxTest;
  cin >> maxTest;

  for (int i = 0; i < maxTest; i++) {
    cout << "#" << i+1 << ' ' << solve() << '\n';
  }

  return 0;
}