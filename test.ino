#include<Servo.h>
String readString;
const int trig = 2;     // chân trig của HC-SR04
const int echo = 3;     // chân echo của HC-SR04
const int R_IS = 1;
const int L_IS = 11;
const int R_EN = 12;
const int L_EN = 13;

const int LeftMotorForward = 7;
const int LeftMotorBackward = 8;

const int RightMotorForward = 10;
const int RightMotorBackward = 4;
const int bangchuyen = 5;
const int choiquet = 6;

 int distance;
Servo servo_motor;
Servo servo_camera;
void setup()
{
  Serial.begin(9600);     // giao tiếp Serial với baudrate 9600
  pinMode(trig,OUTPUT);   // chân trig sẽ phát tín hiệu
  pinMode(echo,INPUT);    // chân echo sẽ nhận tín hiệu
  servo_motor.attach(9);
  //servo_camera.attach(1);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  pinMode(bangchuyen, OUTPUT);
  pinMode(choiquet, OUTPUT);
  pinMode(L_EN, OUTPUT);
  pinMode(R_EN, OUTPUT);
  pinMode(L_IS, OUTPUT);
  pinMode(R_IS, OUTPUT);
  digitalWrite(R_IS, LOW);
  digitalWrite(L_IS,LOW);
  digitalWrite(R_EN, HIGH);
  digitalWrite(L_EN, HIGH);
  distance = readSensor();    // Get Ping Distance.
  delay(100);               // Wait for 100ms.
  distance = readSensor();
  delay(100);
  distance = readSensor();
  delay(100);
  //distance = 100;
  //delay(100);
//  lookRight();
//  lookLeft();
}
 
void loop()
{
  Serial.print("Distance < 40: "+distance);
  distance = readSensor();
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);
  Serial.print("Distance < 40: "+distance);
  if(distance <= 60){
    moveStop();
    delay(300);
    moveBackward();
    delay(300);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);
    if(distanceRight > distanceLeft){
      turnRight();
      delay(300);
      moveStop();
    }else{
      turnLeft();
      delay(300);
      moveStop();
    }
     delay(3000);
    turnOffClearTrash();
  }else{
    int check = checkingTrash();
    if(check == 2){
      moveForward();
      delay(300);
      turnOnClearTrash();
    }else if(check == 3){
      turnOffClearTrash();
      turnRight();
      delay(100);
      moveStop();
    }else{
      turnOffClearTrash();
      turnLeft();
      delay(100);
      moveStop();
    }
    delay(3000);
  }


//  if (distance <= 60)
//  {
//    Serial.print("Distance < 40: "+distance);
//    moveStop();
//    delay(300);
//    moveBackward();
//    delay(400);
//    moveStop();
//    delay(300);
//    distanceRight = lookRight();
//    delay(300);
//    distanceLeft = lookLeft();
//    delay(300);
//  turnOffClearTrash();
//    if (distanceRight >= distanceLeft)
//    {
//      turnRight();
//      delay(300);
//      moveStop();
//    }
//    else
//    {
//      turnLeft();
//      delay(300);
//      moveStop();
//    }
//  
//  }
//  else
//  {
// 
//    Serial.print("Distance: "+distance);
//    if(checkingTrash() == 2){
//      moveForward(); 
//      turnOnClearTrash();
//    }else if(checkingTrash() == 3){
//      turnRight();
//      //turnLeft();
//      delay(3500);
//      moveStop();
//      checkingTrash();
//      turnOffClearTrash();
//    }else{
//      turnLeft();
//      delay(3500);
//      moveStop();
//      checkingTrash();
//      turnOffClearTrash();
//    }
//    
//  }

    distance = readSensor();
//delay(3500);
}

int readSensor(){
    unsigned long duration; // biến đo thời gian
    int distance;           // biến lưu khoảng cách
    
//    /* Phát xung từ chân trig */
    digitalWrite(trig,0);   // tắt chân trig
    delayMicroseconds(2);
    digitalWrite(trig,1);   // phát xung từ chân trig
    delayMicroseconds(5);   // xung có độ dài 5 microSeconds
    digitalWrite(trig,0);   // tắt chân trig
//    
//    /* Tính toán thời gian */
//    // Đo độ rộng xung HIGH ở chân echo. 
    duration = pulseIn(echo,HIGH);  
    // Tính khoảng cách đến vật.
    distance = int(duration/2/29.412);
//    
//    /* In kết quả ra Serial Monitor */
    Serial.print(distance);
    Serial.println("cm");
    delay(200);
    return distance;
}

