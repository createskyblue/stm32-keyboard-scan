int KBPinMap[] = {PB12, PB13, PB14, PB15, PA8, PA9, PA10, PA11, PA12, PA15, PB3, PB4, PB5, PB6, PB7, PB8, PB9, PB11, PB10, PB1, PB0, PA7, PA6, PA5};
int KBScan[24]={0};

void ScanPin(int KBPinMapNum) {
  AllPinIN();
  pinMode(KBPinMap[KBPinMapNum], OUTPUT);
  digitalWrite(KBPinMap[KBPinMapNum], HIGH);
  for (int i = 0; i < sizeof(KBPinMap) / sizeof(KBPinMap[0]); i++) {
    if (i==KBPinMapNum) continue;
    if (analogRead(i)>500) KBScan[i]=1; else KBScan[i]=0;
  }
}

void AllPinIN() {
  for (int i = 0; i < sizeof(KBPinMap) / sizeof(KBPinMap[0]); i++)
    pinMode(KBPinMap[i], INPUT_PULLDOWN);
}

void SerialPrintAllKBScan() {
  char printBuffer[50];
  for (int i = 0; i < sizeof(KBPinMap) / sizeof(KBPinMap[0]); i++) {
    sprintf(printBuffer,"[%d]-%d  ",i,KBScan[i]);
    Serial.print(printBuffer);
  }
  Serial.print('\n');
}

void setup() {
  Serial.begin(9600);
  AllPinIN();
}

void loop() {
  for (int i = 0; i < sizeof(KBPinMap) / sizeof(KBPinMap[0]); i++) {
    ScanPin(i);
  }
  SerialPrintAllKBScan();
  delay(20);
}
