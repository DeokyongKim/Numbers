#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <queue>
#include <map>

using namespace std;

typedef struct _ORDER {
  int type;
  int time;
  int priority;
  string url;
  int N;
  int id;
} ORDER;

typedef struct _JUDGETIME {
  int start;
  int end;
} JUDGETIME;

int orderNum, judgerNum;

vector<ORDER> orders;

struct JUDGER_INDEX_COMPARE {
  bool operator() (const int& a, const int& b) const {
    return a > b;
  }
};

priority_queue<int, vector<int>, JUDGER_INDEX_COMPARE> judgersIndex;

string isJudging[50010];

struct WAITING_COMPARE {
  bool operator() (const _ORDER& a, const _ORDER& b) const {
    if (a.priority == b.priority) return a.time > b.time;
    else return a.priority > b.priority;
  }
};

priority_queue<ORDER, vector<ORDER>, WAITING_COMPARE> waitings;

set<string> waitingUrls;
set<string> judgingUrls;

map<string, JUDGETIME> judgeHistory;

void getOrder(int type) {
  ORDER order = {0, };
  order.type = type;

  if (type == 100) {
    cin >> order.N >> order.url;
    order.time = -1;
  } else if (type == 200) {
    cin >> order.time >> order.priority >> order.url;
  } else if (type == 300) {
    cin >> order.time;
  } else if (type == 400) {
    cin >> order.time >> order.id;
  } else if (type == 500) {
    cin >> order.time;
  }

  orders.push_back(order);
}

bool orderComparator(ORDER a, ORDER b) {
  return a.time < b.time;
}

void getOrders() {
  cin >> orderNum;

  for (int i = 0; i < orderNum; i++) {
    int type;
    cin >> type;

    getOrder(type);
  }

  // sort(orders.begin(), orders.end(), orderComparator);
}

vector<string> split(string url, string spliter) {
  int index = url.find(spliter);
  return {url.substr(0, index), url.substr(index + 1, url.length() + 1 - index)};
}

void requestJudge(ORDER order) {
  if (!waitingUrls.count(order.url)) {
    waitings.push(order);
    waitingUrls.insert(order.url);
  }

  // cout << order.type << " " << order.time << " :AFTER REQUEST: " << waitings.size() << '\n';
}

void setJudgers(ORDER order) {
  for (int i = 0; i < order.N; i++) {
    isJudging[i] = "";

    judgersIndex.push(i+1);
  }

  requestJudge(order);
}

bool isDDOS(string domain, int currentTime) {
  if (judgeHistory[domain].end == -1) return false;

  int start = judgeHistory[domain].start, end = judgeHistory[domain].end;

  int gap = end - start;

  // cout << "TRY TIME: " << currentTime << ", STD TIME: " << start + 3 * gap << '\n';

  if (currentTime < start + 3 * gap) return true;

  return false;
}

void tryJudge(ORDER order) {
  vector<ORDER> tmpOrders;

  if (judgersIndex.empty()) return;

  while(!waitings.empty()) {
    ORDER nextOrder = waitings.top();
    waitings.pop();

    vector<string> domainAndId = split(nextOrder.url, "/");

    string domain = domainAndId[0], id = domainAndId[1];

    if (judgingUrls.count(domain) == 1 || isDDOS(domain, order.time)) {
      tmpOrders.push_back(nextOrder);
      continue;
    }

    int judgerIndex = judgersIndex.top();
    judgersIndex.pop();
    isJudging[judgerIndex] = split(nextOrder.url, "/")[0];

    judgingUrls.insert(domain);
    
    judgeHistory[domain] = {
      order.time,
      -1
    };

    waitingUrls.erase(nextOrder.url);
    // for (auto x : waitingUrls) {
    //   cout << x << ' ';
    // }
    // cout << '\n';

    break;
  }

  for (int i = 0; i < tmpOrders.size(); i++) {
    waitings.push(tmpOrders[i]);
  }

  // cout << order.type << " " << order.time << " :AFTER TRY: " << waitings.size() << '\n';
}

void endJudge(ORDER order) {
  if (isJudging[order.id] == "") return;

  int startTime = judgeHistory[isJudging[order.id]].start;

  judgingUrls.erase(isJudging[order.id]);
  judgeHistory[isJudging[order.id]] = {startTime, order.time};
  judgersIndex.push(order.id);
  isJudging[order.id] = "";

  // cout << order.type << " " << order.time << " :AFTER END: " << waitings.size() << '\n';
}

void executeOrder(ORDER order) {
  if (order.type == 100) setJudgers(order);
  if (order.type == 200) requestJudge(order);
  if (order.type == 300) tryJudge(order);
  if (order.type == 400) endJudge(order);
  if (order.type == 500) cout << waitings.size() << '\n';
}

void executeOrders() {
  for (int i = 0; i < orderNum; i++) {
    executeOrder(orders[i]);
  }
}

int run() {
  getOrders();

  executeOrders();

  return 0;
}