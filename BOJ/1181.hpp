// Silver

// c++을 배울 필요가 있다

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool comp(string a, string b) {
	if (a.length() == b.length()) {
		for (int i = 0; i < a.length(); i++)
			if (a[i] != b[i])
				return a[i] < b[i];
	}
	
	return a.length() < b.length();
}

void run() {
	int n;
	cin >> n;
	
	vector<string> str;
	for (int i = 0; i < n; i++) {
		string a;
		cin >> a;
		str.push_back(a);
	}
	
	sort(str.begin(), str.end(), comp);
	cout << str[0] << '\n';
	for (int i = 1; i < n; i++) {
		if (str[i] == str[i-1]) continue;
		cout << str[i] << '\n';
	}
}


/*
FAILED IDEA 2
#include <string.h>

void run() {
	int n;
	scanf("%d", &n);
	
	char str[20001][51];
	int num[20001] = {0, };
	for (int i = 0; i < n; i++) {
		scanf(" %s", str[i]);
		for (int j = 0; str[i][j]; j++) {
			num[i] += int(str[i][j] - 'a' + 1);
			num[i] *= 27;  // too large...
		}
	}
	
	for (int i = 0; i < n; i++)
		printf("%s %d\n", str[i], num[i]);
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			if (num[j] > num[j + 1]) {
				int ntmp = num[j];
				num[j] = num[j+1];
				num[j+1] = ntmp;
				char stmp[51];
				strcpy(stmp, str[j]);
				strcpy(str[j], str[j+1]);
				strcpy(str[j+1], stmp);
			}
		}
	}
	
	printf("\n======\n");
	for (int i = 0; i < n; i++)
		printf("%s\n", str[i]);
}
*/

/*
FAILED IDEA 1
#include <string.h>

void run() {
	int n;
	scanf("%d", &n);
	
	char str[20001][51];
	int len[20001];
	for (int i = 0; i < n; i++) {
		scanf(" %s", str[i]);
		int length = 0;
		for(;str[i][length];length++);
		len[i] = length;
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n-1; j++) {
			if (len[j] > len[j+1]) {
				char tmp[51];
				strcpy(tmp, str[j]);
				strcpy(str[j], str[j+1]);
				strcpy(str[j+1], tmp);
				int temp;
				temp = len[j];
				len[j] = len[j+1];
				len[j+1] = temp;
			}
		}
	}
	
	for (int j = 0; j < n-1; j++) 
		if (len[j] == len[j+1]) {
			int k = 0;
			for (;k < len[j] && str[j][k] == str[j+1][k]; k++);
			if (k == len[j]) {
				for (int l = j+1; l < n -1; l++) {
					strcpy(str[l], str[l + 1]);
					len[l] = len[l+1];
				}
				n--;
			}
		}
	
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<n-1; j++) {
			if (len[j] == len[j+1]) {
				for (int k = 0; k < len[j]; k++) {
					if (int(str[j][k]) > int(str[j+1][k])) {
						char tmp[51];
						strcpy(tmp, str[j]);
						strcpy(str[j], str[j+1]);
						strcpy(str[j+1], tmp);
						break;
					}
				}
			}
		}
	}
	
	printf("--->%d\n", n);
	for (int i = 0; i < n; i++)
		printf("%s\n", str[i]);
}
*/