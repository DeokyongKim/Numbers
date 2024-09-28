#include <iostream>
#include <vector>
#include <map>
#include <queue>

#define INF 100010

using namespace std;

int n, m;
long long int bias = 0;

typedef struct _COORDINATE {
  int x;
  int y;

  bool operator == (const _COORDINATE& other) {
    return x == other.x && y == other.y;
  }

  bool operator != (const _COORDINATE& other) {
    return x != other.x || y != other.y;
  }

  bool isOverBoundary() {
    return x < 0 || x >= n || y < 0 || y >= m;
  }
} COORDINATE;

typedef struct _RABBIT {
  int id;
  int dist;
  COORDINATE position;
  int jumpCnt;
  long long int score;

  struct WORST_COMPARATOR {
    bool operator() (const _RABBIT& a, const _RABBIT& b) const {
      if (a.jumpCnt == b.jumpCnt) {
        if (a.position.x + a.position.y == b.position.x + b.position.y) {
          if (a.position.x == b.position.x) {
            if (a.position.y == b.position.y) {
              return a.id > b.id;
            }
            return a.position.y > b.position.y;
          }
          return a.position.x > b.position.x;
        }
        return a.position.x + a.position.y > b.position.x + b.position.y;
      }
      return a.jumpCnt > b.jumpCnt;
    }
  };
} RABBIT;

map<int, int> iToId;
map<int, RABBIT> rabbits;

priority_queue<RABBIT, vector<RABBIT>, RABBIT::WORST_COMPARATOR> worstRabbits;

RABBIT bestRabbit;

void printRabbits() {
  for (int i = 0; i < rabbits.size(); i++) {
    RABBIT rabbit = rabbits[iToId[i]];
    cout << "<RABBIT> " << "ID: " << iToId[i] << " Dist: " << rabbit.dist << " Count: " << rabbit.jumpCnt << " Score: " << rabbit.score + bias << " Position: {" << rabbit.position.x << ", " << rabbit.position.y << "}" << '\n';
  }
}

void setRace() {
  int rabbitNum;
  cin >> n >> m >> rabbitNum;

  for (int i = 0; i < rabbitNum; i++) {
    RABBIT rabbit;
    cin >> rabbit.id >> rabbit.dist;
    rabbit.position = {0, 0};
    rabbit.jumpCnt = 0;
    rabbit.score = 0;
    iToId[i] = rabbit.id;

    rabbits[rabbit.id] = rabbit;

    worstRabbits.push(rabbit);
  }
}

COORDINATE getNextPosition(const RABBIT& rabbit) {
  // O(1)
  COORDINATE directions[4] = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1},
  };

  COORDINATE ans = {-1, -1};

  for (int i = 0; i < 4; i++) {
    COORDINATE d = directions[i];
    d = {d.x * rabbit.dist, d.y * rabbit.dist};

    COORDINATE np = {rabbit.position.x + d.x, rabbit.position.y + d.y};

    if (np.isOverBoundary()) {
      if (d.x > 0) {
        np.x %= (2*n - 2);

        if (np.x >= n) {
          np.x = (n-1 - (np.x-(n-1)));
        }
      } else if (d.x < 0) {
        np.x -= (n-1);
        np.x *= -1;
        np.x %= (2*n - 2);

        if (np.x >= n) {
          np.x = (n-1 - (np.x-(n-1)));
        }

        np.x = (n-1 - np.x);
      } else if (d.y > 0) {
        np.y %= (2*m - 2);

        if (np.y >= m) {
          np.y = (m-1 - (np.y-(m-1)));
        }
      } else if (d.y < 0) {
        np.y -= (m-1);
        np.y *= -1;
        np.y %= (2*m - 2);

        if (np.y >= m) {
          np.y = (m-1 - (np.y-(m-1)));
        }

        np.y = (m-1 - np.y);
      }
    }
    
    if (ans.x + ans.y == np.x + np.y) {
      if (ans.x == np.x) {
        if (ans.y < np.y) {
          ans = np;
        }
      } else if (ans.x < np.x) {
        ans = np;
      }
    } else if (ans.x + ans.y < np.x + np.y) {
      ans = np;
    }
  }

  return ans;
}

void addScores(int rabbitId) {
  // O(rabbitNum == 2000)
  int score = rabbits[rabbitId].position.x + rabbits[rabbitId].position.y + 2;

  bias += score;

  rabbits[rabbitId].score -= score;
}

void doRace(int turnNum) {
  int rabbitId = worstRabbits.top().id;
  worstRabbits.pop();
  RABBIT& rabbit = rabbits[rabbitId];

  rabbit.position = getNextPosition(rabbit);
  rabbit.jumpCnt++;

  worstRabbits.push(rabbit);

  if (bestRabbit.position.x + bestRabbit.position.y == rabbit.position.x + rabbit.position.y) {
    if (bestRabbit.position.x == rabbit.position.x) {
      if (bestRabbit.position.y == rabbit.position.y) {
        if (bestRabbit.id < rabbit.id) bestRabbit = rabbit;
      } else if (bestRabbit.position.y < rabbit.position.y) {
        bestRabbit = rabbit;
      }
    } else if (bestRabbit.position.x < rabbit.position.x) {
      bestRabbit = rabbit;
    }
  } else if (bestRabbit.position.x + bestRabbit.position.y < rabbit.position.x + rabbit.position.y) {
    bestRabbit = rabbit;
  }

  addScores(rabbitId);
}

void bonus(int turnNum, int addScore) {
  RABBIT& rabbit = rabbits[bestRabbit.id];

  rabbit.score += addScore;
}

void doRaces(int turnNum, int addScore) {
  bestRabbit.position = {-1, -1};
  bestRabbit.id = -1;

  for (int i = 0; i < turnNum; i++) {
    // cout << "RACE: " << i + 1 << '\n';
    doRace(turnNum);
    // printRabbits();
  }

  bonus(turnNum, addScore);
}

void changeDistance(int id, int l) {
  rabbits[id].dist *= l;
}

long long int getTopScore() {
  long long int topScore = -1;

  for (int i = 0; i < rabbits.size(); i++) {
    int id = iToId[i];

    if (rabbits[id].score + bias > topScore) topScore = rabbits[id].score + bias;
  }
  return topScore;
}

void getOrder() {
  int type;
  cin >> type;

  if (type == 100) {
    setRace();
  } else if (type == 200) {
    int turnNum, addScore;
    cin >> turnNum >> addScore;

    doRaces(turnNum, addScore);
  } else if (type == 300) {
    int id, l;
    cin >> id >> l;
    
    changeDistance(id, l);
  } else if (type == 400) {
    cout << getTopScore() << '\n';
  }
}

void getOrders() {
  int orderNum;
  cin >> orderNum;

  for (int i = 0; i < orderNum; i++) {
    // cout << "ORDER " << i+1 << '\n';
    getOrder();

    // printRabbits();
  }
}

int run() {
  getOrders();

  return 0;
}