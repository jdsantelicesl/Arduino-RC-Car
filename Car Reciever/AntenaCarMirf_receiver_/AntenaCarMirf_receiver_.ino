/* 6/19/2023 working perfectly at receiving and unpacking */
/* 7/1/2023 both motors functioning properly, lost connection loop added.
   Both motors still need calibration*/

// Receiver Code

#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#include <Servo.h>
Servo myServo;

byte packedData;
byte ndata1;
byte ndata2;
float switchX;
float switchY;

void setup()
{
    Serial.begin(9600);

    Mirf.spi = &MirfHardwareSpi;
    Mirf.init();
    Mirf.setRADDR((byte *)"serv1");
    Mirf.payload = sizeof(unsigned long);
    Mirf.config();
    Serial.println("I'm Reciever...");
    delay(100);

    pinMode(2, OUTPUT); //backwards
    pinMode(4, OUTPUT); //forward
    pinMode(3, OUTPUT); //pulse modulated speed
    
    myServo.attach(5);
    myServo.write(90);
}
void loop()
{
    byte data[Mirf.payload];

    // Check if data is available from the transmitter
    if(Mirf.dataReady())
    {
        // Read the data from the transmitter
        Mirf.getData(data);

        ndata1 = (data[0] >> 4) & 0x0F;  // data comes in 1 byte
        ndata2 = (data[0] & 0x0F);       // here it is unpacked to 2
       
        if(ndata1 >= 6 && ndata1 <= 9){
          switchX = 90; // sets a deadzone for a joystick range
        }

        else if (ndata1 < 6){
          switchX = 90 - 5*(ndata1*-1 + 6);
          Serial.print("servo < 6: ");
          Serial.println(switchX);
        } 

        else if(ndata1 > 9){
          switchX = 90 + 5*(ndata1 - 9);
          Serial.print("servo > 9: ");
          Serial.println(switchX);
        }

        // Map the data back to the range of 0-1023 for motors, due to change
        switchY = map(ndata2, 0, 15, 0, 1023);
        
        delay(20);

        // Adjust Servo angle to switchX (steering)
        myServo.write(switchX);

        // speed control with switchY
        if(switchY > 477){
          Serial.println("forward");
          digitalWrite(2, LOW);
          digitalWrite(4, HIGH);
          analogWrite(3, switchY);
          Serial.print("fwd speed: ");
          Serial.println(switchY);
        }

        if(switchY < 477){
          Serial.println("backwards");
          digitalWrite(2, HIGH);
          digitalWrite(4, LOW);
          analogWrite(3, 1023-switchY);
          Serial.print("fwd speed: ");
          Serial.println(switchY);
        }

        if(switchY == 477){
          Serial.println("null");
          digitalWrite(2, LOW);
          digitalWrite(4, LOW);
        }
    }
    
      while(!Mirf.dataReady()){
        unsigned int timeCheck = millis();

        if(millis() - timeCheck > 1000){
          Mirf.spi = &MirfHardwareSpi;
          Mirf.init();
          Mirf.setRADDR((byte *)"serv1");
         Mirf.payload = sizeof(unsigned long);
         Mirf.config();
         Serial.println("Connection reenabled");
         delay(100);
        }
        
        
      }
        
}
