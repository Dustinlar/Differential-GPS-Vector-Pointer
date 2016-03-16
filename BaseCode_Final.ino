

/* GPS Vector Pointer Base Station
  By: Dustin Larsen
  Abstract Eagle Technologies
  Date: March 20th, 2016
  (Beerware license): This code is public domain but you enjoy the project and we meet someday buy me a beer.

    This sketch controls the Base station functionality while incudes the ability to
    recieve GPS coordinates from the target object and compare itto the GPS coordinates
    of the Base station GPS Location. The location of the base station will be calculated
    using a function that increases its accuracy over time by storing all previous values.
    The direction vector between the base station and the target object will then be calculated
    and a servo will be commanded to point a LASER in the direction of the target object.
*/

// gives the ability to use standard DIO pins as serial ports to communicate between other microcontrollers.
#include <SoftwareSerial.h>
//enables a set of tools to parse NEMA data into usable GPS info such as latitude and longitude
#include <TinyGPS.h>
//Enables the use of the servo Library to easily control an analog servo
#include <Servo.h>;


//pins are defined here so they can be easily referenced and changed if needed 
#define gpsRXPIN 5
#define gpsTXPIN 4
#define XbeeRXPIN 2
#define XbeeTXPIN 3
#define ServoPIN 9


//define the objects for the included librarys used in this sketch 
SoftwareSerial bGPS (gpsRXPIN, gpsTXPIN);
SoftwareSerial XBee (XbeeRXPIN, XbeeTXPIN);
TinyGPS gps;
Servo servo1;



//Global variables are declared here, this allows them to be called anywhere
//within the code and is helpful for passing data out of functions. 
float baseLat = 0;
float baseLon = 0;
float baseavgLat;
float baseavgLon;
float targetLat = 0;
float targetLon = 0;
int Status = 0;

//Function headers introduced so functions can be called from anywhere in your sketch for a more logical flow of information.
void getGPS( float* lat, float* lon, int* Status);
void RecieveGPSLocation(float* latData, float* lonData);
void ServoPointCommand(double baseLat, double baseLon, double targetLat, double targetLon);

void setup() {


 //define the status of pins that are used for inputs and outputs
  pinMode(XbeeRXPIN, INPUT);
  pinMode(gpsRXPIN, INPUT);

 //Begin communication with the XBee, the GPS reciver and the Serial console
  XBee.begin(9600);
  bGPS.begin(9600);
  Serial.begin(9600);
  //while (!Serial) {}
  //a message is printed to the console showing that everything is initailized and
  //the program is now functioning
  Serial.println("goodnight moon!");
 }

void loop() {

  //Software serial can only look at one input at a time so we must tell it what to listen to
  //here the sketch switches software serial to Xbee
  XBee.listen();
  //wait for buffer to fill
  delay(2);
  //recieve and parse target GPS location
  RecieveGPSLocation(&targetLat, &targetLon);


  //Switches software serial to GPS
  bGPS.listen();
  //wait for buffer to fill
  delay(2);
  //loops through getGPS function so that it does not stop listening before 
  //current data can be gathered
  int  count = 15;
  while ( count > 0) {
    getGPS( &baseLat, &baseLon, &Status);
    count-- ;
    //if data up to date break out of the loop and reset the count
    if (Status == 2)
    {
      bothGPSknown();
      count = 0;
      break;//redundant?
    }
  }
}

void bothGPSknown()
{
  //once both sets of coordinates are known stop listening to GPS and attach
  //the servo so that it does not recieve noise from GPS reciver(It will twich randomly if you dont do this)
  XBee.listen();
  servo1.attach(ServoPIN);
  //Average the the current base data with the existing, this will increase the accuracy over time since
  //the base hardware will not move even if the GPS data jumps around
  baseavgLat = (baseLat + baseavgLat) / 2;
  baseavgLon = (baseLon + baseavgLon) / 2;

//Print out info to Serial Console
  Serial.print("Base Latitude:");
  Serial.println(baseavgLat, 5);
  Serial.print("Base Longitude:");
  Serial.println(baseavgLon, 5);
  Serial.print("Target Latitude:");
  Serial.println(targetLat, 5);
  Serial.print("Target Longitude:");
  Serial.println(targetLon, 5);
  //passes this data GPS data to control servo
  ServoPointCommand(baseavgLat, baseavgLon, targetLat, targetLon);
  //wait after pointing angle commanded
  delay(1000);
  //Detach servo to prevent jittering while not in use
  servo1.detach();
  //Define status of data as stale 
  Status = 1;
}

