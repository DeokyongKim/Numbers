#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef struct _GUEST {
  int amount;
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

typedef struct _SUSHI {
  int index;
  int enterTime;
  int exitTime;
} SUSHI;

int beltLength, orderNum;

vector<string> names;

vector<ORDER> orders;

map<string, vector<SUSHI> > sushies;

map<string, GUEST> guests;

int guestNum = 0, sushiNum = 0;

void printOrders() {
  int total[400] = {0, };
  for (int i = 0; i < orders.size(); i++) {
    cout << orders[i].category << ' ' << orders[i].t << '\n';
    total[orders[i].category]++;
  }

  cout << '\n';
  cout << "TOTAL : \n";
  cout << "100: " << total[100] << '\n';
  cout << "111: " << total[111] << '\n';
  cout << "200: " << total[200] << '\n';
  cout << "222: " << total[222] << '\n';
  cout << "300: " << total[300] << '\n';

}

bool compare(ORDER a, ORDER b) {
  if (a.t == b.t) {
    return a.category < b.category;
  }
  return a.t < b.t;
}

int getSushiPositionByTime(SUSHI sushi, int t) {
  return (sushi.index + t - sushi.enterTime) % beltLength;
}

void calculateExitTime(string name) {
  int lastTime = 0;

  int guestEnterTime = guests[name].enterTime;

  for (int i = 0; i < sushies[name].size(); i++) {
    if (sushies[name][i].enterTime < guestEnterTime) {
      int curSushiIndex = getSushiPositionByTime(sushies[name][i], guestEnterTime);
      sushies[name][i].exitTime = 
        guestEnterTime + 
        (guests[name].index - curSushiIndex + beltLength) % beltLength;
    } else {
      sushies[name][i].exitTime = 
        sushies[name][i].enterTime + 
        (guests[name].index - sushies[name][i].index + beltLength) % beltLength;
    }

    if (lastTime < sushies[name][i].exitTime) {
      lastTime = sushies[name][i].exitTime;
    }

    ORDER sushiExitOrder;
    sushiExitOrder.category = 111;
    sushiExitOrder.n = -1;
    sushiExitOrder.name = "empty";
    sushiExitOrder.t = sushies[name][i].exitTime;
    sushiExitOrder.x = -1;

    orders.push_back(sushiExitOrder);
  }

  ORDER guestExitOrder;
  guestExitOrder.category = 222;
  guestExitOrder.n = -1;
  guestExitOrder.name = "empty";
  guestExitOrder.t = lastTime;
  guestExitOrder.x = -1;

  orders.push_back(guestExitOrder);
}

void calculateExitTimes() {
  for (int i = 0; i < names.size(); i++) {
    string name = names[i];

    calculateExitTime(name);
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
    sushies[name].push_back({x, t, -1});
  }
  if (order == 200) {
    cin >> t >> x >> name >> n;
    orders.push_back({order, t, x, name, n});
    names.push_back(name);
    guests[name].index = x;
    guests[name].enterTime = t;
    guests[name].amount = n;
  }
  if (order == 300) {
    cin >> t;
    orders.push_back({order, t, -1, "emtpy", -1});
  }
}

void getInput() {
  for (int i = 0; i < orderNum; i++) {
    getOrder();
  }
  
  calculateExitTimes();

  sort(orders.begin(), orders.end(), compare);
}

void executeOrder(int orderIdx) {
  if (orders[orderIdx].category == 100) sushiNum++;
  if (orders[orderIdx].category == 111) sushiNum--;
  if (orders[orderIdx].category == 200) guestNum++;
  if (orders[orderIdx].category == 222) guestNum--;
  if (orders[orderIdx].category == 300) {
    cout << guestNum << ' ' << sushiNum << '\n';
  }
}

void executeOrders() {
  for (int i = 0; i < orders.size(); i++) {
    executeOrder(i);
  }
}

int run() {
  cin >> beltLength >> orderNum;

  getInput();

  executeOrders();

  return 0;
}