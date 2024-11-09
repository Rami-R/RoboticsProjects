# Arduino Maze Solving Robot

## Description

This project involves an Arduino-based robot that uses infrared (IR) sensors and an ultrasonic sensor to navigate a maze. The robot can detect walls and obstacles, follow paths, and avoid dead ends using simple movement logic. Additionally, a **PID (Proportional-Integral-Derivative)** control algorithm is implemented, although it is not fully activated in the current version. The robot uses three IR sensors to detect the path and an ultrasonic sensor for obstacle detection.

### Key Features:
- **Line Following**: The robot follows lines based on inputs from three IR sensors.
- **Maze Solving**: The robot can navigate a maze by detecting walls and obstacles using an ultrasonic sensor.
- **PID Control**: A PID controller is included but is not fully integrated into the movement logic. It can be used for more precise movement control.
- **Motor Control**: The robot uses two DC motors to move forward, turn left or right, and perform a U-turn.

## Hardware Required

- **Arduino Board** (Arduino Uno or any compatible board)
- **3 IR Sensors** (for line following)
- **Ultrasonic Sensor** (for obstacle detection)
- **2 DC Motors**
- **Motor Driver (L298N or similar)**
- **Jumper Wires**
- **Breadboard (optional)**

## Circuit Connections

### IR Sensors:
- **IR1**: Connected to analog pin A5
- **IR2**: Connected to digital pin 2
- **IR3**: Connected to analog pin A4

### Ultrasonic Sensor:
- **Trig Pin**: Connected to pin 4
- **Echo Pin**: Connected to pin 3

### Motors:
- **Motor A (Left Motor)**: Connected to pins A0, A1
- **Motor B (Right Motor)**: Connected to pins A2, A3
- **Motor Driver Pins (EN A, EN B)**: Connected to pins 10 and 11 respectively

## Libraries Used

- **PID_v1**: Used for implementing the PID control algorithm. Currently, the PID logic is included but not fully integrated in the movement functions. You can enable and tune the PID controller for better navigation in maze-solving tasks.
  - To install the PID library, go to **Sketch** > **Include Library** > **Manage Libraries**, and search for **PID** by Brett Beauregard.

## How to Use

1. **Upload the Code**: Load the provided Arduino code onto your Arduino board using the Arduino IDE.
2. **Connect the Hardware**: Set up the robot according to the pin connections described above.
3. **Test the Robot**: Place the robot on a maze and turn it on. The robot will start moving based on the input from the IR sensors and the ultrasonic sensor. It will navigate the maze by following the path and avoiding obstacles.

## Code Overview

- **PID Control**: 
  - The PID control algorithm is included but not yet fully integrated. The robot’s current movement logic uses simple IR sensor readings for navigating the maze.
  - The PID controller can be enabled and tuned for more accurate control over the robot’s movements, particularly useful for line following.

- **Movement Functions**:
  - **Forward()**: Moves the robot forward at full speed.
  - **Left()**: Turns the robot to the left.
  - **Right()**: Turns the robot to the right.
  - **Stop()**: Stops the robot.
  - **U_Turn()**: Performs a 180-degree turn when a dead-end is detected.

- **Sensors**:
  - The IR sensors are used to detect the path and edges of the maze. The robot changes direction based on the readings from these sensors.
  - The ultrasonic sensor is used to detect obstacles ahead of the robot and avoid them by performing a U-turn if a dead end is detected.

## Code Logic

1. **Line Following**:
   - The robot uses three IR sensors to follow a line. The robot moves forward if the middle sensor detects the line and adjusts its direction if it detects a turn or a dead end.
   
2. **Maze Solving**:
   - The robot uses the ultrasonic sensor to detect obstacles ahead. If the distance is too high (indicating no obstacle), the robot moves forward. If an obstacle is detected, the robot performs a U-turn to find another path.

3. **PID Control** (optional):
   - The PID controller is set up to adjust the robot’s movement based on sensor feedback. This can help achieve smoother turns and more precise navigation once it's integrated.

## Potential Improvements

- **Full PID Integration**: The PID controller can be fully integrated to control the robot’s motors more precisely. Fine-tuning the PID parameters (Kp, Ki, Kd) can improve performance in following curves and lines.
- **Path Optimization**: Implementing algorithms for path optimization and memory storage could allow the robot to solve the maze more efficiently.
- **Additional Sensors**: You could add more sensors (e.g., encoders) to improve the robot's navigation and obstacle detection capabilities.

## Troubleshooting

- **Robot doesn’t follow the line properly**: Adjust the IR sensor threshold values in the code to match your maze's characteristics.
- **Robot gets stuck in a dead end**: Ensure the ultrasonic sensor is positioned properly and is detecting obstacles correctly.
- **PID control doesn’t seem to work**: The PID is included but not fully functional yet. You can tweak the PID parameters (`Kp`, `Ki`, `Kd`) or integrate it into the movement logic for smoother control.

### Contact

For questions or contributions, please contact me through GitHub or open an issue in the repository.

![Robot Image](LineMazeRobot/robotimage.png)

