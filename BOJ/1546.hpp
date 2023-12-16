// Bronze

#include <iostream>

void run() {
	int n;
	float arr[1010];
	std::cin >> n;
	for (int i = 0; i < n; i++) std::cin >> arr[i];
	
	float max = 0;
	for (int i = 0; i < n; i++) 
		if (max < arr[i]) max = arr[i];
	
	for (int i = 0; i < n; i++) arr[i] = arr[i] * 100.0 / max;
	
	float sum = 0.0;
	for (int i = 0; i < n; i++) sum += arr[i];
	
	printf("%f\n", sum/n);
}