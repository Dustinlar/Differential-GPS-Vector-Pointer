#GPS Differential Vector Pointer Tutorial

##Introduction

GPS technology is a very useful and elegant technology, the satellites used in this network do most of the work so that the GPS receiver can be made small and simple. As GPS technology becomes more and more accurate, applications in many areas have really taken off. Some of these include driverless cars, mission planning for UAV, and assisted landing of commercial aircraft and many more. GPS systems vary in cost depending on how accurate they are and what other functions they provide so the right receiver needs to be chosen for application. In this project I am demonstrating that you don’t need an expensive receiver to do cool things with this technology. 
This project began as a proof of concept for the ANACONDA 2014/2015 Aerospace Senior project whose mission was to,

>“Design and construct an autonomous tracking and communication support system for an antenna to be used to track unmanned aircraft during flight.”

If you want to check this project out and others follow this link to the CU senior projects page and go to the 2015 projects page. 

[CU Aerospace Senior Projects](http://www.colorado.edu/aerospace/current-students/undergraduates/senior-design-projects?qt-qt_senior_design_2014_15=1#qt-qt_senior_design_2014_15)

##This Project
The underlying principle here is that if two GPS locations are provided by two different recivers a position vector can be calculated between them. This can be used to aim a directional antenna or in the case of this project a laser from one object (the base station) to the other object (Target) at theoretically any distance which is only limited to your ability to provide the base station with the targets GPS location. The theory behind this is very simple and is shown in the figure below. Knowing the horizontal and the vertical difference between points you can use the inverse tangent function to give you the angle that you need. 

->_GPS Vector Diagram_<-



->_Operational video_<-
The video below demonstrates the basic functionality of the system. Showing the laser track the target object as it moves
Video of operation

##Required Materials	<a id="serial-dtr"></a>
Now that I have gotten you excited about the project and have you itching to try it yourself I will walk you through the steps to create this project on your own and see what cool things you can do with it. This projects requires a decent amount of hardware but to put all of it together is relatively simple and minimal soldering 

[Anchor Link](https://learn.sparkfun.com/tutorials/esp8266-thing-hookup-guide/using-the-arduino-addon#serial-dtr)


### Electrical Supplies
These are the parts that you will be able to get off of the Sparkfun website, just take a look at my wishlist to get you going. 
<script src="https://www.sparkfun.com/wish_lists/123390.js"></script>

### Mechanicle Supplies 
Here are a few other materials that you will need to construct this system

* Tripod or other platform
* Mounting Hardware
  * 4x 8-32 B&N
  * 4x 1/2” spacers with #5 sized hole
  * 4x 3-48 B&N
  * 8x 2-56 N
  * 4x 2-56 ½”
  * 4x 2-56 ¾”
  * 6x 1-72 ½”
  * 6x 1-72 N
* Access to a 3D printer

### 3D Models
For this projects the parts were all created on a student edition of solidworks to be printed using My personal 3d printer. My printer is  an [XYZ da Vinci 1.0 AiO](http://us.xyzprinting.com/us_en/Product/da-Vinci-1.0-AiO) and is very useful for making small parts. There are 4 pieces that need to be printed for this project and their files are included below saved as .STL so they can be easily transfered to the 3D printer program. 
Target  
_Target file_  
Base bottom  
_Base bottom file_  
Base top  
_Base top file_  
Laser Mount  
_Laser mount file_  

##Suggested reading
If anything I have discussed so far doesn’t quite click here are some relevant tutorials to get you up to speed and give you everything you need to know to complete this project.  

[GPS basics](https://learn.sparkfun.com/tutorials/gps-basics)  
[XBee sheild hookup guide](https://learn.sparkfun.com/tutorials/xbee-shield-hookup-guide)  
[Serial communication](https://learn.sparkfun.com/tutorials/serial-communication)  
[Configuring XBee's](https://learn.sparkfun.com/tutorials/exploring-xbees-and-xctu-retired)  
[Servo Basics](https://www.sparkfun.com/tutorials/283)

###Electronics assembly
_Note: You will have to take off the Xbee sheild to mount on the final system_  
The electronics in this project all plug directly into pins on the Xbee shield (with the exceptiion of the laser diode) which makes this part pretty strait forward.
* First, you will need to configure both Xbee's so that they are set up on the right channel.This is described in detail [HERE](https://learn.sparkfun.com/tutorials/exploring-xbees-and-xctu-retired).
* Once everything is configured you will need to create two identical assemblies of the redboard with the Xbee sheilds attached. Stackable headers will need to be soldered onto the Xbee sheild.
_Picture of twin assemblies_
* Next you will need to prep the wires of the two GPS recivers and the servo so they can easily be plugged into the sheild 
_picture before and after?_
* The last step will be to connect the Laser diode. To do this you will first need to solder stranded wire to the two holes located on the electronics board.  Be careful when soldering these because too much heat can fry the lasers electronics
_Picture of wires being soldered to eboard_
*Because the laser will be moving these wires cannot just be plugged into the XBee sheild so we will solder the ground to the ground pin to the availible Ground pad and the supply inline with a 10 &ohm resistor.
_picture of this connection_

Here is how all of these should be connected onto the Xbee Sheild(do i need redboard in diagram?)
Connection diagram (fritzing)

####Base station 

###System assembly 
I created Solidworks models to support the electronics parts and to hold the servo and gps recivers in the correct locations. Here are the Solidworks files that are saved in the format used by 3D printing software all you need to do download the files and print them out. If you don’t have a 3d printer there are many locations that will print out these files for you (likely for a price unless you are using a school printer).  
####Target
* Place redBoard without xbee shield in target case so that the USB port is facing the openingand screw 3 or 4 (X) bolts into the available holes. 
* attach 9V Battery holder using (x)bolts
* There is a location for the GPS receiver sunk into the base, use double-sided tape or a glue gun to hold it in place
* On the target modual Plug in GPS receiver to both modules.  

####Base Station
#####Bottom
* Place the two ¼”bolts used to mount on tripod in first since you will not be able to once the redboard is installed. 
* Place redboard into base using (X) bolts and spacers so that it stays above mounting bolts
* Screw battery holder onto holes located on the wall of case  

#####Top
* Remove servo disk from servo
* Screw bolts into 4 counting holes of servo which constrains servo in the correct location
* Attach disk to laser mount lining up the screw hole with bottom on laser mount and putting small screws through both
* Once attached slide screw driver through top hold to screw the screw that holds the servo gear to the servo back in 
* Slide laser into laser mount with wires coming out the back screw 5/8 nut onto front of laser to hold it in place put wires through the available hole(am I going to solder the leads?)
* Place GPS receiver in indent made in top with double-sided tape with wires going through the available hole
* Attach wires as discussed above and place top onto base, should just slide into place

## Code
Here is the basic code to get this system working. you will need to upload the files to their respective systems. There is alot of room for you to play around with these to try an improve the speed or accuracy of the system so see what you can do. You will also need to include these libraries. depending on what version of Arduino you have they may be already included in the standard library.
* Software serial.h
* tinyGPS.h
* Servo.h
### Target

### Base



##Operation
To make sure that the system aligns with the earth reference ensure the correct orientation using a compass by lining up the arrow on the Base Station top (This could be done electronically using a magnetometer). Once powered up Both systems will sit idly as they get satellite lock. Once both have made a lock(maybe take up to a minute) the laser will turn on And the servo will point to where it believes the target object is(if it is substantially off you might need to make sure the whole system is pointing in the right direction(since it is limited in where it works) and that you alined everything using a compass. This will update every few seconds to point at the udated location of the target object which the laser should be hitting. 

Warning! Laser can be harful to eyes so if you are the one holding the target object it would be a good safety measure to have laser

##Resources and going further
GPS parsing info
This could be made much more reactive using better GPS recivers and some more comprehensive code so why not give it a try
This also applys in the Z direction but 
maybe even take what I have created and make something even cooler with the technology
