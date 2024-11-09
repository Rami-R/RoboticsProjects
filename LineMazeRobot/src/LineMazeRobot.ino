// Define constants
const int threshold = 100; // Threshold value for IR sensors
const int threshold2 = 9;  // Threshold value for ultrasonic sensor

// Ultrasonic sensor
int pinTrig = 4;
int pinEcho = 3;
long temps;
int distance;

// Motor A connections
#define enA 10
#define in1 A0
#define in2 A1

// Motor B connections
#define enB 11
#define in3 A2
#define in4 A3

// IR Sensor Pins
#define IR1  A5
#define IR2  2
#define IR3  A4

// PID variables
double Setpoint = 0;  // Desired setpoint
double Input = 0;     // Current sensor value
double Output = 0;    // PID output

// PID tuning parameters
double Kp = 1.0;   // Proportional gain
double Ki = 0.0;   // Integral gain
double Kd = 0.0;   // Derivative gain

// Create PID object
#include <PID_v1.h>
PID pid(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

// Function Prototypes
void Forward();
void Left();
void Right();
void Stop();
void U_Turn();

// Setup function
void setup() {
  // Set motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Initial motor state: OFF
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  // Start the Serial Communication
  Serial.begin(9600);

  // Set all the IR Sensor Pins as inputs
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);

  // Set ultrasonic sensor pins
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  digitalWrite(pinTrig, LOW);

  // Set PID parameters
  pid.SetMode(AUTOMATIC);  // Enable PID control
  pid.SetSampleTime(10);    // Set sample time to 10ms
}

// Loop function
void loop() {
  // Measure distance using ultrasonic sensor
  digitalWrite(pinTrig, HIGH);        
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  temps = pulseIn(pinEcho, HIGH);    
  temps = temps / 2;
  distance = (temps * 340) / 10000.0; // Convert to distance in cm

  // Read IR sensor values
  int value_IR1 = analogRead(IR1);
  int value_IR2 = digitalRead(IR2);
  int value_IR3 = analogRead(IR3);
  value_IR1 = (value_IR1 > threshold) ? 1 : 0; // Convert to digital value
  value_IR3 = (value_IR3 > threshold) ? 1 : 0; // Convert to digital value
  distance = (distance > threshold2) ? 0 : 1; // Convert to digital value

  // Swap values for correct IR sensor orientation
  int a = value_IR1;
  value_IR1 = value_IR3;
  value_IR3 = a;  

  // Debugging: Output sensor values to Serial Monitor
  Serial.print(value_IR1);
  Serial.print(value_IR2);
  Serial.println(value_IR3);
  Serial.print("Distance: ");
  Serial.print(distance);

  // Line following logic with PID control
  if (value_IR1 == LOW && value_IR2 == HIGH && value_IR3 == LOW && distance == LOW) { // Straight path
    Forward();
  }

  if (value_IR1 == HIGH) { // Left turn
    Left();
  }

  if (value_IR1 == LOW && value_IR2 == LOW && value_IR3 == HIGH && distance == LOW) { // Right turn
    Right();
  }

  if (value_IR1 == LOW && value_IR2 == HIGH && distance == LOW) { // Right intersection
    Forward(); // Move forward if straight path is possible
  }

  if (distance == HIGH) { // Dead End
    U_Turn();
    delay(100); // No other direction is possible
  }
}

// Functions for movement control

void Forward() {
  analogWrite(enA, 255); // Max speed for Motor A
  analogWrite(enB, 255); // Max speed for Motor B
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void Right() {
  analogWrite(enA, 255); // Max speed for Motor A
  analogWrite(enB, 255); // Max speed for Motor B
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void Left() {
  analogWrite(enA, 255); // Max speed for Motor A
  analogWrite(enB, 255); // Max speed for Motor B
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void Stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void U_Turn() {
  analogWrite(enA, 255); // Max speed for Motor A
  analogWrite(enB, 255); // Max speed for Motor B
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
