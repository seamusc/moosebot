#include <Wire.h>

#define BALL_COUNTER_PIN 3

// Right one
const byte MY_ADDRESS = 25;
const byte RPI_ADDRESS = 42;
// Left one
//const byte MY_ADDRESS = 42;
//const byte RPI_ADDRESS = 25;
int RpiData[5];
bool gotSignalFromIR = false;
byte ballCounter = 0;
bool isBallPassing = true;

int val;

/**
 * Defines modes of moving the robot
 * depending on the visibility of the ball
 */
enum BALLVISIBILITY {
  RANDOM,     // Ball not visible, random moving and avoiding obstacles
  FORWARD,    // Ball is forward
  LEFT,       // Ball is on the left
  RIGHT       // Ball is on the right
} movement_mode = RANDOM;

/**
 * Processes RPi data, received from I2C
 */
void processRpiData() {
  Serial.println("------Checking for new data from I2C------");
  if(RpiData[0] == 1) {
    // New data came in
    Serial.println("------Processing new Rpi data------");
    if(RpiData[1] == 0) {
      // Ball is not detected
      movement_mode = RANDOM;
    } else if (RpiData[2] == 1) {
      // Ball is on the right
      movement_mode = RIGHT;
    } else if (RpiData[3] == 1) {
      // Ball in center
      movement_mode = FORWARD;
    } else if (RpiData[4] == 1) {
      // Ball on the left
      movement_mode = LEFT;
    }
    // Mark processing as done
    RpiData[0] = 0;
  }
}

/**
 * Sends signal to RPi that ball is picked up
 */
void sendBallPickedUpSignal() {
  if(gotSignalFromIR) {
    Wire.beginTransmission(RPI_ADDRESS);
    Wire.write(ballCounter);
    Wire.endTransmission();
    delay(200);
    ballCounter = 0;
    gotSignalFromIR = false;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(BALL_COUNTER_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(3), counter_ISR, RISING);
  
  Wire.begin(MY_ADDRESS);
  Wire.onReceive(receiveEvent);    
}

void loop() {
  delay(200);
  processRpiData();
  sendBallPickedUpSignal();
  delay(2000);
}

/**
 * ISR for the IR sensor
 */
void counter_ISR() {
  delay(500);
  val = digitalRead(BALL_COUNTER_PIN);
  if (val == HIGH) {
    if (!isBallPassing){
      isBallPassing = true;
      ballCounter++;
      gotSignalFromIR = true;
      Serial.print(">>>>> Num balls collected so far: ");
      Serial.println(ballCounter);
      delay(50);
    }
  } else {
    delay(50);
    isBallPassing = false;
  }
}

/**
 * I2C Receive event
 * 4B from RPi
 * - [0] - New data received
 * - [1] - I see/don't see the ball
 * - [2] - ball is right
 * - [3] - ball is in center
 * - [4] - ball is left
 */
void receiveEvent(int bytes) {
  RpiData[0] = 1; // Mark as new data arrived
  Serial.println(">>>>>> I2C new data received!");
  for (int i = 1; i <= bytes; i++) {
    RpiData[i] = Wire.read();
    Serial.print("[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(RpiData[i]);
  }
}
