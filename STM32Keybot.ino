int KBPinMap[] = {PB12, PB13, PB14, PB15, PA8, PA2, PA1, PA11, PA12, PA15, PB3, PB4, PB5, PB6, PB7, PB8, PB9, PB11, PB10, PB1, PB0, PA7, PA6, PA5};
int KBScan[24] = {0};

void ScanPin(int KBPinMapNum) {
  //设置所有引脚为输入模式
  AllPinIN();
  //设置探针引脚输出
  pinMode(KBPinMap[KBPinMapNum], OUTPUT);
  digitalWrite(KBPinMap[KBPinMapNum], HIGH);

  //轮询引脚，是否有输出电平
  char printBuffer[50];
  for (int i = 0; i < sizeof(KBPinMap) / sizeof(KBPinMap[0]); i++) {
    if (i == KBPinMapNum) continue; //跳过探针引脚
    if (analogRead(KBPinMap[i]) > 3800) {
      sprintf(printBuffer, "[%d-%d]:%d  ", i,KBPinMapNum,analogRead(KBPinMap[i]));
      Serial1.println(printBuffer);
    }
  }
}

void ClearKBScan() {
  //memset(KBScan,0,sizeof(KBScan) / sizeof(KBScan[0]));
  for (int i = 0; i < sizeof(KBScan) / sizeof(KBScan[0]); i++)
    KBScan[i] = 0;
}

void AllPinIN() {
  for (int i = 0; i < sizeof(KBPinMap) / sizeof(KBPinMap[0]); i++)
    pinMode(KBPinMap[i], INPUT_ANALOG);
}

void SerialPrintAllKBScan() {
  char printBuffer[50];
  for (int i = 0; i < sizeof(KBPinMap) / sizeof(KBPinMap[0]); i++) {
    sprintf(printBuffer, "[%d]-%d  ", i, KBScan[i]);
    Serial1.print(printBuffer);
  }
  Serial1.print('\n');
}

void setup() {
  Serial1.begin(115200);
  AllPinIN();
}

void loop() {
  ClearKBScan();

  for (int i = 0; i < sizeof(KBPinMap) / sizeof(KBPinMap[0]); i++)
    ScanPin(i);

  //SerialPrintAllKBScan();
  delay(5);
}
