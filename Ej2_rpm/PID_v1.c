/**********************************************************************************************
 * C PID Library - Version 1.0.1
 * modified my Matthew Blythe <mblythester@gmail.com> mjblythe.com/hacks
 * originally by Brett Beauregard <br3ttb@gmail.com> brettbeauregard.com
 *
 * This Library is licensed under a GPLv3 License
 **********************************************************************************************/
 typedef float FloatType;
 //typedef double floatType;
 #include <stdbool.h>

 //Constants used in some of the functions below
 typedef enum
 {
   PID_Mode_Automatic = 1,
   PID_Mode_Manual    = 0
 } PidModeType;

 typedef enum
 {
   PID_Direction_Direct  = 0,
   PID_Direction_Reverse = 1
 } PidDirectionType;

 typedef struct {
   FloatType dispKp; // * we'll hold on to the tuning parameters in user-entered
   FloatType dispKi; //   format for display purposes
   FloatType dispKd; //

   FloatType kp; // * (P)roportional Tuning Parameter
   FloatType ki; // * (I)ntegral Tuning Parameter
   FloatType kd; // * (D)erivative Tuning Parameter

   PidDirectionType controllerDirection;

   FloatType myInput; // * Pointers to the Input, Output, and Setpoint variables
   FloatType myOutput; //   This creates a hard link between the variables and the
   FloatType mySetpoint; //   PID, freeing the user from having to constantly tell us
                      //   what these values are.  with pointers we'll just know.

 //  unsigned long lastTime;
   FloatType ITerm, lastInput;

   unsigned long SampleTime;
   FloatType outMin, outMax;
   bool inAuto;
 } PidType;

 //commonly used functions **************************************************************************

 //  constructor.  links the PID to the Input, Output, and
 //  Setpoint.  Initial tuning parameters are also set here
 void PID_init(PidType* pid,
     FloatType kp,
     FloatType ki,
     FloatType kd,
     PidDirectionType controllerDirection);

 // sets PID to either Manual (0) or Auto (non-0)
 void PID_SetMode(PidType* pid, PidModeType mode);

 // performs the PID calculation.  it should be
 // called every time loop() cycles. ON/OFF and
 // calculation frequency can be set using SetMode
 // SetSampleTime respectively
 bool PID_Compute(PidType* pid);

 // clamps the output to a specific range. 0-255 by default, but
 // it's likely the user will want to change this depending on
 // the application
 void PID_SetOutputLimits(PidType* pid, FloatType min, FloatType max);

 //available but not commonly used functions ********************************************************

 // While most users will set the tunings once in the
 // constructor, this function gives the user the option
 // of changing tunings during runtime for Adaptive control
 void PID_SetTunings(PidType* pid, FloatType kp, FloatType ki, FloatType kd);

 // Sets the Direction, or "Action" of the controller. DIRECT
 // means the output will increase when error is positive. REVERSE
 // means the opposite.  it's very unlikely that this will be needed
 // once it is set in the constructor.
 void PID_SetControllerDirection(PidType* pid, PidDirectionType Direction);

 // sets the frequency, in Milliseconds, with which
 // the PID calculation is performed.  default is 100
 void PID_SetSampleTime(PidType* pid, int newSampleTime);

 //Display functions ****************************************************************
 // These functions query the pid for interal values.
 //  they were created mainly for the pid front-end,
 // where it's important to know what is actually
 //  inside the PID.
 FloatType PID_GetKp(PidType* pid);
 FloatType PID_GetKi(PidType* pid);
 FloatType PID_GetKd(PidType* pid);
 PidModeType PID_GetMode(PidType* pid);
 PidDirectionType PID_GetDirection(PidType* pid);



//#include "pid.h"
void PID_Initialize(PidType* pid);

/*Constructor (...)*********************************************************
 *    The parameters specified here are those for for which we can't set up
 *    reliable defaults, so we need to have the user set them.
 ***************************************************************************/
void PID_init(PidType* pid, FloatType Kp, FloatType Ki, FloatType Kd,
    PidDirectionType ControllerDirection) {
  pid->myInput = 0;
  pid->myOutput = 0;
  pid->mySetpoint = 0;
  pid->ITerm = 0;
  pid->lastInput = 0;
  pid->inAuto = false;

  PID_SetOutputLimits(pid, 0, 0xffff);

  //default Controller Sample Time is 0.1 seconds
  pid->SampleTime = 100;

  PID_SetControllerDirection(pid, ControllerDirection);
  PID_SetTunings(pid, Kp, Ki, Kd);

//  pid->lastTime = millis() - pid->SampleTime;
}


/* Compute() **********************************************************************
 *     This, as they say, is where the magic happens.  this function should be called
 *   every time "void loop()" executes.  the function will decide for itself whether a new
 *   pid Output needs to be computed.  returns true when the output is computed,
 *   false when nothing has been done.
 **********************************************************************************/
bool PID_Compute(PidType* pid) {
  if (!pid->inAuto) {
    return false;
  }
//  unsigned long now = millis();
//  unsigned long timeChange = (now - pid->lastTime);
//  if (timeChange >= pid->SampleTime) {
    /*Compute all the working error variables*/
    FloatType input = pid->myInput;
    FloatType error = pid->mySetpoint - input;
    pid->ITerm += (pid->ki * error);
    if (pid->ITerm > pid->outMax)
      pid->ITerm = pid->outMax;
    else if (pid->ITerm < pid->outMin)
      pid->ITerm = pid->outMin;
    FloatType dInput = (input - pid->lastInput);

    /*Compute PID Output*/
    FloatType output = pid->kp * error + pid->ITerm - pid->kd * dInput;

    if (output > pid->outMax)
      output = pid->outMax;
    else if (output < pid->outMin)
      output = pid->outMin;
    pid->myOutput = output;

    /*Remember some variables for next time*/
    pid->lastInput = input;
//    pid->lastTime = now;
    return true;
//  } else {
//    return false;
//  }
}


