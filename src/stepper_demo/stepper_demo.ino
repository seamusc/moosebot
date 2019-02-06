#include <Stepper.h>
#define STEPS 2038

// motor pins
#define motorPin1  3     // IN1 on the ULN2003 driver 1
#define motorPin2  4     // IN2 on the ULN2003 driver 1
#define motorPin3  5     // IN3 on the ULN2003 driver 1
#define motorPin4  6     // IN4 on the ULN2003 driver 1


Stepper stepper1(STEPS, motorPin1, motorPin3, motorPin2, motorPin4);


void setup() {

stepper1.setSpeed(10);
Serial.being(9600);
}
void loop(){
  Serial.println("Starting");
  stepper1.step(2038);
  Serial.println("Ending");
}
