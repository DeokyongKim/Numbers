#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int n, s, ans = 1987654321;

typedef struct _WORK {
	int imp = 0;
	int time = 0;
	int bef = 0;
	int done[1010] = {0, };
} WORK;

WORK work[1010];

queue<WORK> q;

int run() {
	cin >> n >> s;
	
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < n; j++) {
			if (i == 0) cin >> work[j].imp;
			if (i == 1) cin >> work[j].time;
			if (i == 2) cin >> work[j].bef;
		}
	
	// check possibility
	int check_sum = 0, chk = 0, check_done[1010] = {0, };
	for (; chk < n && check_sum<s; chk++) {
		if (check_done[chk] == 0) {
			if (work[chk].bef == 0) {
				check_done[chk] = 1;
				check_sum += work[chk].imp;
			} else if (check_done[work[chk].bef-1]) {
				check_done[chk] = 1;
				check_sum += work[chk].imp;
			}
		}
	}
	if (chk == n && check_sum<s) {
		cout << -1 << '\n';
		return 0;
	}
		
	// for (int i = 0; i < 4; i++){
	// 	for (int j = 0; j < n; j++) {
	// 		if (i == 0) cout << work[j].imp << ' ';
	// 		if (i == 1) cout << work[j].time << ' ';
	// 		if (i == 2) cout << work[j].bef << ' ';
	// 		if (i == 3) cout << work[j].index+1 << ' ';
	// 	}
	// 	cout << '\n';
	// }	

	// bfs
	for (int i = 0; i < n; i++)
		if (work[i].bef == 0) {
			work[i].done[i] = i+1;
			q.push(work[i]);
		}
	
	while(!q.empty()) {
		WORK now = q.front();
		q.pop();
				
		if (now.imp >= s) {
			if (ans > now.time) {ans = now.time;
			for (int j = 0; j < n; j++) cout << now.done[j] << ' ';
			cout << " : " << now.time << " / imp: " << now.imp;
								 cout << '\n';
								}
			continue;
		}
		
		for (int i = 0; i < n; i++) {
			if (now.done[i] == 0) {
				if (work[i].bef == 0) {
					now.done[i] = i+1;
					WORK tmp_work;
					tmp_work.imp = now.imp + work[i].imp;
					tmp_work.time = now.time + work[i].time;
					tmp_work.bef = now.bef;
					for (int j = 0; j < n; j++) tmp_work.done[j] = now.done[j];
					
					if (tmp_work.time > ans) continue;
					q.push(tmp_work);
				} else if (now.done[work[i].bef-1]) {
					now.done[i] = i+1;
					WORK tmp_work;
					tmp_work.imp = now.imp + work[i].imp;
					tmp_work.time = now.time + work[i].time;
					tmp_work.bef = now.bef;
					for (int j = 0; j < n; j++) tmp_work.done[j] = now.done[j];
					
					if (tmp_work.time > ans) continue;
					q.push(tmp_work);
				}
				
				
			}
		}
	}
	
	// for (int i = 0 ; i < n; i++){
	// 	for (int j = 0; j < n; j++) cout << visited[i][j] << ' ' ;
	// 	cout << '\n';
	// }
	
	cout << ans << '\n';
	
	return 0;
}