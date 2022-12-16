byte gameMatrix[][MATRIX_SIZE] = {
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
};

unsigned long gameTimer = 0;
unsigned long foodBlinkTimer = 0;
unsigned long foodTimer = 0;
unsigned long snakeBlinkTimer = 0;
unsigned long pauseTime;
byte snakeHistory[64];
byte snakeHistoryLength;
int gameDelay;
bool gameStarted = false;
byte difficulty;
byte lastPrintedTimeLeftSecond = 0;
byte rowSnake;
byte colSnake;
byte rowFood;
byte colFood;

int rowDir;
int colDir;
int nextRowDir;
int nextColDir;

bool foodExists;
bool matrixChanged;
bool gamePaused;
bool gameInfoUpdated;

void runGame() {
  if (!gameStarted) {
    initGame();
  }

  if(joyPress){
    if(gamePaused){
      unpauseGame();
    } else {
      pauseGame();
    }
  }

  if(gamePaused){
    return;
  }

  if (difficulty >= MAX_DIFFICULTY / 2) {
    deleteFood();
  }

  if (!foodExists) {
    generateFood();
  }

  foodBlink();
  snakeBlink();
  handleSnakeInput();
  if (millis() - gameTimer > gameDelay) {
    updateSnakePosition();
    gameTimer = millis();
    matrixChanged = true;
  }

  drawMatrix();
  printGameInfo();
}

void foodBlink() {
  if (difficulty < MAX_DIFFICULTY / 2) {
    if (millis() - foodBlinkTimer > FOOD_BLINK_DELAY) {
      gameMatrix[rowFood][colFood] = 1 - gameMatrix[rowFood][colFood];
      foodBlinkTimer = millis();
      matrixChanged = true;
    }
    return;
  }

  const int currentFoodDelay = map(difficulty, MAX_DIFFICULTY / 2, MAX_DIFFICULTY, MAX_FOOD_DELAY, MIN_FOOD_DELAY);
  const int elapsedTime = millis() - foodTimer;
  const int blinkDelay = elapsedTime <= currentFoodDelay / 2 ? FOOD_BLINK_DELAY : FOOD_BLINK_DELAY / 5;

  if (millis() - foodBlinkTimer > blinkDelay) {
    gameMatrix[rowFood][colFood] = 1 - gameMatrix[rowFood][colFood];
    foodBlinkTimer = millis();
    matrixChanged = true;
  }
}

void snakeBlink() {
  if (millis() - snakeBlinkTimer > SNAKE_DELAY) {
    gameMatrix[rowSnake][colSnake] = 1 - gameMatrix[rowSnake][colSnake];
    snakeBlinkTimer = millis();
    matrixChanged = true;
  }
}

void deleteFood() {
  const int currentFoodDelay = map(difficulty, MAX_DIFFICULTY / 2, MAX_DIFFICULTY, MAX_FOOD_DELAY, MIN_FOOD_DELAY);
  const int elapsedTime = millis() - foodTimer;
  if (elapsedTime > currentFoodDelay) {
    foodExists = false;
    gameMatrix[rowFood][colFood] = 0;
  }
  if (elapsedTime / 1000 != lastPrintedTimeLeftSecond) {
    lastPrintedTimeLeftSecond = elapsedTime / 1000;
    gameInfoUpdated = true;
  }
}

void generateFood() {
  gameMatrix[rowFood][colFood] = 0;
  rowFood = random(0, MATRIX_SIZE - 1);
  colFood = random(0, MATRIX_SIZE - 1);
  while (checkInHistory(rowFood, colFood)) {
    rowFood = random(0, MATRIX_SIZE - 1);
    colFood = random(0, MATRIX_SIZE - 1);
  }
  foodExists = true;
  foodTimer = millis();
}

void processFoodCollect() {
  foodExists = false;
  gameScore += (difficulty + 1) * 10 + snakeHistoryLength * 5;
  gameInfoUpdated = true;
  if (snakeHistoryLength % 3 == 0) {
    // increase difficulty
    difficulty = min(difficulty + 1, MAX_DIFFICULTY - 1);
    gameDelay = map(difficulty, 0, MAX_DIFFICULTY - 1, MAX_GAME_DELAY, MIN_GAME_DELAY);
    gameInfoUpdated = true;
  }
}

