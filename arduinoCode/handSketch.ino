#include "HCPCA9685.h"
#define I2CAdd 0x40
HCPCA9685 HCPCA9685(I2CAdd);
int length2servVal(int length) { //преобразование мм в минимальную длину импульса привода
  int lenMin = 0;
  int lenMax = 20;
  int servoMin = 205;
  int servoMax = 405;
  int value = (length - lenMin) * (servoMax - servoMin) / (lenMax - lenMin) + servoMin;
  return value;
}
char receivedData[6] = {0};
int numOfRecievedData = 0;
void setup() {
  Serial.begin(9600);
  HCPCA9685.Init(SERVO_MODE);
  HCPCA9685.Sleep(false);
  int initPos = length2servVal(20);
  HCPCA9685.Servo(0, initPos);//установка схвата в стартовое положение
  HCPCA9685.Servo(1, initPos); //кисть раскрыта
  HCPCA9685.Servo(2, initPos);
  HCPCA9685.Servo(3, initPos);
  HCPCA9685.Servo(4, initPos);
  HCPCA9685.Servo(5, initPos);
}
void loop() {
  if(Serial.available()) { //если данные пришли
    while(numOfRecievedData < 6) {
      receivedData[numOfRecievedData] = Serial.read(); //считываем данные
      numOfRecievedData++;
    }
  if (numOfRecievedData > 4) numOfRecievedData = 0;
  }
  for(int i = 0; i < 6; i++) {
    HCPCA9685.Servo(i, length2servVal(receivedData[i]));//передаем данные приводам
  }
}
