void handleSnakeInput() {
  if (joyState == JoyMovements::JOY_UP) {
    if (rowDir != 1) {
      nextRowDir = -1;
      nextColDir = 0;
    }
  } else if (joyState == JoyMovements::JOY_DOWN) {
    if (rowDir != -1) {
      nextRowDir = 1;
      nextColDir = 0;
    }
  } else if (joyState == JoyMovements::JOY_RIGHT) {
    if (colDir != -1) {
      nextColDir = 1;
      nextRowDir = 0;
    }
  } else if (joyState == JoyMovements::JOY_LEFT) {
    if (colDir != 1) {
      nextColDir = -1;
      nextRowDir = 0;
    }
  }
}

bool checkInHistory(byte row, byte col) {
  byte position = (row << 4) | col;
  for (int i = 0; i < snakeHistoryLength; ++i) {
    if (snakeHistory[i] == position) {
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