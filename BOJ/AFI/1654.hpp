// Silver

#include <iostream>
#include <algorithm>
 
int k, n;
int arr[10000];
 
long long getCount(long long size) {
    long long cnt = 0;
 
    //k개의 랜선을 size(mid)로 잘라서 나오는 개수를 더해준다. 
    for (int i = 0; i < k; i++) {
        cnt += (arr[i] / size);
    }
 
    return cnt;
}
 
void run() { 
    std::cin >> k >> n;
    for (int i = 0; i < k; i++) std::cin >> arr[i];
 
    //입력 받은 랜선길이를 정렬한다.
    std::sort(arr, arr + k);
 
    int ans;
 
    //자를 수 있는 가장 작은 단위인 1이 left값
    long long left = 1;
    //자를 수 있는 가장 큰 단위(최댓값)인 arr의 마지막 값이 right 
    long long right = arr[k - 1];
 
 
 
    //이분 탐색
    while (left <= right) {

        long long mid = (left + right) / 2;
 
        //mid값으로 잘랐을때 나오는 랜선의 개수를 구한다
        long long cnt = getCount(mid);
 
        //mid값으로 잘라서 나온 랜선의 개수가 n이상이면 더 큰 값으로 잘라도 되므로 left값이 앞으로 간다.
        //현재 최대 길이는 mid값 만큼 자른 경우
        if (cnt >= n) {
            left = mid + 1;
            ans = mid;
        }
        else {
            //현재 mid값으로 랜선을 자르면 n개를 못만드는 경우
            //크기르 줄이기 위해 right를 mid앞쪽으로 당긴다.
            right = mid - 1;
        }
    }
 
    std::cout << ans << '\n';
}


/*
Give up... idk what's wrong...
#include <vector>

void run() {
	int k, n;
	long long int min = 1, max = 0;
	std::vector<int> arr;
	std::cin >> k >> n;
	for (int i = 0; i < k; i++) {
		int tmp;
		std::cin >> tmp;
		
		if (max < tmp) max = (long long int)tmp;
		arr.push_back(tmp);
	}
	
	long long int mid = (min + max)/2;
	while(min != max) {
		mid = (min + max)/2;
		
		int cnt = 0;
		for (int i = 0; i < k; i++) cnt += (int)(arr[i] / mid);
		
		//printf("cnt: %d min: %d mid: %d max: %d\n", cnt, min, mid, max);
		
		if (cnt >= n) min = mid + 1;
		else max = mid;
	}
	
	int tmpcnt = 0;
	for (int i = 0; i < k; i++) tmpcnt += (int)(arr[i] / mid);
	
	//printf("LAST CHECK : %d\n", tmpcnt);
	
	if (tmpcnt < n) printf("%lld\n", mid-1);
	else printf("%lld\n", mid);
}
*/

/*
Logical Error and Out of Time
void run() {
	int k, n;
	std::vector<int> arr;
	std::cin >> k;
	std::cin >> n;
	for (int i = 0; i < k; i++) {
		int tmp;
		std::cin >> tmp;
		arr.push_back(tmp);
	}
	
	int min = 2147483647;
	int max = 0;
	
	for (int i = 0; i < k; i++) {
		if (min > arr[i])
			min = arr[i];
		if (max < arr[i])
			max = arr[i];
	}
	
	for (int len = max; len > 0; len--) {
		int sum = 0;
		for (int i = 0; i < k; i++) {
			sum += (int)(arr[i] / len);
		}
		if (sum >= n) {
			printf("%d\n", len);
			break;
		}
	}
}
*/