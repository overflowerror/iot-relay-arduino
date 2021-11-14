#ifndef _IOT_RELAY_H_
#define _IOT_RELAY_H_

#include <ESP8266WiFi.h>

#define MAX_DATA_VALUES (10)
#define CONNECTION_TIMEOUT (2000)
#define CHECK_TIMEOUT (500)

class IotRelay {
    public:
      void begin(String addr, int port, String id, String loc);
      void connect(String ssid, String password);
      void add(String key, String value);
      int send();

    private:
      WiFiClient client;
      String addr;
      int port;
      String id;
      String loc;
      int size;
      String keys[MAX_DATA_VALUES];
      String values[MAX_DATA_VALUES];
};

#endif
