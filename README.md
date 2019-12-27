# ROBOCON-19

### ***Robocon is an **International level robotics competition** hosted by ABU. Robocon 19 was hosted by Mongolia with the challenge to develop 2 autonomous robots amongst which 1 was a **Quadruped Robot** ***.

We designed an autonomous quadruped bot inspired from the anatomy of a horse.
![*Autonomous Quadruped bot*](https://github.com/ash2703/Robocon-19/raw/master/images/best-bot.PNG)


4 legs of the bot consists of 8 revolute joints i.e. each leg consists of 2 revolute joints. Revolute action is performed with the help of digital servos capable of rotating 0-120 degrees precisely.

All the 4 legs are attached symmetrically to a solid frame such that the CG *(centre of gravity)* of the system lies in the centre of the frame and also the CG lies inside the triangle formed by 3 joints when a leg is suspended for the bot to be dynamically stable.

**Trot Gait** The bot is made dynamically stable using quadruped gait for higher speed and dynamic stability. Trot Gait is used similar to the motion of a horse. Two diagonal legs swings forward while other two support the body and move backward. The speed of the bot is decided by the frequency of raising and pushing the legs of the bots. More the speed, more is the stability.

Rotary actuators 8 digital servos *(**CYS8218->36kgcm 0.18sec/60 degree,4us dead-band**)*, each are used to provide revolute action at the joints of legs. Digital servos provide better resolution at higher precision angles, faster response and constant torque. All the servos are connected to a single micro-controller (AtMega2560) which controls the servos simultaneously using various algorithms.

## DESIGN DETAILS
#### Design
Major components of MR2 consists of : 
 *   1. Aluminium profile frame 
 *   2. Acrylic sheet 
  *  3. Servo motors 
   * 4. Arduino Mega2560 microcontroller 
   * 5. Raspberry pi (3B+) 
   * 6. R-pi camera 
   *7. Servo motor clamps 
    *8. MPU6050 (IMU) 
   * 9. Composite material links 
   * 10. Sharp IR proximity sensor 
   * 11. Kill switch 
   
#### Gerege receiving  and raising mechanism 
##### Gerege Resting Mechanism (MR2) 
Gerege slides from the slider on MR1 and rests on same slider mechanism mounted on top of MR2. It consist of two links driven by servo motors. Initially the position of links is aligned to receive gerege from MR1. Once mechanism detects the presence of gerege on slider, the two slider links rotates, nearly flattens and rests on MR2 with the help of servo motor till it reaches mountain. When the bot climbs the mountain, the servo motor rotates the slider that holds the gerege and holds it vertically up by 1000mm from the ground level.
 <br/>   
![Gerege Receiving Mechanism](https://github.com/paresh1997/ROBOCON_2019/blob/master/ROBOCON_2019/images/gerege_receiving_mech.PNG)     ![Gerege Raising Mechanism](https://github.com/paresh1997/ROBOCON_2019/blob/master/ROBOCON_2019/images/gerege_raising_mech.PNG)
<br/>
MR2 is designed as an autonomous quadruped bot inspired from the anatomy of a horse. 

4 legs of MR2 consists of 8 revolute joints i.e. each leg consists of 2 revolute joints. Revolute action is performed with the help of digital servos capable of rotating (0-180 deg.) precisely. 

All the 4 legs are attached symmetrically to a solid frame such that the CG (centre of gravity) of the system lies in the centre of the frame and also the CG lies inside the triangle formed by 3 joints when a leg is suspended for the bot to be dynamically stable. 
<br/>
![MR2 Top-view](https://github.com/paresh1997/ROBOCON_2019/blob/master/ROBOCON_2019/images/top-view.PNG)
![Leg and their links along with servos](https://github.com/paresh1997/ROBOCON_2019/blob/master/ROBOCON_2019/images/leg_naming.PNG)
<br/>
#### Balancing of the bot
The bot is equipped with an ***inertial measurement unit (MPU-6050)*** which provides yaw, pitch and roll data processed using a digital motion processor which is integrated inside the (MPU-6050), it integrates the accelerometer, magnetometer and gyroscope readings to provide precise angle in all the 3 axis i.e. YPR (Yaw-Pitch-Roll). 

The data read from the MPU is then used to decide the direction of the robot w.r.t reference plane. The inclination of the bot is continuously monitored in roll and pitch axis. This data is then fed into the PID balancing algorithm which decides the amount of rotation needed to be given to each servo to regain stability of the bot. The algorithm returns the amount of height each leg must change in-order to regain its set stage. We take the help of inverse kinematics to calculate the angle each servo must rotate to achieve that particular height.

#### Trot Gait
The bot is made dynamically stable using quadruped gait for higher speed and dynamic stability. Trot Gait is used similar to the motion of a horse. Two diagonal legs swings forward while other two support the body and move backward. The speed of the bot is decided by the frequency of raising and pushing the legs of the bots. More the speed, more is the stability. 

#### Rotary Actuators
**8** digital servos (CYS8218->36kgcm 0.18sec/60 degree,4us dead-band) 36 kg-cm torque,  each are used to provide revolute action at the joints of legs. Digital servos provide better resolution at higher precision angles, faster response and constant torque.***All the servos are connected to a single micro-controller (AtMega2560) which controls the servos simultaneously using various algorithms***

#### Detection (Rope, sand dune, turning points and checkpoint colors) 
For the detection of turns, ropes and sand dunes, we are using a camera along with a raspberry pi for performing digital image processing on the snaps taken by the camera. The camera module starts taking images of the front facing path after certain time interval. Every image will be processed and checked for edges. If the edge is detected, the algorithm will decide if the edges is to be considered a rope, turn or sand dune based on the color. Raspberry pi will trigger a pulse on one of GPIO pins which is connected to micro-controller Arduino Mega2560. On receiving this pulse, microcontroller will decide on what has to be done next by the bot. 

![Details of MR2](https://github.com/paresh1997/ROBOCON_2019/blob/master/ROBOCON_2019/images/naming_pic.PNG)

The bot is initially at the reference state. When the bot starts moving towards the destination the state is changed. The error is calculated taking into consideration the reference state and current state. This error is calculated in reference with the values of YPR (Yaw-Pitch-Roll) provided by MPU6050. This error values are used by to calculate appropriate angle by which each of servo should rotate to balance itself and move forward. This is achieved with the help of inverse kinematics. The error value is fed into inverse kinematics equations applied on the links of each leg of bot. These equations returns the values of position (precise angle) by which each of the servo rotates in order to balance and traverse in required direction. MPU6050 along with inverse kinematics provides intelligent solution for traversal and balancing of MR2.

###### *Inverse Kinematics equations for calculating position angles of servos*
Solving for theta_1 and theta_2 :<br/>
**Theta_1 = atan(y/x) – atan(a2*sin(theta_2) / a1 + a2*cos(theta_2));**<br/>
**Theta_2 = pi – acos((sqrt(x^2 + y^2) – a1^2 – a2^2) / 2*ai*a2);** <br/>
Where, <br/>
   Theta_1 = required angle of link 1 <br/>
   Theta_2 = required angle of link 2 <br/>

![Calculation flowchart](https://github.com/paresh1997/ROBOCON_2019/blob/master/ROBOCON_2019/images/Capture.PNG)

The autonomous robot is designed with research based approach which includes latest technologies with technology stack of OpenCV (Python), Atmel studio (Embedded C), Microprocessor (Raspberry-pi), Simulators(SolidWorks, Catia, Proteus, Eagle, V-Rep), Micro-Controller (Arduino), Inverse Kinematics etc. <br/>            
***All the mentioned algorithms and working mechanisms combined together provides best possible solution with provided hardware for the problem statement proposed by ABUROBOCON 2019.***
