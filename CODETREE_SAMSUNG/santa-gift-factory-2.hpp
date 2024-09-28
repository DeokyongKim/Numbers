#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef struct _GIFT {
  int front;
  int rear;

  int getInfo() {
    return front + 2 * rear;
  }
} GIFT;

typedef struct _BELT {
  int front;
  int rear;
  int cnt;

  int getInfo() {
    return front + 2 * rear + 3 * cnt;
  }
} BELT;

map<int, GIFT> gifts;
map<int, BELT> belts;

int n, m;
void printBelts() {
  for (int i = 1; i <= n; i++) {
    cout << "<BELT " << i << "> [CNT: " << belts[i].cnt << "] GIFTS: ";
    for (int j = belts[j].front; j != -1; j = gifts[j].rear) {
      cout << j << ' ';
    }
    cout << '\n';
  }

  // for (int i = 1; i <= m; i++) {
  //   cout << "<GIFT " << i << "> FRONT: " << gifts[i].front << " REAR: " << gifts[i].rear << '\n';  
  // }
}

void setFactory() {
  cin >> n >> m;

  for (int i = 1; i <= n; i++) {
    BELT belt;

    belt.cnt = 0;
    belt.front = -1;
    belt.rear = -1;
    
    belts[i] = belt;
  }

  for (int i = 1; i <= m; i++) {
    GIFT gift;
    int belt;

    cin >> belt;

    if (belts[belt].front == -1) {
      belts[belt].front = i;
      belts[belt].rear = i;
      gift.front = -1;
      gift.rear = -1;
    } else {
      gift.front = belts[belt].rear;
      gift.rear = -1;
      gifts[belts[belt].rear].rear = i;
      belts[belt].rear = i;
    }

    belts[belt].cnt++;

    gifts[i] = gift;
  }
}

void moveEveryGifts(int from, int to) {
  if (belts[from].cnt == 0) return;

  if (belts[to].cnt == 0) {
    belts[to].front = belts[from].front;
    belts[to].rear = belts[from].rear;
    belts[to].cnt = belts[from].cnt;
  } else {
    gifts[belts[from].rear].rear = belts[to].front;
    gifts[belts[to].front].front = belts[from].rear;

    belts[to].front = belts[from].front;
    belts[to].cnt += belts[from].cnt;
  }

  belts[from].front = -1;
  belts[from].rear = -1;
  belts[from].cnt = 0;
}

void dropGift(int beltId) {
  BELT& belt = belts[beltId];

  if (belt.cnt == 0) return;

  if (belt.cnt == 1) {
    belt.front = -1;
    belt.rear = -1;
    belt.cnt = 0;
  } else {
    int oldFront = belt.front;
    int newFront = gifts[oldFront].rear;

    gifts[oldFront].rear = -1;
    gifts[newFront].front = -1;

    belt.front = newFront;
    belt.cnt--;
  }
}

void putGift(int beltId, int giftId) {
  BELT& belt = belts[beltId];
  GIFT& gift = gifts[giftId];

  if (belt.cnt == 0) {
    belt.front = giftId;
    belt.rear = giftId;
    belt.cnt++;
  } else {
    int oldFront = belt.front;

    gifts[oldFront].front = giftId;
    gift.rear = oldFront;

    belt.front = giftId;
    belt.cnt++;
  }
}

void changeFront(int a, int b) {
  if (belts[a].cnt == 0 && belts[b].cnt == 0) return;

  if (belts[a].cnt == 0) {
    int giftId = belts[b].front;

    dropGift(b);
    putGift(a, giftId);
  } else if (belts[b].cnt == 0) {
    int giftId = belts[a].front;

    dropGift(a);
    putGift(b, giftId);
  } else {
    int giftIdA = belts[a].front;
    int giftIdB = belts[b].front;

    dropGift(a);
    dropGift(b);

    putGift(a, giftIdB);
    putGift(b, giftIdA);
  }
}

void moveHalfGifts(int from, int to) {
  BELT &bf = belts[from], &bt = belts[to];

  if (bf.cnt/2 < 1) return;

  int half = bf.cnt / 2, halfGiftId = bf.front;

  for (int cnt = 0; cnt < half-1; cnt++) {
    halfGiftId = gifts[halfGiftId].rear;
  }

  GIFT& halfGift = gifts[halfGiftId];

  int newFromFront = halfGift.rear;
  int oldToFront = bt.front;

  halfGift.rear = oldToFront;
  gifts[oldToFront].front = halfGiftId;
  gifts[newFromFront].front = -1;

  bt.front = bf.front;
  bt.cnt += half;

  bf.front = newFromFront;
  bf.cnt -= half;
}

void getOrder() {
  int type;
  cin >> type;

  // cout << "ORDER " << type << '\n';

  if (type == 100) {
    setFactory();
  } else if (type == 200) {
    int from, to;
    cin >> from >> to;

    moveEveryGifts(from, to);

    cout << belts[to].cnt << '\n';
  } else if (type == 300) {
    int a, b;
    cin >> a >> b;

    changeFront(a, b);

    cout << belts[b].cnt << '\n';
  } else if (type == 400) {
    int from, to;
    cin >> from >> to;

    moveHalfGifts(from, to);

    cout << belts[to].cnt << '\n';
  } else if (type == 500) {
    int giftId;
    cin >> giftId;

    cout << gifts[giftId].getInfo() << '\n';
  } else if (type == 600) {
    int beltId;
    cin >> beltId;

    cout << belts[beltId].getInfo() << '\n';
  }

  // printBelts();
}

void getOrders() {
  int orderNum;
  cin >> orderNum;

  for (int i = 0; i < orderNum; i++) {
    getOrder();
  }
}

int run() {
  getOrders();

  return 0;
}