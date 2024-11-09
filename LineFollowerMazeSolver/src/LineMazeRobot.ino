// Threshold values
const int threshold = 100;  // IR sensor threshold for detecting line
const int threshold2 = 9;   // Ultrasonic sensor threshold for obstacle detection

// Ultrasonic sensor pins
int pinTrig = 4;  // Trigger pin
int pinEcho = 3;  // Echo pin
long timeElapsed;
int distance;

// Motor connections
#define enA 10  // Motor A speed control
#define in1 A0  // Motor A direction control 1
#define in2 A1  // Motor A direction control 2
#define enB 11  // Motor B speed control
#define in3 A2  // Motor B direction control 1
#define in4 A3  // Motor B direction control 2

// IR sensor pins
#define IR1 A5  // Left sensor
#define IR2 2   // Center sensor
#define IR3 A4  // Right sensor

// Speed constant for motors
const int MAX_SPEED = 255;  // Max motor speed (range 0-255)

// Function Prototypes
void Forward();
void Left();
void Right();
void Stop();
void U_Turn();

void setup() {
  // Set up motor control pins as outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Initial state: motors off
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  // Serial communication for debugging
  Serial.begin(9600);

  // IR sensor pins set as inputs
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);

  // Ultrasonic sensor pins setup
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);

  digitalWrite(pinTrig, LOW);  // Initial state for trigger
}

void loop() {
  // Measure distance with ultrasonic sensor
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  
  // Calculate distance in cm
  timeElapsed = pulseIn(pinEcho, HIGH) / 2;
  distance = (timeElapsed * 340.0) / 10000.0;

  // Read IR sensor values and apply thresholds
  int value_IR1 = (analogRead(IR1) > threshold) ? HIGH : LOW;
  int value_IR2 = digitalRead(IR2);
  int value_IR3 = (analogRead(IR3) > threshold) ? HIGH : LOW;
  int isObstacle = (distance > threshold2) ? LOW : HIGH;

  // Debugging output
  Serial.print("IR1: "); Serial.print(value_IR1);
  Serial.print(" IR2: "); Serial.print(value_IR2);
  Serial.print(" IR3: "); Serial.print(value_IR3);
  Serial.print(" Distance: "); Serial.println(distance);

  // Decision-making for maze navigation
  if (value_IR1 == LOW && value_IR2 == HIGH && value_IR3 == LOW && isObstacle == LOW) {
    Forward();  // Move forward if on track and no obstacle
  } else if (value_IR1 == HIGH) {
    Left();     // Left turn if left sensor detects line
  } else if (value_IR1 == LOW && value_IR2 == LOW && value_IR3 == HIGH && isObstacle == LOW) {
    Right();    // Right turn if right sensor detects line
  } else if (value_IR1 == LOW && value_IR2 == HIGH && isObstacle == LOW) {
    Forward();  // Continue forward if at a T-intersection and no obstacle
  } else if (isObstacle == HIGH) {
    U_Turn();   // Perform a U-turn if obstacle detected
    delay(100);
  }
}

// Function to move forward
void Forward() {
  analogWrite(enA, MAX_SPEED);  // Set motor A speed
  analogWrite(enB, MAX_SPEED);  // Set motor B speed
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

// Function to turn left
void Left() {
  analogWrite(enA, MAX_SPEED);
  analogWrite(enB, MAX_SPEED);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

// Function to turn right
void Right() {
  analogWrite(enA, MAX_SPEED);
  analogWrite(enB, MAX_SPEED);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

// Function to stop
void Stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

// Function to perform a U-turn
void U_Turn() {
  analogWrite(enA, MAX_SPEED);
  analogWrite(enB, MAX_SPEED);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  Stop();
}
