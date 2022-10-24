
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include "max6675.h"
#include <SPI.h>

// const char* ssid = "KEI123";
// const char* password = "4qe%T#.QL+9=8$r";
////////////////////////////////////
const char* ssid = "LT 1C";
const char* password = "kost3";
//Local DEPLOY
// const char* mqtt_server = "192.168.11.124"; // Local IP address of Raspberry Pi
// const char* mqtt_server = "192.168.1.144";
// const char* mqtt_username = "kei124";
// const char* mqtt_pass = "1234";

// Set your Static IP address
// IPAddress staticIP(192, 168, 11, 132);
// // Set your Gateway IP address
// IPAddress gateway(192, 168, 11, 254);

// IPAddress subnet(255, 255, 255, 0);
// IPAddress dns(210, 145, 254, 162);   //optional

//Public TRY
// Add your MQTT Broker IP address, example:

const char *mqtt_server = "utilitydemo.colinn.id";
const char *mqtt_username = "demo";
const char *mqtt_password = "demo123";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
char temp1[50];

//SPI Bus 1 Init(VSPI)
int CLK = 18;
int SO = 19;
int CS1 = 5;
// int CS2 = 17;
// int CS3 = 16;
//SPI Bus 2 Init(HSPI)
// int CLK = 14;
// int SO = 12;
// int CS1 = 15;
// int CS4 = ;
// int CS5 = ;
// int CS6 = ;

MAX6675 temp_sensor1(CLK, CS1, SO);
// MAX6675 temp_sensor2(CLK, CS2, MISO);
// MAX6675 temp_sensor3(CLK, CS3, MISO);
// MAX6675 temp_sensor4(CLK, CS4, MISO);
// MAX6675 temp_sensor5(CLK, CS5, MISO);
// MAX6675 temp_sensor6(CLK, CS6, MISO);

// LED Pin
const int ledPin[2] = {14,27};
//Temp Reading
// float temp_raw;
// float Temp_Mapped[];

//Convert
// Temp_Conv = map(val, 0, 1023, 0, 255);

void setup()
{
    Serial.begin(115200);

    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);

    for (uint8_t i = 0; i <= 1; i++)
    {
        pinMode(ledPin[i],OUTPUT);
    }
    

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

    if (String(topic) == "esp32/output")
    {
        Serial.print("Changing output to ");
        if (messageTemp == "on")
        {
            Serial.println("on");
            digitalWrite(ledPin[0], HIGH);
            digitalWrite(ledPin[1], HIGH);
        }
        else if (messageTemp == "off")
        {
            Serial.println("off");
            digitalWrite(ledPin[0], LOW);
            digitalWrite(ledPin[1], LOW);
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
            client.subscribe("esp32/output");
            client.subscribe("esp32/st1");
            client.subscribe("esp32/st2");
            client.subscribe("esp32/st3");
            client.subscribe("esp32/st4");
            client.subscribe("esp32/st5");
            client.subscribe("esp32/st6");
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
    if (now - lastMsg > 5000)
    {
        // temperature = module.readCelsius()+10; //why add 10??
        float temperature1 = temp_sensor1.readCelsius();
        dtostrf(temperature1, 4, 2, temp1);
        lastMsg = now;
      
      
        // String Test_json = "[{\"temp1\": "+temp1+"}]";
        String Test_json2 = "[{\"temp1\": " + String(temp1) + "},{\"temp2\": " + String(temp1) + "},{\"temp3\": " + String(temp1) + "},{\"temp4\": " + String(temp1) + "},{\"temp5\": " + String(temp1) + "},{\"temp6\": " + String(temp1) + "}]";
        // String Temp_json = "[ { \"temp\": " + Temp_Mapped[0] + " }, { \"temp\": " + Temp_Mapped[1] + " }, { \"temp\": " + Temp_Mapped[2] + " }, { \"temp\": " + Temp_Mapped[3] + " }, { \"temp\": " + Temp_Mapped[4] + "}, { \"temp\": " + Temp_Mapped[5] + " } ]";

        client.publish("esp32/temperature", Test_json2.c_str());
        // client.publish("esp32/temperature", Temp_json.c_str());


    }
}