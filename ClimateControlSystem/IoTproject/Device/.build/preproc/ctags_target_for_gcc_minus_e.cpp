# 1 "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino"
# 1 "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino"
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. 
// To get started please visit https://microsoft.github.io/azure-iot-developer-kit/docs/projects/remote-monitoring/?utm_source=ArduinoExtension&utm_medium=ReleaseNote&utm_campaign=VSCode
# 5 "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino" 2
# 6 "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino" 2
# 7 "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino" 2
# 8 "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino" 2
# 9 "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino" 2
# 10 "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino" 2
# 11 "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino" 2
# 12 "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino" 2



static bool isConnected = false;

DevI2C *ext_i2c;
HTS221Sensor *ht_sensor;
LPS22HBSensor *lp_sensor;

char wifiBuff[128];

float temperature = 50;
char temperatureUnit = 'F';
float humidity = 50;
char humidityUnit = '%';
float pressure = 55;
const char *pressureUnit = "psig";

const char *roomSchema = "chiller-sensors;v1";
const char *interval = "00:00:05";
const char *deviceType = "Chiller";
const char *deviceFirmware = "1.0.0";
const char *deviceFirmwareUpdateStatus = "";
const char *deviceLocation = "Madrid";
const double deviceLatitude = 40.418371;
const double deviceLongitude =-3.797997;



const char *twinProperties="{\"Protocol\": \"MQTT\", \"SupportedMethods\": \"Reboot,FirmwareUpdate,LedColor\", \"Telemetry\": { \"%s\": {\"Interval\": \"%s\",\"MessageTemplate\": \"{\\\"temperature\\\":${temperature},\\\"temperature_unit\\\":\\\"${temperature_unit}\\\", \\\"humidity\\\":${humidity},\\\"humidity_unit\\\":\\\"${humidity_unit}\\\",\\\"pressure\\\":${pressure},\\\"pressure_unit\\\":\\\"${pressure_unit}\\\"}\",\"MessageSchema\": {\"Name\": \"%s\",\"Format\": \"JSON\",\"Fields\": {\"temperature\": \"Double\", \"temperature_unit\": \"Text\",\"humidity\": \"Double\",\"humidity_unit\": \"Text\",\"pressure\": \"Double\",\"pressure_unit\": \"Text\" } } } },\"Type\": \"%s\",\"Firmware\": \"%s\",\"Model\":\"AZ3166\",\"FirmwareUpdateStatus\": \"%s\",\"Location\": \"%s\",\"Latitude\": %f,\"Longitude\": %f}";

bool sendDeviceInfo()
{
  char reportedProperties[2048];
  snprintf(reportedProperties,2048, twinProperties,roomSchema, interval ,roomSchema,deviceType,deviceFirmware,deviceFirmwareUpdateStatus,deviceLocation,deviceLatitude,deviceLongitude);
  return DevKitMQTTClient_ReportState(reportedProperties);
}

void twinCallback(DEVICE_TWIN_UPDATE_STATE updateState, const unsigned char *payLoad, int length){
  do{{ if (0) { (void)printf("*** Twin State: %s",updateState?"Complete":"Partial"); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 51 "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino" 3 4
 __null
# 51 "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino"
 ) l(AZ_LOG_INFO, "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino", __func__, 51, 0x01, "*** Twin State: %s",updateState?"Complete":"Partial"); } }; }while((void)0,0);
}

RGB_LED rgbLed;
uint8_t colors[][3] = {
        {255, 0, 0}, // red
        {0, 255, 0}, // green
        {0, 0, 255}, // blue
        {0, 0, 0},
        {255, 255, 0},
        {0, 255, 255},
        {255, 0, 255},
        {255, 255, 255}
    };
uint8_t colorindex;
bool doReset=false;

int device_method_callback(const char *methodName, const unsigned char *payload, int length, unsigned char **response, int *responseLength){

  do{{ if (0) { (void)printf("*** Remote method: %s",methodName); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 70 "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino" 3 4
 __null
# 70 "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino"
 ) l(AZ_LOG_INFO, "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino", __func__, 70, 0x01, "*** Remote method: %s",methodName); } }; }while((void)0,0);

  if(strcmp(methodName,"LedColor")==0){
    int n=sizeof(colors)/sizeof(colors[0]);
    uint8_t *color=colors[(colorindex++)%n];
    rgbLed.setColor(color[0],color[1],color[2]);

    const char *ok="{\"result\":\"OK\"}";
    *responseLength=strlen(ok);
    *response = (unsigned char*)malloc(*responseLength);
    strncpy((char *)(*response), ok, *responseLength);
    return 200;
  }

  if(strcmp(methodName,"Reboot")==0){
    doReset=true;

    const char *reset="{\"result\":\"RESET\"}";
    *responseLength=strlen(reset);
    *response = (unsigned char*)malloc(*responseLength);
    strncpy((char *)(*response), reset, *responseLength);
    return 201;
  }

  do{ { if (0) { (void)printf("*** Remote method: %s not found",methodName); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 94 "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino" 3 4
 __null
# 94 "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino"
 ) l(AZ_LOG_ERROR, "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino", __func__, 94, 0x01, "*** Remote method: %s not found",methodName); } }; }while((void)0,0);
  return 500;
}

