void saveToEEPROM() {
  EEPROM.put(0, gameSettings);
}

void loadFromEEPROM() {
  EEPROM.get(0, gameSettings);
  gameSettings.lcdContrast = constrain(gameSettings.lcdContrast, 0, MAX_LCD_CONTRAST - 1);
  gameSettings.lcdBrightness = constrain(gameSettings.lcdBrightness, 0, MAX_LCD_BRIGHTNESS - 1);
  gameSettings.matrixBrightness = constrain(gameSettings.matrixBrightness, 0, MAX_MATRIX_BRIGHTNESS - 1);
  ledMatrix.shutdown(0, false);
  updateSettings();
  lightMatrixByRows(nullptr);

  lcd.begin(LCD_LENGTH, 2);
}