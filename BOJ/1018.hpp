// Silver

#include <stdio.h>
#include <stdlib.h>

void run() {
	int n, m, map[60][60] = {0, };
	scanf("%d %d", &n, &m);
	
	int ans1[60][60] = {0, }, ans2[60][60] = {0, };
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			ans1[i][j] = (((i+j)%2==0) ? 1:0);
			ans2[i][j] = (((i+j)%2==0) ? 0:1);
		}
	
	for (int i = 0; i<n; i++)
		for (int j = 0; j < m; j++) {
			char c;
			scanf(" %c", &c);
			map[i][j] = (c=='W'?1:0);
			ans1[i][j] = abs(map[i][j] - ans1[i][j]);
			ans2[i][j] = abs(map[i][j] - ans2[i][j]);
		}
	
	int change1 = 198765432, change2 = 198765432;
	for (int i = 0; i <= n-8; i++)
		for (int j = 0; j <= m-8; j++) {
			int tmp1 = 0, tmp2 = 0;
			
			for (int k = i; k < i + 8; k++)
				for (int l = j; l < j + 8; l++) {
					tmp1 += ans1[k][l];
					tmp2 += ans2[k][l];
				}
			
			if (change1 > tmp1) change1 = tmp1;
			if (change2 > tmp2) change2 = tmp2;
		}
	
	printf("%d\n", change1>change2?change2:change1);
}