#include <TinyGPS.h>
#include <SoftwareSerial.h> 
float lat = 0.00,lon = 0.00; // create variable for latitude and longitude object  
SoftwareSerial gpsSerial(8,9);//rx,tx 
TinyGPS gps; // create gps object 
int Btn=10;

void setup()
{ 
  Serial.begin(9600); // connect serial 
  //Serial.println("The GPS Received Signal:"); 
  gpsSerial.begin(9600); // connect gps sensor  
  pinMode(Btn, INPUT_PULLUP);
} 

void loop()
{ 
  while(gpsSerial.available())
  { // check for gps data 
    if(gps.encode(gpsSerial.read()))// encode gps data 
    {  
      gps.f_get_position(&lat,&lon); // get latitude and longitude 
    } 
  } 
  String latitude = String(lat,6); 
  String longitude = String(lon,6); 
  if (digitalRead(Btn)==LOW)
  {
    Serial.println("http://maps.google.com/maps?q=loc:"+latitude+","+longitude); 
  }
  delay(1000); 
}
