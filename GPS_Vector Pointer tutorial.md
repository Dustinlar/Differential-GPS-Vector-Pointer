#GPS Differential Vector Pointer Tutorial

##Introduction

GPS technology is a very useful and elegant technology, the satellites used in this network do most of the work so that the GPS receiver can be made small and simple. As GPS technology becomes more and more accurate, applications in many areas have really taken off. Some of these include driverless cars, mission planning for UAV, and assisted landing of commercial aircraft and many more. GPS systems vary in cost depending on how accurate they are and what other functions they provide so the right receiver needs to be chosen for application. In this project I am demonstrating that you don’t need an expensive receiver to do cool things with this technology. 
This project began as a proof of concept for the ANACONDA 2014/2015 Aerospace Senior project whose mission was to,

>“Design and construct an autonomous tracking and communication support system for an antenna to be used to track unmanned aircraft during flight.”

If you want to check this project out and others follow this link to the CU senior projects page and go to the 2015 projects page . 

[CU Aerospace Senior Projects](http://www.colorado.edu/aerospace/current-students/undergraduates/senior-design-projects?qt-qt_senior_design_2014_15=1#qt-qt_senior_design_2014_15)

The underlying principle here is that if you have two GPS locations provided by two different recivers a position vector can be calculated between them. This can be used to aim a directional antenna or in the case of this project a laser from one object (the base station) to the other object (Target) at theoretically any distance which is only limited to your ability to provide the base station with the targets GPS location 
##This Project
The video below demonstrates the basic functionality of the system. Showing the laser track the target object as it moves
Video of operation

##GPS vector description
The theory behind this is very simple and is shown in the figure below. Knowing the horizontal and the vertical difference between points you can use the arc tan function to give you the angle that you need. 
Picture displaying GPS Vector

##Required Materials	
Now that I have gotten you excited about the project and have you itching to try it yourself I will walk you through the steps to create this project on your own and see what cool things you can do with it. This projects requires a decent amount of hardware but to put all of it together is relatively simple and minimal soldering 
Sparkfun
Sparfun Wishlist
Other

3d Printer/ Solidworks

Screws
*4x 8-32 B&N
*4x 1/2” spacers with #5 sized hole
*4x 3-48 B&N
*8x 2-56 N
*4x 2-56 ½”
*4x 2-56 ¾”
*6x 1-72 ½”
*6x 1-72 N

Tripod

##Suggested reading
If anything I have discussed so far doesn’t quite click here are some relevant tutorials to get you up to speed and give you everything you need to know to complete this project.  

[GPS basics](https://learn.sparkfun.com/tutorials/gps-basics)  
[XBee sheild hookup guide](https://learn.sparkfun.com/tutorials/xbee-shield-hookup-guide)  
[Serial communication](https://learn.sparkfun.com/tutorials/serial-communication)  
[Configuring XBe's](https://learn.sparkfun.com/tutorials/exploring-xbees-and-xctu-retired)  

###Electronics assembly
_Note: You will have to take off the Xbee sheild to mount on the final system_  

* Configure xbees using explorer and XTCU program (enter addresses, can be done through Arduino code but this is a simpler interface)
* Create two complete XBee sheild assemblyes 
* Modify GPS wires so that they can connect to redboard inputs 
* Modify Servo wires to allow plug into redboard
* Solder stranded wire to laser

* On the base 

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
Need to include these librarys along with the code I added
Software serial.h
tinyGPS.h
Servo.h

##Operation
To make sure that the system aligns with the earth reference ensure the correct orientation using a compass by lining up the arrow on the Base Station top (This could be done electronically using a magnetometer). Once powered up Both systems will sit idly as they get satellite lock. Once both have made a lock(maybe take up to a minute) the laser will turn on And the servo will point to where it believes the target object is(if it is substantially off you might need to make sure the whole system is pointing in the right direction(since it is limited in where it works) and that you alined everything using a compass. This will update every few seconds to point at the udated location of the target object which the laser should be hitting. 

Warning! Laser can be harful to eyes so if you are the one holding the target object it would be a good safety measure to have laser


##Resources and going further
GPS parsing info
This could be made much more reactive using better GPS recivers and some more comprehensive code so why not give it a try

maybe even take what I have created and make something even cooler with the technology
