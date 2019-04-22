#include  <SPI.h> 
#include "nRF24L01.h"
#include "RF24.h"     //Modül ile ilgili kütüphaneleri ekliyoruz
int mesaj[2];      //mesaj isminde bir dizi tanımlıyoruz
RF24 verici(2,3);     //kütüphane tarafından kullanılacak pinleri tanımlıyoruz
const uint64_t kanal = 0xE8E8F0F0E1LL; //kanalı tanımlıyoruz 

int fsrPin = 0;     // the FSR and 10K pulldown are connected to a0
int pulse = 1;     // the FSR and 10K pulldown are connected to a0
int pulseReading;
int fsrReading;     // the analog reading from the FSR resistor divider
int fsrVoltage;     // the analog reading converted to voltage
unsigned long fsrResistance;  // The voltage converted to resistance, can be very big so make "long"
unsigned long fsrConductance; 
long fsrForce;       // Finally, the resistance converted to force
 

void setup() {
 verici.begin();       //nrf yi başlatıyoruz
 verici.openWritingPipe(kanal);  //kanal id sı tanımlanıyor
}


void loop(void) {
  fsrReading = analogRead(fsrPin); 
  pulseReading = analogRead(pulse);
  
  fsrVoltage = map(fsrReading, 0, 1023, 0, 5000);
  fsrResistance = 5000 - fsrVoltage;     // fsrVoltage is in millivolts so 5V = 5000mV
  fsrResistance *= 10000;   
  fsrResistance /= fsrVoltage;
  fsrConductance = 1000000;           // we measure in micromhos so 
  fsrConductance /= fsrResistance;
  if (fsrConductance <= 1000) {
      fsrForce = fsrConductance / 80;
   } else {
      fsrForce = fsrConductance - 1000;
      fsrForce /= 30;
   }
    mesaj[0] = fsrForce;
    mesaj[1]=pulseReading;
    verici.write(mesaj, sizeof(mesaj));


  
  delay(2000);

}
