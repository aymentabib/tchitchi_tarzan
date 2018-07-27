/*
un suiveur de ligne/éviteur d'odstacle avec correction pid.
*/
#include <NewPing.h>
#include "pid_follower.h"
//
//float Kp = 40, Ki = 5, Kd = 10;
float Kp = 255*2/12, Ki = 255*2/12, Kd = 0;
//float Kp = 12, Ki = 10, Kd = 10;
float error = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0, previous_I = 0;
byte sensor[5] = {0, 0, 0, 0, 0};
int initial_motor_speed = 255;
unsigned int pulse_controle = 0;
unsigned int sensor_controle = 0;
int s;
int duration = 0;
int distance = 0;
//#define test
//
NewPing sonar(trig, echo, 100);


void setup()
{
  //
  sonar.timer_ms(500, timer_callback);
  //
  pinMode(pwm_left, OUTPUT); //PWM Pin 1
  pinMode(pwm_right, OUTPUT); //PWM Pin 2
  pinMode(trig , OUTPUT);
  pinMode(echo , INPUT);
  pinMode(leftForward , OUTPUT);
  pinMode(leftBackward , OUTPUT);
  pinMode(rightForward , OUTPUT);
  pinMode(rightBackward , OUTPUT);
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);
#ifdef test
  //Enable Serial Communications
  Serial.begin(9600);
#endif
  Serial.begin(9600);

}
void loop()
{
  /*
  while(1)
  {
    //avance(255);
    delay(2000);
    gauche(255);
    delay(2000);
    //droite(255);
    //delay(2000);
    //arriere(255);
    delay(2000);
    
  }
*/


  
    sensor_controle++;
    //if (sensor_controle == 1)
    {
      read_sensor_values();
      sensor_controle = 0;
      calculate_pid();
    }
#ifdef test
    Serial.write("\n s0 :");
    Serial.print(sensor[0], HEX);
    Serial.write("- s1 :");
    Serial.print(sensor[1], HEX);
    Serial.write("- s2 :");
    Serial.print(sensor[2], HEX);
    Serial.write("- s3 :");
    Serial.print(sensor[3], HEX);
    Serial.write("- s4 :");
    Serial.print(sensor[4], HEX);
#endif
    
    motor_control();
  


}


void timer_callback()
{

  
}

void calculate_pid()
{
  P = error;
  I = I + previous_I;
  D = error - previous_error;

  PID_value = (Kp * P) + (Ki * I) + (Kd * D);

  previous_I = I;
  previous_error = error;
}

void motor_control()
{
  // Calculating the effective motor speed:
  int left_motor_speed = initial_motor_speed - PID_value;
  int right_motor_speed = initial_motor_speed + PID_value;

  // The motor speed should not exceed the max PWM value
  constrain(left_motor_speed, -255, 255);
  constrain(right_motor_speed, -255, 255);
  //Serial.println(left_motor_speed);
  //Serial.println(right_motor_speed);

  //analogWrite(9,initial_motor_speed-PID_value);   //Left Motor Speed

  if (left_motor_speed >= 0 && right_motor_speed >= 0)
  {
    analogWrite(pwm_left, left_motor_speed);  //Left Motor Speed
    analogWrite(pwm_right, right_motor_speed); //Right Motor Speed
    // avance
    digitalWrite(leftForward, HIGH);
    digitalWrite(leftBackward, LOW);
    digitalWrite(rightForward, HIGH);
    digitalWrite(rightBackward, LOW);

  }
  else if (left_motor_speed < 0 && right_motor_speed >= 0)
  {

    analogWrite(pwm_left, abs(left_motor_speed));  //Left Motor Speed
    analogWrite(pwm_right, right_motor_speed); //Right Motor Speed
    //gauche
    digitalWrite(leftForward, LOW);
    digitalWrite(leftBackward, HIGH);
    digitalWrite(rightForward, HIGH);
    digitalWrite(rightBackward, LOW);
  }
  else if (left_motor_speed >= 0 && right_motor_speed < 0)
  {
    analogWrite(pwm_left, left_motor_speed);  //Left Motor Speed
    analogWrite(pwm_right, abs(right_motor_speed)); //Right Motor Speed
    //droite
    digitalWrite(leftForward, HIGH);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, HIGH);
  }
  else if (left_motor_speed < 0 && right_motor_speed < 0)
  {
    analogWrite(pwm_left, abs(left_motor_speed));  //Left Motor Speed
    analogWrite(pwm_right, abs(right_motor_speed)); //Right Motor Speed
    //back error !!!!
     digitalWrite(leftForward, LOW);
    digitalWrite(leftBackward, HIGH);
    digitalWrite(rightForward, LOW);
    digitalWrite(rightBackward, HIGH);

  }




  //analogWrite(pwm_left, left_motor_speed);  //Left Motor Speed
  //analogWrite(pwm_right, right_motor_speed); //Right Motor Speed
  //following lines of code are to make the bot move forward
  /*The pin numbers and high, low values might be different
    depending on your connections */


}




