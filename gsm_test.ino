#include<SoftwareSerial.h>
 long randNumber;

SoftwareSerial mySerial1 (2,3);

void setup()
{
  mySerial1.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
  randomSeed(analogRead(0));
}


void loop()
{
  if (Serial.available()>0)
   switch(Serial.read())
  {
    case 's':
      mySerial1.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second
     mySerial1.println("AT+CMGS=\"+916380359193\"\r"); // Replace x with mobile number
     delay(1000);
     randNumber = random(999,9999);
     Serial.println(randNumber);
     mySerial1.println("Temperature is:");// The SMS text you want to send
     mySerial1.println("91.40F");
     mySerial1.println("BPM is");
     mySerial1.println("66");
     delay(100);
     mySerial1.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      delay(1000);
      break;



      
    case 'r':
      mySerial1.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
      delay(1000);
      break;
  }

 if (mySerial1.available()>0)
   Serial.write(mySerial1.read());
}
