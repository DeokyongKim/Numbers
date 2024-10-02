/////////////////////////////////////////////////////////////////////////////////////////////
// 기본 제공코드는 임의 수정해도 관계 없습니다. 단, 입출력 포맷 주의
// 아래 표준 입출력 예제 필요시 참고하세요.
// 표준 입력 예제
// int a;
// float b, c;
// double d, e, f;
// char g;
// char var[256];
// long long AB;
// cin >> a;                            // int 변수 1개 입력받는 예제
// cin >> b >> c;                       // float 변수 2개 입력받는 예제 
// cin >> d >> e >> f;                  // double 변수 3개 입력받는 예제
// cin >> g;                            // char 변수 1개 입력받는 예제
// cin >> var;                          // 문자열 1개 입력받는 예제
// cin >> AB;                           // long long 변수 1개 입력받는 예제
/////////////////////////////////////////////////////////////////////////////////////////////
// 표준 출력 예제
// int a = 0;                            
// float b = 1.0, c = 2.0;               
// double d = 3.0, e = 0.0; f = 1.0;
// char g = 'b';
// char var[256] = "ABCDEFG";
// long long AB = 12345678901234567L;
// cout << a;                           // int 변수 1개 출력하는 예제
// cout << b << " " << c;               // float 변수 2개 출력하는 예제
// cout << d << " " << e << " " << f;   // double 변수 3개 출력하는 예제
// cout << g;                           // char 변수 1개 출력하는 예제
// cout << var;                         // 문자열 1개 출력하는 예제
// cout << AB;                          // long long 변수 1개 출력하는 예제
/////////////////////////////////////////////////////////////////////////////////////////////

#include<iostream>
#include <vector>
#include <queue>
#include <math.h>
#include <cstring>

#define MAX_N 100000

using namespace std;

typedef struct _NODE {
  int depth;
  vector<int> children;
} NODE;

NODE nodes[MAX_N];
long long int ans = 0;
int dp[MAX_N][17];

void initialize() {
  ans = 0;
  memset(dp, 0, sizeof(int) * MAX_N * 17);
}

void getNodes() {
  int n;
  cin >> n;

  nodes[1].children.clear();
  nodes[1].depth = 0;

  for (int i = 2; i <= n; i++) {
    nodes[i].children.clear();
    int tmp;
    cin >> tmp;
    dp[i][0] = tmp;
    nodes[tmp].children.push_back(i);
    nodes[i].depth = nodes[tmp].depth + 1;

    for (int id = 1; id < floor(log2(nodes[i].depth)) + 1; id++) {
      dp[i][id] = dp[dp[i][id-1]][id-1];
    }
  }
}

int getCommonAncestor(int a, int b) {
 // LCA algorithm
  if (nodes[a].depth > nodes[b].depth) {
    a = dp[a][0];
  } else if (nodes[b].depth > nodes[a].depth) {
    b = dp[b][0];
  }

  if (a != b) {
    for (int height = ceil(log2(nodes[a].depth)); height >= 0; height--) {
      if (nodes[a].depth < pow(2, height)) continue;
      
      if (dp[a][height] != 0 && dp[a][height] != dp[b][height]) {
        a = dp[a][height];
        b = dp[b][height];
      }
    }

    a = dp[a][0];
  }

  return a;
}

long long int getDistance(int a, int b) {
  int commonAncestor = getCommonAncestor(a, b);

  return nodes[a].depth - nodes[commonAncestor].depth + nodes[b].depth - nodes[commonAncestor].depth;
}

void bfs() {
  queue<int> q;
  q.push(1);
  int nowPosition = q.front();

  while(!q.empty()) {
    int cur = q.front();
    q.pop();

    ans += getDistance(nowPosition, cur);
    nowPosition = cur;

    for (int i = 0; i < nodes[cur].children.size(); i++) {
      q.push(nodes[cur].children[i]);
    }
  }
}

int run()
{
	int test_case;
	int T;

	cin>>T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for(test_case = 1; test_case <= T; ++test_case)
	{
    initialize();

    getNodes();

    bfs();

    cout << "#" << test_case << ' ' << ans << '\n';
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}