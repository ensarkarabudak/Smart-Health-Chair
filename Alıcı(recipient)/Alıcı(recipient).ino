#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"           //Modül ile ilgili kütüphaneleri ekliyoruz
int mesaj[2];
RF24 alici(2,3);
const uint64_t kanal = 0xE8E8F0F0E1LL;  

void setup() {
Serial.begin(9600);
 
 alici.begin();
 alici.openReadingPipe(1,kanal);
 alici.startListening();

  }

void loop() {

  if (alici.available())                //check when received data available
  {
    alici.read(mesaj, sizeof(mesaj));
      Serial.print("BASINÇ: ");
      Serial.print(mesaj[0]);    
      Serial.println(" Newton");
      
      Serial.print("♥ KALP: ");
      Serial.print(mesaj[1]/10);    
      Serial.println(" BPM ");
  }

}
