#include <Servo.h>
#include <stdio.h>

int PS_1 = A0;//wrist
int PS_2 = A1;//thumb
int PS_3 = A2;//index
int PS_4 = A3;//middle
int PS_5 = A4;//ring
int PS_6 = A5;//pinky


// servos
Servo s1;
int s1Val;
Servo s2;
int s2Val;
Servo s3;
int s3Val;
Servo s5;
int s5Val;
Servo s4;
int s4Val;
Servo s6;
int s6Val;

//Define variable to store sensor readings:
int ps1read;
int ps2read;
int ps3read;
int ps4read;
int ps5read;
int ps6read;

// Define minimum and maximum pressure values for calibration
int minPressureValue1 = 0;
int maxPressureValue1 = 100;
int minPressureValue2 = 0;
int maxPressureValue2 = 100;
int minPressureValue3 = 0;
int maxPressureValue3 = 100;
int minPressureValue4 = 0;
int maxPressureValue4 = 100;
int minPressureValue5 = 0;
int maxPressureValue5 = 100;
int minPressureValue6 = 0;
int maxPressureValue6 = 100;
int maxPressureValue;

// Define minimum and maximum servo angle values for calibration
int minServoAngle1 = 0;
int maxServoAngle1 = 90;

// offset variables
//long psSum[6] = {0, 0, 0, 0, 0, 0};
long ps1Avg;
long ps1Sum;
int ps1Offset;

long ps2Avg;
long ps2Sum;
int ps2Offset;

long ps3Avg;
long ps3Sum;
int ps3Offset;

void calibrate();
int calibrateMaxValues(int);
  
void calibrate(){
  Serial.println("In about 3 seconds, relax your hand.");
  delay(3000);

  // minimum pressure & rotation calculations
  minPressureValue1 = analogRead(PS_1);
  minPressureValue2 = analogRead(PS_2);
  minPressureValue3 = analogRead(PS_3);
  minPressureValue4 = analogRead(PS_4);
  Serial.println(minPressureValue4);
  minPressureValue5 = analogRead(PS_5);
  minPressureValue6 = analogRead(PS_6);

  Serial.println("That was great!");

  Serial.println("In about 3 seconds, apply significant pressure on the wrist and each finger individually as they appear on the screen.");
  delay(3000);

  // maximum pressure & rotation calculations
  Serial.print("Wrist");
  maxPressureValue1 = calibrateMaxValues(PS_1);
  Serial.print(" | Thumb");
  maxPressureValue2 = calibrateMaxValues(PS_2);  
  Serial.print(" | Index");
  maxPressureValue3 = calibrateMaxValues(PS_3);
  Serial.print(" | Middle");
  maxPressureValue4 = calibrateMaxValues(PS_4);
  Serial.print(" | Ring");
  maxPressureValue5 = calibrateMaxValues(PS_5);
  Serial.print(" | Pinky");
  maxPressureValue6 = calibrateMaxValues(PS_6);
  Serial.println();
}

int calibrateMaxValues(int pressurePort){
  Serial.print(" => Max Pressure: ");
  delay(5000);
  maxPressureValue = analogRead(pressurePort);
  Serial.print(maxPressureValue);
  return maxPressureValue;
}

long avgOffSetPS1(){
  // ps1Offset = analogRead(A0);
  for(int i = 0; i < 99; i++){
    ps1Sum += analogRead(A0);
  }
  ps1Avg = ps1Sum/100;
  ps1Offset = ps1Avg-analogRead(A0);
  return ps1Offset;
}

long avgOffSetPS2(){
  // ps1Offset = analogRead(A0);
  for(int i = 0; i < 99; i++){
    ps2Sum += analogRead(A1);
  }
  ps2Avg = ps2Sum/100;
  ps2Offset = ps2Avg-analogRead(A1);
  return ps2Offset;
}

long avgOffSetPS3(){
  // ps1Offset = analogRead(A0);
  for(int i = 0; i < 99; i++){
    ps3Sum += analogRead(A2);
  }
  ps3Avg = ps3Sum/100;
  ps3Offset = ps3Avg-analogRead(A2);
  return ps3Offset;
}