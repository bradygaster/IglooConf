#include <Arduino.h>
#line 1 "/Users/bradygaster/source/IglooConf/RealTimeIoTMonitor/DeviceClient/IoTproject/Device/device.ino"
#line 1 "/Users/bradygaster/source/IglooConf/RealTimeIoTMonitor/DeviceClient/IoTproject/Device/device.ino"
#include "AZ3166WiFi.h"
#include "DevKitMQTTClient.h"

static bool hasWifi = false;
static bool hasIoTHub = false;

#line 7 "/Users/bradygaster/source/IglooConf/RealTimeIoTMonitor/DeviceClient/IoTproject/Device/device.ino"
void setup();
#line 28 "/Users/bradygaster/source/IglooConf/RealTimeIoTMonitor/DeviceClient/IoTproject/Device/device.ino"
void loop();
#line 7 "/Users/bradygaster/source/IglooConf/RealTimeIoTMonitor/DeviceClient/IoTproject/Device/device.ino"
void setup() {
  // put your setup code here, to run once:
  if (WiFi.begin() == WL_CONNECTED)
  {
    hasWifi = true;
    Screen.print(1, "Running...");

    if (!DevKitMQTTClient_Init())
    {
      hasIoTHub = false;
      return;
    }
    hasIoTHub = true;
  }
  else
  {
    hasWifi = false;
    Screen.print(1, "No Wi-Fi");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (hasIoTHub && hasWifi)
  {
    char buff[128];

    // replace the following line with your data sent to Azure IoTHub
    snprintf(buff, 128, "{\"topic\":\"iot\"}");
    
    if (DevKitMQTTClient_SendEvent(buff))
    {
      Screen.print(1, "Sending...");
    }
    else
    {
      Screen.print(1, "Failure...");
    }
    delay(2000);
  }
}

