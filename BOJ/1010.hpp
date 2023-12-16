// Silver

#include <stdio.h>

void run() {
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++) {
		long long int n, m, ans = 1;
		scanf("%lld %lld", &n, &m);
		
		for (long long int j = 0; j < n; j++) {
			ans = ans * (m - j) / (j + 1);
		}
		printf("%lld\n", ans);
	}
}