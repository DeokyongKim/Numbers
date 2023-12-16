// Bronze

// https://www.acmicpc.net/problem/10807
#include <stdio.h>

void run() {
	int n, arr[105], v;
	scanf("%d", &n);
	for (int i = 0; i <n; i++) scanf("%d", arr + i);
	scanf("%d", &v);
	int cnt = 0;
	for (int i = 0; i <n; i++) if (arr[i] == v) cnt++;
	printf("%d", cnt);
}
