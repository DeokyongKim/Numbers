#include <iostream>
#include <math.h>

using namespace std;

int n, slide;
int board[110][110];
int ans;

bool isSlideAble(int line[], int curIdx, int dir) {	
	int nowVal = abs(line[curIdx]);
	if (dir == -1) {
		// postVal > nowVal
		if (line[curIdx] < 0) return false;
		if (curIdx - (slide-1) < 0) return false;

		for (int i = 0; i < slide; i++) 
			if (nowVal != line[curIdx + dir*i]) return false;
	} else if (dir == 1) {
		// postVal < nowVal
		if (curIdx + slide >= n) return false;

		for (int i = 0; i < slide; i++)
			if (nowVal-1 != line[curIdx + dir*i + 1]) return false;
	}

	return true;
}

void makeSlide(int line[], int curIdx, int dir) {
	if (dir == -1)
		// postVal > nowVal
		for (int i = 0; i < slide; i++)
			line[curIdx + dir*i] *= -1;
	else if (dir == 1)
		// postVal < nowVal
		for (int i = 0; i < slide; i++)
			line[curIdx + dir*i + 1] *= -1;
}

void checkLine(int line[], int row, int col) {
	for (int i = 0; i < n; i++) {
		if (i >= n-1) {
			// if (row >= 0) cout << "ROW: " << row << '\n';
			// else if (col >= 0) cout << "COL: " << col << '\n';
			// else cout << "ERR: " << row << ' ' << col << '\n';

			ans++;
			return;
		}

		int nowVal = abs(line[i]);
		int postVal = line[i+1];
		int subVal = nowVal - postVal;

		if (subVal > 1 || subVal < -1) return;

		if (subVal == 0) continue;

		// nowVal > postVal
		if (subVal == 1) {
			bool slidable = isSlideAble(line, i, subVal);
			if (!slidable) return;
			makeSlide(line, i, subVal);
			i += (slide-1);
		}

		// postVal > nowVal
		if (subVal == -1) {
			bool slidable = isSlideAble(line, i, subVal);
			if (!slidable) return;
			makeSlide(line, i, subVal);
		}
	}
}

int run() {
	cin >> n >> slide;
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++)
			cin >> board[i][j];

	// watch each row
	for (int row = 0; row < n; row++) {
		int tmpline[110] = {0, };
		for (int col = 0; col < n; col++)
			tmpline[col] = board[row][col];

		checkLine(tmpline, row, -1);
	}

	// watch each col
	for (int col = 0; col < n; col++) {
		int tmpline[110] = {0, };
		for (int row = 0; row < n; row++)
			tmpline[row] = board[row][col];

		checkLine(tmpline, -1, col);
	}

	cout << ans << '\n';

	return 0;
}