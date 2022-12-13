#include <Wire.h>
#include <MPU6050_light.h>
int dataX, dataY;
const int SWJoy = 2;
const int ledGreen = 10; 
const int ledRed1 = 9; 
const int ledRed2 = 11; 

MPU6050 mpu(Wire);
unsigned long timer = 0;

void setup() {
  Serial.begin(9600);
  pinMode(SWJoy, INPUT);
  digitalWrite(SWJoy, HIGH);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed1, OUTPUT);
  pinMode(ledRed2, OUTPUT);
  Wire.begin();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } 
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets();
  Serial.println("Done!\n");
}

int x;

void loop() {
  mpu.update();
  x = digitalRead(SWJoy);
  if (x == 0)
  {
    Serial.print("B");
    digitalWrite(ledRed1, LOW);
    digitalWrite(ledRed2, HIGH);
  }
  else
  {
    digitalWrite(ledRed1, HIGH);
    digitalWrite(ledRed2, LOW);
  }
  Serial.println(digitalRead(SWJoy));
  
  if((millis()-timer)>10)
  {
    digitalWrite(ledGreen, HIGH);
    dataX = mpu.getAngleX()*50;
    dataY = mpu.getAngleZ()*50;
    Serial.print("x");
    Serial.println(int(dataX), DEC);
    Serial.print("Y");
    Serial.println(int(dataY), DEC);
  timer = millis();
  }
  delay(10);
}
