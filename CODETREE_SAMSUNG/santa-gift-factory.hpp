// 3H

#include <iostream>
#include <map>
#include <vector>

#define MAX_BELT 13

using namespace std;

typedef struct _GIFT {
  int weight;
  int belt;
  int frontId;
  int rearId;
} GIFT;

map<int, GIFT> gifts;
map<int, int> belts;
map<int, int> frontOfBelts;
map<int, int> backOfBelts;

bool isBeltAble[MAX_BELT];

void printGifts() {
  cout << "GIFTS: ";
  for (auto iter = gifts.begin(); iter != gifts.end(); iter++) {
    cout << "ID: " <<  iter->first << " BELT: " << belts[iter->second.belt] << "\n";
  }
  cout << '\n';
}

int getRightBelt(int belt) {
  while(true) {
    if (belts[belt] == belt) return belt;
    belt = belts[belt];
  }
}

void setFactory() {
  int n, m;
  cin >> n >> m;

  vector<int> ids;
  vector<int> weights;

  for (int i = 0; i < n; i++) {
    int id;
    cin >> id;
    ids.push_back(id);
  }

  for (int i = 0; i < n; i++) {
    int weight;
    cin >> weight;
    weights.push_back(weight);
  }

  for (int belt = 0; belt < m; belt++) {
    int adjust = (n/m) * (belt);

    isBeltAble[belt] = true;
    belts[belt] = belt;

    for (int i = 0; i < (n / m); i++) {
      GIFT gift;
      gift.weight = weights[i + adjust];
      gift.belt = belt;

      if (i == 0) {
        gift.frontId = 0;
        if (i + 1 == n / m) {
          gift.rearId = 0;
          backOfBelts[belt] = ids[i + adjust];  
        }
        else gift.rearId = ids[i+1+ adjust];

        frontOfBelts[belt] = ids[i + adjust];
      } else if (i == n/m - 1) {
        if (0 != n/m-1) {
          gift.rearId = 0;
          gift.frontId = ids[i-1+ adjust];
          backOfBelts[belt] = ids[i + adjust];
        }
      } else {
        gift.frontId = ids[i-1+ adjust];
        gift.rearId = ids[i+1+ adjust];
      }

      gifts[ids[i + adjust]] = gift;
    }
  }
}

void removeGiftById(int id) {
  int frontId = gifts[id].frontId;
  int rearId = gifts[id].rearId;

  int belt = getRightBelt(gifts[id].belt);

  if (frontId == 0 && rearId != 0) {
    GIFT& rear = gifts[rearId];

    frontOfBelts[belt] = rearId;
    rear.frontId = 0;
  } else if (frontId != 0 && rearId == 0) {
    GIFT& front = gifts[frontId];

    backOfBelts[belt] = frontId;
    front.rearId = 0;
  } else if (frontId != 0 && rearId != 0) {
    GIFT& front = gifts[frontId];
    GIFT& rear = gifts[rearId];

    front.rearId = rearId;
    rear.frontId = frontId;
  } else {
    frontOfBelts[belt] = 0;
    backOfBelts[belt] = 0;
  }

  gifts.erase(id);
}

void putGiftAtBackById(int id, GIFT gift) {
  int belt = getRightBelt(gift.belt);

  if (backOfBelts[belt] == 0) {
    frontOfBelts[belt] = id;
    backOfBelts[belt] = id;

    gift.frontId = 0;
    gift.rearId = 0;
  } else {
    int backId = backOfBelts[belt];
    GIFT& backGift = gifts[backId];

    backOfBelts[belt] = id;

    backGift.rearId = id;
    gift.rearId = 0;
    gift.frontId = backId;
  }

  gifts[id] = gift;
}

void dropGifts(long long int maxWeight) {
  long long int ans = 0;
  
  for (int i = 0; i < belts.size(); i++) {
    if (isBeltAble[i]) {
      int id = frontOfBelts[i];

      if (id == 0) continue;

      GIFT gift = gifts[id];

      if (gift.weight <= maxWeight) {
        ans += gift.weight;

        removeGiftById(id);
      } else {
        removeGiftById(id);
        putGiftAtBackById(id, gift);
      }
    }
  }

  cout << ans << '\n';
}

void removeGift(int id) {
  if (gifts.count(id)) {
    removeGiftById(id);

    cout << id << '\n';
  } else {
    cout << "-1\n";
  }
}

void findGift(int id) {
  if (gifts.count(id)) {
    int belt = getRightBelt(gifts[id].belt);

    GIFT& gift = gifts[id];

    if (gift.frontId != 0) {
      if (gift.rearId == 0) {
        int newBackId = gift.frontId;
        int oldFrontId = frontOfBelts[belt];

        GIFT& oldFront = gifts[oldFrontId];
        GIFT& newBack = gifts[newBackId];

        oldFront.frontId = id;
        newBack.rearId = 0;
        gift.frontId = 0;
        gift.rearId = oldFrontId;

        frontOfBelts[belt] = id;
        backOfBelts[belt] = newBackId;
      } else {
        int newBackId = gift.frontId;
        int oldFrontId = frontOfBelts[belt];
        int oldBackId = backOfBelts[belt];

        GIFT& oldFront = gifts[oldFrontId];
        GIFT& oldBack = gifts[oldBackId];
        GIFT& newBack = gifts[newBackId];

        oldFront.frontId = oldBackId;
        oldBack.rearId = oldFrontId;
        newBack.rearId = 0;
        gift.frontId = 0;

        frontOfBelts[belt] = id;
        backOfBelts[belt] = newBackId;
      }
    }

    cout << belt+1 << '\n';
  } else {
    cout << "-1\n";
  }
}

void beltBreakdown(int beltNum) {
  if (isBeltAble[beltNum]) {
    int newBelt = (beltNum+1) % belts.size();

    for (; !isBeltAble[newBelt] && newBelt != beltNum; newBelt = (newBelt+1) % belts.size());

    int oldBeltFrontId = frontOfBelts[beltNum];
    int oldBeltBackId = backOfBelts[beltNum];
    int newBeltBackId = backOfBelts[newBelt];

    if (oldBeltFrontId != 0 && newBeltBackId != 0) {
      GIFT& oldBeltFront = gifts[oldBeltFrontId];
      GIFT& newBeltBack = gifts[newBeltBackId];

      oldBeltFront.frontId = newBeltBackId;
      newBeltBack.rearId = oldBeltFrontId;

      backOfBelts[newBelt] = oldBeltBackId;
    } else if (oldBeltFrontId != 0 && newBeltBackId == 0) {
      frontOfBelts[newBelt] = oldBeltFrontId;
      backOfBelts[newBelt] = oldBeltBackId;
    }

    belts[beltNum] = newBelt;
    isBeltAble[beltNum] = false;

    cout << beltNum+1 << '\n';
  } else {
    cout << "-1\n";
  }
}

void getOrder() {
  int type;
  cin >> type;

  if (type == 100) {
    setFactory();
  } else if (type == 200) {
    int maxWeight;
    cin >> maxWeight;
    dropGifts(maxWeight);
  } else if (type == 300) {
    int id;
    cin >> id;
    removeGift(id);
  } else if (type == 400) {
    int id;
    cin >> id;
    findGift(id);
  } else if (type == 500) {
    int beltNum;
    cin >> beltNum;
    beltBreakdown(beltNum-1);
  }
}

void getOrders() {
  int maxOrder;
  cin >> maxOrder;

  for (int i = 0; i < maxOrder; i++) {
    getOrder();
    // printGifts();
  }
}

int run() {
  getOrders();

  return 0;
}