#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

typedef struct _GUEST {
  int amount;
  string name;
  int index;
  int enterTime;
} GUEST;

int beltLength, orderNum;

map<string, vector<pair<int, int> > > list;
vector<GUEST> guests;

int startPoint = 0, guestNum = 0, sushiNum = 0;

int getRightSushiIndex(pair<int, int> sushi, int t) {
  return (sushi.first + (t - sushi.second)) % beltLength;
}

void printSushies() {
  int totalSushi = 0;

  cout << "\nSUSHIES:\n";
  for (auto id = list.begin(); id != list.end(); id++) {
    string name = id -> first;
    cout << name << " : ";
    for (int i = 0; i < list[name].size(); i++) {
      cout << getRightSushiIndex(list[name][i], startPoint) << ", ";
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

void eatSushi(int past, int now, int id) {
  int to = (guests[id].index) % beltLength;
  int from = (guests[id].index - (now - past) + beltLength) % beltLength;

  string name = guests[id].name;

  if (from <= to) {
    for (int i = list[name].size() - 1; i >= 0; i--) {
      if (getRightSushiIndex(list[name][i], past) >= from && getRightSushiIndex(list[name][i], past) <= to) {
        cout << guests[id].name << " EAT " << getRightSushiIndex(list[name][i], past) << '\n';
        list[name].erase(list[name].begin() + i);
        sushiNum--;
        guests[id].amount--;
        if (guests[id].amount == 0) {
          guestNum--;
          guests.erase(guests.begin() +id);
          break;
        }
      }
    }
  } else if (to < from) {
    for (int i = list[name].size() - 1; i >= 0; i--) {
      if ((getRightSushiIndex(list[name][i], past) >= 0 && getRightSushiIndex(list[name][i], past) <= to) || (getRightSushiIndex(list[name][i], past) < beltLength && getRightSushiIndex(list[name][i], past) >= from)) {
        cout << guests[id].name << " ATE " << getRightSushiIndex(list[name][i], past) << '\n';
        list[name].erase(list[name].begin() + i);
        sushiNum--;
        guests[id].amount--;
        if (guests[id].amount == 0) {
          guestNum--;
          guests.erase(guests.begin() +id);
          break;
        }
      }
    }
  }
}

void setStartPoint(int t) {
  int past = startPoint;

  startPoint = t;

  int now = startPoint;

  for (int i = 0; i < guests.size(); i++) {
    eatSushi(past+1, now, i);
  }
}

void serveSushi() {
  int t, x;
  string name;

  cin >> t >> x >> name;

  setStartPoint(t);

  list[name].push_back({x, t});

  sushiNum++;

  for (int i = 0; i < guests.size(); i++) {
    eatSushi(t, t, i);
  }
}

void takeSushi() {
  int t, x, n;
  string name;

  cin >> t >> x >> name >> n;

  setStartPoint(t);

  guests.push_back({n, name, x, t});

  eatSushi(t, t, guests.size() - 1);
  
  guestNum++;
}

void takePhoto() {
  int t;
  cin >> t;

  setStartPoint(t);

  cout << guestNum << ' ' << sushiNum << '\n';
}

void getOrder() {
  int order;

  cin >> order;

  if (order == 100) serveSushi();
  if (order == 200) takeSushi();
  if (order == 300) takePhoto();

  printSushies();
  printGuests();

  cout << "++++++++++++++++++++++++++++++++++++++++\n";
}

void getInput() {
  for (int i = 0; i < orderNum; i++) {
    getOrder();
  }
}

int run() {
  cin >> beltLength >> orderNum;

  getInput();

  return 0;
}