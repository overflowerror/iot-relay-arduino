#include "IotRelay.h"


void IotRelay::begin(String addr, int port, String id, String loc) {
  this->addr = addr;
  this->port = port;
  this->id = id;
  this->loc = loc;
  this->size = 0;
}

void IotRelay::connect(String ssid, String password) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void IotRelay::add(String key, String value) {
  keys[size] = key;
  values[size] = value;

  size++;
}

int IotRelay::send() {
  client.connect(addr, port);
  client.print("id=");
  client.print(id);
  client.print("\n");
  client.print("loc=");
  client.print(loc);
  client.print("\n");
  for(int i = 0; i < size; i++) {
    client.print(keys[i]);
    client.print("=");
    client.print(values[i]);
    client.print("\n");
  }
  client.print("\n");

  size = 0;

  unsigned long startTime = millis();
  while (client.available() < 3) {
    if (millis() - startTime > CONNECTION_TIMEOUT) {
      client.stop();
      return -1;
    }
    delay(CHECK_TIMEOUT);
  }

  if (client.read() != 'o' || client.read() != 'k') {
    client.stop();
    return -1;
  }

  client.stop();
  return 0;
}
