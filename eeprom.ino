#define SHIFT_DATA 2
#define SHIFT_CLK 3
#define SHIFT_LATCH 4
#define EEPROM_D0 5
#define EEPROM_D7 12
#define WRITE_EN 13
#define MAX 8192

void setup() {
  // put your setup code here, to run once:
  pinMode(SHIFT_DATA, OUTPUT);
  pinMode(SHIFT_CLK, OUTPUT);
  pinMode(SHIFT_LATCH, OUTPUT);
  digitalWrite(WRITE_EN, HIGH);
  pinMode(WRITE_EN, OUTPUT);
  Serial.begin(57600);

  byte segdisp[] = {
    0b1111110,
    0b0110000,
    0b1101101,
    0b1111001,
    0b0110011,
    0b1011011,
    0b1011111,
    0b1110000,
    0b1111111,
    0b1111011,
    0b1110111,
    0b0011111,
    0b1001110,
    0b0111101,
    0b1001111,
    0b1000111
  };
  // writeRangeEEPROM(0, MAX, 0x00);
  writeArrayEEPROM(0, segdisp, 16);
  // for(int i = 0; i < MAX; i++) { writeEEPROM(i, i % 256); }
  // writeRangeEEPROM(0, 256, 0x00);
  printRangeEEPROM(0, 256);

}

void loop() {}

void setAddress(int address, bool outputEnable) {

  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (address >> 8) | (outputEnable ? 0x00 : 0x80));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, address);

  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
}

byte readEEPROM(int address) {
  for(int i = EEPROM_D0; i <= EEPROM_D7; i++) {
    pinMode(i, INPUT);
  }
  setAddress(address, /*outputEnable*/ true);
  byte data = 0;
  for(int pin = EEPROM_D7; pin >= EEPROM_D0; pin--) {
    data = (data << 1) + digitalRead(pin);
  }
  return data;
}

void writeEEPROM(int address, byte data) {
  for(int i = EEPROM_D0; i <= EEPROM_D7; i++) {
    pinMode(i, OUTPUT);
  }
  setAddress(address, /*outputEnable*/ false);

  for(int i = EEPROM_D0; i <= EEPROM_D7; i++) {
    digitalWrite(i, data & 1);
    data = data >> 1;
  }
  digitalWrite(WRITE_EN, LOW);
  delayMicroseconds(1);
  digitalWrite(WRITE_EN, HIGH);
  delay(1);
}

// prints range of memory from [first, last)
// in segments of 16 bytes per line
void printRangeEEPROM(int first, int last) {
  for(int i = first; i < last; i += 16) {
    byte data[16];

    for(int j = 0; j < 16; j++) {
      data[j] = readEEPROM(i + j);
    }
    char buf[80];
    sprintf(buf, "%04x:  %02x %02x %02x %02x %02x %02x %02x %02x    %02x %02x %02x %02x %02x %02x %02x %02x",
      i, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7],
      data[8], data[9], data[10], data[11], data[12], data[13], data[14], data[15]);
    Serial.println(buf);
  }
}

// writes value to each byte from [first, last)
void writeRangeEEPROM(int first, int last, byte value) {
  for(int i = first; i < last; i++) {
    writeEEPROM(i, value);
  }
}

// writes value to each byte from [first, last)
void writeArrayEEPROM(int first, byte* value, int sz) {
  for(int i = 0; i < sz; i++) {
    writeEEPROM(first + i, value[i]);
  }
}
