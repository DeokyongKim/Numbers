#include <iostream>
#include <time.h>
#include <vector>
#include <math.h>

#define MAX_USER 2

using namespace std;

typedef struct _COORDINATE {
    int x;
    int y;
} COORDINATE;

typedef struct _CHARGER {
    COORDINATE position;
    int coverage;
    int performance;
} CHARGER;

const COORDINATE directions[5] = {
    {0, 0},
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1},
};

vector<COORDINATE> moveHistory[MAX_USER];
vector<CHARGER> chargers;
COORDINATE users[MAX_USER];

int maxCharged = 0;

void initialize() {
    for (int i = 0; i < MAX_USER; i++) {
        moveHistory[i].clear();
    }
    
    users[0] = {1, 1};
    users[1] = {10, 10};
    
    chargers.clear();
    maxCharged = 0;
}

void getInput() {
    int moveNum, chargerNum;
    
    cin >> moveNum >> chargerNum;
    
    for (int userNum = 0; userNum < MAX_USER; userNum++) {
        moveHistory[userNum].push_back(directions[0]);
        for (int i = 0; i < moveNum; i++) {
            int dirIdx;
            cin >> dirIdx;
            
            moveHistory[userNum].push_back(directions[dirIdx]);
        }
    }
    
    for (int i = 0; i < chargerNum; i++) {
        CHARGER charger;
        
        cin >> charger.position.y >> charger.position.x >> charger.coverage >> charger.performance;
        
        chargers.push_back(charger);
    }
}

int getRange(COORDINATE a, COORDINATE b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

bool isInRange(COORDINATE a, CHARGER charger) {
    // cout << getRange(a, charger.position) << " VS " << charger.coverage << " : " << (getRange(a, charger.position) <= charger.coverage ? 1 : 0) << '\n';
    return getRange(a, charger.position) <= charger.coverage;
}

void moveUsers() {
    for (int i = 0; i < moveHistory[0].size(); i++) {
        for (int userIdx = 0; userIdx < MAX_USER; userIdx++) {
            int nx = users[userIdx].x + moveHistory[userIdx][i].x;
            int ny = users[userIdx].y + moveHistory[userIdx][i].y;
            users[userIdx] = {nx, ny};
        }
        
        // cout << "A: " << users[0].x << ", " << users[0].y << '\n';
        // cout << "B: " << users[1].x << ", " << users[1].y << '\n';
        
        int maxSum = 0;
        
        int aCharge = 0, bCharge = 0;
        
        for (int a = 0; a < chargers.size(); a++) {
            for (int b = 0; b < chargers.size(); b++) {
                int partialSum = 0;
                int pa = 0, pb = 0;
                
                bool aIn = isInRange(users[0], chargers[a]);
                bool bIn = isInRange(users[1], chargers[b]);
                
                if (!aIn && !bIn) {
                    // cout << "ONE! ";
                    continue;
                }
                else if (!aIn && bIn) {
                    partialSum = chargers[b].performance;
                    pb = partialSum;
                    // cout << "TWO! ";
                }
                else if (aIn && !bIn) {
                    partialSum = chargers[a].performance;
                    pa = partialSum;
                    // cout << "THREE! ";
                }
                else {
                    // cout << "FOUR! ";
                    if (a == b) {
                        partialSum = chargers[a].performance;
                        pa = partialSum / 2;
                        pb = partialSum / 2;
                    }
                    else {
                        partialSum = chargers[a].performance + chargers[b].performance;
                        pa = chargers[a].performance;
                        pb = chargers[b].performance;
                    }
                    
                }
                
                if (partialSum > maxSum) {
                    maxSum = partialSum;
                    aCharge = pa;
                    bCharge = pb;
                }
            }
        }
        // cout << "AT " << i << " MAX SUM: " << maxSum << " A: " << aCharge << " B: " << bCharge << '\n';
        
        maxCharged += maxSum;
    }
}

int solve() {
    initialize();
    
    getInput();
    
    moveUsers();
    
    return maxCharged;
}

int run() {
    int testCases;
    cin >> testCases;
    
    for (int i = 1; i <= testCases; i++) {
        cout << "#" << i << " " << solve() << '\n';
    }
}