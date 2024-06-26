#include <Servo.h>
#include <stdio.h>
#include <setup/SensorCalibration.ino>

void setup() {
  // Begin serial communication at a baud rate of 115200:
  Serial.begin(115200);
  Serial.println("Welcome to the glove!");
  calibrate();
  
  s1.attach(11, 1000, 2000);
  s1.writeMicroseconds(1000);

  s2.attach(10, 1000, 2000);
  s2.writeMicroseconds(1000);
  
  s3.attach(9, 1000, 2000);
  s3.writeMicroseconds(1000);
  
  s4.attach(6, 1000, 2000);
  s4.writeMicroseconds(1000);

  s5.attach(5, 1000, 2000);
  s5.writeMicroseconds(1000);

  s6.attach(3, 1000, 2000);
  s6.writeMicroseconds(1000);

  delay(5000); 
}

int i;
long moveStartTime = millis();
unsigned long progress = millis() - moveStartTime;
long angle;

void loop() {
  // Read the pin and store the output:

  ps1read = analogRead(PS_1);
  delay(15);
  // map(value, fromLow, fromHigh, toLow, toHigh)
  s1Val = map(ps1read, minPressureValue1, maxPressureValue1, 0, 90);
  //s1.write(s1Val); // servo.write(angle)

  i = s1.read();
  moveStartTime = millis();
  //while(i < 90 && i < s1Val){
    Serial.println(moveStartTime);
    progress = millis() - moveStartTime;
    
    int startAngle = s1.read(); // 30°
    int stopAngle  = s1Val; // 90°
    int MOVING_TIME = 3000;
    angle = map(progress, 0, MOVING_TIME, startAngle, stopAngle);
    s1.write(angle); 
    
  Serial.print(ps1read);
  Serial.print(" -> ");
  Serial.print(s1Val);
  Serial.print(",");
  
  ps2read = analogRead(PS_2);
  delay(15);
  s2Val = map(ps2read, minPressureValue2, maxPressureValue2, 0, 90);
  s2.write(s2Val);
  Serial.print(ps2read);
  Serial.print(" -> ");
  Serial.print(s2Val);
  Serial.print(",");

  ps3read = analogRead(PS_3);
  delay(15);
  s3Val = map(ps3read, minPressureValue3, maxPressureValue3, 0, 90);
  s3.write(s3Val);
  Serial.print(ps3read);
  Serial.print(" -> ");
  Serial.print(s3Val);
  Serial.print(",");

  ps4read = analogRead(PS_4);
  delay(15);
  s4Val = map(ps4read, minPressureValue4, maxPressureValue4, 0, 90);
  s4.write(s4Val);
  Serial.print(ps4read);
  Serial.print(" -> ");
  Serial.print(s4Val);
  Serial.print(",");
  
  ps5read = analogRead(PS_5);
  delay(15);
  s5Val = map(ps5read, minPressureValue5, maxPressureValue5, 0, 90);
  s5.write(s5Val);
  Serial.print(ps5read);
  Serial.print(" -> ");
  Serial.print(s5Val);
  Serial.print(",");

  ps6read = analogRead(PS_6);
  delay(15);
  s6Val = map(ps6read, minPressureValue6, maxPressureValue6, 0, 90);
  s6.write(s6Val);
  Serial.print(ps6read);
  Serial.print(" -> ");
  Serial.println(s6Val);

  delay(500); //Delay 500 ms.
}