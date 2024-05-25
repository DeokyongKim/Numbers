#include <iostream>
#include <algorithm>

using namespace std;

int n, rightList[10010], leftList[10010], dp[10010];

int ans = 0, ansList[10010], finalList[10010];

void solve(int rightIdx, int got, int ceiling) {
  if (rightIdx <= 0) {
    if (got > ans) {
      ans = got;

      // cout << "NOW!!!: " << ans << '\n';

      for (int i = 1, j = 0; i <= n; i++) {
        if (ansList[i]) {
          finalList[j++] = i; 
          // cout << i << '\n';
        }
      }
      // cout << '\n';
    }
    return;
  }

  if (dp[rightIdx] > got) return;

  dp[rightIdx] = got;

  // cout << rightIdx << ' ' << leftList[rightList[rightIdx]] << ' ' << ceiling <<'\n';

  int curNumber = rightList[rightIdx];
  int leftIdx = leftList[curNumber];

  if(leftIdx < ceiling) {
    ansList[curNumber] = 1;
    solve(leftIdx-1, got + 1, leftIdx);
    ansList[curNumber] = 0;
  }
  solve(rightIdx-1, got, ceiling);
}

int run() {
  cin >> n;

  for (int i = 1; i <= n; i++) {
    int val;
    cin >> val;
    leftList[val] = i;
  }
  for (int i = 1; i <= n; i++) {
    cin >> rightList[i];
  }

  solve(n, 0, n+1);
  cout << ans << '\n';

  for (int i = 0; i < ans; i++) cout << finalList[i] << ' ';
  cout << '\n';

  return 0;
}