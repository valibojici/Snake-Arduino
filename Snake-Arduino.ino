#include <LiquidCrystal.h>
#include <EEPROM.h>
#include "LedControl.h"
#include "Constants.h"
#include "Settings.h"
#include "Player.h"

Settings gameSettings;
LedControl ledMatrix = LedControl(dinPin, clockPin, loadPin, 0);  //DIN, CLK, LOAD, No. DRIVER
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int gameScore = 0;
unsigned long gameStartTime = 0;
GameState gameState = GameState::INTRO;
GameState lastGameState = GameState::GAMERUNNING;
JoyMovements joyState;
byte joyPress;

void setup() {
  loadFromEEPROM();
  loadLcdCharacters();
  pinMode(contrastPin, OUTPUT);
  pinMode(backlightPin, OUTPUT);
  pinMode(swPin, INPUT_PULLUP);
}

GameStateFunction gameStateFunctions[] = {
  intro,
  mainMenu,
  settingsMenu,
  settingsSubMenu,
  settingsSubMenu,
  settingsSubMenu,
  settingsSubMenu,
  settingsSubMenu,
  aboutMenu,
  howToPlayMenu,
  highscoresMenu,
  gameOverMenu,
  newHighscore,
  resetHighscores,
  runGame,
};

void loop() {
  joyState = getJoyMovement();
  joyPress = joyPressed();

  gameStateFunctions[gameState]();
  checkGameStateChange();
}

void checkGameStateChange() {
  if (gameState != lastGameState) {
    if (gameState != GAMERUNNING) {
      lightMatrixByRows(matrixMenuImages[gameState]);
    }
    lastGameState = gameState;
  }
}

void lightMatrixByRows(const int array[]) {
  if (array == nullptr) {
    for (int row = 0; row < MATRIX_SIZE; ++row) {
      ledMatrix.setRow(0, row, 0);
    }
    return;
  }
  for (int row = 0; row < MATRIX_SIZE; ++row) {
    ledMatrix.setRow(0, row, array[row]);
  }
}

void lightMatrix(byte matrix[][MATRIX_SIZE]) {
  for (int i = 0; i < MATRIX_SIZE; ++i) {
    for (int j = 0; j < MATRIX_SIZE; ++j) {
      ledMatrix.setLed(0, i, j, matrix[i][j]);
    }
  }
}

void updateSettings() {
  const int contrastVal = map(gameSettings.lcdContrast, 0, MAX_LCD_CONTRAST - 1, MIN_LCD_CONTRAST_OUTPUT, MAX_LCD_CONTRAST_OUTPUT);
  const int backlightVal = map(gameSettings.lcdBrightness, 0, MAX_LCD_BRIGHTNESS - 1, MIN_LCD_BRIGHTNESS_OUTPUT, MAX_LCD_BRIGHTNESS_OUTPUT);
  const int brightnessVal = map(gameSettings.matrixBrightness, 0, MAX_MATRIX_BRIGHTNESS - 1, 0, 15);
  analogWrite(contrastPin, contrastVal);
  analogWrite(backlightPin, backlightVal);
  ledMatrix.setIntensity(0, brightnessVal);
}

void loadLcdCharacters(){
  lcd.createChar(ARROW_CODE, arrow);
  lcd.createChar(ARROW_DOWN_CODE, arrowDown);
  lcd.createChar(ARROW_UP_CODE, arrowUp);
}