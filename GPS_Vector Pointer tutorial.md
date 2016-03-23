#GPS Differential Vector Pointer Tutorial

##Introduction

GPS technology is a very useful and elegant technology, the satellites used in this network do most of the work so that the GPS receiver can be made small and simple. As GPS technology becomes more and more accurate, applications in many areas have really taken off. Some of these include driverless cars, mission planning for UAVs, assisted landing of commercial aircraft and many more. GPS systems vary in cost depending accuracy and what other functions they provide so the right receiver needs to be chosen for the desired application. In this project I am demonstrating that an expensive receiver is not needed to do cool things with this technology. 
This project began as a proof of concept for the ANACONDA 2014/2015 Aerospace Senior project whose mission was to,

>“Design and construct an autonomous tracking and communication support system for an antenna to be used to track unmanned aircraft during flight.”

If you want to check this project out and others follow this link to the CU senior projects page and go to the 2015 projects page. 

[CU Aerospace Senior Projects](http://www.colorado.edu/aerospace/current-students/undergraduates/senior-design-projects?qt-qt_senior_design_2014_15=1#qt-qt_senior_design_2014_15)

##This Project
The underlying principle here is that if two GPS locations are provided by two different recivers, a position vector can be calculated between them. This can be used to aim a directional antenna (or in the case of this project a laser) from one object (the base station) to the other object (Target) at any distance which is only limited to your ability to provide the base station with the targets GPS location. This system consists of two seperate assemblies. The targets only purpose is to recives its GPS location, parse the data, and send that back to the base station. The base station then recives the targets GPS location and compares it to its own GPS location to calculate the positional vector. The base station also includes a 180 degree servo and a laser so the direction can be visualized.

->_(1)System Diagram_<-

The theory behind this is shown in the figure below in that knowing the horizontal and the vertical difference between points you can use the inverse tangent function to give you the pointing angle needed to control the mechanism. 

->(2)Theory Diagramm<-

##Required Materials	
Now that I have you itching to try this project yourself I will walk you through the steps to create this on your own and see what other exciting things you can do with the hardware. This projects requires a decent amount of materials but to put all of it together is relatively simple. 

### Electrical Supplies
Here is a list of all the sparkfun materials you will need for this project. 

<script src="https://www.sparkfun.com/wish_lists/123390.js"></script>

### Mechanical Supplies 
You will need some hardware to put the electronics parts together into the final system. To get everything together you will need.

* Access to a 3D printer
* Tripod with universal camera mount platform
* Magnetic compass
* Mounting Hardware
  * 4 X 8-32 Machine screws
  * 3x 1/2” spacers with #5 sized through hole
  * 3x 2-56 ½” Machine screws
  * 3x 2-56 ¾” Machine screws
  * 6x 2-56 Hex Nuts
  * 6x 1-72 ½” Flathead screws
  * 6x 1-72 Hex Nuts
  * 2 x 0-80 Flathead screws
  * 1 5/16th O-ring with 1/16th wall thickness or less


### 3D Models
For this project the cases and laser mount were all created on a student edition of solidworks to be printed using My personal 3d printer. My printer is  an [XYZ da Vinci 1.0 AiO](http://us.xyzprinting.com/us_en/Product/da-Vinci-1.0-AiO) and is very useful for making small parts. There are 4 pieces that need to be printed for this project and their files are included below saved as .STL so they can be easily transfered to the 3D printer program. 

Target  

->_(3)Target_<- 

Base bottom  

->_(4)Base_Bottom_<-  

Base top  

->_(5)Base_Top_<-  

Laser Mount  

->_(6)Base_LaserMount_<- 

##Suggested reading
If anything I have discussed so far doesn’t quite click or you get confused later here are some relevant tutorials to get you up to speed and give you everything you need to know to complete this project.  

[GPS basics](https://learn.sparkfun.com/tutorials/gps-basics)  
[Serial communication](https://learn.sparkfun.com/tutorials/serial-communication)  
[Servo Basics](https://www.sparkfun.com/tutorials/283)

###Electronics assembly
_Note: You will have to take off the Xbee sheild to mount on the final system_  
The electronics in this project all plug directly into pins on the Xbee shield (with the exceptiion of the laser diode) which makes this part pretty strait forward. I have designed this mechanism so that the connections are not permanent and can be taken apart but you can solder the connections instead if you you would like.

* First, you will need to configure both Xbees so that they are set up on the right channel.This is described in detail [HERE](https://learn.sparkfun.com/tutorials/exploring-xbees-and-xctu-retired)
* Once everything is configured you will need to create two identical assemblies of the redboard with the Xbee sheilds attached. Stackable headers will need to be soldered onto the Xbee sheild so that it can be mounted ontop of the Redboard.A detailed walkthrough of this process is described [HERE](https://learn.sparkfun.com/tutorials/xbee-shield-hookup-guide)

->_(7)XbeeshieldAssym_<-

* Next you will need to prepare the wires of the two GPS recivers and the servo so they can easily be plugged into the sheild. I cut off the existing connectors and soldered them to the wires after the connector is cut off [these](https://www.sparkfun.com/products/13685). The wires for the target GPS reciver can be made shorter so you dont have excess wire but this is up to you just make sure you leave enough length to reach the pins.

->_(8)Preppedcables_<-

* The last step will be to connect the Laser diode. To do this you will first need to solder stranded wire to the two holes located on the electronics board. Ensure that they are attached to the correct pads shown here and you are careful when soldering these because too much heat can fry the lasers electronics. 

->_(9)Laserwireconnection_<-

*Because the laser will be moving these wires cannot just be plugged into the XBee sheild we will solder the ground wire to the availible Grounded pad and the supply inline with a 10 &ohm resistor. and this will be done on the Xbee sheild used on the base(do i need this? will I be able to regulate using PMW?)

->_picture of this connection still needed_<-

Here is how all of these should be connected onto the Xbee Sheild

->_(11)CircuitDiagrams_<-


###System assembly 

####Base Station

#####Bottom
* Place redboard into base using  32-56 ¾” Machine screws with the 3 spacers inbetween so it is elevated off the base of the case. This is to ensure that the mounting hole is availible which depending on your tripod mounting situation you might need. 

->_(12)spacers_<-

* connect the 9V battery mount onto holes located on the wall of case just as you did for the target assembly. 

->_(13)Mountedparts_<-

* Depending on your tripod this step may be differnt but mine has a piece with the mounting screw that can be threaded into the availible mounting hole and works quite nicely.

->_(14)tripodmount_<-

#####Top
* Remove Circular disk from servo by removing attachment screw
* Place servo in the availible cavity with the output gear closer to the GPS cavity. Once in screw 8-32 into 4 counting holes of servo which constrains servo in the correct location. You shouldnt need nuts for the other side since the holes are close fit and the ABS used is soft and allows you to easily screw to a tight fit.

->_(15)Servomount_<-
* Attach circular servo disk to laser mount concetricaly with the hole on the bottom on laser mount. mount this by placing two 0-80 Flathead screws through the countersunk holes within the laser cavity. You may need to open up the holes on the circular wheel since they will be used as pins and you will not be able to screw them in. These are to ensure that the two parts are connected in the right orientation and if loose you may need to use an adhesive to attach these.

->_(16)Lasermount_<-

* Next you will attach this assembly to the servo. Slide the circular disk back onto the servo then use the screw you took out to screw it back on using the availible hole in the laser mount to access it with a screw driver. You will probebly need to ensure that 90 degrees commanded to the servo has the assembly pointed directly perpendicular to the arrow. A simple sketch can help you out with this because any error will throw off the whole system.

->_(17)mounttoservo_<-

* Push the laser through the hole in the top platform and into laser mount. you will have to do this first since the other side is already soldered onto Xbee shield
* Place O ring over exposed part of the laser to hold it in place. This can be a little finicky so you can use glue from a glue gun to hold it in place as an alternative.

->_(18)PlaceLaser_<-

* Place GPS receiver in indent made in top just like you did on the target assembly with wires going through the available hole

->_(19)AttachGPS_<-

* Put Xbee sheild onto redboard and Attach wires as displayed in the cicuit diagram and you are good to go.

->_(20)Fullbase_<-

####Target
* Place redBoard without xbee shield in target case so that the USB port is facing the opening and place 3 2-56 ¾” Machine screws into any three available holes. Use the corresponding nuts to secure them in place from the back.
* Attach the 9V Battery holder using 3 1-72 ½” Flathead screws and secure them using the corresponding nuts on the back.

->_(21)Mounted parts_<-

* There is a cavity made for the GPS receiver sunk into the base, use a glue gun or other advesion method to hold it in place
* Once everything is attached place the Xbee sheild back on the redboard and connect everything as discussed above.  

->_(22)Fulltarget_<-

## Code
Here is the basic code to get this system functioning. You will need to upload the files to their respective systems. There is alot of room for you to play around with these to try an improve the speed or accuracy of the system so see what you can do. You will also need to include these libraries which depending on what version of Arduino you have installed they may be already included in the standard library.
* Software serial.h
* tinyGPS.h
* Servo.h

_Target Code_

_Base code_

##Operation
To make sure that the system aligns with the earth reference ensure the system is in the the correct orientationm by using a compass to lining up the arrow with North on the Base Station top (This could be done electronically using a magnetometer). Once powered up , both systems will sit idly as they aquire satellite lock. Once both have made a lock(maybe take up to a minute) the laser will turn on And the servo will point to where it believes the target object is. This will update continuously to point at the most recent location  of the target object. If the angle is substantially off or the servo is maxed out in one direction you might need to make sure the whole system is pointing in the right direction since it is limited in whhich direction it works 

Warning! Laser can be harful to eyes so if you are the one holding the target object it would be a good safety measure to have laser glasses for 532nm wavelength. 

##Going further
I hope you enjoyed this tutorial and if you make any additions to the code or hardware I would love to see what you do. A magnetometer could be added so that it can automatically lock with the earths reference frame. This could also work in 3 dimentions so if a two DOF gimbal is added you can track the object anywhere.
