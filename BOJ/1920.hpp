// Silver

#include <iostream>
#include <algorithm>
#define MAX 100000
using namespace std;
int n, m, num;
int arr[MAX];

void solution(int num){
    int start = 0;
    int end = n - 1;
    int mid;

    while(start <= end){
        mid = (start + end) / 2;

        if(arr[mid] == num){
            cout << 1 << "\n";
            return;
        }
        else if(arr[mid] < num){
            start = mid + 1;
        }
        else if(arr[mid] > num){
            end = mid - 1;
        }
    }
    
    cout << 0 << "\n";
    return;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    bool flag = false;
    cin >> n;
    
    for(int i = 0 ; i < n ; i++) cin >> arr[i];
    sort(arr, arr + n);
    
    cin >> m;
    
    for(int i = 0 ; i < m ; i++){
        cin >> num;
        solution(num);
    }

    return 0;
}