void updateSnakePosition() {
  rowDir = nextRowDir;
  colDir = nextColDir;
  historyPush(rowSnake, colSnake);
  if (rowSnake == 0 && rowDir == -1) {
    rowSnake = MATRIX_SIZE - 1;
  } else if (rowSnake == MATRIX_SIZE - 1 && rowDir == 1) {
    rowSnake = 0;
  } else {
    rowSnake += rowDir;
  }

  if (colSnake == 0 && colDir == -1) {
    colSnake = MATRIX_SIZE - 1;
  } else if (colSnake == MATRIX_SIZE - 1 && colDir == 1) {
    colSnake = 0;
  } else {
    colSnake += colDir;
  }

  if (rowSnake == rowFood && colSnake == colFood) {
    processFoodCollect();
    if (gameSettings.soundIsEnabled) {
      tone(buzzerPin, FOOD_BUZZER_FREQUENCY, SNAKE_BUZZER_DURATION);
    }
  } else {
    historyPop();
    if (gameSettings.soundIsEnabled) {
      tone(buzzerPin, SNAKE_BUZZER_FREQUENCY, SNAKE_BUZZER_DURATION);
    }
  }

  if (checkInHistory(rowSnake, colSnake) || snakeHistoryLength == 64) {
    gameStarted = false;
    gameState = GAMEOVER;
  }
}

void initGame() {
  srandom(millis());
  difficulty = constrain(gameSettings.difficulty, 0, MAX_DIFFICULTY - 1);
  gameDelay = map(difficulty, 0, MAX_DIFFICULTY - 1, MAX_GAME_DELAY, MIN_GAME_DELAY);
  snakeHistoryLength = 0;
  for (int i = 0; i < difficulty / 2; ++i) {
    historyPush(0, i);
  }
  colSnake = difficulty / 2;
  rowSnake = 0;
  gameMatrix[rowSnake][colSnake] = 1;
  nextRowDir = rowDir = 0;
  nextColDir = colDir = 1;
  gameScore = 0;
  gameInfoUpdated = true;
  foodExists = false;
  matrixChanged = true;
  gameStartTime = millis();
  gameStarted = true;
  gamePaused = false;
  gamePaused = false;
  lcd.clear();
}

void printGameInfo() {
  if (gameInfoUpdated) {
    gameInfoUpdated = false;
    String top = "Score: " + String(gameScore);
    String bottom;
    if (gamePaused) {
      top = "Paused!";
      bottom = "Press to unpause";
    } else if (difficulty < MAX_DIFFICULTY / 2) {
      bottom = "Difficulty: " + String(difficulty + 1);
    } else {
      const int currentDelay = map(difficulty, MAX_DIFFICULTY / 2, MAX_DIFFICULTY, MAX_FOOD_DELAY, MIN_FOOD_DELAY);
      const int elapsedTime = millis() - foodTimer;
      const unsigned long timeLeft = (elapsedTime <= currentDelay ? (currentDelay - elapsedTime) : 0);
      bottom = "Diff: " + String(difficulty + 1) + " Time: " + String(timeLeft / 1000);
    }
    printLcdLines(top.c_str(), bottom.c_str(), OPTION_NONE);
  }
}

void pauseGame() {
  gamePaused = true;
  pauseTime = millis();
  gameInfoUpdated = true;
  printGameInfo();
}

void unpauseGame() {
  gamePaused = false;
  unsigned long elapsedTime = millis() - pauseTime;
  gameStartTime += elapsedTime;  
  foodBlinkTimer += elapsedTime;  // ignore pause but add so it wont change difference
  snakeBlinkTimer += elapsedTime;
  foodTimer += elapsedTime;
  gameTimer += elapsedTime;
  gameInfoUpdated = true;
  printGameInfo();
}

void drawMatrix() {
  if (!matrixChanged) {
    return;
  }
  matrixChanged = false;

  byte foodValue = gameMatrix[rowFood][colFood];
  byte snakeValue = gameMatrix[rowSnake][colSnake];

  resetMatrix();

  for (int i = 0; i < snakeHistoryLength; ++i) {
    byte row = (snakeHistory[i] & '\xf0') >> 4;
    byte col = snakeHistory[i] & '\x0f';
    gameMatrix[row][col] = 1;
  }
  gameMatrix[rowSnake][colSnake] = snakeValue;
  gameMatrix[rowFood][colFood] = foodValue;
  lightMatrix(gameMatrix);
}

void resetMatrix() {
  for (int i = 0; i < MATRIX_SIZE; ++i) {
    for (int j = 0; j < MATRIX_SIZE; ++j)
      gameMatrix[i][j] = 0;
  }
}