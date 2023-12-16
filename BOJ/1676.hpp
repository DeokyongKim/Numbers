// Silver

#include <stdio.h>

void run() {
	int n;
	scanf("%d", &n);
	
	int five = n/5 + n/5/5 + n/5/5/5;
	
	printf("%d\n", five);
}