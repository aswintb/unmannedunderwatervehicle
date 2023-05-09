#include <Servo.h>

  Servo ESC1;
  Servo ESC2;
  Servo ESC3;
  Servo ESC4;
  Servo ESC5;
    

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
    }
    
    int spin_motor(int rpm) 
    {
      int potValue = map(rpm, 0, 1023, 0, 180);   // scale it to use it with the servo library (value between 0 and 180)

      if (potValue >= 90) {
        potValue = potValue - 90;
      }
      else if (potValue <= 90) {
        potValue = 90 - potValue;
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
}

void loop() {


  //Joystick Left 

  int potValueLY =analogRead(A0);  // reads the value of the potentiometer (value between 0 and 1023):::: +y direction left side 
  
  if (potValueLY >=(1023/2))
  {
  int val=myMotor1.spin_motor(potValueLY);
  ESC1.write(val);
  ESC2.write(val);
  }

  else if (potValueLY <=(1023/2))
  {
  int val=myMotor1.spin_motor(potValueLY);
  ESC3.write(val);
  }

  //Joystick Right

  int potValueRY =analogRead(A2);  // reads the value of the potentiometer (value between 0 and 1023):::: +y direction left side 
  
  if (potValueRY >=(1023/2)) //+y
  {
  int val=myMotor1.spin_motor(potValueRY);
  ESC4.write(val);
  ESC5.write(val);
  }


  //-x
  int potValueRX =analogRead(A3);
  if (potValueRX <=(1023/2))
  {
  int val=myMotor1.spin_motor(potValueRX);
  ESC5.write(val);
  }
//+x
 else if (potValueRX >=(1023/2))
  {
  int val=myMotor1.spin_motor(potValueRX);
  ESC4.write(val);
  }

}
