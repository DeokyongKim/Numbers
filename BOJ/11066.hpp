#include <iostream>
#include <algorithm>
#define INF 1987654321

using namespace std;

long long int chapter, fileSize[510], memo[510][510];

void getTotalSize() {
  for (int i = 0; i < chapter; i++) memo[i][i] = 0;

  for (int len = 1; len < chapter; len++) {
    for (int start = 0; start < chapter; start++) {
      int end = start + len;

      if (end >= chapter) continue;
      if (memo[start][end] != INF) continue;

      long long int partialSum = 0;
      for (int i = start; i <= end; i++) partialSum += fileSize[i];

      long long int min = INF;
      for (int middle = start; middle < end; middle++) {
        long long int tmp = memo[start][middle] + memo[middle+1][end] + partialSum;
        if (min > tmp) min = tmp;
      }
      memo[start][end] = min;
    }
  }
}

int run() {
  int TEST_CASE;
  cin >> TEST_CASE;

  for (int test_case = 0; test_case < TEST_CASE; test_case++) {
    int ans = 0;

    cin >> chapter;
    for (int i = 0; i < chapter; i++) {
      cin >> fileSize[i];
    }

    for (int i = 0; i < chapter; i++) {
      for (int j = 0; j < chapter; j++) {
        memo[i][j] = INF;
      }
    }

    getTotalSize();

    cout << memo[0][chapter-1] << '\n';

    for (int i = 0; i < chapter; i++) {
      for (int j = 0; j < chapter; j++) {
        if (memo[i][j] < 0) cout << "-1" << '\t';
        else if (memo[i][j] == INF) cout << "INF" << '\t';
        else cout << memo[i][j] << '\t';
      }
      cout << '\n';
    }
  }

  return 0;
}