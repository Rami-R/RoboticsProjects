#include <dht.h>
#include <NewPing.h>

dht DHT;
int Sensor = 7;
int Temp;
int Humidity;

// MQ9 Gas Sensor pin
const int MQ9_PIN = A0;

// Ultrasonic sensor pins
#define TRIG_PIN 10
#define ECHO_PIN 11
NewPing sonar(TRIG_PIN, ECHO_PIN, 200); // Max distance in cm

// Actuators
const int FAN_PIN = 5;
const int LED_RED = 6;
const int LED_GREEN = 8;

//////////////////////////////////////////////
// RemoteXY include library //
//////////////////////////////////////////////

#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>

#include <RemoteXY.h>

// RemoteXY connection settings
#define REMOTEXY_SERIAL_RX 2
#define REMOTEXY_SERIAL_TX 3
#define REMOTEXY_SERIAL_SPEED 9600

// RemoteXY configurate
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] = // Updated interface (115 bytes)
{ 255,0,0,36,0,96,0,16,31,0,67,4,58,25,20,5,2,24,11,67,4,58,
41,20,5,2,24,11,129,0,16,24,18,6,1,84,101,109,112,40,67,41,32,58,
0,129,0,12,41,18,6,6,72,117,109,105,100,105,116,195,169,40,37,41,58,
0,129,0,12,58,15,6,6,68,105,115,116,97,110,99,101,0,5,64,18,70,
8,8,2,129,0,15,80,15,6,6,71,97,115,32,76,101,118,101,108,0 };

struct {
  // Output variables
  char text_Temp[11];
  char text_Humidity[11];
  char text_Distance[11];
  char text_Gas[11];

  // Input variables
  uint8_t led_red;      // Switch for Red LED
  uint8_t led_green;    // Switch for Green LED
  uint8_t fan_control;  // Switch for Fan

  // Other variables
  uint8_t connect_flag; // =1 if wire connected, else =0
} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
// END RemoteXY include //
/////////////////////////////////////////////

void setup() {
  RemoteXY_Init();

  // Setup pins
  pinMode(FAN_PIN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(MQ9_PIN, INPUT);
}

void loop() {
  RemoteXY_Handler();

  // Read temperature and humidity
  int chk = DHT.read11(Sensor);
  Temp = DHT.temperature;
  Humidity = DHT.humidity;

  // Convert to strings for RemoteXY
  dtostrf(Temp, 0, 1, RemoteXY.text_Temp);
  dtostrf(Humidity, 0, 1, RemoteXY.text_Humidity);

  // Read ultrasonic distance
  unsigned int distance = sonar.ping_cm();
  dtostrf(distance, 0, 1, RemoteXY.text_Distance);

  // Read gas level
  int gasValue = analogRead(MQ9_PIN);
  dtostrf(gasValue, 0, 0, RemoteXY.text_Gas);

  // Control LEDs based on RemoteXY switches
  digitalWrite(LED_RED, RemoteXY.led_red);
  digitalWrite(LED_GREEN, RemoteXY.led_green);

  // Control fan based on RemoteXY switch
  digitalWrite(FAN_PIN, RemoteXY.fan_control);

  delay(1500);
}
