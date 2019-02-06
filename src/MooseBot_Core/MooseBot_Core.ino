#define ECHO_PIN_LEFT  A4  
#define TRIG_PIN_LEFT  A5 
#define ECHO_PIN_RIGHT  A2  
#define TRIG_PIN_RIGHT  A3 
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define MIN_CAR_SPEED 100
#define MAX_CAR_SPEED 250

int rightDistanceLeft = 0, leftDistanceLeft = 0, middleDistanceLeft = 0;
int rightDistanceRight = 0, leftDistanceRight = 0, middleDistanceRight = 0;

void delays(unsigned long t) {
  for(unsigned long i = 0; i < t; i++) {
    delay(1);
  }
}

int getDistanceLeft() {
  digitalWrite(TRIG_PIN_LEFT, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_LEFT, HIGH);
  delayMicroseconds(20);
  digitalWrite(TRIG_PIN_LEFT, LOW);
  return (int)pulseIn(ECHO_PIN_LEFT, HIGH) / 58; // in cm
}

int getDistanceRight() {
  digitalWrite(TRIG_PIN_RIGHT, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_RIGHT, HIGH);
  delayMicroseconds(20);
  digitalWrite(TRIG_PIN_RIGHT, LOW);
  return (int)pulseIn(ECHO_PIN_RIGHT, HIGH) / 58; // in cm
}

void forward(int carSpeed, bool debug = false){ 
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  Serial.println("Go forward!");
}

void back(int carSpeed, bool debug = false){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  Serial.println("Go back!");
}

void left(int carSpeed, bool debug = false){
  analogWrite(ENA,carSpeed);
  analogWrite(ENB,carSpeed);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH); 
  Serial.println("Go left!");
}

void right(int carSpeed, bool debug = false){
  analogWrite(ENA,carSpeed);
  analogWrite(ENB,carSpeed);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  Serial.println("Go right!");
}

void stop(bool debug = false){
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  Serial.println("Stop!");
}

void distanceReadings() {
//  if(func_mode == ObstaclesAvoidance){
//    servo.write(90);
    delays(500);
    middleDistanceLeft = getDistanceLeft();
    middleDistanceRight = getDistanceRight();
    Serial.println("--------------------");
    Serial.print("LeftReading: ");
    Serial.println(middleDistanceLeft);
    Serial.print("RightReading: ");
    Serial.println(middleDistanceRight);
//    if(middleDistance <= 40) {
//      stop();
//      delays(500);
////      servo.write(10);
//      right();
//      delays(180);
////      delays(1000);
//      rightDistanceLeft = getDistanceLeft();
//      rightDistanceRight = getDistanceRight();
//      
//      
//      delays(500);
////      servo.write(90);
//      left();
//      delays(360);
////      delays(1000);
////      servo.write(170);
////      delays(1000); 
//      leftDistanceLeft = getDistanceLeft();
//      leftDistanceRight = getDistanceRight();
//      
//      delays(500);
////      servo.write(90);
//      delays(1000);
//      if(rightDistance > leftDistance) {
//        right();
//        delays(360);
//      } else if(rightDistance < leftDistance) {
//        left();
//        delays(360);
//      } else if((rightDistance <= 40) || (leftDistance <= 40)) {
//        back();
//        delays(180);
//      } else {
//        forward();
//      }
//    } else {
//        forward();
//    }  
//  }  
}

void setup() {
  Serial.begin(9600);
  // Left ultrasonic sensor
  pinMode(ECHO_PIN_LEFT, INPUT);
  pinMode(TRIG_PIN_LEFT, OUTPUT);
  // Right ultrasonic sensor
  pinMode(ECHO_PIN_RIGHT, INPUT);
  pinMode(TRIG_PIN_RIGHT, OUTPUT);
  // Wheels
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {
  distanceReadings();
  

  
//  forward();
//  delays(5000);
//  stop();
//  delays(3000);
//  back();
//  delays(5000);
//  stop();
//  delays(3000);
}
