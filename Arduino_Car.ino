
#include <IRremote.h>

// senzorul IR
const int ledIR = 11;
IRrecv irrecv(ledIR); 
decode_results results;

// distance sensor
const int pingPin = 12 ; 
const int echoPin = 13 ;

// LEDs
int ledStop1 = 3;
int ledStop2 = 4;

// left motor = motor 1 
int EnA = 10;
int motor1_in1 = 9; 
int motor1_in2 = 8;

//right motor = motor 2
int EnB = 5;
int motor2_in3 = 6; 
int motor2_in4 = 7;

void setup(){
  pinMode(ledStop1, OUTPUT);
  pinMode(ledStop2, OUTPUT);
  pinMode(motor1_in1, OUTPUT);
  pinMode(motor1_in2, OUTPUT);
  pinMode(motor2_in3, OUTPUT);
  pinMode(motor2_in4, OUTPUT); 
  pinMode(EnA, OUTPUT);
  pinMode(EnB, OUTPUT);
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);//initialize serial 
  irrecv.enableIRIn(); //enable ir receiver module   
}

void Forward(){
  digitalWrite(ledStop1, LOW);
  digitalWrite(ledStop2, LOW);
  digitalWrite(motor1_in1, HIGH);
  digitalWrite(motor1_in2, LOW);
  analogWrite(EnA, 70);
  digitalWrite(motor2_in3, HIGH);
  digitalWrite(motor2_in4, LOW);
  analogWrite(EnB, 100);
  delay(1500); 
}

void Backward(){
  digitalWrite(ledStop1, LOW);
  digitalWrite(ledStop2, HIGH);
  digitalWrite(motor1_in1, LOW);
  digitalWrite(motor1_in2, HIGH);
  analogWrite(EnA, 70);
  digitalWrite(motor2_in3, LOW);
  digitalWrite(motor2_in4, HIGH);
  analogWrite(EnB, 95);
  delay(1500);  
}

void TurnRight(){
  digitalWrite(motor1_in1, HIGH);
  digitalWrite(motor1_in2, LOW);
  analogWrite(EnA, 60);
  digitalWrite(motor2_in3, HIGH);
  digitalWrite(motor2_in4, LOW);
  digitalWrite(ledStop1, LOW);
  digitalWrite(ledStop2, LOW);
  analogWrite(EnB, 255);
  delay(1500); 
}


void TurnLeft(){
  digitalWrite(motor1_in1, HIGH);
  digitalWrite(motor1_in2, LOW);
  analogWrite(EnA, 255);
  digitalWrite(motor2_in3, HIGH);
  digitalWrite(motor2_in4, LOW);
  digitalWrite(ledStop1, LOW);
  digitalWrite(ledStop2, LOW);
  analogWrite(EnB, 80);
  delay(1500); 
}


void Stop(){
  digitalWrite(motor1_in1, LOW);
  digitalWrite(motor1_in2, LOW);
  analogWrite(EnA, 0);
  digitalWrite(motor2_in3, LOW);
  digitalWrite(motor2_in4, LOW);
  digitalWrite(ledStop1, HIGH);
  digitalWrite(ledStop2, LOW);
  analogWrite(EnB, 0);
  delay(1500);  
}


void loop(){
    long duration, cm;
    digitalWrite(pingPin, LOW);
    delayMicroseconds(20);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(pingPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    cm = microsecondsToCentimeters(duration);
    Serial.print(cm);
    Serial.print("==>");
    Serial.println(results.value);
    if (cm>15)
    {   
        if (irrecv.decode(&results) && results.value == 3772778233)  
        {
                 Forward();
                 irrecv.resume(); 
         }       

       if (irrecv.decode(&results) && results.value == 3772819033) 
       {
               TurnLeft();
               irrecv.resume(); 
       }
       if (irrecv.decode(&results) && results.value == 3772794553) 
       {
                TurnRight();
                irrecv.resume(); 
       }
        if (irrecv.decode(&results) && results.value == 3772782313) 
        {
              Stop();
              irrecv.resume(); 
        }
        if (irrecv.decode(&results) && results.value == 3772810873) 
        {
              Backward();
              irrecv.resume(); 
         } 
    }   
    if (cm<15)
    {
              Stop();
              irrecv.resume(); 
              if (irrecv.decode(&results) && results.value == 3772810873 || cm<15)
                 {
                  Backward();
                  irrecv.resume(); 
                  }  
     }
}
long microsecondsToCentimeters(long microseconds){
  return microseconds/29/2 ;
  }
