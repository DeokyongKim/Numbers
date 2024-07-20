// Spent roughly two hours. Actually less than two hours. 

#include <iostream>
#include <vector>

using namespace std;

int fishbowl[110][110] = {0, };

int bowlNum, maxFishDifference, endIndex;

void printBowl() {
  for (int i = 0; i < bowlNum; i++) {
    for (int j = 0; j < endIndex; j++) {
    if (fishbowl[i][j] == 0) break;
      cout << fishbowl[i][j] << '\t';
    }
    cout << '\n';
  }
  cout << '\n';
}

void clearBowl() {
  for (int i = 0; i <= bowlNum; i++) {
    for (int j = 0; j <= bowlNum; j++) {
      fishbowl[i][j] = 0;
    }
  }
}

bool isEnd() {
  int min = 0x7fffffff, max = -1;
  for (int i = 0; i < bowlNum; i++) {
    if (fishbowl[0][i] > 0) {
      if (fishbowl[0][i] < min) min = fishbowl[0][i];
      if (fishbowl[0][i] > max) max = fishbowl[0][i];
    }
  }

  if (max - min <= maxFishDifference) return true;
  else return false;
}

void addFishToLeastFishbowl() {
  int min = 0x7fffffff;

  for (int i = 0; i < bowlNum; i++) {
    if (fishbowl[0][i] < min) {
      min = fishbowl[0][i];
    }
  }

  for (int i = 0; i < bowlNum; i++) {
    if (fishbowl[0][i] == min) {
      fishbowl[0][i]++;
    }
  }
}

void stackLeftFishbowl() {
  int left = fishbowl[0][0];

  for (int i = 0; i < bowlNum-1; i++) {
    fishbowl[0][i] = fishbowl[0][i+1];
  }
  fishbowl[0][bowlNum - 1] = 0;

  fishbowl[1][0] = left;

  endIndex--;
}

pair<int, int> getLastStackedIndexAndMaxHeight() {
  int lastStackedIndex = 0, maxHeight = 0;

  for (int i = 0; i < endIndex; i++) {
    if (fishbowl[1][i] > 0) {
      lastStackedIndex = i+1;

      int height = 1;
      for (; fishbowl[height][i] > 0; height++);

      maxHeight = height;
    } else {
      break;
    }
  }

  return {lastStackedIndex, maxHeight};
}

bool isAbleToStack() {
  pair<int, int> data = getLastStackedIndexAndMaxHeight();

  int lastStackedIndex = data.first;
  int maxHeight = data.second;

  if (endIndex - lastStackedIndex >= maxHeight) return true;
  else return false;
}

void makeStack() {
  pair<int, int> data = getLastStackedIndexAndMaxHeight();

  int lastStackedIndex = data.first;
  int maxHeight = data.second;

  int tmp[maxHeight + 1][lastStackedIndex + 1] = {0, };
  int left[endIndex - lastStackedIndex + 1] = {0, };

  for (int i = 0; i < lastStackedIndex; i++) {
    for (int j = 0; j < maxHeight; j++) {
      tmp[j][i] = fishbowl[j][i];
    }
  }

  for (int i = 0; i < endIndex - lastStackedIndex; i++) {
    left[i] = fishbowl[0][i + lastStackedIndex];
  }

  clearBowl();

  endIndex -= lastStackedIndex;

  for (int i = 0; i < endIndex; i++) {
    fishbowl[0][i] = left[i];
  }

  for (int i = 0; i < lastStackedIndex; i++) {
    for (int j = 0; j < maxHeight; j++) {
      fishbowl[lastStackedIndex-1 - i + 1][j] = tmp[j][i];
    }
  }
}

void makeFinalStack() {
  while(isAbleToStack()) {
    makeStack();
  }
}

void adjustFishes() {
  int sub[110][110] = {0, };

  pair<int, int> direction[4] = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
  };

  for (int i = 0; i < bowlNum; i++) {
    for (int j = 0; j < endIndex; j++) {
      if (fishbowl[i][j] == 0) break;

      for (int dir = 0; dir < 4; dir++) {
        int dx = direction[dir].first;
        int dy = direction[dir].second;

        int nx = i + dx;
        int ny = j + dy;

        if (nx >= 0 && ny >= 0 && fishbowl[nx][ny] > 0) {
          if (fishbowl[i][j] > fishbowl[nx][ny]) {
            int difference = fishbowl[i][j] - fishbowl[nx][ny];
            int d = difference / 5;
            sub[i][j] -= d;
            sub[nx][ny] += d;
          }
        }
      }
    }
  }

  for (int i = 0; i < bowlNum; i++) {
    for (int j = 0; j < endIndex; j++) {
      fishbowl[i][j] += sub[i][j];
    }
  }
}

void makeFishbowlsToLine() {
  int tmp[110] = {0, };

  int cnt = 0;

  for (int i = 0; i < endIndex; i++) {
    for (int j = 0; fishbowl[j][i] > 0; j++) {
      tmp[cnt++] = fishbowl[j][i];
    }
  }

  clearBowl();

  endIndex = bowlNum;

  for (int i = 0; i < endIndex; i++) {
    fishbowl[0][i] = tmp[i];
  }
}

void makeHalfStack(int height) {
  int midIndex = endIndex / 2;

  int front[2][110] = {0, }, rear[2][110] = {0, };

  for (int i = 0; i < midIndex; i++) {
    for (int j = 0; j < height; j++) {
      front[j][i] = fishbowl[j][i];
    }
  }

  for (int i = 0; i < midIndex; i++) {
    for (int j = 0; j < height; j++) {
      rear[j][i] = fishbowl[j][i + midIndex];
    }
  }

  clearBowl();
  endIndex /= 2;

  for (int i = 0; i < endIndex; i++) {
    for (int j = 0; j < height; j++) {
      fishbowl[j][i] = rear[j][i];
    }
  }

  for (int i = 0; i < endIndex; i++) {
    for (int j = 0; j < height; j++) {
      fishbowl[j + height][i] = front[height-1 - j][endIndex-1 - i];
    }
  }
}

void makeHalfAndHalfStack() {
  makeHalfStack(1);
  makeHalfStack(2);
}

void solve() {
  int cnt = 0;

  while(!isEnd()) {
    cnt++;

    addFishToLeastFishbowl();

    stackLeftFishbowl();

    makeFinalStack();

    adjustFishes();

    makeFishbowlsToLine();

    makeHalfAndHalfStack();

    adjustFishes();
    
    makeFishbowlsToLine();
  }

  cout << cnt << '\n';
}

int run() {
  cin >> bowlNum >> maxFishDifference;

  endIndex = bowlNum;

  for (int i = 0; i < bowlNum; i++) {
    cin >> fishbowl[0][i];
  }

  solve();

  return 0;
}