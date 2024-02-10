#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#define MAX 1023
#define LL long long
const LL INF = 1e9;
using namespace std;

int N;
int dx[2] = {+1, -1}; // +1, -1의 계산을 for문으로 하기 위한 배열
LL cache[11][101][(1<<10)+1]; // memoization
// DFS함수
// start : 현재 number(0~9)
// idx : 현재 number의 위치(0~99)
// state : 0~9의 상태를 나타내기 위한 수
LL solve(int start, int idx, int state){
	if(idx == N-1){
		if(state == MAX) return 1;
		else return 0;
	}
	LL& ret = cache[start][idx][state];
	if(ret != -1) return ret;
	ret = 0;
	
	for(int i=0; i<2; i++){
		int next = start + dx[i];
		if(next == 10 || next == -1) continue;
		ret += solve(next, idx + 1, state | 1<<next);
	}
	return ret %= INF;
}

int run(){
	scanf("%d", &N);
	memset(cache, -1, sizeof(cache));
	
	LL ans = 0;
	for(int i=1; i<10; i++)
		ans += solve(i, 0, 1<<i);
	
	printf("%lld \n", ans % INF);
}