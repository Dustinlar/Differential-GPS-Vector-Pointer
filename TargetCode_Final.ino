/*GPS Vector Pointer Target
   This sketch simiulates any system that has a GPS beacon and has the ability to
   broadcast this information for other systems to pick up. This could be a plane/drone
   a car/rover or even a solar panel on a space elevator climber. This recieves updating GPS
   coordinates and from an attached GPS reciever, parses the incoming NEMA data and
   send that information using an Xbee connection to the base station.
*/


/*We need to include a couple outside librarys. TinyGPS.h enables a set of tools to
   parse NEMA data into usable GPS info such as latitude and longitude. SoftwareSerial.h gives
   this sketch the ability to use standard DIO pins as serial ports to communicate between
   other microcontrollers. in this case we need one for reciving NEMA data and one
   to communicate using the Xbee. The standard UART on the redboard is reserved for programming
   and as a serial connection to the consol for Control and information purposes.
*/
#include <TinyGPS.h>
#include <SoftwareSerial.h>

//At this point we will define the pins used for serial communication, we
// do this so its easy to change them if needed.
#define gpsRXPIN 5
#define gpsTXPIN 4//this one is unused and doesnt have a conection
#define XbeeRXPIN 2//in this case we will also not use this pin
#define XbeeTXPIN 3

//Next we define the objects used in this sketch this includes two SoftwareSerial objects
//one for refering to the GPS connection and one for the Xbee connection. we also create an
//object that allows us to access the TinyGPS library
SoftwareSerial tGPS (gpsRXPIN, gpsTXPIN);
SoftwareSerial XBee (XbeeRXPIN, XbeeTXPIN); // RX, TX
TinyGPS gps;

//Global variables and functions are declared here, this allows them to be called anywhere
//within the code and is helpful for passing data out of functions. Dont get in the habit \
// of using these though because as your code gets longer its easy to lose track of where
//you are changing these variables and can lead to a headach when a problem arises.
float TargetLat;
float TargetLon;
int Status = 0;
//Function headers can be placed here so that functions can be placed below your setup
//and loop function for a more logical flow of information.
void SendGPSLocation(float Lat, float Lon, int Status);
void getGPS( float* lat, float* lon, int* Status);

void setup() {
  //This function is run before the your program begins to loop, here we define the status
  //of pins that are used for inputs and outputs
  pinMode(gpsRXPIN, INPUT);
  pinMode(XbeeTXPIN, OUTPUT);
  //Next communication begins between the three systems along for the baud rate for each
  //some of these can handle a larger baud rate but you need to make sure they match what
  //they are communicating with
  tGPS.begin(9600);
  Serial.begin(9600);
  XBee.begin(9600);
  while (!Serial) {}
  //a message is printed to the console showing that everything is initailized and
  //the program is now functioning
  Serial.println("Hello");

}

void loop()
//This
{
  // Recieves NEMA data from GPS reciever and Parses Latitude and longitude data
  //returns information using pointers including info on stagnant data

  //because only one Software serial port can be read at the same time we must tell
  //the redboard what to listen to. Here we tell it to listen to the tGPS serial object
  //then call the function that will recieve and parse the signal from the GPS reciver
  tGPS.listen();
  getGPS(&TargetLat, &TargetLon, &Status);
  //Print status to console to know if you are getting good data or not.
  //No Lock = 0, Old Data(>5 sec old) = 1, Good Data = 2
  Serial.println(Status);
  Serial.println(TargetLon);
  Serial.println(TargetLat);
  //we dont want to waste precious processing space or battery power by sending bad data
  //back to the base station so only when the Status variable = 2 for good data we will send
  //the information to the base station
  if (Status == 2)
    //if the data is up to data, send it to base station
  {
    //Switch Software serial port to the Xbee
    XBee.listen();
    //wait for it to become availible(might be unneccesary
    while (!XBee) {}
    //call the function that turns the info into a string and sends it to base station
    SendGPSLocation(TargetLat, TargetLon, Status);
    //wait for 2 seconds to ensure base station does not get overloaded
    delay(1000);
  }



}


void SendGPSLocation(float Lat, float Lon, int Status)
/* this sketch will send values from one modual to another(starting by sending values to XTCU)
  This will eventually send parsed GPS data from the target modual to the base station modual
*/
{
  // Convert GPS data from float into string
  String latData = String(Lat, 5);
  String lonData = String(Lon, 5);
  

  //Concatinate needed data into one string that begins with $ so the parser knows when data starts
  String GPSdata = "$";
  
  GPSdata += latData;
  GPSdata += ",";
  GPSdata += lonData;
  //Send Data as string "xx.yyyyy,-xxx,yyyyy" not able to handle changing signs 
  //but since this is a demo project thats ok
  XBee.println(GPSdata);
  //Print GPS string to console for debugging
  Serial.println(GPSdata);

}


void getGPS( float* lat, float* lon, int* Status)
/*This function switches the softserial pin to the one used for GPS then recieves NEMA data from a GPS
  reciver which is passed into a TinyGPS Object and parsed using its internal functions for $GPRMC info. This function uses
  pointers to pass infomation to pass back to parent function which includes Latitude, longitude,( velocity,
  heading) and the status of the GPS signal.

  function call where variables can be nammed whatever they want as long as they have &:
  getGPS(&latitude, &longitude, &Status);
*/
{
  //Initilize pin to recieve NEMA (have to do it here because we need to switch between
  //software serial pins (if time permits interrupts could be used)
  //pinMode(gpsRXPIN, INPUT);
  // tGPS.begin(9600);
  //define local variables
  float flat;
  float flon;
  unsigned long fix_age;

  //look for serial data from GPS and loop untill the end of NEMA string
  while (tGPS.available())
  {
    //Serial.println("YO");
    int c = tGPS.read();
    if (gps.encode(c));
    {}
  }
  //(is this the correct order for this?^^)

  //Pulled parsed data from gps object
  gps.f_get_position(&flat, &flon, &fix_age);
  *lat = flat;
  *lon = flon;
  //  float falt = gps.f_altitude(); // +/- altitude in meters
  //  float fc = gps.f_course(); // course in degrees
  //  float fmps = gps.f_speed_mps(); // speed in m/sec

  // check if data is relavent
  if (fix_age == TinyGPS::GPS_INVALID_AGE)
    //No fix detected;
  {
    *Status = 0;
  }

  else if (fix_age > 5000)
    //Warning: possible stale data!;
  {
    *Status = 1;
  }

  else
    //Data is current;
  {
    *Status = 2;
  }

}
