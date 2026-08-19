# Quadruped Robot Dog (Arduino + Servos + Ultrasonic)

A four‑leg robot built using Arduino, SG90/MG90S servos, and an HC‑SR04 ultrasonic sensor. This README includes wiring instructions, Arduino IDE setup, servo calibration, full build steps, and how to fix the initial servo angle problem.

## Features
- 4‑leg walking gait (trot pattern)
- Ultrasonic obstacle detection
- Custom servo angle calibration
- Adjustable offsets for each leg
- Fully Arduino‑based

## Hardware Required
- Arduino Uno
- 4x SG90 or MG90S servo motors
- HC‑SR04 ultrasonic sensor
- External 5V power supply for servos
- Jumper wires
- Breadboard (optional)
- Robot frame (3D printed or DIY)

## Wiring Guide

### Servo Wiring
Each servo has 3 wires:
- Brown/Black → GND  
- Red → 5V (external power recommended)  
- Orange/Yellow → Arduino signal pin  

Servo signal pins:
- Front Left → D3  
- Front Right → D5  
- Back Left → D6  
- Back Right → D9  

Important:
Do NOT power servos from the Arduino 5V pin.  
Use an external 5V supply and connect Arduino GND + Power Supply GND together.

### Ultrasonic Sensor Wiring (HC‑SR04)
- VCC → 5V  
- GND → GND  
- TRIG → D10  
- ECHO → D11  

## Install Arduino IDE
1. Go to https://www.arduino.cc/en/software and Download Arduino IDE
2. Open Arduino IDE 
3. Tools → Board → Arduino Uno
4. Tools → Port → COMx  

## Uploading the Code
1. Disconnect servo signal wires (D3, D5, D6, D9)  
2. Connect Arduino via USB  
3. Open the .ino file  
4. Click Upload  
5. After upload finishes, reconnect servo wires  
6. Power the robot with external 5V  

If you see “not in sync: resp=0x00”, disconnect servos and upload again.

## Servo Initial Position Problem

Quadruped robots require each servo to start at the correct neutral angle.  
If servo horns are mounted differently, the robot will:
- Lay flat on the ground  
- Move only two legs  
- Walk incorrectly  
- Rotate legs forward/backward instead of down  

This project had this issue.

## Fixing the Initial Position Problem

### Step 1 — Test each leg individually
Upload a simple test:
servo.write(0);
servo.write(90);
servo.write(180);

Observe which angle makes the leg point straight down.

### Step 2 — Record correct angles
After testing each leg separately, the correct neutral angles were:
offsetFL = 0;     // Front Left  
offsetFR = 180;   // Front Right  
offsetBL = 180;   // Back Left  
offsetBR = 0;     // Back Right  

These offsets ensure all legs start in the correct downward position.

### Step 3 — Use offsets in the walking code
The walking code automatically reverses movement depending on whether the servo’s neutral angle is 0° or 180°.

## Walking Logic
The robot uses a simple trot gait:
1. Front‑Left + Back‑Right move together  
2. Front‑Right + Back‑Left move together  

Each step includes:
- Lift  
- Push forward  
- Drop  

Movement direction is automatically reversed depending on the servo’s offset (0° or 180°).

## Calibration Steps
1. Upload a sketch that sets all servos to 90°  
2. Remove each servo horn  
3. Rotate the horn until the leg points straight down  
4. Test angles: 0°, 90°, 180°  
5. Record which angle makes each leg face down  
6. Set offsets accordingly  
7. Update the walking code  
8. Test walking and adjust offsets if needed

## Demo
Add photos or videos of your robot here.

## Contributing
Pull requests are welcome. Improve the gait, add turning, or enhance stability.

## License
MIT License
