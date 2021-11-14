#include <IotRelay.h>

const char* ssid = "wifi-ssid";
const char* password = "wifi-password";

const char* addr = "ip to iot relay server";
int port = 20159;
const char* id = "main-sensor";
const char* loc = "living-room";

IotRelay relay;

void setup() {
  Serial.begin(9600);
  
  relay.connect(ssid, password);
  relay.begin(addr, port, id, loc);
}

void loop() {
  relay.add("temp", String(31.415, 3));
  relay.add("humid", String(42));
  relay.send();

  delay(5000);
}
