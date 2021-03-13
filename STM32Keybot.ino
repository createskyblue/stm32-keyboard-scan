#define SWAP(x, y) \
	(y) = (x) + (y); \
	(x) = (y) - (x); \
	(y) = (y) - (x);

//按键映射表，按需修改
//{探针id,接收id,ASCII}
byte KeyMap[][3]={
  {5,19,'1'},
  {5,18,'2'},
  {6,19,'3'},
  {8,19,'6'},
  {8,18,'7'},
  {9,19,'8'},
  {5,17,'q'},
  {5,20,'w'},
  {6,18,'e'},
  {8,17,'y'},
  {9,17,'u'},
  {9,18,'i'},
  {10,20,'o'},
  {5,21,'a'},
  {6,20,'s'},
  {6,17,'d'},
  {8,20,'h'},
  {9,20,'j'},
  {9,21,'k'},
  {10,21,'l'},
  {5,22,'z'},
  {6,21,'x'},
  {6,22,'c'},
  {8,22,'b'},
  {8,21,'n'},
  {9,22,'m'},
  {10,22,'<'},
  {11,22,'>'},
  {11,21,'/'},
};

//KBPinMap 按照键盘排线接入开发板的顺序填写引脚设定
//                 0     1     2     3     4    5    6   7    8    9    10    11    12   13   14   15   16   17    18    19   20   21   22   23
int KBPinMap[] = {PB12, PB13, PB14, PB15, PC13, PA4, PA3, PA2, PA1, PA0, PC15, PC14, PB5, PB6, PB7, PB8, PB9, PB11, PB10, PB0, PB1, PA7, PA6, PA5};
int KBScan[] = {0};

/*
    @函数 ScanKeyMap
    @作用   搜索按键映射表并输出按键映射
    @传入
        byte a 探针id
        byte b 接收id
    @传出 
        char
*/
char ScanKeyMap(byte a,byte b){
  if (a>b) {
    byte c=a;
    a=b;
    b=c;
  }
  for (int i=0;i<sizeof(KeyMap)/sizeof(KeyMap[0]);i++) {
    if (KeyMap[i][0]==a&&KeyMap[i][1]==b) return KeyMap[i][2];
  }
  char printBuffer[50];
  sprintf(printBuffer, "--- error a:%d b:%d ---",a,b);
  Serial1.print(printBuffer);
  return 0;
}

/*
    @函数 ScanPin
    @作用 使能某个引脚作用为探针，并对接收脚进行扫描
    @传入
        int KBPinMapNum 探针引脚
    @传出 -
*/
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
    if (analogRead(KBPinMap[i])>2000) {
      KBScan[i] = 1;  
      sprintf(printBuffer, "%c # 探针[%d]:%d  ->  接收[%d]:%d",ScanKeyMap(KBPinMapNum,i), KBPinMapNum, KBPinMap[KBPinMapNum], i, KBScan[i]);
      Serial1.println(printBuffer);
    }
  }
}



/*
    @函数 ClearKBScan
    @作用 清除接收引脚状态表
    @传入 -
    @传出 -
*/
void ClearKBScan() {
  memset(KBScan,0,sizeof(KBScan) / sizeof(KBScan[0]));
  /*
  for (int i = 0; i < sizeof(KBScan) / sizeof(KBScan[0]); i++)
    KBScan[i] = 0;
    */
}

/*
    @函数 AllPinOut
    @作用 全部引脚IO设置为输出模式
    @传入 -
    @传出 -
*/
void AllPinOut() {
  for (int i = 0; i < sizeof(KBPinMap) / sizeof(KBPinMap[0]); i++) {
    pinMode(KBPinMap[i], OUTPUT);
    digitalWrite(KBPinMap[i], HIGH);
  }
}
/*
    @函数 AllPinIN
    @作用 全部引脚IO设置为输入模式
    @传入 -
    @传出 -
*/
void AllPinIN() {
  for (int i = 0; i < sizeof(KBPinMap) / sizeof(KBPinMap[0]); i++)
    pinMode(KBPinMap[i], INPUT_PULLDOWN);
}

/*
    @函数 SerialPrintAllKBScan
    @作用 串口输出 引脚状态表
    @传入 -
    @传出 -
*/
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
  Serial1.println("     航顺半导体                             ,]]OO@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@OOO|[`              ");
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
}

void loop() {

  ClearKBScan();

  for (int i = 0; i < sizeof(KBPinMap) / sizeof(KBPinMap[0]); i++)
    ScanPin(i);

  //SerialPrintAllKBScan();

}
