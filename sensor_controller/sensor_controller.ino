#include <ArduinoJson.h>

#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include "max6675.h"
#include <SPI.h>

//WIFI Config
const char *ssid = "LT 1C";
const char *password = "kost3";

// Set your Static IP address
// IPAddress staticIP(192, 168, 11, 132);
//Set your Gateway IP address
// IPAddress gateway(192, 168, 11, 254);
// IPAddress subnet(255, 255, 255, 0);
// IPAddress dns(210, 145, 254, 162);   //optional

StaticJsonBuffer<200> jsonBuffer;
char json[100];

//MQTT Config
const char *mqtt_server = "utilitydemo.colinn.id";
const char *mqtt_username = "demo";
const char *mqtt_password = "demo123";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
char temp1[50],temp2[50],temp3[50],temp4[50],temp5[50],temp6[50];

float calibrate1, calibrate2, calibrate3, calibrate4, calibrate5, calibrate6;
// SPI Bus 1 Init (Max 3 sensor di 1 bus)
int CLK = 18;
int SO = 19;
int CS1 = 5;
int CS2 = 17;
int CS3 = 16;
// SPI Bus 2 Init
 int H_CLK = 14;
 int H_SO = 12;
 int CS4 = 27;
 int CS5 = 26;
 int CS6 = 25;

MAX6675 temp_sensor1(CLK, CS1, SO);
MAX6675 temp_sensor2(CLK, CS2, SO);
MAX6675 temp_sensor3(CLK, CS3, SO);
MAX6675 temp_sensor4(H_CLK, CS4, H_SO);
MAX6675 temp_sensor5(H_CLK, CS5, H_SO);
MAX6675 temp_sensor6(H_CLK, CS6, H_SO);

void setup()
{
    Serial.begin(115200);

    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
    // pinMode(ledPin, OUTPUT);
    delay(500);
}

void setup_wifi()
{
    delay(10);

    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *message, unsigned int length)
{
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");
    String messageTemp;

    for (int i = 0; i < length; i++)
    {
        Serial.print((char)message[i]);
        messageTemp += (char)message[i];
    }
    Serial.println();

    if (String(topic) == "sensbey/calibtest")
    {
        Serial.print("Calibration Data");
            JsonObject &root = jsonBuffer.parseObject(messageTemp);
        if (!root.success())
        {
            Serial.println("parseObject() failed");
            return;
        } else {
            Serial.print("Sukses");

        }
        if(root.containsKey("calibration1")){
            calibrate1 = root["calibration1"];
            Serial.print(calibrate1);
            jsonBuffer.clear();

        }
        if(root.containsKey("calibration2")){
            calibrate2 = root["calibration2"];
            Serial.print(calibrate2);
            jsonBuffer.clear();
        }
        if(root.containsKey("calibration3")){
            calibrate3 = root["calibration3"];
            Serial.print(calibrate3);
            jsonBuffer.clear();
        }
        if(root.containsKey("calibration4")){
            calibrate4 = root["calibration4"];
            Serial.print(calibrate4);
            jsonBuffer.clear();
        }
        if(root.containsKey("calibration5")){
            calibrate5 = root["calibration5"];
            Serial.print(calibrate5);
            jsonBuffer.clear();
        }
        if(root.containsKey("calibration6")){
            calibrate6 = root["calibration6"];
            Serial.print(calibrate6);
            jsonBuffer.clear();
        }
    }
    
}


void reconnect()
{
    // Loop until we're reconnected
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect("ESP8266Client", mqtt_username, mqtt_password))
        {
            Serial.println("connected");
            // Subscribe
//            client.subscribe("sensbey/st1");
//            client.subscribe("sensbey/st2");
//            client.subscribe("sensbey/st3");
//            client.subscribe("sensbey/st4");
//            client.subscribe("sensbey/st5");
//            client.subscribe("sensbey/st6");
            client.subscribe("sensbey/calibtest");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void loop()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();

    long now = millis();
    if (now - lastMsg > 250)
    {
        float temperature1 = temp_sensor1.readCelsius()+calibrate1;
        float temperature2 = temp_sensor2.readCelsius()+calibrate2;
        float temperature3 = temp_sensor3.readCelsius()+calibrate3;
        float temperature4 = temp_sensor4.readCelsius()+calibrate4;
        float temperature5 = temp_sensor5.readCelsius()+calibrate5;
        float temperature6 = temp_sensor6.readCelsius()+calibrate6;
   
        dtostrf(temperature1, 4, 2, temp1);
        dtostrf(temperature2, 4, 2, temp2);
        dtostrf(temperature3, 4, 2, temp3);
        dtostrf(temperature4, 4, 2, temp4);
        dtostrf(temperature5, 4, 2, temp5);
        dtostrf(temperature6, 4, 2, temp6);
        lastMsg = now;

        String Temp_json = "[{\"temp1\": " + String(temp1) + "},{\"temp2\": " + String(temp2) + "},{\"temp3\": " + String(temp3) + "},{\"temp4\": " + String(temp4) + "},{\"temp5\": " + String(temp5) + "},{\"temp6\": " + String(temp6) + "}]";
        

        client.publish("sensbey/temperature", Temp_json.c_str());
    }
}
