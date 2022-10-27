#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

uint8_t servonum = 3;


#define SERVO_MIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVO_MAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define FREQUENCY 50 // Analog servos run at ~50 Hz updates

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("commencing serial connection");


  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(FREQUENCY);  // Analog servos run at ~50 Hz updates

  delay(10);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available())
  {
    String str = Serial.readString();
    evalStr(str); 
  }

}

int pulseWidth(int angle)
{
int pulse_wide, analog_value;
pulse_wide = map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
Serial.println(analog_value);
return analog_value;
}


void evalStr(String str)
{
  //Serial.print(str.length());
  if(str.length() < 4 )
  {
    Serial.println("erroroneus data recevied ");
  }
  else
    Serial.println("ok");
    
  char motorId = str.charAt(0);
  String subStrInt = str.substring(1, (str.length()-2));
  int motorAngle = subStrInt.toInt();
  Serial.println(motorId);
  Serial.println(motorAngle);
  if(motorId == 'a')
  {
    runMotorA(motorAngle);
  }
  if(motorId == 'b')
  {
    runMotorB(motorAngle);
  }
  if(motorId == 'c')
  {
    runMotorC(motorAngle);
  }
  if(motorId == 'd')
  {
    runMotorD(motorAngle);
  }
  
}
void runMotorA(int target)
{
  pwm.setPWM(0, 0, pulseWidth(target));
  delay(1000);
  Serial.print("Axis A set to ");
  Serial.print(target);
  Serial.print("\n"); 
}
void runMotorB(int target)
{
  pwm.setPWM(1, 0, pulseWidth(target));
  delay(1000);
  Serial.print("Axis B set to ");
  Serial.print(target);
  Serial.print("\n"); 
}
void runMotorC(int target)
{
  pwm.setPWM(2, 0, pulseWidth(target));
  delay(1000);
  Serial.print("Axis C set to ");
  Serial.print(target);
  Serial.print("\n"); 
}
void runMotorD(int target)
{
  pwm.setPWM(3, 0, pulseWidth(target));
  delay(1000);
  Serial.print("Axis D set to ");
  Serial.print(target);
  Serial.print("\n"); 
}
