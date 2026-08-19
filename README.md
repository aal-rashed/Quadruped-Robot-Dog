# Quadruped Robot Dog (Arduino + Servo + Ultrasonic)

This project is a simple quadruped robot built using an Arduino, four servo motors, and an ultrasonic sensor for obstacle detection.  
The robot uses a basic walking gait and calibrated servo angles to ensure stable movement.

---

## 🐾 Features
- Four‑leg walking gait (trot pattern)
- Ultrasonic obstacle detection
- Custom servo angle calibration
- Adjustable offsets for each leg
- Fully Arduino‑based

---

## ⚙️ Hardware Used
- Arduino Uno
- 4x SG90 or MG90S servo motors
- HC‑SR04 ultrasonic sensor
- External 5V power supply for servos
- Jumper wires
- Custom 3D‑printed or DIY robot frame

---

## 🚨 Important: Servo Initial Position Problem
When building a quadruped robot, **each servo must start at the correct neutral angle**.  
If the servo horns are mounted differently, the robot will:

- Lay flat on the ground  
- Move only two legs  
- Walk incorrectly  
- Rotate legs forward/backward instead of down  

This happened in this project.

### ❗ The Problem
Some servos were mounted in opposite directions, so:

- Front‑Left and Back‑Right legs faced **down at 0°**
- Front‑Right and Back‑Left legs faced **down at 180°**

This caused the robot to behave incorrectly until calibration was done.

---

## ✅ Solution: Test Each Leg Angle Individually
To fix the issue, each leg was tested **one by one** using a simple calibration sketch:

```cpp
servo.write(0);
servo.write(90);
servo.write(180);
