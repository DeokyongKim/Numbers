// Gold

#include <iostream>
#include <cstring>
#include <algorithm>
#define endl '\n'
using namespace std;

int n, m;
int score[11];
// [B][A]: 팔굽혀펴기의 누적 횟수가 A인데 현재 팀의 점수가 B일 때 득점한 최대 점수
int dp[1100][5001];

int dfs(int prefixSum, int nowScore) {
	if (nowScore == n) return prefixSum;
	int& ret = dp[prefixSum][nowScore];
	if (ret != -1) return ret;

	ret = 0;
	for (int i = 0; i < m; i++) {
		if (prefixSum + score[i] + nowScore > n) continue;
		ret = max(ret, dfs(prefixSum + score[i], prefixSum + score[i] + nowScore));
	}

	return ret;
}

int run() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	while (t--) {
		cin >> n >> m;

		for (int i = 0; i < m; i++) {
			cin >> score[i];
		}

		memset(dp, -1, sizeof(dp));

		int result = dfs(0, 0);
		cout << (result ? result : -1) << endl;
	}
	return 0;
}

// #include <iostream>

// using namespace std;

// int n, m, score[15], ans, dp[5010][110];

// int getTotalScore() {
//   for (int curRound = 1; curRound < 100; curRound++) {
//     for (int num = 1; num <= n; num++) {
//       if (dp[num][curRound] == -1) continue;
//       for (int sc = 0; sc < m; sc++) {
//         int nextNum = num + dp[num][curRound] + score[sc];
//         dp[nextNum][curRound + 1] = dp[num][curRound] + score[sc];
//       }
//     }
//   }
// }

// int run() {
//   int TEST_CASE;
//   cin >> TEST_CASE;
//   for (int test_case = 0; test_case < TEST_CASE; test_case++) {
//     ans = -1;

//     cin >> n >> m;

//     for (int i = 0; i <= n; i++) {
//       for (int j = 0; j <= 100; j++)
//         dp[i][j] = -1;
//     }

//     for (int i = 0; i < m; i++) {
//       cin >> score[i];
//       dp[score[i]][1] = score[i];  
//     }

//     getTotalScore();

//     int max = -1;
//     for (int i = 1; i < 100; i++)
//       if (max < dp[n][i]) max = dp[n][i];

//     cout << max << '\n';

//     // for (int i = 1; i <= n; i++) {
//     //   for (int j = 1; j <= 10; j++) {
//     //     cout << dp[i][j] << '\t' ;
//     //   }
//     //   cout << '\n';
//     // }
//     // cout << '\n';
//   }

//   return 0;
// }



// #include <iostream>
// #include <algorithm>

// using namespace std;

// int n, m, score[15], memo[5010], did[5010];

// int run() {
//   int TEST_CASE;
//   cin >> TEST_CASE;
//   for (int test_case = 0; test_case < TEST_CASE; test_case++) {
//     cin >> n >> m;

//     for (int i = 0; i < m; i++) cin >> score[i];

//     for (int i = 0; i <= n; i++) {
//       memo[i] = 0;
//       did[i] = 0;
//     }

//     sort(score, score + m);

//     for (int i = 0; i < m; i++) {
//       memo[score[i]] = score[i];
//       did[score[i]] = 1;
//     }

//     for (int i = score[0]; i <= n; i++) {
//       if (did[i] == 0) continue;

//       for (int j = 0; j < m; j++) {
//         int curN = i + score[j] + memo[i];
//         int curScore = memo[i] + score[j];
//         if (curN <= n) {
//           if (memo[curN] < curScore) {
//             did[curN] = 1;
//             memo[curN] = curScore;
//           }
//         }
//       }
//     }

//     if (did[n] == 0) cout << -1 << '\n';
//     else cout << memo[n] << '\n';

//     for (int i = 0; i <= n; i++) cout << memo[i] << ' ';
//     cout << "\n\n";
//   }

//   return 0;
// }