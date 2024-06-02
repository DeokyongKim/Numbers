#include <iostream>

using namespace std;

typedef struct _BLOCK {
  int type;
  int x;
  int y;
} BLOCK;

int n;

BLOCK block[10010] = {0, };

int blue[4][6] = {0, }, green[6][4] = {0, };

int score = 0;

void moveGreen(BLOCK b) {
  if (b.type == 1) {
    int col = b.y;

    for (int row = 0; row < 6; row++) {
      if (row == 5) {
        green[5][col] = 1;
        break;
      } else if (green[row+1][col]) {
        green[row][col] = 1;
        break;
      }
    }
  } else if (b.type == 2) {
    int col1 = b.y, col2 = b.y + 1;

    for (int row = 0; row < 6; row++) {
      if (row == 5) {
        green[5][col1] = 1;
        green[5][col2] = 1;
        break;
      } else if (green[row+1][col1] || green[row+1][col2]) {
        green[row][col1] = 1;
        green[row][col2] = 1;
        break;
      }
    }
  } else if (b.type == 3) {
    int col = b.y;
    
    for (int row = 0; row < 6; row++) {
      if (row == 5) {
        green[5][col] = 1;
        green[4][col] = 1;
        break;
      } else if (green[row+1][col]) {
        green[row][col] = 1;
        green[row-1][col] = 1;
        break;
      }
    }
  }
}

void scoreGreen() {
  for (int row = 0; row < 6; row++) {
    bool full = true;
    for (int col = 0; col < 4; col++) {
      if (green[row][col] == 0) {
        full = false;
        break;
      }
    }

    if (full) {
      score++;
      for (int col = 0; col < 4; col++) green[row][col] = 0;

      for (int tmpRow = row; tmpRow > 0; tmpRow--) {
        for (int col = 0; col < 4; col++) {
          green[tmpRow][col] = green[tmpRow-1][col];
        }
      }

      for (int col = 0; col < 4; col++) green[0][col] = 0;
    }
  }
}

bool isGreenTop() {
  for (int row = 0; row < 2; row++) {
    for (int col = 0; col < 4; col++) {
      if (green[row][col]) return true;
    }
  }
  return false;
}

void downGreen() {
  int deletion = 0;
  
  for (int row = 0; row < 2; row++) {
    for (int col = 0; col < 4; col++) {
      if (green[row][col]) {
        deletion++;
        break;
      }
    }
  }

  for (int row = 5; row >= deletion; row--) {
    for (int col = 0; col < 4; col++) {
      green[row][col] = green[row - deletion][col];
    }
  }

  for (int row = 0; row < 2; row++) {
    for (int col = 0; col < 4; col++) {
      green[row][col] = 0;
    }
  }
}

void putGreen(BLOCK b) {
  moveGreen(b);
  scoreGreen();
  if (isGreenTop()) {
    downGreen();
  }
}

void moveBlue(BLOCK b) {
  if (b.type == 1) {
    int row = b.x;

    for (int col = 0; col < 6; col++) {
      if (col == 5) {
        blue[row][col] = 1;
        break;
      } else if (blue[row][col+1]) {
        blue[row][col] = 1;
        break;
      }
    }
  } else if (b.type == 2) {
    int row = b.x;

    for (int col = 0; col < 6; col++) {
      if (col == 5) {
        blue[row][col] = 1;
        blue[row][col-1] = 1;
        break;
      } else if (blue[row][col+1]) {
        blue[row][col] = 1;
        blue[row][col-1] = 1;
        break;
      }
    }
  } else if (b.type == 3) {
    int row1 = b.x;
    int row2 = b.x+1;

    for (int col = 0; col < 6; col++) {
      if (col == 5) {
        blue[row1][col] = 1;
        blue[row2][col] = 1;
        break;
      } else if (blue[row1][col+1] || blue[row2][col+1]) {
        blue[row1][col] = 1;
        blue[row2][col] = 1;
        break;
      }
    }
  }
}

void scoreBlue() {
  for (int col = 0; col < 6; col++) {
    bool full = true;
    for (int row = 0; row < 4; row++) {
      if (blue[row][col] == 0) {
        full = false;
        break;
      }
    }

    if (full) {
      score++;

      for (int tmpCol = col; tmpCol > 0; tmpCol--) {
        for (int row = 0; row < 4; row++) {
          blue[row][tmpCol] = blue[row][tmpCol - 1];
        }
      }

      for (int row = 0; row < 4; row++) blue[row][0] = 0;
    }
  }
}

bool isBlueTop() {
  for (int col = 0; col < 2; col++) {
    for (int row = 0; row < 4; row++) {
      if (blue[row][col]) return true;
    }
  }

  return false;
}

void downBlue() {
  int deletion = 0;

  for (int col = 0; col < 2; col++) {
    for (int row = 0; row < 4; row++) {
      if (blue[row][col]) {
        deletion++;
        break;
      }
    }
  }

  for (int col = 5; col >= deletion; col--) {
    for (int row = 0; row < 4; row++) {
      blue[row][col] = blue[row][col-deletion];
    }
  }

  for (int col = 0; col < 2; col++) {
    for (int row = 0; row < 4; row++) {
      blue[row][col] = 0;
    }
  }
}

void putBlue(BLOCK b) {
  moveBlue(b);
  scoreBlue();
  if (isBlueTop()) {
    downBlue();
  }
}

int getBlueTile() {
  int sum = 0;

  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 6; col++) {
      sum += blue[row][col];
    }
  }

  return sum;
}

int getGreenTile() {
  int sum = 0;

  for (int row = 0; row < 6; row++) {
    for (int col = 0; col < 4; col++) {
      sum += green[row][col];
    }
  }

  return sum;
}

void printBlueBoard() {
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 6; col++) {
      cout << blue[row][col] << ' ' ;
    }
    cout << '\n';
  }

  cout << '\n';
}

void printGreenBoard() {
  for (int row = 0; row < 6; row++) {
    for (int col = 0; col < 4; col++) {
      cout << green[row][col] << ' ' ;
    }
    cout << '\n';
  }
  cout << '\n';
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) cin >> block[i].type >> block[i].x >> block[i].y;

  for (int blockNumber = 0; blockNumber < n; blockNumber++) {
    putGreen(block[blockNumber]);
    putBlue(block[blockNumber]);

    // cout << blockNumber << ": \n";

    // printBlueBoard();
    // printGreenBoard();
  }

  cout << score << '\n' << getBlueTile() + getGreenTile() << '\n';

  return 0;
}