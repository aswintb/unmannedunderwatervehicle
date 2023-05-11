#include <Servo.h>

  Servo ESC1;
  Servo ESC2;
  Servo ESC3;
  Servo ESC4;
  Servo ESC5;
  Servo gripper;

 int gripperstate;
 int gripperopen=0;
 int gripperclose=180;
    

class Motor {
  private:
  
  
  public:
    void setup() 
    {
      ESC1.attach(3, 1000, 2000); 
      ESC2.attach(5, 1000, 2000); 
      ESC3.attach(6, 1000, 2000);
      ESC4.attach(9, 1000, 2000);
      ESC5.attach(10, 1000, 2000);
      gripper.attach(11);
    }
    
    int spin_motor(int rpm) 
    {
      int potValue = map(rpm, 0, 1023, 0, 180);   // scale it to use it with the servo library (value between 0 and 180)

      if (potValue >= 90) 
      {
        potValue = potValue - 90;
      }
      else if (potValue <= 90) {
        potValue = 90 - potValue;
        //potValue =  potValue;
      }

      Serial.println(potValue);
     return potValue;
     // ESC1.write(potValue);    // Send the signal to the ESC
    }
};

Motor myMotor1;



void setup() {

  Serial.begin(9600);
  myMotor1.setup();
  pinMode(2,INPUT_PULLUP);
  gripper.write(gripperopen);
}

void loop() {

int st=0;



  int potValueLY =analogRead(A0);  // reads the value of the potentiometer (value between 0 and 1023):::: +y direction left side 
  int potValueRY =analogRead(A2);  // reads the value of the potentiometer (value between 0 and 1023):::: +y direction right side
  int potValueRX =analogRead(A3);
  int buttonvalue=digitalRead(2);

  if(buttonvalue==LOW)
  {
    if(gripperstate==0)
    {
      gripper.write(gripperopen);
      gripperstate=1;

    }

     else if(gripperstate==1)
    {
      gripper.write(gripperclose);
      gripperstate=0;

    }

    
  }

 

  
 if (potValueRY  > 1000)
  {

    ESC1.write(0);
    ESC2.write(0);
    ESC3.write(0);
    ESC4.write(0);
    ESC5.write(0);
  }

 //Joystick Left 

  if (potValueLY < (1023/2))
  {
 
  digitalWrite(12,HIGH);
  int val=myMotor1.spin_motor(potValueLY);
  ESC1.write(val);
  ESC2.write(val);
  }

 if (potValueLY >((1023/2)+10))
  {
    digitalWrite(12,HIGH);
    int val=myMotor1.spin_motor(potValueLY);
    ESC3.write(val);
  }

  //Joystick Right

  
  

  //+y 


  if (potValueRY  <(1023/2)-10) //+y
  {
    digitalWrite(12,HIGH);
    int val=myMotor1.spin_motor(potValueRY);
    ESC4.write(val);
    ESC5.write(val);
  }

 




  //-x

  if (potValueRX > (1023/2))
  {
    digitalWrite(12,HIGH);
    int val=myMotor1.spin_motor(potValueRX);
    ESC5.write(val);
  }
//+x
if (potValueRX <(1023/2))
  {
    digitalWrite(12,HIGH);
    int val=myMotor1.spin_motor(potValueRX);
    ESC4.write(val);
  }



/*Here's a step-by-step algorithm of the provided Arduino code:

1. Include the Servo library.
2. Declare six Servo objects, ESC1 to ESC5, and gripper.
3. Declare two integer variables, gripperstate, and gripperopen and initialize them with 0 and 180 respectively. Also, declare gripperclose as 180.
4. Define a class named Motor.
5. Declare a public method called setup() that performs the following:
   a. Call the attach() method of each Servo object to assign PWM pins and set the pulse range for the ESCs and gripper servo.
6. Declare a public method called spin_motor() that takes an integer rpm as input and returns an integer value.
7. In the spin_motor() method, perform the following steps:
   a. Map the rpm value to a range between 0 and 180 using the map() function.
   b. If the mapped value is greater than or equal to 90, subtract 90 from it.
   c. Otherwise, subtract the mapped value from 90.
   d. Print the mapped value to the Serial Monitor.
   e. Return the mapped value.
8. Create an instance of the Motor class called myMotor1.
9. In the setup() function, perform the following steps:
   a. Call the begin() method of the Serial object to initialize communication with the Serial Monitor.
   b. Call the setup() method of myMotor1 to attach the ESCs and gripper servo.
   c. Set pin 2 as an input and enable the internal pull-up resistor.
   d. Write the gripperopen value to the gripper servo.
10. In the loop() function, perform the following steps:
    a. Read the analog values from three potentiometers connected to pins A0, A2, and A3, and store them in the potValueLY, potValueRY, and potValueRX variables respectively.
    b. Read the digital value from pin 2 and store it in the buttonvalue variable.
    c. If buttonvalue is LOW, toggle the gripper state and write the corresponding gripper value to the gripper servo.
    d. If potValueRY is greater than 1000, stop all the ESCs by writing 0 to them.
    e. If potValueLY is less than half of the maximum value, set the digital pin 12 to HIGH, call the spin_motor() method of myMotor1 with potValueLY as input, and write the returned value to ESC1 and ESC2.
    f. If potValueLY is greater than half of the maximum value plus 10, set the digital pin 12 to HIGH, call the spin_motor() method of myMotor1 with potValueLY as input, and write the returned value to ESC3.
    g. If potValueRY is less than half of the maximum value minus 10, set the digital pin 12 to HIGH, call the spin_motor() method of myMotor1 with potValueRY as input, and write the returned value to ESC4 and ESC5.
    h. If potValueRX is greater than half of the maximum value, set the digital pin 12 to HIGH, call the spin_motor() method of myMotor1 with potValueRX as input, and write the returned value to ESC5.
    i. If potValueRX is less than half of the maximum value, set the digital pin 12 to HIGH, call the spin_motor() method of myMotor1 with potValueRX as input, and write the returned value to ESC4.
11. Repeat step 10 continuously.*/
}

