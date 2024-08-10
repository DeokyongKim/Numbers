#include <iostream>

using namespace std;

int n, orderNumber;

int parents[100010], authority[100010], alarm[100010][25];

bool on[100010];

void printAlarm() {
  for (int i = 0; i <= n; i++) {
    cout << i << ": ";
    for (int j = 0; j <= 20; j++) {
      cout << alarm[i][j] << ' ' ;
    }
    cout << '\n';
  }
  cout << '\n';
}

void setParentsAndAuthority() {  
  for (int i = 1; i <= n; i++) {
    cin >> parents[i];
    on[i] = true;
  }
  for (int i = 1; i <= n; i++) {
    cin >> authority[i];
    if (authority[i] > 20) authority[i] = 20;
  }

  for (int i = 1; i <= n; i++) {
    for (int parent = parents[i], level = authority[i] - 1; level >= 0; parent = parents[parent], level--) {
      alarm[parent][level]++;

      if (parent == 0 || !on[parent]) break;
    }
  }
}

void onAndOff(int id) {
  on[id] = !on[id];

  if (!on[id]) {
    for (int parent = parents[id], level = 1; authority[id] - level >= 0 ; parent = parents[parent], level++) {
      alarm[parent][authority[id] - level]--;
      if (parent == 0 || !on[parent]) break;
    }
    for (int parent = parents[id], level = 1; ; parent = parents[parent], level++) {
      for (int i = level; i < 20; i++) {
        alarm[parent][i-level] -= alarm[id][i];
      }
      
      if (parent == 0 || !on[parent]) break;
    }
  } else {
    for (int parent = parents[id], level = 1; authority[id] - level >= 0 ; parent = parents[parent], level++) {
      alarm[parent][authority[id] - level]++;
      if (parent == 0 || !on[parent]) break;
    }
    for (int parent = parents[id], level = 1; ; parent = parents[parent], level++) {
      for (int i = level; i < 20; i++) {
        alarm[parent][i-level] += alarm[id][i];
      }
      
      if (parent == 0 || !on[parent]) break;
    }
  }
}

void changeAlarmState() {
  int id;
  cin >> id;
  
  onAndOff(id);
}

void changeAuthorityPower() {
  int id, power;
  cin >> id >> power;

  if (power > 20) power = 20;

  bool befOn = on[id];

  if (on[id]) onAndOff(id);

  authority[id] = power;

  if (befOn) onAndOff(id);
}

void changeParent() {
  int id1, id2;
  cin >> id1 >> id2;

  bool befOn1 = on[id1];
  bool befOn2 = on[id2];

  if (on[id1]) onAndOff(id1);
  if (on[id2]) onAndOff(id2);

  int tmp = parents[id1];
  parents[id1] = parents[id2];
  parents[id2] = tmp;

  if (befOn1) onAndOff(id1);
  if (befOn2) onAndOff(id2);
}

void computeNumberOfChatGetAlarm() {
  int id;
  long long int ans = 0;
  cin >> id;

  for (int i = 0; i < 20; i++) {
    if (alarm[id][i] > 0) ans += alarm[id][i];
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