/*  6/20/2023 working only with a "return;" command reason is still unknown. Update, return command did not work 
 *   "while(Mirf.isSending())" seems to fix the problem this time.
  */

// Sender Code

#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

void setup()
{
    Serial.begin(9600);

    Mirf.spi = &MirfHardwareSpi;
    Mirf.init();
    Mirf.setRADDR((byte *)"clie1");
    Mirf.payload = sizeof(unsigned long);
    Mirf.config();
    Serial.println("I'm Sender...");
    delay(100);
}
void loop()
{
    // Read the controller input
    unsigned int switchX = analogRead(A1);
    unsigned int switchY = analogRead(A0);

    if(switchX > 1020){ //1023 is very unstable on joystick and causes lag
      switchX = 1020; //simple bug fix
    }
    
    Serial.print("SwitchX: ");
    Serial.println(switchX);
    Serial.print("SwitchY: ");
    Serial.println(switchY);

    // Map the controller input to a range of 0-15 for transmission
    byte data[2];
    data[0] = map(switchX, 0, 1020, 0, 15);
    data[1] = map(switchY, 0, 1023, 0, 15);

    // place data 1 and 2 in a single byte so it can be sent
    byte packedData = ((data[0] << 4) | (data[1]));

    // declare reciever of data
    Mirf.setTADDR((byte *)"serv1"); 
    // Send the data to the receiver
    Mirf.send((byte *)&packedData);
    while(Mirf.isSending()){
    }
    delay(50);
    //code will jam and not run loop if antena doesnt receive
}
