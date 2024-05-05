#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int row, col, key;

int board[110][110];

int t = 0, curRow = 3, curCol = 3;

typedef struct _NUM {
  int num;
  int cnt;
} NUM;

bool comp(NUM a, NUM b) {
  if (a.cnt == b.cnt) return a.num < b.num;
  return a.cnt < b.cnt;
}

int run() {
  cin >> row >> col >> key;

  for (int i = 1; i <= curRow; i++) {
    for (int j = 1; j <= curCol; j++) {
      cin >> board[i][j];
    }
  }

  for (; t <= 100; t++) {
    // check
    if (board[row][col] == key) {
      cout << t << '\n';
      return 0;
    }

    // Calculate
    if (curRow >= curCol) {
      for (int i = 1; i <= curRow; i++) {
        int numArr[110] = {0, };

        int minNum = 0x7fffffff;
        int maxNum = 0;

        for (int j = 1; j <= curCol; j++) {
          if (board[i][j] == 0) continue;
          numArr[board[i][j]]++;

          if (minNum > board[i][j]) minNum = board[i][j];
          if (maxNum < board[i][j]) maxNum = board[i][j];
        }

        vector<NUM> numVec;

        for (int j = minNum; j <= maxNum; j++) {
          if (numArr[j]) numVec.push_back({j, numArr[j]});
        }

        for (int j = 1; j <= curCol; j++) board[i][j] = 0;

        if (numVec.size() * 2 > curCol) curCol = numVec.size() * 2;

        sort(numVec.begin(), numVec.end(), comp);

        for (int j = 0; j < numVec.size(); j++) {
          int front = j*2 + 1, rear = j*2 + 2;

          board[i][front] = numVec[j].num;
          board[i][rear] = numVec[j].cnt;
        }
      }
    } else {
      for (int i = 1; i <= curCol; i++) {
        int numArr[110] = {0, };

        int minNum = 0x7fffffff;
        int maxNum = 0;

        for (int j = 1; j <= curRow; j++) {
          if (board[j][i] == 0) continue;
          numArr[board[j][i]]++;

          if (minNum > board[j][i]) minNum = board[j][i];
          if (maxNum < board[j][i]) maxNum = board[j][i];
        }

        vector<NUM> numVec;

        for (int j = minNum; j <= maxNum; j++) {
          if (numArr[j]) numVec.push_back({j, numArr[j]});
        }

        for (int j = 1; j <= curRow; j++) board[j][i] = 0;

        if (numVec.size() * 2 > curRow) curRow = numVec.size() * 2;

        sort(numVec.begin(), numVec.end(), comp);

        for (int j = 0; j < numVec.size(); j++) {
          int front = j*2 + 1, rear = j*2 + 2;

          board[front][i] = numVec[j].num;
          board[rear][i] = numVec[j].cnt;
        }
      }
    }
  }

  cout << "-1\n";

  return 0;
}