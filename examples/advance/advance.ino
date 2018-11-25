#include <WiFiMan.h>

Config conf;

void setup() 
{
    //create default object with authentication,serial control.Authentication and serial control can be set with WiFiMan(bool authentication,bool serialControl); or enable later (read below)
    WiFiMan wman = WiFiMan();
  
    //clear all config (delete config.json)
    //wman.deleteConfig();
    
    //set serial control. during config mode , device can be config via serial command
    wman.setSerialControl(true);

    //enable webserver authentication.If the username and password are not set , ap will use default value "admin":"password"
    wman.setAuthentication(true);
    //set username to login (this CANNOT be change later).default is "admin"
    wman.setMasterUsername("user");
    //set password use in the first time login.This can be changed in config menu.Default is "password"
    wman.setDefaultMasterPasswd("httpPassword");

    //force config mode .Device will skip auto connect and jump straid into softAP mode(config portal)
    //wman.forceApMode();

    //Change WebUI of config portal with custom device info
    wman.setWebUi("Page title","page banner","build : 0.01","Branch : master","device type : esp8266","page footer");
    //Change WebUI of config portal,deviceInfo will be fill with chipID
    //wman.setWebUi("Page title","page banner","build : 0.01","Branch : master","page footer");
    //set text of the help page
    wman.setHelpInfo("This is the help page");

    //set ap ip/gateway/subnet . default is 192.168.1.1/192.168.1.1/255.255.255.0
    wman.setApConfig(IPAddress(192, 168, 1, 1),IPAddress(192, 168, 1, 1),IPAddress(255, 255, 255, 0));
    //set max connect attempt, default is 36
    wman.setMaxConnectAttempt(50);
    //set timeout of AP mode (min), server will turnoff after timeout.default is 15 mins
    wman.setConfigTimeout(10);
    //set default ap SSID .in ap mode, SSID will be <apName>+<chipID> .Default is esp8266-idxxxxxx
    wman.setApName("DeviceNo");
    //set softAP password , if password is blank, the will be set without password
    wman.setApPasswd("apPassword");
    
    //config commands must be called before start
    wman.start();

    //wman.getConfig(&conf) will return false if connect failed or config portal timeout
    if(wman.getConfig(&conf))
    {
        //display device status
        Serial.println("Connected to AP");
        Serial.print("SSID : ");
        Serial.println(conf.wifiSsid);
        Serial.print("Passwd : ");
        Serial.println(conf.wifiPasswd);
        Serial.print("MQTT server : ");
        Serial.println(conf.mqttAddr);
        Serial.print("MQTT password : ");
        Serial.println(conf.mqttPasswd);
        Serial.print("MQTT username : ");
        Serial.println(conf.mqttUsername);
        Serial.print("MQTT Id : ");
        Serial.println(conf.mqttId);
        Serial.print("Sub topic : ");
        Serial.println(conf.mqttSub);
        Serial.print("Pub topic : ");
        Serial.println(conf.mqttPub);
        Serial.print("MQTT port : ");
        Serial.println(conf.mqttPort);
        Serial.print("Master password : ");
        Serial.println(conf.masterPasswd);
        Serial.print("Device mDNS name : ");
        Serial.println(conf.mdnsName);
        Serial.print("IP : ");
        Serial.println(conf.localIP);
    }
}

void loop() 
{
  //
}