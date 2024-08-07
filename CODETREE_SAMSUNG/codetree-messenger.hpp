#include <iostream>
#include <queue>

using namespace std;

int n, orderNumber;

int parents[100010], authority[100010];

int children[100010][2];

void setParentsAndAuthority() {
  for (int i = 1; i <= n; i++) {
    cin >> parents[i];
    if (children[parents[i]][0] == 0) children[parents[i]][0] = i;
    else children[parents[i]][1] = i;
  }
  for (int i = 1; i <= n; i++) {
    cin >> authority[i];
  }
}

void changeAlarmState() {
  int id;
  cin >> id;

  authority[id] *= -1;
}

void changeAuthorityPower() {
  int id, power;
  cin >> id >> power;

  if (authority[id] < 0) authority[id] = -1 * power;
  else authority[id] = power;
}

void changeParent() {
  int id1, id2;
  cin >> id1 >> id2;

  int parent1 = parents[id1], parent2 = parents[id2];

  int c1Idx, c2Idx;
  if (children[parent1][0] == id1) c1Idx = 0;
  if (children[parent1][1] == id1) c1Idx = 1;
  if (children[parent2][0] == id2) c2Idx = 0;
  if (children[parent2][1] == id2) c2Idx = 1;

  // change children array
  int tmpChild = children[parent1][c1Idx];
  children[parent1][c1Idx] = children[parent2][c2Idx];
  children[parent2][c2Idx] = tmpChild;

  // change parents array
  int tmpParent = parents[id1];
  parents[id1] = parents[id2];
  parents[id2] = tmpParent;
}

void computeNumberOfChatGetAlarm() {
  int targetId, ans = 0;
  cin >> targetId;

  typedef struct _NODE {
    int id;
    int level;
  } NODE;

  queue<NODE> q;
  q.push({targetId, 0});

  while(!q.empty()) {
    int curId = q.front().id;
    int curLv = q.front().level;
    q.pop();

    if (targetId != curId && authority[curId] <= 0) continue;

    for (int i = 0; i < 2; i++) {
      int childId = children[curId][i];

      if (authority[childId] > curLv) ans++;

      if (childId > 0) q.push({childId, curLv+1});
    }
  }
  
  cout << ans << '\n';
}

void getOrder() {
  int order;
  cin >> order;

  if (order == 100) setParentsAndAuthority();
  if (order == 200) changeAlarmState();
  if (order == 300) changeAuthorityPower();
  if (order == 400) changeParent();
  if (order == 500) computeNumberOfChatGetAlarm();
}

void getInput() {
  for (int i = 0; i < orderNumber; i++) getOrder();
}

int run() {
  cin >> n >> orderNumber;

  getInput();

  return 0;
}