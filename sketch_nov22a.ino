#include<Servo.h>
String readString;
const int trig = 2;     // chân trig của HC-SR04
const int echo = 3;     // chân echo của HC-SR04

const int LeftMotorForward = 10;
const int LeftMotorBackward = 12;
const int RightMotorForward = 11;
const int RightMotorBackward = 13;


const int bangchuyen = 7;

const int choiquet = 8;

 int distance;
Servo servo_motor;
Servo servo_camera;
void setup()
{
  Serial.begin(9600);     // giao tiếp Serial với baudrate 9600
  pinMode(trig,OUTPUT);   // chân trig sẽ phát tín hiệu
  pinMode(echo,INPUT);    // chân echo sẽ nhận tín hiệu
  servo_motor.attach(9);
  servo_camera.attach(1);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  pinMode(bangchuyen, OUTPUT);
  pinMode(choiquet, OUTPUT);
  distance = readSensor();    // Get Ping Distance.
  delay(100);               // Wait for 100ms.
  distance = readSensor();
  delay(100);
  distance = readSensor();
  delay(100);
  distance = readSensor();
  delay(100);
}
 
void loop()
{
    int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);
  if (distance <= 40)
  {
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distanceRight >= distanceLeft)
    {
      turnRight();
      delay(300);
      moveStop();
    }
    else
    {
      turnLeft();
      delay(300);
      moveStop();
    }
  
  }
  else
  {
    if(checkingTrash() == 0){
      moveForward(); 
      turnOnClearTrash();
    }else if(checkingTrash() == 1){
      turnRight();
      delay(1200);
      CameraLookRight();
    }else{
      turnLeft();
      delay(1200);
      CameraLookLeft();
    }
    
  }

    distance = readSensor();

}

int readSensor(){
    unsigned long duration; // biến đo thời gian
    int distance;           // biến lưu khoảng cách
    
    /* Phát xung từ chân trig */
    digitalWrite(trig,0);   // tắt chân trig
    delayMicroseconds(2);
    digitalWrite(trig,1);   // phát xung từ chân trig
    delayMicroseconds(5);   // xung có độ dài 5 microSeconds
    digitalWrite(trig,0);   // tắt chân trig
    
    /* Tính toán thời gian */
    // Đo độ rộng xung HIGH ở chân echo. 
    duration = pulseIn(echo,HIGH);  
    // Tính khoảng cách đến vật.
    distance = int(duration/2/29.412);
    
    /* In kết quả ra Serial Monitor */
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
}

void moveForward()    // Move Forward Function for Motor Driver.
{
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(RightMotorBackward, LOW);
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(LeftMotorBackward, LOW);

    Serial.println("moveForward");
}

void moveBackward()   // Move Backward Function for Motor Driver.
{
  //analogWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  analogWrite(RightMotorBackward, 255);
  digitalWrite(LeftMotorForward, HIGH);
  analogWrite(LeftMotorBackward, 255);
  //analogWrite(RightMotorForward, HIGH);
  Serial.println("moveBackward");
}

void turnRight()      // Turn Right Function for Motor Driver.
{
  digitalWrite(RightMotorForward, 0);
  digitalWrite(RightMotorBackward, 255);
  digitalWrite(LeftMotorForward, 255);
  digitalWrite(LeftMotorBackward, 0);
  Serial.print("turnRight");
}

void turnLeft()       // Turn Left Function for Motor Driver.
{
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
  Serial.print("turnLeft");
}
int lookRight()     // Look Right Function for Servo Motor
{  
  servo_motor.write(50);
  delay(500);
  int distance = readSensor();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int lookLeft()      // Look Left Function for Servo Motor 
{
  servo_motor.write(180);
  delay(500);
  int distance = readSensor();
  delay(100);
  servo_motor.write(115);
  return distance;
}
int CameraLookRight()     // Look Right Function for Servo Motor
{  
  servo_camera.write(50);
  delay(500);
  int distance = checkingTrash();
  delay(100);
  servo_camera.write(115);
  return distance;
}

int CameraLookLeft()      // Look Left Function for Servo Motor 
{
  servo_camera.write(180);
  delay(500);
  int distance = checkingTrash();
  delay(100);
  servo_camera.write(115);
  return distance;
}
void turnOnClearTrash(){
  
  digitalWrite(bangchuyen, 255);
  digitalWrite(choiquet, 255);
}
int checkingTrash(){
  while(!Serial.available()) {}
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
    Serial.println(readString); //see what was received
  }

  delay(500);

  // serial write section

  char ard_sends = '1';
  Serial.print("Arduino sends: ");
  Serial.println(ard_sends);
  Serial.print("\n");
  Serial.flush();
  return readString.toInt();
}
