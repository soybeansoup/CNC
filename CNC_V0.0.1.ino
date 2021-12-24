#include <AccelStepper.h>

///// Define some steppers and the pins they will use /////
AccelStepper stepperX(AccelStepper::DRIVER, 2, 5, 0, 0); //step, dir (<- is for driver. Fullwire is reversed. See default GRBL pinout for arduino)
AccelStepper stepperY(AccelStepper::DRIVER, 3, 6, 0, 0);
AccelStepper stepperZ(AccelStepper::DRIVER, 4, 7, 0, 0);


//////////////////////////////
///// Define our globals /////
//////////////////////////////

//our limit switch pins
int limX = 9;
int limY = 10;
int limZ = 12;

//cutter diameter in mm (25.4mm = 1in)
int cutterDiameter = 51;

float stepOver = .25; //what percentage of the bit size to step over. Percentage from 0 to 1
float stepDown = 2; //how much material to take off in the Z axis in mm
float runningStepDown = 0;

float workWidth = 50; //work piece width (Y axis) in mm
float workLength = 50; //work length in mm
float heightToRemove = 6; //height to remove in mm.

//our driver defined steps per revolution
//the pitch of all of the lead screws is approximately the same (5.5mm/r)
float XscrewPitch = 5; //one revolution will move us how many mm
float YscrewPitch = 10;
float ZscrewPitch = 5;

int XstepsPerRev = 1000;
int YstepsPerRev = 1000;
int ZstepsPerRev = 1000;


/////////////////////////////////////////////////
///// Use globals to calculate our movement /////
/////////////////////////////////////////////////

float XstepsPerMM = XstepsPerRev / XscrewPitch;
float YstepsPerMM = YstepsPerRev / YscrewPitch;
float ZstepsPerMM = ZstepsPerRev / ZscrewPitch;


float moveXwidth = (cutterDiameter*stepOver) * XstepsPerMM;
float moveX = (cutterDiameter*stepOver) * XstepsPerMM;
float moveYwidth = (workWidth * YstepsPerMM) / 2; //y jogs back and forth (1,-1) so need to divide by 2
float moveZwidth = -(stepDown * ZstepsPerMM);
float moveZ = stepDown * ZstepsPerMM; //counter to increment our stepdown

// Ex: X axis has a max pre-deflection speed of ~700rpm so we run within a margin of error
// in RPMs if the desire to go as fast as possible
int preDeflectSpeedX = 500; // max ~400
int preDeflectSpeedY = 500;// max ~1800
int preDeflectSpeedZ = 1000;// max ~3000

//find our speeds
float Xspeed = preDeflectSpeedX * XstepsPerRev;
float Yspeed = preDeflectSpeedY * YstepsPerRev;
float Zspeed = preDeflectSpeedZ * ZstepsPerRev;


///// Set up our limit switches and configure our motors /////
void setup() {

  
    ///// Set up digital interrupts (limit switches) by axis /////
    attachInterrupt(digitalPinToInterrupt(limX), killSwitch, CHANGE);
    attachInterrupt(digitalPinToInterrupt(limY), killSwitch, CHANGE);
    attachInterrupt(digitalPinToInterrupt(limZ), killSwitch, CHANGE);

    ///// Configure motor settings. Gets calculated on setup /////
    stepperX.setMaxSpeed(Xspeed); //max speed in steps per inch
    stepperX.setAcceleration(2000.0); //after how many steps we reach our top speed
    //stepperX.moveTo(moveXwidth); //how far to move in steps. Negative will reverse. (as of writing positive ints -> east, negative -> west)
    
    stepperY.setMaxSpeed(Yspeed);
    stepperY.setAcceleration(10000.0);
    stepperY.moveTo(moveYwidth); //positive will move north, negative south

    
    stepperZ.setMaxSpeed(Zspeed);
    stepperZ.setAcceleration(2000.0);
    stepperZ.moveTo(moveZwidth); //negative will go down, positive up
}


//main loop
void loop() {
  
  //as long as we still have material to remove on the Z
  while ( runningStepDown = heightToRemove) {

    if (stepperY.distanceToGo() == 0) {
      stepperZ.run();
    }

    if ( moveXwidth <= workLength * XstepsPerMM ) {

      stepperY.run();

      //if we get to the end of our work space on the y..
      if (stepperY.distanceToGo() == 0 ) {

        //shuffle along the x pbased off bit size and passover 
        stepperX.run();
        stepperX.moveTo(moveXwidth);

        //once we finish on the x...
        if (stepperX.distanceToGo() == 0 ) {
          moveXwidth += moveX;
          stepperY.moveTo(-stepperY.currentPosition());
        }
      }
    }
    //If we are finished moving the length...
    else if ( stepperX.distanceToGo() == 0 && moveXwidth >= workLength ) {
      
      //increment our stepdown and decrement our z movement
      runningStepDown += stepDown;
      moveZwidth -= moveZ;
      stepperZ.moveTo(moveZwidth);  

      //reset the X after jogging back...
      stepperX.moveTo(-moveXwidth);  
      moveXwidth = moveX;
    }
  }
}


///// Logic for limits. Called by the digital interrupts for each axis /////
void killSwitch() {
    stepperX.stop(); //stop motor
    stepperX.disableOutputs(); //disable power

    stepperY.stop();
    stepperY.disableOutputs();
  
    stepperZ.stop();
    stepperZ.disableOutputs();
}

