# Smart IoT-Based Home Automation System with Environmental Monitoring and Actuator Control

This project demonstrates an intelligent home automation system built using embedded systems and IoT technologies. It integrates multiple sensors, actuators, and a smartphone application for real-time monitoring and control of domestic tasks. 

The system boosts home efficiency by enabling users to monitor environmental conditions and control devices such as fans and LEDs from a smartphone app. It employs the RemoteXY library to create a user-friendly graphical interface.

---

## **Features**

### 1. **Environmental Monitoring**
- **Temperature & Humidity**: Real-time readings from a DHT11 sensor are displayed in the app.
- **Gas Detection**: Monitors air quality using an MQ9 gas sensor and displays the gas level in the app.
- **Distance Measurement**: Uses an ultrasonic sensor to measure distances and display them in the app.

### 2. **Actuator Control**
- **LEDs**: Two LEDs (Red and Green) can be turned on/off via the smartphone app.
- **Fan**: A fan can be controlled from the app to improve home ventilation.

### 3. **IoT Integration**
- The system uses the **RemoteXY** platform for wireless communication between the microcontroller and a smartphone. This allows for a seamless user experience.

---

## **Components Used**

### **1. Microcontroller**
- Arduino-compatible board.

### **2. Sensors**
- **DHT11 Sensor**: Measures temperature and humidity.
- **MQ9 Gas Sensor**: Monitors gas concentration in the environment.
- **Ultrasonic Sensor (HC-SR04)**: Measures distance.

### **3. Actuators**
- **Fan**: Operated via a relay or direct connection.
- **LEDs**: Two LEDs for visual indicators.

### **4. Communication**
- **SoftwareSerial**: Configures serial communication for data transfer.
- **RemoteXY**: Manages the smartphone interface.

---

## **Circuit Diagram**

The circuit consists of:
- The **DHT11 sensor** connected to digital pin 7.
- The **MQ9 gas sensor** connected to analog pin A0.
- The **Ultrasonic sensor** (HC-SR04) with:
  - Trigger pin connected to pin 10.
  - Echo pin connected to pin 11.
- Actuators:
  - **Fan** connected to pin 5.
  - **Red LED** connected to pin 6.
  - **Green LED** connected to pin 8.
- **RemoteXY** communication:
  - RX pin connected to pin 2.
  - TX pin connected to pin 3.

---

## **Installation and Setup**

### 1. **Hardware Setup**
1. Connect the components as per the circuit diagram.
2. Ensure all connections are secure and powered correctly.

### 2. **Software Setup**
1. Install the Arduino IDE from [here](https://www.arduino.cc/en/software).
2. Install the following required libraries in the Arduino IDE:
   - **DHT Sensor Library**: For temperature and humidity.
   - **NewPing Library**: For ultrasonic distance measurement.
   - **RemoteXY Library**: For the app interface.
   - To install these libraries:
     - Go to **Sketch > Include Library > Manage Libraries**.
     - Search for each library by name and click **Install**.

3. Open the `smart_home_automation.ino` file in the Arduino IDE.

4. Upload the code to your Arduino board.

### 3. **RemoteXY Configuration**
1. Download the RemoteXY app:
   - [Google Play Store](https://play.google.com/) or
   - [Apple App Store](https://www.apple.com/app-store/).
2. Follow the app setup instructions in the RemoteXY library documentation to connect your smartphone to the system.

---

## **How It Works**

1. **Environmental Monitoring**:
   - The system continuously monitors temperature, humidity, gas levels, and distance.
   - Values are updated in the smartphone app every 1.5 seconds.

2. **Actuator Control**:
   - Use the app to turn on/off LEDs and control the fan in real-time.

3. **User Interface**:
   - A simple and intuitive app displays sensor data and provides actuator controls.

---

## **Future Enhancements**
- Add additional sensors like motion detectors or light sensors for advanced automation.
- Integrate with a cloud-based IoT platform for remote access and data logging.
- Enable voice control using platforms like Google Assistant or Alexa.

---

## **Contributors**
- **Rami BOUMEKHITA** - Project Lead

## **Acknowledgments**
- Thanks to the developers of the RemoteXY platform for their intuitive IoT interface.
- Inspired by similar IoT projects on [Hackster.io](https://www.hackster.io/).
