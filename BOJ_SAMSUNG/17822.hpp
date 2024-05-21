#include <iostream>

using namespace std;

int discQuantity, integerQuantity, rotateNumber;

// disc: dics의 숫자가 적혀 있음
int disc[55][55], eachDiscNum[55];

void rotateDisc(int idx, int dir, int num) {
  for (int i = idx; i < discQuantity; i += (idx+1)) {

    // apply direction
    num *= (dir == 0 ? -1 : 1);

    int disctop = 0;
    
    // make num to positive number 
    num = num % integerQuantity + (num < 0 ? integerQuantity : 0);

    disctop = (disctop + num) % integerQuantity;

    // relocate numbers to proper position
    int tmpDisc[55] = {0, };

    for (int i = 0; i < integerQuantity; i++) {
      tmpDisc[i] = disc[idx][(i + disctop) % integerQuantity];
    }

    for (int i = 0; i < integerQuantity; i++) {
      disc[idx][i] = tmpDisc[i];
    }
  }
}

void clearAdjacency() {
  int adjacency[55][55] = {0, };
  int haveAdjacency[55] = {0, };
  
  // check are there same numbers in adjacency
  for (int i = 0; i < discQuantity; i++) {
    for (int j = 0; j < integerQuantity; j++) {
      if (disc[i][j] < 0) continue;

      if (j - 1 >= 0 && disc[i][j] == disc[i][j-1]) {
        haveAdjacency[i] = 1;
        adjacency[i][j] = 1;
        adjacency[i][j-1] = 1;
      }
      if (j + 1 < integerQuantity && disc[i][j] == disc[i][j+1]) {
        haveAdjacency[i] = 1;
        adjacency[i][j] = 1;
        adjacency[i][j+1] = 1;
      }
      if (i - 1 >= 0 && disc[i][j] == disc[i-1][j]) {
        haveAdjacency[i] = 1;
        haveAdjacency[i-1] = 1;
        adjacency[i][j] = 1;
        adjacency[i-1][j] = 1;
      }
      if (i + 1 < discQuantity && disc[i][j] == disc[i+1][j]) {
        haveAdjacency[i] = 1;
        haveAdjacency[i+1] = 1;
        adjacency[i][j] = 1;
        adjacency[i+1][j] = 1;
      }
    }
  }

  // erase and relocate numbers
  for (int i = 0; i < discQuantity; i++) {
    if (haveAdjacency[i]) {
      int tmp = 0;
      for (int j = 0; j < integerQuantity; j++) {
        if (adjacency[i][j] == 1) {
          disc[i][j] = -1;
          tmp++;
        }
      }
      eachDiscNum[i] = tmp;
    } else {
      float mean;
      for (int j = 0; j < integerQuantity; j++) {
        if (disc[i][j] > 0) mean += disc[i][j];
      }
      mean /= (float)eachDiscNum[i];
      for (int j = 0; j < integerQuantity; j++) {
        if (mean < disc[i][j]) disc[i][j]--;
        else if (mean > disc[i][j]) disc[i][j]++;
      }
    }
  }
}

void printDisc() {
  for (int i = 0; i < discQuantity; i++) {
    for (int j = 0; j < integerQuantity; j++) {
      cout << disc[i][j] << ' ';
    }
    cout << '\n';
  }
  cout << "====================\n";
}

int run() {
  cin >> discQuantity >> integerQuantity >> rotateNumber;

  for (int i = 0; i < discQuantity; i++) {
    for (int j = 0; j < integerQuantity; j++) {
      cin >> disc[i][j];
    }
    eachDiscNum[i] = integerQuantity;
  }

  printDisc();

  for (int testCount = 0; testCount < rotateNumber; testCount++) {
    int discIndex, rotateDirection, rotateCount;
    cin >> discIndex >> rotateDirection >> rotateCount;

    rotateDisc(discIndex - 1, rotateDirection, rotateCount);
    printDisc();

    clearAdjacency();

    printDisc();
    cout << "===========\n";
  }

  int sum = 0;
  for (int i = 0; i < discQuantity; i++) {
    for (int j = 0; j < integerQuantity; j++) {
      if (disc[i][j] > 0) sum += disc[i][j];
    }
  }

  cout << sum << '\n';

  return 0;
}