/* SetTunings(...)*************************************************************
 * This function allows the controller's dynamic performance to be adjusted.
 * it's called automatically from the constructor, but tunings can also
 * be adjusted on the fly during normal operation
 ******************************************************************************/

void PID_SetTunings(PidType* pid, FloatType Kp, FloatType Ki, FloatType Kd) {
  if (Kp < 0 || Ki < 0 || Kd < 0){
    return;
  }

  pid->dispKp = Kp;
  pid->dispKi = Ki;
  pid->dispKd = Kd;

  FloatType SampleTimeInSec = ((FloatType) pid->SampleTime) / 1000;
  pid->kp = Kp;
  pid->ki = Ki * SampleTimeInSec;
  pid->kd = Kd / SampleTimeInSec;

  if (pid->controllerDirection == PID_Direction_Reverse) {
    pid->kp = (0 - pid->kp);
    pid->ki = (0 - pid->ki);
    pid->kd = (0 - pid->kd);
  }
}

/* SetSampleTime(...) *********************************************************
 * sets the period, in Milliseconds, at which the calculation is performed
 ******************************************************************************/
void PID_SetSampleTime(PidType* pid, int NewSampleTime) {
  if (NewSampleTime > 0) {
    FloatType ratio = (FloatType) NewSampleTime / (FloatType) pid->SampleTime;
    pid->ki *= ratio;
    pid->kd /= ratio;
    pid->SampleTime = (unsigned long) NewSampleTime;
  }
}

/* SetOutputLimits(...)****************************************************
 *     This function will be used far more often than SetInputLimits.  while
 *  the input to the controller will generally be in the 0-1023 range (which is
 *  the default already,)  the output will be a little different.  maybe they'll
 *  be doing a time window and will need 0-8000 or something.  or maybe they'll
 *  want to clamp it from 0-125.  who knows.  at any rate, that can all be done
 *  here.
 **************************************************************************/
void PID_SetOutputLimits(PidType* pid, FloatType Min, FloatType Max) {
  if (Min >= Max) {
    return;
  }
  pid->outMin = Min;
  pid->outMax = Max;

  if (pid->inAuto) {
    if (pid->myOutput > pid->outMax) {
      pid->myOutput = pid->outMax;
    } else if (pid->myOutput < pid->outMin) {
      pid->myOutput = pid->outMin;
    }

    if (pid->ITerm > pid->outMax) {
      pid->ITerm = pid->outMax;
    } else if (pid->ITerm < pid->outMin) {
      pid->ITerm = pid->outMin;
    }
  }
}

/* SetMode(...)****************************************************************
 * Allows the controller Mode to be set to manual (0) or Automatic (non-zero)
 * when the transition from manual to auto occurs, the controller is
 * automatically initialized
 ******************************************************************************/
void PID_SetMode(PidType* pid, PidModeType Mode)
{
    bool newAuto = (Mode == PID_Mode_Automatic);
    if(newAuto == !pid->inAuto)
    {  /*we just went from manual to auto*/
        PID_Initialize(pid);
    }
    pid->inAuto = newAuto;
}

/* Initialize()****************************************************************
 *  does all the things that need to happen to ensure a bumpless transfer
 *  from manual to automatic mode.
 ******************************************************************************/
void PID_Initialize(PidType* pid) {
  pid->ITerm = pid->myOutput;
  pid->lastInput = pid->myInput;
  if (pid->ITerm > pid->outMax) {
    pid->ITerm = pid->outMax;
  } else if (pid->ITerm < pid->outMin) {
    pid->ITerm = pid->outMin;
  }
}

/* SetControllerDirection(...)*************************************************
 * The PID will either be connected to a DIRECT acting process (+Output leads
 * to +Input) or a REVERSE acting process(+Output leads to -Input.)  we need to
 * know which one, because otherwise we may increase the output when we should
 * be decreasing.  This is called from the constructor.
 ******************************************************************************/
void PID_SetControllerDirection(PidType* pid, PidDirectionType Direction) {
  if (pid->inAuto && Direction != pid->controllerDirection) {
    pid->kp = (0 - pid->kp);
    pid->ki = (0 - pid->ki);
    pid->kd = (0 - pid->kd);
  }
  pid->controllerDirection = Direction;
}

/* Status Funcions*************************************************************
 * Just because you set the Kp=-1 doesn't mean it actually happened.  these
 * functions query the internal state of the PID.  they're here for display
 * purposes.  this are the functions the PID Front-end uses for example
 ******************************************************************************/
FloatType PID_GetKp(PidType* pid) {
  return pid->dispKp;
}
FloatType PID_GetKi(PidType* pid) {
  return pid->dispKi;
}
FloatType PID_GetKd(PidType* pid) {
  return pid->dispKd;
}
PidModeType PID_GetMode(PidType* pid) {
  return pid->inAuto ? PID_Mode_Automatic : PID_Mode_Manual;
}
PidDirectionType PID_GetDirection(PidType* pid) {
  return pid->controllerDirection;
}
