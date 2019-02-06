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


long duration, cm;


void delays(unsigned long t) {
  for(unsigned long i = 0; i < t; i++) {
    delay(1);
  }
}

int getDistanceLeft() {
   pinMode(TRIG_PIN_LEFT, OUTPUT);
   digitalWrite(TRIG_PIN_LEFT, LOW);
   delayMicroseconds(2);
   digitalWrite(TRIG_PIN_LEFT, HIGH);
   delayMicroseconds(10);
   digitalWrite(TRIG_PIN_LEFT, LOW);
   pinMode(ECHO_PIN_LEFT, INPUT);
   duration = pulseIn(ECHO_PIN_LEFT, HIGH);
   cm = microsecondsToCentimeters(duration);
   pinMode(TRIG_PIN_LEFT, OUTPUT);
   delay(2);
   
   return cm;
   
}

int getDistanceRight() {
   pinMode(TRIG_PIN_RIGHT, OUTPUT);
   digitalWrite(TRIG_PIN_RIGHT, LOW);
   delayMicroseconds(2);
   digitalWrite(TRIG_PIN_RIGHT, HIGH);
   delayMicroseconds(10);
   digitalWrite(TRIG_PIN_RIGHT, LOW);
   pinMode(ECHO_PIN_RIGHT, INPUT);
   duration = pulseIn(ECHO_PIN_RIGHT, HIGH);
   cm = microsecondsToCentimeters(duration);
   pinMode(TRIG_PIN_RIGHT, OUTPUT);
   delay(2);
  
   return cm;
}

void forward(int carSpeed, bool debug = false){ 
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  Serial.print("Go forward at ");
  Serial.println(carSpeed);

  
}

void back(int carSpeed, bool debug = false){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  Serial.print("Go back at ");
  Serial.println(carSpeed);
}

void left(int carSpeed, bool debug = false){
  analogWrite(ENA,carSpeed);
  analogWrite(ENB,carSpeed);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW); 
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
    middleDistanceLeft = getDistanceLeft();
    middleDistanceRight = getDistanceRight();
    Serial.println("--------------------");
    Serial.print("LeftReading: ");
    Serial.println(middleDistanceLeft);
    Serial.print("RightReading: ");
    Serial.println(middleDistanceRight);
    if (middleDistanceLeft <= 20 || middleDistanceRight <= 20){
      right(250);
      delay(250);
      stop();
    } else {
      back(200);
      delay(100);
      stop();
    }
}

void setup() {
  Serial.begin(9600);
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
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
