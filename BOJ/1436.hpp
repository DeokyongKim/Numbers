// Silver

#include <iostream>
#include <string>

// Sometimes, just doing can be answer
void run() {
	int n;
	scanf("%d", &n);
	
	int cnt = 0;
	int num = 666;
	while(1) {
		std::string strnum = std::to_string(num);
		
		int is_three = 0;
		for (int i = 0; i < strnum.length(); i++) {
			if (strnum[i] != '6') is_three = 0;
			
			if (strnum[i] == '6') is_three++;
			if (is_three == 3) {
				cnt++;
				break;
			}
		}
		
		if (cnt == n) {
			printf("%d\n", num);
			return;
		}
		num++;
	}
}

/*
FAILED ALGORITHM... MATH WAS NOT GOOD FOR THIS PROBLEM...
#include <math.h>

///뭔가 덜 세고있음....
// 20이랑 21이 같은 숫자임...
int possible(int n) {
	return (int)pow(10, n-3) + (n-3) * 9 *(int)pow(10, n-4);
}

int find666(int n) {
	while(n) {
		int tmp = n;
		int a = tmp%10;
		tmp /= 10;
		int b = tmp%10;
		tmp /= 10;
		int c = tmp%10;
		tmp /= 10;
		
		if (a == 6 && b == 6 && c == 6) return 1;
		n /= 10;
	}
	return 0;
}

void run() {
	int n;
	scanf("%d", &n);
	int i = 3, total = 0;
	while(1) {
		total += possible(i);
		if (total >= n) break;
		i++;
	}
	
	int c = 0;
	if (total == n) c = 1;
	
	printf("%dth: %d < ? < %d, %d < ? <%d\n", n, (int)pow(10, i-1), (int)pow(10, i), total - possible(i), total);
	
	i--;
	total -= possible(i+1);
	
	int cnt = total;
	int start = 1;
	for (int j = 0; j < i + c; j++) start *= 10;
	
	while (cnt != n) {
		start++;
		if(find666(start)) cnt++;
	}
	printf("%d\n", start);
}
*/