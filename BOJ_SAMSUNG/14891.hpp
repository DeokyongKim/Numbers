// Gold

#include <iostream>
#include <vector>

#define GEAR 4
#define TOOTH 8
// 0 1 '2' 3 4 5 '6' 7
#define pii pair<int, int>

using namespace std;

int gear[GEAR][TOOTH];
int k;
pii rotate[101];

void rotateGear(int gearNum, int dir) {
	if (dir > 0) {
		// clockwise
		int tmp = gear[gearNum][TOOTH-1];

		for (int i = TOOTH-1; i >= 0; i--)
			gear[gearNum][i] = gear[gearNum][i-1];

		gear[gearNum][0] = tmp;
	} else if (dir < 0) {
		// counterclockwise
		int tmp = gear[gearNum][0];

		for (int i = 1; i < TOOTH; i++)
			gear[gearNum][i-1] = gear[gearNum][i];

		gear[gearNum][TOOTH-1] = tmp;
	}
} 

void rotateAllGear(int gearNum, int dir) {
	if (gearNum == 0) {
		if (gear[0][2] != gear[1][6]) {
			if (gear[1][2] != gear[2][6]) {
				if (gear[2][2] != gear[3][6]) {
					rotateGear(3, -dir);
				}
				rotateGear(2, dir);
			}
			rotateGear(1, -dir);
		}
		rotateGear(0, dir);
	}

	if (gearNum == 1) {
		if (gear[0][2] != gear[1][6]) {
			rotateGear(0, -dir);
		}
		if (gear[1][2] != gear[2][6]) {
			if (gear[2][2] != gear[3][6]) {
				rotateGear(3, dir);
			}
			rotateGear(2, -dir);
		}
		rotateGear(1, dir);
	}

	if (gearNum == 2) {
		if (gear[2][2] != gear[3][6]) {
			rotateGear(3, -dir);
		}
		if (gear[1][2] != gear[2][6]) {
			if (gear[0][2] != gear[1][6]) {
				rotateGear(0, dir);
			}
			rotateGear(1, -dir);
		}
		rotateGear(2, dir);
	}

	if (gearNum == 3) {
		if (gear[3][6] != gear[2][2]) {
			if (gear[2][6] != gear[1][2]) {
				if (gear[1][6] != gear[0][2]) {
					rotateGear(0, -dir);
				}
				rotateGear(1, dir);
			}
			rotateGear(2, -dir);
		}
		rotateGear(3, dir);
	}
}

int getScore() {
	return gear[0][0] + 2*gear[1][0] + 4*gear[2][0] + 8*gear[3][0];
}

void solve() {
	for (int rotateCount = 0; rotateCount < k; rotateCount++) {
		rotateAllGear(rotate[rotateCount].first-1, rotate[rotateCount].second);
	}

	cout << getScore() << '\n';
}

int main() {	
	for (int i = 0; i < GEAR; i++)
		for (int j = 0; j < TOOTH; j++) {
			char tmp;
			cin >> tmp;
			gear[i][j] = tmp - '0';
		}

	cin >> k;
	for (int i = 0; i < k; i++)
		cin >> rotate[i].first >> rotate[i].second;

	solve();

	return 0;
}