#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef struct _GUEST {
  int amount;
  string name;
  int index;
  int enterTime;
} GUEST;

typedef struct _ORDER {
  int category = -1;
  int t = -1;
  int x = -1;
  string name;
  int n = -1;
} ORDER;

int beltLength, orderNum;

map<string, vector<pair<int, int> > > list;
vector<GUEST> guests;
vector<ORDER> orders;

int curTime = 0, guestNum = 0, sushiNum = 0;

int getCurrentSushiPosition(pair<int, int> sushi, int t) {
  return (sushi.first + (t - sushi.second)) % beltLength;
}

void printSushies() {
  int totalSushi = 0;

  cout << "\nSUSHIES:\n";
  for (auto id = list.begin(); id != list.end(); id++) {
    string name = id -> first;
    cout << name << " : ";
    for (int i = 0; i < list[name].size(); i++) {
      cout << getCurrentSushiPosition(list[name][i], curTime) << ", ";
      totalSushi++;
    }
    cout << '\n';
  }
  cout << '\n';

  if (totalSushi != sushiNum) cout << "PROBLEM!!!!!!!!!!!!!!!!!!!!!\n";
}

void printGuests() {
  int totalGuest = 0;

  cout << "\nGUESTS:\n";
  for (int i = 0; i < guests.size(); i++) {
    cout << guests[i].name << " : position is " << guests[i].index << ", amount is " << guests[i].amount << '\n';
    totalGuest++;
  }
  cout << '\n';

  if (totalGuest != guestNum) cout << "PROBLEM!!!!!!!!!!!!!!!!!!!!!\n";
}

bool isSushiInRange(int sushiIndex, int start, int end) {
  
  if (start <= end) {
    if (start <= sushiIndex && end >= sushiIndex) return true;
    return false;
  } else {
    if (start <= sushiIndex || end >= sushiIndex) return true;
    return false;
  }
}

void eatSushi(int guestId, int from, int to) {
  string guestName = guests[guestId].name;

  // cout << guestName << " EATS SUSHI FROM " << from << " to " << to << '\n';

  for (int i = list[guestName].size()-1; i >= 0; i--) {
    if (isSushiInRange(getCurrentSushiPosition(list[guestName][i], curTime), to, from)) {
      list[guestName].erase(list[guestName].begin() + i);
      sushiNum--;
      guests[guestId].amount--;

      if (guests[guestId].amount == 0) {
        guests.erase(guests.begin() + guestId);
        guestNum--;
        break;
      }
    }
  }

  if (list[guestName].size() == 0) list.erase(guestName);
}

void rotateTable(int nextTime) {
  int timeGap = nextTime - curTime;

  for (int i = 0; i < guests.size(); i++) {
    eatSushi(
      i, 
      (guests[i].index - 1 + beltLength) % beltLength, 
      timeGap >= beltLength ? guests[i].index : ((guests[i].index - timeGap + beltLength) % beltLength)
    );
  }

  curTime = nextTime;
}

void serveSushi(int orderIdx) {
  ORDER cur = orders[orderIdx];

  int t = cur.t, x = cur.x;
  string name = cur.name;

  rotateTable(t);

  list[name].push_back({x, t});

  sushiNum++;

  for (int i = 0; i < guests.size(); i++) {
    eatSushi(i, guests[i].index, guests[i].index);
  }
}

void takeSushi(int orderIdx) {
  ORDER cur = orders[orderIdx];

  int t = cur.t, x = cur.x, n = cur.n;
  string name = cur.name;

  rotateTable(t);

  guests.push_back({n, name, x, t});

  int newGuestIndex = guests.size() - 1;

  eatSushi(newGuestIndex, x, x);
  
  guestNum++;
}

void takePhoto(int orderIdx) {
  ORDER cur = orders[orderIdx];

  int t = cur.t;

  rotateTable(t);

  cout << guestNum << ' ' << sushiNum << '\n';
}

bool compare(ORDER a, ORDER b) {
  if (a.t == b.t) {
    a.category < b.category;
  } else {
    return a.t < b.t;
  }
}

void getOrder() {
  int order;

  cin >> order;

  int t, x, n;
  string name;

  if (order == 100) {
    cin >> t >> x >> name;
    orders.push_back({order, t, x, name, -1});
  }
  if (order == 200) {
    cin >> t >> x >> name >> n;
    orders.push_back({order, t, x, name, n});
  }
  if (order == 300) {
    cin >> t;
    orders.push_back({order, t, -1, "emtpy", -1});
  }

  sort(orders.begin(), orders.end(), compare);
}

void getInput() {
  for (int i = 0; i < orderNum; i++) {
    getOrder();
  }
}

void executeOrder(int orderIdx) {
  if (orders[orderIdx].category == 100) serveSushi(orderIdx);
  if (orders[orderIdx].category == 200) takeSushi(orderIdx);
  if (orders[orderIdx].category == 300) takePhoto(orderIdx);
}

void executeOrders() {
  for (int i = 0; i < orderNum; i++) {
    executeOrder(i);
  }
}

int run() {
  cin >> beltLength >> orderNum;

  getInput();

  executeOrders();

  return 0;
}