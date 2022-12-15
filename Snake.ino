void handleSnakeInput() {
  if (joyState == JoyMovements::JOY_UP) {
    if (rowDir == 0) {
      rowDir = -1;
      colDir = 0;
    }
  } else if (joyState == JoyMovements::JOY_DOWN) {
    if (rowDir == 0) {
      rowDir = 1;
      colDir = 0;
    }
  } else if (joyState == JoyMovements::JOY_RIGHT) {
    if (colDir == 0) {
      colDir = 1;
      rowDir = 0;
    }
  } else if (joyState == JoyMovements::JOY_LEFT) {
    if (colDir == 0) {
      colDir = -1;
      rowDir = 0;
    }
  }
}

bool checkInHistory(byte row, byte col) {
  byte temp = (row << 4) | col;
  for (int i = 0; i < snakeHistoryLength; ++i) {
    if (snakeHistory[i] == temp) {
      return true;
    }
  }
  return false;
}

byte historyPop() {
  byte temp = snakeHistory[0];
  for (int i = 0; i < snakeHistoryLength; ++i) {
    snakeHistory[i] = snakeHistory[i + 1];
  }
  snakeHistoryLength--;
  return temp;
}

void historyPush(int row, int col) {
  snakeHistory[snakeHistoryLength] = (row << 4) | col;
  snakeHistoryLength++;
}