
/* 
  DC Motor control by Arduino UNO and L298P Motor Shield Board
  Date : 22/7/2020  
*/
#include <Servo.h> 
Servo camera;

int BPWM  =  11;    
int MotorB1 =  13;    
int MotorB2 =  8;    
  
int APWM =  10; 
int MotorA1 = 12;     
int MotorA2 =  3;   

int Buzzer = 4;     // PIN Buzzer
int PWMSET = 255;   // SET Speed Motor  Test 50% = 128 and Test 100% = 255

int Servo_PIN = 9;
void setup() {
  Serial.begin(9600);

  camera.attach(Servo_PIN);
  
  pinMode(4, OUTPUT);   // Buzzer  

  digitalWrite(4,HIGH);
  delay(300);
  digitalWrite(4,LOW);
  delay(100);
 
  pinMode(12, OUTPUT);  
  pinMode(3, OUTPUT);   
  pinMode(10, OUTPUT);   
  
  pinMode(13, OUTPUT);  
  pinMode(8, OUTPUT);   
  pinMode(11, OUTPUT);   
}
 
void loop() { 
  int pos;
      for(pos = 0; pos < 120; pos += 1){
        camera.write(pos);
        delay(15);
    }
    for(pos = 120; pos>=1; pos-=1) {                        
        camera.write(pos);
        delay(15);                                                      
    }
//  int rotation;
//  if(Serial.read() != -1){
//    rotation = Serial.read();
//    Serial.println(char(rotation));
//  }
  
// ---- Loop CW --------------
  digitalWrite(MotorA1, LOW);
  digitalWrite(MotorA2, HIGH);
  analogWrite(APWM, PWMSET);
 
  digitalWrite(MotorB1, HIGH);
  digitalWrite(MotorB2, HIGH);
  analogWrite(BPWM, PWMSET); 
  delay(0);  
// ---- END Loop CW ----------

  analogWrite(APWM, 255);
  analogWrite(BPWM, 255); 
  delay(0);
//
// 
//// ---- Loop CCW -------------
//  digitalWrite(MotorA1, HIGH);
//  digitalWrite(MotorA2, LOW);
//  analogWrite(APWM, PWMSET);
// 
//  digitalWrite(MotorB1, LOW);
//  digitalWrite(MotorB2, HIGH);
//  analogWrite(BPWM, PWMSET); 
//  delay(0);
//// ---- END Loop CCW ---------- 
//
//  analogWrite(APWM, 0);
//  analogWrite(BPWM, 0); 
//  delay(0);
//
//
//// ---- Loop Motor1 CCW -----------
//  digitalWrite(MotorA1, HIGH);
//  digitalWrite(MotorA2, LOW);
//  analogWrite(APWM, PWMSET);
// 
//  digitalWrite(MotorB1, LOW);
//  digitalWrite(MotorB2, LOW);
//  analogWrite(BPWM, 0); 
//  delay(0);  
//// ---- END Loop Motor1 CCW --------
//
//  analogWrite(APWM, 0);
//  analogWrite(BPWM, 0); 
//  delay(0);
//
//
//// ---- Loop Motor2 CCW ------------
//  digitalWrite(MotorA1, LOW);
//  digitalWrite(MotorA2, LOW);
//  analogWrite(APWM, 0);
// 
//  digitalWrite(MotorB1, LOW);
//  digitalWrite(MotorB2, HIGH);
//  analogWrite(BPWM, PWMSET); 
//  delay(2000);  
//// ---- END Loop Motor2 CCW --------
//
//  
//  analogWrite(APWM, 0);
//  analogWrite(BPWM, 0); 
//  delay(0);
//  
//  digitalWrite(4,HIGH);
//  delay(0);
//  digitalWrite(4,LOW);
 
}
