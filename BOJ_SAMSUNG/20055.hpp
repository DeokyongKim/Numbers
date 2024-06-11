#include <iostream>

using namespace std;

typedef struct _BELT {
    int robot;
    int durability;
} BELT;

int n, k;
BELT belt[300];

bool isEnd() {
    int cnt = 0;
    
    for (int i = 1; i <= 2*n; i++) {
        if (!belt[i].durability) cnt++;
    }
    
    if (cnt >= k) return true;
    return false;
}

void moveBelt() {
    BELT lastOne = belt[2*n];
    
    for (int i = 2*n; i > 1; i--) {
        belt[i].robot = belt[i-1].robot;
        belt[i].durability = belt[i-1].durability;
    }
    
    belt[1].robot = lastOne.robot;
    belt[1].durability = lastOne.durability;
    
    if (belt[n].robot) {
        belt[n].robot = 0;
    }
}

void moveRobot() {
    if (belt[2*n].robot) {
        if (belt[1].durability) {
            belt[1].durability--;
            belt[1].robot = belt[2*n].robot;
            belt[2*n].robot = 0;
        }
    }
    
    for (int i = 2*n-1; i > 0; i--) {
        if (belt[i].robot && belt[i+1].durability && !belt[i+1].robot) {
            if (i+1 != n) {
                belt[i+1].robot = belt[i].robot;
            }
            
            belt[i+1].durability--;
            belt[i].robot = 0;
        }
    }
}

void putRobot() {
    if (belt[1].durability) {
        belt[1].robot = 1;
        belt[1].durability--;
    }
}

void solve() {
    int level = 0;
    
    while(!isEnd()) {
        moveBelt();
        moveRobot();
        putRobot();
        level++;
    }
    
    cout << level << '\n';
}

int run()
{
    cin >> n >> k;
    
    for (int i = 1; i <= 2*n; i++) {
        cin >> belt[i].durability;
    }
    
    solve();

    return 0;
}
