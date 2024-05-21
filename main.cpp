#include "./BOJ_SAMSUNG/17822.hpp"
#include <time.h>

int main() {
	clock_t start, end;
	double duration;

	freopen("input.txt", "r", stdin);

	start = clock();

	run();

	end = clock();

	duration = (double)(end - start) / CLOCKS_PER_SEC;
	cout << duration << '\n';

	return 0;
}
