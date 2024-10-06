#include <iostream>
#include <time.h>
#include <cstring>
#include <vector>
#include <queue>

#define MAX_N 50
#define MAX_M 50

using namespace std;

typedef struct _COORDINATE {
    int x;
    int y;
    
    bool operator == (_COORDINATE &other) {
        return x == other.x && y == other.y;
    }
} COORDINATE;

const vector<vector<COORDINATE> > directions = {
    {{100, 100}}, 
    {{1, 0}, {-1, 0}, {0, 1}, {0, -1}},
    {{-1, 0}, {1, 0}},
    {{0, -1}, {0, 1}},
    {{-1, 0}, {0, 1}},
    {{1, 0}, {0, 1}},
    {{1, 0}, {0, -1}},
    {{-1, 0}, {0, -1}},
};

int n, m, board[MAX_N][MAX_M], exodusTime;

COORDINATE turnel;

void initialize() {
    memset(board, 0, sizeof(int) * MAX_N * MAX_M);
}

void getInput() {
    cin >> n >> m >> turnel.x >> turnel.y >> exodusTime;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
        }
    }
}

void printArray(int array[MAX_N][MAX_M]) {
    cout << '\n';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << array[i][j] << ' ';
        }
        cout << '\n';
    }
}

bool isOutOfBound(int x, int y) {
    return x < 0 || x >= n || y < 0 || y >= m;
}

bool isConnected(COORDINATE a, COORDINATE b) {
    vector<COORDINATE> aDirections = directions[board[a.x][a.y]];
    vector<COORDINATE> bDirections = directions[board[b.x][b.y]];
    
    bool aToB = false, bToA = false;
    
    for (int i = 0; i < aDirections.size(); i++) {
        COORDINATE next = {a.x + aDirections[i].x, a.y + aDirections[i].y};
        if (next == b) {
            aToB = true;
            break;
        }
    }
    
    for (int i = 0; i < bDirections.size(); i++) {
        COORDINATE next = {b.x + bDirections[i].x, b.y + bDirections[i].y};
        if (next == a) {
            bToA = true;
            break;
        }
    }
    
    return aToB && bToA;
}

typedef struct _QUEUE_TYPE {
    COORDINATE position;
    int enterTime;
} QUEUE_TYPE;

int getPossiblePlaces() {
    int visited[MAX_N][MAX_M] = {0, };
    queue<QUEUE_TYPE> q;
    
    int ans = 1;
    visited[turnel.x][turnel.y] = 1;
    q.push({turnel, 1});
    
    while(!q.empty()) {
        QUEUE_TYPE positionAndTime = q.front();
        q.pop();
        
        COORDINATE position = positionAndTime.position;
        int enterTime = positionAndTime.enterTime;
        
        int dirIdx = board[position.x][position.y];
        
        for (int i = 0; i < directions[dirIdx].size(); i++) {
            int nx = position.x + directions[dirIdx][i].x;
            int ny = position.y + directions[dirIdx][i].y;
            
            if (isOutOfBound(nx, ny) || visited[nx][ny] || enterTime >= exodusTime || board[nx][ny] <= 0) continue;
            
            if (isConnected(position, {nx, ny})) {
                q.push({{nx, ny}, enterTime+1});
                ans++;
                visited[nx][ny] = 1;
            }
        }
    }
    
    // printArray(visited);
    
    return ans;
}

int solve() {
    initialize();
    
    getInput();
    
    return getPossiblePlaces();
}

int run() {
    int testCases;
    cin >> testCases;
    
    for (int i = 1; i <= testCases; i++) {
        cout << "#" << i << " " << solve() << '\n';
    }
    
    return 0;
}

int main() {
    clock_t solveStartTime, solveEndTime;
    double solveDuration;
    
    solveStartTime = clock();
    
    run();
    
    solveEndTime = clock();
    
    solveDuration = (double)(solveEndTime - solveStartTime) / CLOCKS_PER_SEC;
    
    cout << solveDuration << '\n';
    
    return 0;
}