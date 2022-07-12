#include <TinyGPS.h>
#include <SoftwareSerial.h>
#include<Wire.h>

float lat = 0.00,lon = 0.00; // create variable for latitude and longitude object  
SoftwareSerial gpsSerial(8,9);//rx,tx 
TinyGPS gps; // create gps object 
int Btn=10;

const int MPU_addr=0x68;  
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
float ax=0, ay=0, az=0;
int buzzer = 13;
int StopBtn=12;

boolean fall = false;  

int angleChange=0;

void mpu_read(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true); 
  AcX=Wire.read()<<8|Wire.read();    
  AcY=Wire.read()<<8|Wire.read();  
  AcZ=Wire.read()<<8|Wire.read(); 
  Tmp=Wire.read()<<8|Wire.read(); 
  GyX=Wire.read()<<8|Wire.read();
  GyY=Wire.read()<<8|Wire.read();
  GyZ=Wire.read()<<8|Wire.read();  
  }

void setup()
{ 
  Serial.begin(9600); // connect serial  
  gpsSerial.begin(9600); // connect gps sensor  
  pinMode(Btn, INPUT_PULLUP);

  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  
  Wire.write(0);     
  Wire.endTransmission(true);
  pinMode(StopBtn, INPUT_PULLUP);
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
    delay(100);
  } 

  mpu_read();
  ax = (AcX-2050)/16384.00;
  ay = (AcY-77)/16384.00;
  az = (AcZ-1947)/16384.00;
  
  float Raw_AM = pow(pow(ax,2)+pow(ay,2)+pow(az,2),0.5);
  int AM = Raw_AM * 10; 

  if (AM>25)
  {
    fall=true;
  }

  if (fall==true){ 
    while (digitalRead(StopBtn)==HIGH)
    {
      tone(buzzer,450);
      delay(200);
      noTone(buzzer);
      delay(200);
    }
    fall = false; 
    }
  delay(100);
}
