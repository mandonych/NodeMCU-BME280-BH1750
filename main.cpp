#include <Arduino.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <Ticker.h>

#include <BH1750.h> //https://github.com/claws/BH1750
BH1750 lightMeter;

#include <Adafruit_Sensor.h> //https://github.com/adafruit/Adafruit_Sensor
#include <Adafruit_BME280.h> //https://github.com/adafruit/Adafruit_BME280_Library
Adafruit_BME280 bme;

Ticker flipper;

const char* ssid     = "WiFi_name";
const char* password = "WiFi_password";

const char* host = "narodmon.ru";
const int httpPort = 8283;

const int interval = 10*60; // 10 minutes

int tm = interval;
int deviceCount = 0;

void flip(){
  tm--;
  //Serial.println(tm);
}

void setup() {

  Wire.begin();
  Serial.begin(115200);
  lightMeter.begin();
  bme.begin();
  // Start timer
  flipper.attach(1, flip);
}

//---------Sending data to https://narodmon.ru/--------------------------------

void Send() {

// Connecting to Wi-Fi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

// Sending to Serial data of Wi-Fi connection
  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());
  Serial.println();

  // Connecting to server
  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;

  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
     //return;
  }

  // Sending data
  // Data sending API you can find on the website naroddmon.ru in the Help section
  Serial.println("Sending...");
  client.print("#");
  client.print(WiFi.macAddress()); // Sending MAC of ESP8266
  client.print("#");
  client.print("NodeMCU+BME280+BH1750"); // Device name
  client.print("#");
  client.print("you latitude"); // Location of the sensor (latitude)
  client.print("#");
  client.print("you longitude"); // Location of the sensor (longitude)
  client.print("#");
  client.print("225");
  client.println();
  client.print("#");
  client.print("T1"); // Sensor type. T - temperature, 1 - device number
  client.print("#");
  client.print(bme.readTemperature());
  client.println();
  client.print("#");
  client.print("H1"); // Sensor type. H - humidity, 1 - device number
  client.print("#");
  client.print(bme.readHumidity());
  client.println();
  client.print("#");
  client.print("P1"); // Sensor type. P - pressure, 1 - device number
  client.print("#");
  client.print(bme.readPressure() / 100.0F);
  uint16_t lux = lightMeter.readLightLevel(); // Get illumination data from BH1750
  client.println();
  client.print("#");
  client.print("L1"); // Sensor type. L - lightMeter, 1 - device number
  client.print("#");
  client.print(lux);
  client.println();
  client.println("##");

  delay(10);

  Serial.print("Requesting: ");
  while(client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
      }

  client.stop();
  Serial.println();
  Serial.println("Closing connection");
  WiFi.disconnect();
  Serial.println("Disconnect WiFi.");

}

void loop() {
 if (tm == 0){                        // if the timer is over
    flipper.detach();                 // disable
    tm = interval;                    // reset the timer variable
    delay(10);
    Send();                           // sending
    flipper.attach(1, flip);          // turn on the timer interrupt
  }


}