void RecieveGPSLocation(float* latData, float* lonData)
/*
   This function looks for a current GPS value to be recieved from target which then reads nthe 
   compound string and places latitude and longitude data into their respective strings
   then converts those strings to float to pass variables back to main loop using pointers
*/
{
  //declares and clears variables used in this function
  String GPSdata = "";
  char inChar;
  String A = "";
  
  //reads buffer till string identifier is seen
  while ( inChar != '$')
  {
    inChar = XBee.read();
  }
  //once data string is identified loop till "\n" is seen which identifies the end of the data

  while ( inChar != '\n' ) {
    //wait for buffer to fill 
    delay(1);
    //read next character
    inChar = XBee.read();
    //concatinate into GPSdata string
    GPSdata += inChar;
  }



  //Parse Latitude data from string and send it back to main loop
  A = GPSdata.substring(0,  9);
  *latData = A.toFloat();
  //Clear string A
  A = "";
  //Parse Longitude data from string and send it back to main loop
  A = GPSdata.substring(9);
  *lonData = A.toFloat();

}

void getGPS( float* lat, float* lon, int* Status)
/*This function switches the softwareserial pin to the one used for the GPS reciver then recieves the NEMA data 
  which is passed into a TinyGPS Object and parsed using its internal functions for $GPRMC info. This function uses
  pointers to pass infomation to pass back to parent function which includes Latitude, longitude,and Status of the GPS signal.

  function call where variables can be nammed whatever they want as long as they have &:
  getGPS(&latitude, &longitude, &Status);
*/
{
  //define local variables
  float flat;
  float flon;
  unsigned long fix_age;

  //look for serial data from GPS and loop untill the end of NEMA string
  while (bGPS.available())
  {
    int c = bGPS.read();
    if (gps.encode(c));
    {
    }
    delay(2); //this delay is a fine lie, may have problems later
  }

  // Use tinyGPS library to parse information
  gps.f_get_position(&flat, &flon, &fix_age);
  *lat = flat;
  *lon = flon;

  // check if data is relavent and print update to serial port
  if (fix_age == TinyGPS::GPS_INVALID_AGE)
    //No fix detected;
  {
    *Status = 0;
    //delay(10);
    //Serial.println("");
    Serial.println("no GPS data recieved from base");//doesnt work when I take out print functions
  }

  else if (fix_age > 5000)
    //Warning: possible stale data!;
  {
    *Status = 1;
    // delay(10);
    Serial.println("Stale GPS data recieved from base");
  }

  else
    //Data is current;
  {
    *Status = 2;
    //delay(10);
    //Serial.println("");
    Serial.println("GPS data recieved from base");
  }

}

void ServoPointCommand(float baseLat, float baseLon, float targetLat, float targetLon)
/* THis function will take the cordinates of the base station and the target object
    then calculate the angle between then using the inverse tangent function.
*/
{
  //Define Local variables
  float latDiff, lonDiff, theta;
  double servoPosition;

  //Calculate difference
  latDiff = (targetLat - baseLat);
  lonDiff = (targetLon - baseLon);
  //Calculate angle
  theta =   atan2 (latDiff, lonDiff);
  theta = theta * 180 / 3.145;

  //Print result to console
  Serial.println("latDiff");
  Serial.println(latDiff);
  Serial.println("lonDiff");
  Serial.println(lonDiff);
  Serial.println("theta");
  Serial.println(theta);

  //Map the calculated angle into a value the servo will understand
  servoPosition = map(theta, -180, 0, 0, 180);
  servoPosition = constrain(servoPosition, 0, 180);
  servo1.write(servoPosition);

}
