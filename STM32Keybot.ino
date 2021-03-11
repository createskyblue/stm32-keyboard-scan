//                 0     1     2     3     4    5    6   7    8    9    10    11    12   13   14   15   16   17    18    19   20   21   22   23
int KBPinMap[] = {PB12, PB13, PB14, PB15, PA8, PA4, PA3, PA2, PA1, PA0, PC15, PC14, PB5, PB6, PB7, PB8, PB9, PB11, PB10, PB0, PB1, PA7, PA6, PA5};
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
    if (digitalRead(KBPinMap[i])) {
      sprintf(printBuffer, "[%d->%d]", KBPinMapNum, i);
      Serial1.println(printBuffer);
      KBScan[i] = 1;
    }
    /*
      if (analogRead(KBPinMap[i]) > 4000) {
      sprintf(printBuffer, "[%d->%d]:%d  ", KBPinMapNum, i, analogRead(KBPinMap[i]));
      Serial1.println(printBuffer);
      }
    */
  }
}

void AllPinOut() {
  for (int i = 0; i < sizeof(KBPinMap) / sizeof(KBPinMap[0]); i++) {
    pinMode(KBPinMap[i], OUTPUT);
    digitalWrite(KBPinMap[i], HIGH);
  }
}

void ClearKBScan() {
  //memset(KBScan,0,sizeof(KBScan) / sizeof(KBScan[0]));
  for (int i = 0; i < sizeof(KBScan) / sizeof(KBScan[0]); i++)
    KBScan[i] = 0;
}

void AllPinIN() {
  for (int i = 0; i < sizeof(KBPinMap) / sizeof(KBPinMap[0]); i++)
    pinMode(KBPinMap[i], INPUT_PULLDOWN);
}

void SerialPrintAllKBScan() {
  char printBuffer[50];
  for (int i = 0; i < sizeof(KBPinMap) / sizeof(KBPinMap[0]); i++) {
    sprintf(printBuffer, "[%d]-%d ", i, KBScan[i]);
    Serial1.print(printBuffer);
  }
  Serial1.print("\n\r");
}

void setup() {
  Serial1.begin(115200);
  Serial1.println("                                                                                                   *]]*");
  Serial1.println("                                                                                           *]]OOO@@@@| ");
  Serial1.println("                                                                                   ,]]|OOO@@@@@@@@@@|  ");
  Serial1.println("                                                                            ]]OOO@@@@@@@@@@@@@@@@@@O   ");
  Serial1.println("                                                                    ,|OOOO@@@@@@@@@@@@@@@@@@@@@@@@O    ");
  Serial1.println("     西欧有意法                                             ]|OOO@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@O     ");
  Serial1.println("     中国有航顺                                     ]]OOO@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@OOOO[      ");
  Serial1.println("     航顺 M C U                             ,]]OO@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@OOO|[`              ");
  Serial1.println("                                     ,]|OOO@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@OOO|[[                       ");
  Serial1.println("                               ,]|OO@@@@@@@@@@@@@@@@@@@@@@@@@@@@@OOOO[[               ]]]OO@@@O        ");
  Serial1.println("                          ,|O@@@@@@@@@@@@@@@@@@@@@@@@@@@OOOO[`               ]]]O@@@@@@@@@@@@O`        ");
  Serial1.println("                     *|O@@@@@@@@@@@@@@@@@@@@@@@OOOO|[`              ]]|O@@@@@@@@@@@@@@@@@@@@@`         ");
  Serial1.println("                 ]OO@@@@@@@@@@@@@@@@@@@@OOO[[*           *]|OO@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@^          ");
  Serial1.println("             ,OO@@@@@@@@@@@@@@@@OOO|[*          ]]|OO@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@^           ");
  Serial1.println("          ]OO@@@@@@@@@@@@@OO|`          ]|OO@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@^            ");
  Serial1.println("       ,O@@@@@@@@@@@@O[[        ,]O@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@^             ");
  Serial1.println("     ,O@@@@@@@@OO[`       ,|O@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@O|[[[`               ");
  Serial1.println("   ,O@@@@@@OO[       ]O@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@O[[[                           ");
  Serial1.println("  |@@@@@O|*     ,|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@OOO[|@@@@@@`                               ");
  Serial1.println(" O@@@O|     ,O@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@O|[`         |@@@@@^                                ");
  Serial1.println("=O@O`    ]O@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@O|[`                |@@@@@^                                 ");
  Serial1.println("O@O    |@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@|                    |@@@@@^                                  ");
  Serial1.println("O|   |@@@@@@@@@@@@@@@@@@@@@@@@O[` =@@@@@|                    |@@@@@^                                   ");
  Serial1.println(" *  |@@@@@@@@@@@@@@@@@@@@@O[     =@@@@@O  ]|OOOOOO]`        =@@@@@|       ,O@@@@@@|                    ");
  Serial1.println("   =@@@@@@@@@@@@@@@@@@@@|       ,@@@@@@O@@@@@@@@@@@@@|     =@@@@@O      |@@@@@@|                       ");
  Serial1.println("   =@@@@@@@@@@@@@@@@@@@`        O@@@@@@@@|` **|@@@@@@@^   =@@@@@O    |@@@@@@|                          ");
  Serial1.println("    =@@@@@@@@@@@@@@@@@O        O@@@@@O`        *@@@@@O`  ,@@@@@O  ,O@@@@@@@@@@@|                       ");
  Serial1.println("     ,O@@@@@@@@@@@@@@@@O`     O@@@@@^          O@@@@@`  ,O@@@@O*|@@@@@@@@@@@@@@O                       ");
  Serial1.println("        [O@@@@@@@@@@@@@@@@|  |@@@@@^          O@@@@@^   O@@@@@`         =@@@@@@`                       ");
  Serial1.println("            [O@@@@@@@@@@@@@@@@@@@@^          |@@@@@`   O@@@@@^          |@@@@@`                        ");
  Serial1.println("                  [[OO@@@@@@@@@@@@@@@OOO|]]]|@@@@@^   |@@@@@^          |@@@@O`                         ");
  Serial1.println("                           ,[[[|OOOOO@@@@@@@@@@@@@@@@@@@@@@@OOOOOO|[`                                  ");

  AllPinIN();
  //AllPinOut();
}

void loop() {

  ClearKBScan();

  for (int i = 0; i < sizeof(KBPinMap) / sizeof(KBPinMap[0]); i++)
    ScanPin(i);

  //SerialPrintAllKBScan();

}
