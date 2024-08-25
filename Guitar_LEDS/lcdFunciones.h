


#define LCD_I2C_ADDR        0x3E

#define LCD_MODE_COMMAND    0x00
#define LCD_MODE_DATA       0x40

#define LCD_CLEARDISPLAY    0x01
#define LCD_RETURNHOME      0x02
#define LCD_ENTRYMODESET    0x04
#define LCD_DISPLAYCONTROL  0x08
#define LCD_CURSORSHIFT     0x10
#define LCD_FUNCTIONSET     0x20
#define LCD_SETCGRAMADDR    0x40
#define LCD_SETDDRAMADDR    0x80

#define LCD_8BITMODE        0x10
#define LCD_4BITMODE        0x00
#define LCD_2LINE           0x08
#define LCD_1LINE           0x00
#define LCD_5x10DOTS        0x04
#define LCD_5x8DOTS         0x00

#define LCD_DISPLAYON       0x04
#define LCD_DISPLAYOFF      0x00
#define LCD_CURSORON        0x02
#define LCD_CURSOROFF       0x00
#define LCD_BLINKON         0x01
#define LCD_BLINKOFF        0x00

#define LCD_ENTRYRIGHT      0x00
#define LCD_ENTRYLEFT       0x02
#define LCD_ENTRYSHIFTINC   0x01
#define LCD_ENTRYSHIFTDEC   0x00


void lcdSend(unsigned char value, unsigned char mode) {
  Wire.beginTransmission(LCD_I2C_ADDR);
  Wire.write(mode);
  Wire.write(value);
  Wire.endTransmission();
  delayMicroseconds(50);
}

void lcdSetup() {
  Wire.begin();
  Wire.begin();
  delay(50);

  lcdSend(LCD_FUNCTIONSET | LCD_8BITMODE | LCD_2LINE | LCD_5x8DOTS, LCD_MODE_COMMAND);
  lcdSend(LCD_DISPLAYCONTROL | LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF, LCD_MODE_COMMAND);
  lcdSend(LCD_CLEARDISPLAY, LCD_MODE_COMMAND);
  delayMicroseconds(2000);  
  lcdSend(LCD_ENTRYMODESET | LCD_ENTRYLEFT | LCD_ENTRYSHIFTDEC, LCD_MODE_COMMAND);
}

void lcdClear() {
  lcdSend(LCD_CLEARDISPLAY, LCD_MODE_COMMAND);
  delayMicroseconds(2000);
}

void lcdSetCursor(int x, int y) {
  int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
  if (y > 3) y = 3;
  lcdSend(LCD_SETDDRAMADDR | (x + row_offsets[y]), LCD_MODE_COMMAND);
}

void lcdPrint(const char *str) {
  while (*str != 0) {
    lcdSend(*str, LCD_MODE_DATA);
    str++;
  }
}

