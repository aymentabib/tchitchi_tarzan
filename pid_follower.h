#include <arduino.h>
#define on 0
#define off 1
#define trig 12
#define echo 11
#define leftForward  8
#define leftBackward  13
#define rightForward  11
#define rightBackward 12
#define pwm_left 9
#define pwm_right 10//
//
#define S1 7
#define S2 6
#define S3 5
#define S4 4
#define S5 3

//
#define temps 400
//
//#define test // sivousvoulez affichez sur rs232 décommenter test
//


extern float Kp , Ki, Kd;
extern float error, P, I, D, PID_value;
extern float previous_error, previous_I;
extern byte sensor[5] ;
extern int initial_motor_speed;
extern unsigned int pulse_controle;
extern int s;
extern int duration;
extern int distance;





//
void read_sensor_values(void);
void calculate_pid(void);
void motor_control(void);

void eviteur(void);
void avance(unsigned int speed);
void gauche(unsigned int speed);
void droite(unsigned int speed);
void arriere(unsigned int speed);
void stopp(); 
