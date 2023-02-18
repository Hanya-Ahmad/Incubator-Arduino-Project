#include <SoftwareSerial.h>
//DHT imports
// #include "DHT.h"
#define dht_dpin A0  // Analog Pin sensor is connected to
int relayPin = 7;
#include "dht.h"
#include ""

dht DHT;

int min_temp = 30;
SoftwareSerial MyBlue(0, 1);  // TX | RX
int max_temp = 32;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Serial.println("Enter AT commands:");
  pinMode(relayPin, OUTPUT);
  // HC-06 default serial speed is 9600
  // bluetooth.begin(9600);
  Serial.begin(9600);
}

void loop() {
  //from bluetooth to Terminal.
  if (MyBlue.available())
    Serial.write(MyBlue.read());
  //from termial to bluetooth
  if (Serial.available())
    MyBlue.write(Serial.read());
  checkT_H();
  printReadings();
  delay(500);
}

void printReadings() {
  DHT.read11(dht_dpin);
  // Serial.print("Current readHumidity() = ");
  Serial.print("")
  Serial.print(DHT.temperature);
  // Serial.println(analogRead())
  Serial.print(" ");
  Serial.println(DHT.humidity);
  // Serial.print("%  ");
  // Serial.print("temperature = ");
  // Serial.println("°C  ");
}

void checkT_H() {
  //here we run a check on the temperature.
  if (DHT.temperature <= min_temp) {
    //this means that temperature is low, we must turn on the heat source (relay)
    digitalWrite(relayPin, HIGH);
  } else if (DHT.temperature >= max_temp) {
    //this means that the temperature is now optimal, we must turn off the heat source
    digitalWrite(relayPin, LOW);
  } 
}
