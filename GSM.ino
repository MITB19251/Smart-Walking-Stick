#include <SoftwareSerial.h>
SoftwareSerial mySerial(9,10);
char msg;
char number;

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  Serial.println("Enter character:");
  Serial.println("s : to send message");
  Serial.println("c : to make a call");
  Serial.println("d : to disconnect a call");
  Serial.println("r : to redial");
  Serial.println();
  delay(100);
}

void loop() {
  if (Serial.available()>0)
    switch(Serial.read())
   {
    case 's':
      mySerial.println("AT+CMGF=1");
      delay(1000); 
      mySerial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r");
      delay(1000);
      mySerial.println("I am SMS from GSM Module");
    case 'c':                  
      mySerial.println("ATD +91xxxxxxxxxx;\r");
    case 'r':
      mySerial.println("ATDL");
    case 'd':
      mySerial.println("ATH");
   }
}
