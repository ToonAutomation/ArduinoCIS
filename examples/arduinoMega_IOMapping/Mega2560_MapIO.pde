#include <Arduino.h>
#include "ProtocolEx.h"

#define Node 2
ProtocolEx Ex;

void setup() 
{
    // Init Serial
    Serial.begin(115200);
    // Begin Node and Serial
    Ex.Begin(Node,Serial);

    Ex.SetDeviceName("Arduino-Ex2");
    // Setpin 2 - 25 is OUTPUT
    pinMode(13,OUTPUT);
    pinMode(12,OUTPUT);
    pinMode(11,OUTPUT);
    pinMode(10,OUTPUT);
    pinMode(9,OUTPUT);
    pinMode(8,OUTPUT);
    pinMode(7,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(4,OUTPUT);
    pinMode(3,OUTPUT);
    pinMode(2,OUTPUT);
    pinMode(22,OUTPUT);
    pinMode(23,OUTPUT);
    pinMode(24,OUTPUT);
    pinMode(25,OUTPUT);
   
    //Setpin 26 - 53 is INPUT
    pinMode(26,INPUT);
    pinMode(27,INPUT);
    pinMode(28,INPUT);
    pinMode(29,INPUT);
    pinMode(30,INPUT);
    pinMode(31,INPUT);
    pinMode(32,INPUT);
    pinMode(33,INPUT);
    pinMode(34,INPUT);
    pinMode(35,INPUT);
    pinMode(36,INPUT);
    pinMode(37,INPUT);
    pinMode(38,INPUT);
    pinMode(39,INPUT);
    pinMode(40,INPUT);
    pinMode(41,INPUT);
    pinMode(42,INPUT);
    pinMode(43,INPUT);
    pinMode(44,INPUT);
    pinMode(45,INPUT);
    pinMode(46,INPUT);
    pinMode(47,INPUT);
    pinMode(48,INPUT);
    pinMode(49,INPUT);
    pinMode(50,INPUT);
    pinMode(51,INPUT);
    pinMode(52,INPUT);
    pinMode(53,INPUT);

    
}


void loop() 
{
   // Example Mapping Digital Input     
   MovBit(Ex.I[0],0,digitalRead(26)); // Address I0.0
   MovBit(Ex.I[0],1,digitalRead(27)); // Address I0.1
   MovBit(Ex.I[0],2,digitalRead(28)); // Address I0.2
   MovBit(Ex.I[0],3,digitalRead(29)); // Address I0.3
   MovBit(Ex.I[0],4,digitalRead(30)); // Address I0.4 
   MovBit(Ex.I[0],5,digitalRead(31)); // Address I0.5 
   MovBit(Ex.I[0],6,digitalRead(32)); // Address I0.6
   MovBit(Ex.I[0],7,digitalRead(33)); // Address I0.7
   MovBit(Ex.I[0],8,digitalRead(34)); // Address I0.8
   MovBit(Ex.I[0],9,digitalRead(35)); // Address I0.9
   MovBit(Ex.I[0],10,digitalRead(36)); // Address I0.10
   MovBit(Ex.I[0],11,digitalRead(37)); // Address I0.11
   MovBit(Ex.I[0],12,digitalRead(38)); // Address I0.12
   MovBit(Ex.I[0],12,digitalRead(39)); // Address I0.13
   MovBit(Ex.I[0],13,digitalRead(40)); // Address I0.14
   MovBit(Ex.I[0],14,digitalRead(41)); // Address I0.15

   MovBit(Ex.I[1],0,digitalRead(42)); // Address I1.0
   MovBit(Ex.I[1],1,digitalRead(43)); // Address I1.1
   MovBit(Ex.I[1],2,digitalRead(44)); // Address I1.2
   MovBit(Ex.I[1],3,digitalRead(45)); // Address I1.3
   MovBit(Ex.I[1],4,digitalRead(46)); // Address I1.4
   MovBit(Ex.I[1],5,digitalRead(47)); // Address I1.5
   MovBit(Ex.I[1],6,digitalRead(48)); // Address I1.6
   MovBit(Ex.I[1],7,digitalRead(49)); // Address I1.7
   MovBit(Ex.I[1],8,digitalRead(50)); // Address I1.8
   MovBit(Ex.I[1],9,digitalRead(51)); // Address I1.9
   MovBit(Ex.I[1],10,digitalRead(52)); // Address I1.10
   MovBit(Ex.I[1],11,digitalRead(53)); // Address I1.11
   
   // Example Mapping Analog Input
   Ex.I[2] = analogRead(A0);   // Address I2
   Ex.I[3] = analogRead(A1);   // Address I3
   Ex.I[4] = analogRead(A2);   // Address I4
   Ex.I[5] = analogRead(A3);   // Address I5
   Ex.I[6] = analogRead(A4);   // Address I6
   Ex.I[7] = analogRead(A5);   // Address I7
   Ex.I[8] = analogRead(A6);   // Address I8
   Ex.I[9] = analogRead(A7);   // Address I9
   Ex.I[10] = analogRead(A8);   // Address I10
   Ex.I[11] = analogRead(A9);   // Address I11
   Ex.I[12] = analogRead(A10);   // Address I12
   Ex.I[13] = analogRead(A11);   // Address I13
   Ex.I[14] = analogRead(A12);   // Address I14
   Ex.I[15] = analogRead(A13);   // Address I15
   Ex.I[16] = analogRead(A14);   // Address I16
   Ex.I[17] = analogRead(A15);   // Address I17

   // Example Mapping Float Data
   Ex.Float[0] = ((float)Ex.I[2]/1023)*5 ; // Address Float0
   Ex.Float[1] = ((float)Ex.I[3]/1023)*5 ; // Address Float1
   Ex.Float[2] = ((float)Ex.I[4]/1023)*5 ; // Address Float2
   Ex.Float[3] = ((float)Ex.I[5]/1023)*5 ; // Address Float3
   Ex.Float[4] = ((float)Ex.I[6]/1023)*5 ; // Address Float4
   Ex.Float[5] = ((float)Ex.I[7]/1023)*5 ; // Address Float5
   Ex.Float[6] = ((float)Ex.I[8]/1023)*5 ; // Address Float6
   Ex.Float[7] = ((float)Ex.I[9]/1023)*5 ; // Address Float7
   Ex.Float[8] = ((float)Ex.I[10]/1023)*5 ; // Address Float8
   Ex.Float[9] = ((float)Ex.I[11]/1023)*5 ; // Address Float9
   Ex.Float[10] = ((float)Ex.I[12]/1023)*5 ; // Address Float10
   Ex.Float[11] = ((float)Ex.I[13]/1023)*5 ; // Address Float11
   Ex.Float[12] = ((float)Ex.I[14]/1023)*5 ; // Address Float12
   Ex.Float[13] = ((float)Ex.I[15]/1023)*5 ; // Address Float13

   //Example Mapping String 
   Ex.FillText(0,"Arduino Mega2560"); // Address text0
   Ex.FillText(1,"CIS Design"); // Address text1
   Ex.FillText(2,"ArduinoTechs"); // Address text2 

   // Wait Recive and Send Data Between Host
   if( Ex.ScanLoop() == true)
   {
        // ScanLoop Exchange Data Between host ok
        // dosomething();
   }

}


