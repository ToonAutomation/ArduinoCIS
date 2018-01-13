/*****************************************************************************************
ArduinoUno Map Input Output AnalogInput 
Write by Natthapong ArduinoTechs
******************************************************************************************/
#include "ProtocolEx.h"

#define Node 1
ProtocolEx Ex;

void setup() 
{
    // Init Serial
    Serial.begin(115200);
    // Begin Node and Serial
    Ex.Begin(Node,Serial);

    Ex.SetDeviceName("Arduino-Ex1");
    // Setpin 13,12,11,10,9,8 is OUTPUT
    pinMode(13,OUTPUT);
    pinMode(12,OUTPUT);
    pinMode(11,OUTPUT);
    pinMode(10,OUTPUT);
    pinMode(9,OUTPUT);
    pinMode(8,OUTPUT);

    // Setpin 7,6,5,4,3,2 is INPUT
    pinMode(7,INPUT);
    pinMode(6,INPUT);
    pinMode(5,INPUT);
    pinMode(4,INPUT);
    pinMode(3,INPUT);
    pinMode(2,INPUT);
}


void loop() 
{
   // Mapping Digital Input     
   MovBit(Ex.I[0],0,digitalRead(7)); // Address I0.0
   MovBit(Ex.I[0],1,digitalRead(6)); // Address I0.1 
   MovBit(Ex.I[0],2,digitalRead(5)); // Address I0.2 
   MovBit(Ex.I[0],3,digitalRead(4)); // Address I0.3
   MovBit(Ex.I[0],4,digitalRead(3)); // Address I0.4
   MovBit(Ex.I[0],5,digitalRead(2)); // Address I0.5
   // Mapping Analog Input
   Ex.I[1] = analogRead(A0);   // Address I1  
   Ex.I[2] = analogRead(A1);   // Address I2
   Ex.I[3] = analogRead(A2);   // Address I3
   Ex.I[4] = analogRead(A3);   // Address I4
   Ex.I[5] = analogRead(A4);   // Address I5
   Ex.I[6] = analogRead(A5);   // Address I6
   // Mapping Digital Output
   digitalWrite(13,GetBit(Ex.Q[0],0)); // Address Q0.0
   digitalWrite(12,GetBit(Ex.Q[0],1)); // Address Q0.1
   digitalWrite(11,GetBit(Ex.Q[0],2)); // Address Q0.2
   digitalWrite(10,GetBit(Ex.Q[0],3)); // Address Q0.3
   digitalWrite(9, GetBit(Ex.Q[0],4)); // Address Q0.4
   digitalWrite(8, GetBit(Ex.Q[0],5)); // Address Q0.5
   // Mapping Float Data
   Ex.Float[0] = ((float)Ex.I[1]/1023)*5 ; // Address Float1
   Ex.Float[1] = ((float)Ex.I[2]/1023)*5 ; // Address Float2
   Ex.Float[2] = ((float)Ex.I[3]/1023)*5 ; // Address Float3
   Ex.Float[3] = ((float)Ex.I[4]/1023)*5 ; // Address Float4
   Ex.Float[4] = ((float)Ex.I[5]/1023)*5 ; // Address Float5
   Ex.Float[5] = ((float)Ex.I[6]/1023)*5 ; // Address Float6
   Ex.Float[6] = ((float)Ex.I[7]/1023)*5 ; // Address Float7
   // Mapping String 
   Ex.FillText(0,"Arduino Uno"); // Address text0
   Ex.FillText(1,"CIS Design"); // Address text1
   Ex.FillText(2,"ArduinoTechs"); // Address text2 

   // Wait Recive and Send Data Between Host
   if( Ex.ScanLoop() == true)
   {
        // ScanLoop Exchange Data Between host ok
        // dosomething();
   }

}

