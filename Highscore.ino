void resetHighscores() {
  const int delay = 2000;
  static bool reseted = false;
  static unsigned long timer = 0;
  if (!reseted) {
    timer = millis();
    reseted = true;
    gameSettings.highscoresCount = 0;
    saveToEEPROM();
    printLcdLines("Highscores", "reseted!", OPTION_NONE);
    timer = millis();
  }

  if (millis() - timer > delay) {
    reseted = false;
    gameState = SETTINGS;
  }
}

bool isNewHighscore() {
  if (gameSettings.highscoresCount < MAX_HIGHSCORES_COUNT) {
    return true;
  }
  return gameScore > gameSettings.highscores[MAX_HIGHSCORES_COUNT - 1].score;
}

void insertNewHighscore(const String& name) {
  int& highscoresCount = gameSettings.highscoresCount;

  byte position = MAX_HIGHSCORES_COUNT - 1;
  if (highscoresCount < MAX_HIGHSCORES_COUNT) {
    position = highscoresCount;  // 1 after the end
    highscoresCount++;
  }
  while (position > 0 && gameSettings.highscores[position - 1].score < gameScore) {
    strcpy(gameSettings.highscores[position].name, gameSettings.highscores[position - 1].name);
    gameSettings.highscores[position].score = gameSettings.highscores[position - 1].score;
    position--;
  }
  strcpy(gameSettings.highscores[position].name, name.c_str());
  gameSettings.highscores[position].score = gameScore;

  saveToEEPROM();
}

void newHighscore() {
  static bool menuChanged = true;
  static String name = "AAAAA";
  static byte cursorPos = 0;
  const int LETTER_START_INDEX = 5;
  const int MAX_CURSOR_POS = 5;
  const int ARROW_INDEX = 11;

  if (menuChanged) {
    menuChanged = false;
    printLcdLines("New highscore!", getNewHighscoreText(name).c_str(), OPTION_NONE);
    if (cursorPos >= 0 && cursorPos <= MAX_CURSOR_POS-1) {
      lcd.setCursor(cursorPos + LETTER_START_INDEX, 1);
    } else {
      lcd.setCursor(ARROW_INDEX, 1);
    }
    lcd.blink();
  }

  if (joyState == JOY_LEFT && cursorPos > 0) {
    cursorPos--;
    menuChanged = true;
  } else if (joyState == JOY_RIGHT && cursorPos < MAX_CURSOR_POS) {
    cursorPos++;
    menuChanged = true;
  } else if ((joyState == JOY_UP || joyState == JOY_DOWN) && cursorPos != MAX_CURSOR_POS) {
    char letter = name.charAt(cursorPos);
    if (joyState == JOY_UP) {
      letter = letter + 1 > 'Z' ? 'A' : letter + 1;
    } else {
      letter = letter - 1 < 'A' ? 'Z' : letter - 1;
    }
    name.setCharAt(cursorPos, letter);
    menuChanged = true;
  }

  if (joyPress && cursorPos == MAX_CURSOR_POS) {
    insertNewHighscore(name);
    lcd.noBlink();
    menuChanged = true;
    cursorPos = 0;
    name = String("AAAAA");
    gameState = MAINMENU;
  }
}

String getNewHighscoreText(String name) {
  return String("Name ") + name + String(" >");
}