void InitWiFi()
{
  Screen.print("WiFi \r\n \r\nConnecting...\r\n             \r\n");

  if(WiFi.begin() == WL_CONNECTED)
  {
    IPAddress ip = WiFi.localIP();
    sprintf(wifiBuff, "WiFi \r\n %s\r\n %s \r\n \r\n",WiFi.SSID(),ip.get_address());
    Screen.print(wifiBuff);
    isConnected = true;
  }
  else
  {
    sprintf(wifiBuff, "WiFi  \r\n             \r\nNo connection\r\n                 \r\n");
    Screen.print(wifiBuff);
  }
}

void sendData(const char *data, const char *schema){
  time_t t = time(
# 117 "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino" 3 4
                 __null
# 117 "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino"
                     );
  char buf[sizeof "2011-10-08T07:07:09Z"];
  strftime(buf, sizeof buf, "%FT%TZ", gmtime(&t));

  EVENT_INSTANCE* message = DevKitMQTTClient_Event_Generate(data, MESSAGE);

  DevKitMQTTClient_Event_AddProp(message, "$$CreationTimeUtc", buf);
  DevKitMQTTClient_Event_AddProp(message, "$$MessageSchema", schema);
  DevKitMQTTClient_Event_AddProp(message, "$$ContentType", "JSON");

  DevKitMQTTClient_SendEventInstance(message);
}

void showSensors()
{
  try
  {
    ht_sensor->reset();
    ht_sensor->getTemperature(&temperature);
    //convert from C to F
    temperature = temperature*1.8 + 32;

    ht_sensor->getHumidity(&humidity);

    lp_sensor->getPressure(&pressure);

    char buff[128];
    sprintf(buff, "Environment \r\n Temp:%s%c    \r\n Humidity:%s%c  \r\n Atm: %s%s",f2s(temperature, 1),temperatureUnit, f2s(humidity, 1), humidityUnit, f2s(pressure,1), pressureUnit);
    Screen.print(buff);

    char sensorData[200];
    sprintf_s(sensorData, sizeof(sensorData), "{\"temperature\":%s,\"temperature_unit\":\"%c\",\"humidity\":%s,\"humidity_unit\":\"%c\",\"pressure\":%s,\"pressure_unit\":\"%s\"}", f2s(temperature, 1), temperatureUnit,f2s(humidity, 1), humidityUnit,f2s(pressure, 1), pressureUnit);
    sendData(sensorData,roomSchema);
  }
  catch(int error)
  {
    do{ { if (0) { (void)printf("*** Read sensor failed: %d",error); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 153 "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino" 3 4
   __null
# 153 "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino"
   ) l(AZ_LOG_ERROR, "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino", __func__, 153, 0x01, "*** Read sensor failed: %d",error); } }; }while((void)0,0);
  }
}

void setup() {

  ext_i2c = new DevI2C(D14, D15);

  ht_sensor = new HTS221Sensor(*ext_i2c);
  ht_sensor->init(
# 162 "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino" 3 4
                 __null
# 162 "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino"
                     );

  lp_sensor= new LPS22HBSensor(*ext_i2c);
  lp_sensor->init(
# 165 "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino" 3 4
                 __null
# 165 "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino"
                     );

  //Scan networks and print them into console
  int numSsid = WiFi.scanNetworks();
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
     Serial.print(thisNet);
     Serial.print(") ");
     Serial.print(WiFi.SSID(thisNet));
     Serial.print("\tSignal: ");
     Serial.print(WiFi.RSSI(thisNet));
     Serial.print("\tEnc type: ");
     Serial.println(WiFi.encryptionType(thisNet));
  }

  InitWiFi();

  if (isConnected)
  {
    // Microsoft collects data to operate effectively and provide you the best experiences with our products. 
    // We collect data about the features you use, how often you use them, and how you use them.
    send_telemetry_data_async("", "RemoteMonitoringSetupV2", "");

    //setup the MQTT Client
    DevKitMQTTClient_SetDeviceMethodCallback(&device_method_callback);
    DevKitMQTTClient_SetDeviceTwinCallback(&twinCallback);
    DevKitMQTTClient_SetOption("MiniSolution", "RemoteMonitoringV2");
    DevKitMQTTClient_Init(true); //set to true to use twin

    // Send the Twin data for the Remote Monitoring
    bool infoSent=sendDeviceInfo();
    do{{ if (0) { (void)printf("*** Twin update: %s",infoSent?"yes":"no"); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 195 "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino" 3 4
   __null
# 195 "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino"
   ) l(AZ_LOG_INFO, "/Users/bradygaster/Documents/IoTWorkbenchProjects/examples/devkit_remotemonitoring/Device/RemoteMonitoringV2.ino", __func__, 195, 0x01, "*** Twin update: %s",infoSent?"yes":"no"); } }; }while((void)0,0);
  }
}



static uint64_t send_interval_ms;
static uint64_t reset_interval_ms;

void loop() {
  // put your main code here, to run repeatedly:
  if(isConnected)
  {
    if((int)(SystemTickCounterRead() - send_interval_ms)>5000)
    {
      showSensors();
      send_interval_ms = SystemTickCounterRead();
    }

    if((int)(SystemTickCounterRead() - reset_interval_ms)>5000){
      if(doReset){
         __NVIC_SystemReset();
      }
      reset_interval_ms = SystemTickCounterRead();
    }
  }
}
