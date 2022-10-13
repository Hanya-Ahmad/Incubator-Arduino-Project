#include <SoftwareSerial.h>


int relaypin = 8;

//DHT imports
#include <dht.h>
#define dht_apin A0 // Analog Pin sensor is connected to
int min_temp = 36.3;
SoftwareSerial bluetooth(0, 1); // RX | TX
int max_temp = 39;
dht DHT;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
 

    // HC-06 default serial speed is 9600
  bluetooth.begin(9600);
  Serial.begin(9600);
}

void loop() {
    DHT.read11(dht_apin);
    
    Serial.print("Current humidity = ");
    bluetooth.print(DHT.humidity);
    Serial.print("%  ");
    bluetooth.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");


      //here we run a check on the temperature.
if (DHT.temperature <= min_temp)
  {
    //this means that temperature is low, we must turn on the heat source (relay)
    digitalWrite(relaypin, HIGH);
  }
  else if( DHT.temperature >= max_temp)
  {
    //this means that the temperature is now optimal, we must turn off the heat source
    digitalWrite(relaypin, LOW);
  }
  
  delay(500);
}
