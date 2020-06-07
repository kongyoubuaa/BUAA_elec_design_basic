const int TrigPin = 5; 
const int EchoPin = 6; 
const int Vcc = 4;
const int GND = 7;
double distance; 
boolean flag;

void setup() 
{   // 初始化串口通信及连接SR04的引脚
       Serial.begin(9600); 
       pinMode(TrigPin, OUTPUT); 
   // 要检测引脚上输入的脉冲宽度，需要先设置为输入状态
       pinMode(EchoPin, INPUT); 
       pinMode(Vcc, OUTPUT);
       pinMode(GND, OUTPUT);
       pinMode(13, OUTPUT);
       digitalWrite(Vcc, HIGH);
       digitalWrite(GND, LOW);
       flag = true;
} 

void loop() 
{ 
   // 产生一个10us的高脉冲去触发TrigPin 
       digitalWrite(TrigPin, LOW); 
       delayMicroseconds(2); 
       digitalWrite(TrigPin, HIGH); 
       delayMicroseconds(10);
       digitalWrite(TrigPin, LOW); 
   // 检测脉冲宽度，并计算出距离
       distance = pulseIn(EchoPin, HIGH) / 58.8;
       distance = (int(distance * 100.0)) / 100.0;
       Serial.print("Distance:");
       Serial.print(distance); 
       Serial.println("cm"); 
       if (distance <= 5.0) {
         digitalWrite(13, HIGH);
         delay(1000);
       } else if (distance >= 150.0) {
         for (int i = 0; i < 10; i++) {
           if (flag) {
             digitalWrite(13, HIGH);
             flag = false;
           } else {
             digitalWrite(13, LOW);
             flag = true;
           }
           delay(100);
         }
       } else {
         flag = true;
         digitalWrite(13, LOW);
         delay(1000);
       }
}
