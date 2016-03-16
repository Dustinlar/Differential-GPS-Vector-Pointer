#GPS Differential Vector Pointer Tutorial
(to be converted to Markdown format) 

-What is this "blinky" project doing, and why do I care? 
##Introduction

GPS technology is a very useful and elegant technology, the satellites used in this network do most of the work so that the GPS receiver can be made small and simple. As GPS technology becomes more and more accurate, applications in many areas have really taken off. Some of these include driverless cars, mission planning for UAV, and assisted landing of commercial aircraft and many more. GPS systems vary in cost depending on how accurate they are and what other functions they provide so the right receiver needs to be chosen for application. In this project I am demonstrating that you don’t need an expensive receiver to do cool things with this technology. 
This project began as a proof of concept for the ANACONDA 2014/2015 Aerospace Senior project whose mission was to,

“Design and construct an autonomous tracking and communication support system for an antenna to be used to track unmanned aircraft during flight.”

If you want to check this project out and others follow this link to the CU senior projects page. 

http://www.colorado.edu/aerospace/current-students/undergraduates/senior-design-projects?qt-qt_senior_design_2014_15=1#qt-qt_senior_design_2014_15

The underlying principle here is that if you have two GPS locations provided by two different recivers a position vector can be calculated between them. This can be used to aim a directional antenna or in the case of this project a laser from one object (the base station) to the other object (Target) at theoretically any distance which is only limited to your ability to provide the base station with the targets GPS location 
GPS vector description
The theory behind this is very simple and is shown in the figure below. Knowing the horizontal and the vertical difference between points you can use the arc tan function to give you the angle that you need. 

Video of Operation
This Project
The video below demonstrates the basic functionality of the system. Showing the laser track the target object as it moves
Video of operation

##Suggested reading
If anything I have discussed so far doesn’t quite click here are some relevant tutorials to get you up to speed and give you everything you need to know to complete this project.  
GPS
https://learn.sparkfun.com/tutorials/gps-basics
https://learn.sparkfun.com/tutorials/xbee-shield-hookup-guide
https://learn.sparkfun.com/tutorials/serial-communication
https://learn.sparkfun.com/tutorials/exploring-xbees-and-xctu-retired

https://learn.sparkfun.com/tutorials/how-to-solder---through-hole-soldering
https://learn.sparkfun.com/tutorials/using-github
https://learn.sparkfun.com/tutorials/using-github-to-share-with-sparkfun
https://learn.sparkfun.com/tutorials/arduino-shields





-How do I build it? 
Now that I have gotten you excited about the project and have you itching to try it yourself I will walk you through the steps to create this project on your own and see what cool things you can do with it

https://cdn.sparkfun.com/datasheets/GPS/GP-20U7.pdf

##Required Materials	
This projects requires a decent amount of hardware but to put all of it together is relatively simple and minimal soldering 
Sparkfun
Sparfun Wishlist
Other

3d Printer/ Solidworks

Screws
4x 8-32 B&N
4x !/2” spacers with #5 sized hole
4x 3-48 B&N
8x 2-56 N
4x 2-56 ½”
4x 2-56 ¾”
6x 1-72 ½”
6x 1-72 N

Tripod
###Electronics assembly
Note: some of this may have to be disassembled to construct the final system  
*2
Xbee setup
Configure xbees using explorer and XTCU program (enter addresses, can be done through Arduino code but this is a simpler interface)
Can leave default but need to define addresses of both xbees and define network
Test connection between shield and explorer using demo code and XCTU


Solder headers onto Xbee shield
Insert Xbee onto shield (white lines line up) and ensure switch is on Dline
Place on top of redboard, it wont go entirely on because of barrel plug so just make sure its level.
Modify GPS wires so that they can connect to redboard inputs (could solder but that’s more permanent)
Plug in GPS receiver to both modules.
Connection diagram (fritzing)

####Base station 
Modify Servo wires to allow plug into reboard
###System assembly 
I created Solidworks models to support the electronics parts and to hold the servo and gps recivers in the correct locations. Here are the Solidworks files that are saved in the format used by 3D printing software all you need to do download the files and print them out. If you don’t have a 3d printer there are many locations that will print out these files for you (likely for a price unless you are using a school printer).  
####Target
Place redBoard without xbee shield in   target case so that the USB and screw 3 or 4 (X) bolts into the available holes. 
Do the same thing with  9V Battery holder using (x)bolts
There is a location for the GPS receiver sunk into the base, use backless double-sided tape to hold it in place(other advesiv method cold work but this will be the best
Connect all the wires as discussed above
####Base Station
#####Bottom
Place the two ¼”bolts in first since you will not be able to once the redboard is installed. 
Place redboard into base using (X) bolts and spacers so that it stays above mounting bolts
Screw battery holder onto holes located on the wall of case
#####Top
Remove servo disk
Screw bolts into 4 counting holes of servo which constrains servo in the correct location
Attach disk to laser mount lining up the screw hole with small hole on laser mount
Once attached slide screw driver through top hold to screw the screw that holds the servo gear to the servo back in 
Slide laser into laser mount with wires coming out the back screw 5/8 nut onto front of laser to hold it in place put wires through the available hole
Place GPS receiver in indent made in top with double-sided tape with wires going through the available hole
Attach all the wire as discussed above and place top onto base, should just slide into place


Ensuring the correct orientation using a compass(could be made to use a GPS with a compass or a magnetometer) this is to make sure that the system aligns with the earth reference frame (probably should incude some info on this)

##Risks or possible mistakes
Xbee addresses not matched up or configured
Warning! Laser can be harful to eyes so if you are the one holding the target object it would be a good safety measure to have laser glasses at 300nm wave length 
Code
Once fully assembled upload code to both boards and plug in batterys. Works completely standalone but connection to serial consol could be used to see data collected as it comes in.
Need to include these librarys
Software serial.h
tinyGPS.h
Servo.h
##What you should see
Both systems will sit idly as they get satellite lock. Once both have made a lock(maybe take up to a minute) the laser will turn on And the servo will point to where it believes the target object is(if it is substantially off you might need to make sure the whole system is pointing in the right direction(since it is limited in where it works) and that you alined everything using a compass. This will update every few seconds to point at the udated location of the target object which the laser should be hitting. This could be made much more reactive using better GPS recivers and some more comprehensive code so why not give it a try
Resources and going further
GPS parsing info

maybe even take what I have created and make something even cooler with the technology