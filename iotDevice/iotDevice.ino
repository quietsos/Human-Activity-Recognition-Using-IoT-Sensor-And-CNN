#include <PubSubClient.h>
#include "WiFi.h"
#include <Adafruit_Sensor.h>

// Wifi credentials
const char* ssid = "quiet";
const char* password =  "fuck you";

// Initialize the MQTT client
WiFiClient espClient;
PubSubClient client(espClient);

// Connect to the MQTT broker
const char *mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;

String datap ="Hello this is sohan" ;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  wifiConnect();
  client.setServer(mqtt_server, mqtt_port);
  mqttConnect();

}

void mqttConnect(){
  client.connect("esp32");
  while (!client.connected()) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("MQTT connected!");
}


void wifiConnect() {
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); //show ip address when connected on serial monitor.
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      //      // Subscribe
      //      client.subscribe("esp32/output");
//      client.publish("data", datap);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }

    
  }

}



void loop() {
//  if (!client.connected()) {
//    reconnect();
//  }
//  client.loop();

  
  client.publish("mytopic",datap.c_str());
  delay(1000);



}
