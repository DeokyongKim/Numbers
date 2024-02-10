// Gold

#include <iostream>

#define INF 1987654321

using namespace std;

int min(int a, int b, int c) {return a<b?(a<c?a:c):(b<c?b:c);}
int max(int a, int b, int c) {return a>b?(a>c?a:c):(b>c?b:c);}

int n, input[2][3], minScore[2][3], maxScore[2][3];

int run() {
	
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 3; j++) {
			minScore[i][j] = INF;
			maxScore[i][j] = -INF;
		}
	
	cin >> n;
	
	for (int i = 0; i < 1; i++) {	
		for (int j = 0; j < 3; j++) {
			cin >> input[1][j];
			minScore[1][j] = input[1][j];
			maxScore[1][j] = input[1][j];
		}
	}
	
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < 3; j++) {
			minScore[0][j] = minScore[1][j];
			maxScore[0][j] = maxScore[1][j];
			input[0][j] = input[1][j];
		}
		
		for (int j = 0; j < 3; j++) 
			cin >> input[1][j];
		
		minScore[1][0] = (minScore[0][0]<minScore[0][1]?minScore[0][0]:minScore[0][1]) + input[1][0];
		minScore[1][1] = min(minScore[0][0], minScore[0][1], minScore[0][2]) + input[1][1];
		minScore[1][2] = (minScore[0][2]<minScore[0][1]?minScore[0][2]:minScore[0][1]) + input[1][2];
	
		maxScore[1][0] = (maxScore[0][0]>maxScore[0][1]?maxScore[0][0]:maxScore[0][1]) + input[1][0];
		maxScore[1][1] = max(maxScore[0][0], maxScore[0][1], maxScore[0][2]) + input[1][1];
		maxScore[1][2] = (maxScore[0][2]>maxScore[0][1]?maxScore[0][2]:maxScore[0][1]) + input[1][2];
	}
	
	cout << max(maxScore[1][0], maxScore[1][1], maxScore[1][2]) << ' ';
	cout << min(minScore[1][0], minScore[1][1], minScore[1][2]) << '\n';

	
// 	cout << "\n max: ";
// 	for (int i = 0; i < 3; i++) cout << maxScore[1][i] << ' ';
// 	cout << "\n min: ";
// 	for (int i = 0; i < 3; i++) cout << minScore[1][i] << ' ';
// 	cout << '\n';
	
	return 0;
}