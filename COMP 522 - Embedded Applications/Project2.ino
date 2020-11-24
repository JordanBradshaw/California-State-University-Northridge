#include <Stepper.h>
  
#define STEPS 2038 // the number of steps in one revolution of your motor (28BYJ-48)
const int buttonPin = 2;
const int INPUT1 = 2;
const int INPUT2 = 4;
int buttonState = 0;
int currVelocity = 0;
Stepper stepper(STEPS, 8, 10, 9, 11);

  
void setup() {
  pinMode(INPUT1,INPUT);
  pinMode(INPUT2,INPUT);
  //stepper.step(STEPS);
  //stepper.setSpeed(2);
 } 


void loop(){
  toggleMachine();
}
void toggleMachine(){
switch (buttonState){
  case 0:
    stateInit();
    buttonState=1;
    break;
  case 1:
    state1();
    break;
 }
}

void stateInit(){
  //input1Check();
  stepper.setSpeed(0);
  stepper.step(STEPS);

}

void state1(){
  //input1Check();
  stepper.setSpeed(1);
  stepper.step(STEPS);
}/*
void state2(){
  input1Check();
  stepper.setSpeed(2);
  stepper.step(STEPS);
}
void state3(){
  input1Check();
  stepper.setSpeed(3);
  stepper.step(STEPS);
}
void state4(){
  input2Check();
  stepper.setSpeed(4);
  stepper.step(STEPS);
}

void input1Check(){
  int input1State = digitalRead(INPUT1);
  if (input1State == HIGH) {
    buttonState++;
  }
}
void input2Check(){
  int input2State = digitalRead(INPUT2);
  if (input2State == HIGH){
     buttonState=0;
  }
}*/
