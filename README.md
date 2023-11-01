# Arduino RC Car

About: Arduino RC Car is a repository used to contain all code files and other resources related to the Arduino RC Car project. Please see this [Video of Car](https://www.reddit.com/r/robotics/comments/16mijlp/rc_car_made_with_arduino_and_fusion360/?rdt=49786) on Reddit.

See document below for:
- Code Guide.
- STL files and wiring (on Thingiverse).
- Additional Information

**Code Guide:**
There are two folders on the repository: Car Reciever and Controller. These Two folders contain the controller sender code and the RC car receiver code. These files can be downloaded and ran.
They are contained within their specific folders because Arduino will not run a file that is not contained on a folder with the same name as file. Open Sender Code and Receiver Code, ignore the "sketch" files.

Sender code overview:
- Establishes radio connection with receiver.
- Takes input from joystick.
- Reduces data size.
- Combines X-axis and Y-axis data onto a single byte.
- Sends data to receiver.

Receiver code overview:
- Establishes radio connection with sender.
- Receives byte input from sender.
- Unpacks data into X-axis and Y-axis.
- Adjusts X-axis for steering and sends to servo motor.
- Adjusts Y-axis for speed and direction control and sends it to LN298 motor driver.

**STL Files and Wiring:**
Please see pictures in [Thingiverse Profile](https://www.thingiverse.com/thing:6188559). These pictures contain wiring and STL files of RC Car, controller has not yet been uploaded.
See other posts on Thingiverse for additional designs such as battery pack. 

**Additional Information**
The Arduino RC Car Project was created in order to gain experience with 3D printing, electronic modules (radio antenna specifically), and control systems. 
The project was started by Juan Santelices on 6/23, finished 7/23, but constantly improved since.
