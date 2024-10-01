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
#include <map>
#include <queue>
#include <math.h>

#define MAX_N 100000

using namespace std;

vector<int> parentIds;
map<int, vector<int> > nodes;
int ans = 0;

void initialize() {
  parentIds.clear();
  nodes.clear();
  ans = 0;
}

void getNodes() {
  int n;
  cin >> n;
  parentIds.push_back(-1);
  parentIds.push_back(0);

  for (int i = 2; i <= n; i++) {
    int tmp;
    cin >> tmp;
    parentIds.push_back(tmp);
    nodes[tmp].push_back(i);
  }
}

int getDistance(int a, int b) {
  int visited[MAX_N] = {0, };

  int aCnt = 1, bCnt = 1;
  visited[a] = aCnt++;
  visited[b] = bCnt++;

  if (a == b) return 0;

  // cout << a << " TO " << b << " IS ";

  while(true) {
    if (parentIds[a] > 0) {
      a = parentIds[a];
      if (visited[a] > 0) {
        // cout << abs(visited[a] + aCnt - 2) << '\n'; 
        return abs(visited[a] + aCnt - 2);
      }
      visited[a] = aCnt++;
    }

    if (parentIds[b] > 0) {
      b = parentIds[b];
      if (visited[b] > 0) {
        // cout << abs(visited[b] + bCnt - 2) << '\n'; 
        return abs(visited[b] + bCnt - 2);
      }
      visited[b] = bCnt++;
    }
  }
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

    for (int i = 0; i < nodes[cur].size(); i++) {
      q.push(nodes[cur][i]);
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