// Gold

#include <iostream>
#include <queue>

// this damn thing always says i'm wrong faq
// but nothing wrong i think...
// if you see this later, try this problem again. PLZ

using namespace std;

typedef struct _calc {
	int start;
	int present;
	int count;
} calc;

calc setCalc(int _start, int _present, int _count) {
	calc tmp;
	tmp.start = _start;
	tmp.present = _present;
	tmp.count = _count;
	return tmp;
}

int getTenOverWhat(int number) {
	int cnt = 0;
	while(number) {
		cnt++;
		number/=10;
	}
	return cnt;
}

bool isPossible(int number, int array[]) {
	while(number) {
		int underTen = number%10;
		if(array[underTen] == 1) return false;
		number /= 10;
	}
	return true;
}

void run() {
	int n, m, broken[20];
	int visited[1111000] = {0, };
	
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int idx;
		cin >> idx;
		broken[idx] = 1;
	}
		
	queue<calc> q;
	
	calc fromHundred, fromGoal;
	
	fromHundred = setCalc(100, 100, 0);
	fromGoal = setCalc(n, n, getTenOverWhat(n));
	
	q.push(fromHundred);
	q.push(fromGoal);
	
	while(!q.empty()) {
		calc tmp = q.front();
		q.pop();
		
		if (visited[tmp.present] == 1) continue;
		
		if (tmp.start == 100) {
			if (tmp.present == n) {
				cout << tmp.count << '\n';
				break;
			}
			if (tmp.present-1 >= 0) q.push(setCalc(tmp.start, tmp.present-1, tmp.count+1));
			if (tmp.present+1 <= 1110000) q.push(setCalc(tmp.start, tmp.present+1, tmp.count+1));
			visited[tmp.present] = 1;
		}
		else {
			if (isPossible(tmp.present, broken)) {
				cout << tmp.count << '\n';
				break;
			}
			if (tmp.present - 1 >= 0) q.push(setCalc(tmp.start, tmp.present-1, tmp.count+1));
			if (tmp.present+1 <= 1110000) q.push(setCalc(tmp.start, tmp.present+1, tmp.count+1));
			visited[tmp.present] = 1;
		}
	}
}



/*
#include <queue>

using namespace std;

bool isPossible(int number, int brkn[], int k) {
	if (number == 0) {
		for (int i =0 ; i <k; i++)
			if (brkn[i] == number) return false;
	}
	
	while(number) {
		int tmp = number%10;
		for (int i = 0; i < k; i++) 
			if (brkn[i] == tmp) return false;
		number /= 10;
	}
	return true;
}

int pow(int a) {
	int num = 0;
	
	if (a == 0) return 1;
	
	while(a) {
		num++;
		a/=10;
	}
	return num;
}

typedef struct GROUP {
	int first;
	int second;
	int third;
} group;

group make_group(int a, int b, int c) {
	group tmp;
	tmp.first = a;
	tmp.second = b;
	tmp.third = c;
	return tmp;
}

void run() {
	int n, m, broken[20], visit[1100010] = {0, };
	
	cin >> n >> m;
	for (int i = 0; i < m; i++) cin >> broken[i];
	
	queue<group> q;

	// 0 means staring from 100, 1 means starting from n
	q.push(make_group(100, 0, 0));
	q.push(make_group(n, pow(n), 1));
	
	if (n == 100) {
		cout << 0 << '\n';
		return;
	}
	
	while(!q.empty()) {
		group a = q.front();
		q.pop();
		
		if (visit[a.first] == 1) continue;
		
		if (a.third == 0) {
			if (a.first == n) {
				cout << a.second << '\n';
				return;
			}
			if (a.first - 1 >= 0) 
				q.push(make_group(a.first-1, a.second+1, a.third));
			q.push(make_group(a.first+1, a.second+1, a.third));
		}
		
		if (a.third == 1) {
			if (isPossible(a.first, broken, m)) {
				cout << a.second << '\n';
				return;
			}
			if (a.first - 1 >= 0) 
				q.push(make_group(a.first-1, a.second+1, a.third));
			q.push(make_group(a.first+1, a.second+1, a.third));		
		}
		
		visit[a.first] = 1;
	}
}
*/

/* we need to use queue
bool isPossible(int goal, int brkn[], int k) {
	if (goal == 0) {
		for (int i =0 ; i <k; i++)
			if (brkn[i] == goal) return false;
	}
	
	while(goal) {
		int tmp = goal%10;
		for (int i = 0; i < k; i++) 
			if (brkn[i] == tmp) return false;
		goal /= 10;
	}
	return true;
}

int pow(int a) {
	int num = 0;
	
	if (a == 0) return 1;
	
	while(a) {
		num++;
		a/=10;
	}
	return num;
}

int planA(int now, int goal, int brkn[], int k, int rival) {
	for (int i = 0; i<500001; i++) {
		if (i >= rival) return 1987654321;
		if (now + i <= 500000 && now + i == goal && isPossible(now + i, brkn, k)) return i;
		if (now - i >= 0 && now - i == goal && isPossible(now - i, brkn, k)) return i;
	}
}

int planB(int now, int goal, int brkn[], int k) {
	for (int i = 0; i<500001; i++) {
		if (goal + i <= 500000 && isPossible(goal+i, brkn, k)) return pow(goal + i) + i;
		if (goal - i >= 0 && isPossible(goal-i, brkn, k)) return pow(goal - i) + i;
	}
}

int howMany(int now, int goal, int brkn[], int k) {
	if (now == goal) return 0;
	
	int b = planB(now, goal, brkn, k);
	int a = planA(now, goal, brkn, k, b);
	
	return a > b ? b : a;
}

void run() {
	int n, m, broken[20];
	
	cin >> n >> m;
	
	for (int i = 0; i < m; i++) cin >> broken[i];
	
	cout << howMany(100, n, broken, m) << '\n';
}
*/