void moveStop()       // Move Stop Function for Motor Driver.
{
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  Serial.println("moveStop");
}

void moveForward()    // Move Forward Function for Motor Driver.
{
    analogWrite(RightMotorForward, 0);
    analogWrite(RightMotorBackward, 123);
    analogWrite(LeftMotorForward, 0);
    analogWrite(LeftMotorBackward, 123);

    Serial.println("moveForward");
}

void moveBackward()   // Move Backward Function for Motor Driver.
{
  //analogWrite(RightMotorForward, HIGH);
  analogWrite(RightMotorForward, 92);
  analogWrite(RightMotorBackward, 0);
  analogWrite(LeftMotorForward, 92);
  analogWrite(LeftMotorBackward, 0);
  //analogWrite(RightMotorForward, HIGH);
  Serial.println("moveBackward");
}

void turnRight()      // Turn Right Function for Motor Driver.
{
  //delay(3500);
  analogWrite(RightMotorForward, 0);
  analogWrite(RightMotorBackward, 51);
  analogWrite(LeftMotorForward, 51);
  analogWrite(LeftMotorBackward, 0);
  delay(300);
//  Serial.println(" turnRight-----------  "+ checkcam);
  //Serial.print( checkcam);
}

void turnLeft()       // Turn Left Function for Motor Driver.
{
  Serial.println("turnLeft");
  //Serial.print(checkcam);
  //delay(3500);
 analogWrite(RightMotorForward, 51);
  analogWrite(RightMotorBackward, 0);
  analogWrite(LeftMotorForward, 0);
  analogWrite(LeftMotorBackward, 51);
  delay(300);

}
int lookRight()     // Look Right Function for Servo Motor
{  
  servo_motor.write(50);
  delay(500);
  int distance = readSensor();
  delay(100);
  servo_motor.write(115);
  Serial.println("lookRight");
  return 50;
}

int lookLeft()      // Look Left Function for Servo Motor 
{
  servo_motor.write(180);
  delay(500);
  int distance = readSensor();
  delay(100);
  servo_motor.write(115);
  Serial.println("lookLeft");
  return 100;
}
//int CameraLookRight()     // Look Right Function for Servo Motor
//{  
//  servo_camera.write(50);
//  delay(500);
//  int distance = checkingTrash();
//  delay(100);
//  servo_camera.write(115);
//  Serial.println("cam right");
//  return distance;
//}
//
//int CameraLookLeft()      // Look Left Function for Servo Motor 
//{
//  
//  servo_camera.write(180);
//  delay(500);
//  int distance = checkingTrash();
//  delay(100);
//  servo_camera.write(115);
//  Serial.println("cam left");
//  return distance;
//}
void turnOnClearTrash(){
  
  digitalWrite(bangchuyen, 255);
  digitalWrite(choiquet, 0);
  Serial.print("turnOnClearTrash");
}
void turnOffClearTrash(){
  
  digitalWrite(bangchuyen, 0);
  digitalWrite(choiquet, 0);
  Serial.print("turnOffClearTrash");
}
int checkingTrash(){
  int ans = 10;
  while(!Serial.available()) {return 10;}
  // serial read section
  while (Serial.available())
  {
    if (Serial.available() >0)
    {
      String c = Serial.readString();  //gets one byte from serial buffer
      readString = c; //makes the string readString
    }
  }

  if (readString.length() >0)
  {
    Serial.print("Arduino received: ");  
     ans = readString.charAt(0) - '0';
    Serial.println(ans); //see what was received
  }else{
    return 10;
  }

  delay(500);

  // serial write section

  char ard_sends = '1';
  Serial.print("Arduino sends: ");
  //Serial.println(ard_sends);
  Serial.print("\n");
  Serial.flush();
  
  Serial.println(ans);
  delay(2000);
  return ans;
}
