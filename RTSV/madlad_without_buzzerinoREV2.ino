#include <Servo.h>
#include <SoftwareSerial.h>
// for variables
unsigned int distance;
unsigned long duration;
long newDistance;
long IRdistance;
long newIRdistance;
// for pins
const int bluetoothRx = 0;
const int bluetoothTx = 1;
const int triggerPin = 3;
const int echoPin = 4;
const int sensorservoPin = 6;
const int driveservoPin = 9;
const int buttonPin = 12;
const int IRsensor = 13;
int buttonStatus = 0;
int Run = 0;
// for values
boolean currentState;
boolean previousState;



Servo sensorservo;
Servo driveservo;
//SoftwareSerial bluetooth(bluetoothTx, bluetoothRx); 

void setup()
{
  pinMode(IRsensor, INPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT);
  sensorservo.attach(sensorservoPin);
  driveservo.attach(driveservoPin);
  Serial.begin(9600);
  sensorservo.write(90);
  driveservo.writeMicroseconds(1500);
}
int calculateIRdistance()
{
  currentState = digitalRead(IRsensor);
   if (previousState != currentState && currentState == HIGH)
       {
        newIRdistance = IRdistance + ((5.25 * PI)/4);
        return newIRdistance;
       }
       previousState = currentState;
        IRdistance = newIRdistance;
}


int calculatedistance()
{
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2); 
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = 0.01723 * duration;
  if (distance < 200)
  {
  return distance;
  }
  else if (distance = 200)
  {
    return distance = 200;
  }
  else (distance > 200);
  {
    return distance = 200;
  }
}

void motor() {
   if (distance<200);
   {
    for(int i=0;i<=165;i+=10)
    {          
    sensorservo.write(i);
    delay(100);
    int IRDistance = calculateIRdistance();
    Serial.print(IRDistance);
    Serial.print(",");
    distance = calculatedistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.println();
    
    buttonStatus = digitalRead(buttonPin);
    if(buttonStatus == HIGH && Run == 0){
  Run = 1;
  }
  if(buttonStatus == LOW && Run == 1){
  Run = 2;
  driveservo.writeMicroseconds(1000);
  }
  if(buttonStatus == HIGH && Run == 2){
  Run = 3;
  }
  if(buttonStatus == LOW && Run == 3){
  driveservo.writeMicroseconds(1500);
  Run = 0;
  }
    }                  
      

    for(int i=165;i>=0;i-=10)
    {  
    sensorservo.write(i);
    delay(100);
    int IRDistance = calculateIRdistance();
    Serial.print(IRDistance);
    Serial.print(",");
    distance = calculatedistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.println();
    
    buttonStatus = digitalRead(buttonPin);
    if(buttonStatus == HIGH && Run == 0){
  Run = 1;
  }
  if(buttonStatus == LOW && Run == 1){
  Run = 2;
  driveservo.writeMicroseconds(1000);
  }
    if(buttonStatus == HIGH && Run == 2){
  Run = 3;
  }
  if(buttonStatus == LOW && Run == 3){
  driveservo.writeMicroseconds(1500);
  Run = 0;
  }
    }
    }
  }
  
void loop()
{
  buttonStatus = digitalRead(buttonPin);
  if(buttonStatus == HIGH && Run == 0){
  Run = 1;
  }
  if(buttonStatus == LOW && Run == 1){
  Run = 2;
  driveservo.writeMicroseconds(1000);
  motor();
  }
  if(buttonStatus == LOW && Run == 2){
  Run = 2;
  driveservo.writeMicroseconds(1000);
  motor();
  }
}
    
