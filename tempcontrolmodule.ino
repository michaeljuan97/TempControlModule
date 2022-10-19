
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include "max6675.h"
// #include <Adafruit_BME280.h>
// #include <Adafruit_Sensor.h>

// Replace the next variables with your SSID/Password combination
// const char *ssid = "Wokwi-GUEST";
// const char *password = "";

const char* ssid = "KEI123";
const char* password = "4qe%T#.QL+9=8$r";
//Local DEPLOY
const char* mqtt_server = "192.168.11.124"; // Local IP address of Raspberry Pi
const char* mqtt_username = "kei124";
const char* mqtt_pass = "1234";

// Set your Static IP address
IPAddress staticIP(192, 168, 11, 132);
// Set your Gateway IP address
IPAddress gateway(192, 168, 11, 254);

IPAddress subnet(255, 255, 255, 0);
IPAddress dns(210, 145, 254, 162);   //optional

//Public TRY
// Add your MQTT Broker IP address, example:
// const char* mqtt_server = "192.168.1.144";
// const char *mqtt_server = "utilitydemo.colinn.id";
// const char *mqtt_username = "demo";
// const char *mqtt_password = "demo123";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int temp = 0;

//SPI Init
int CLK = 14;
int MISO = 12;
//Temp Init
int CS1 = ;
int CS2 = ;
int CS3 = ;
int CS4 = ;
int CS5 = ;
int CS6 = ;

MAX6675 temp_sensor1(CLK, CS1, MISO);
MAX6675 temp_sensor2(CLK, CS2, MISO);
MAX6675 temp_sensor3(CLK, CS3, MISO);
MAX6675 temp_sensor4(CLK, CS4, MISO);
MAX6675 temp_sensor5(CLK, CS5, MISO);
MAX6675 temp_sensor6(CLK, CS6, MISO);

// LED Pin
const int ledPin = 4;
//Temp Reading
float temp_raw;
float Temp_Mapped[];

//Convert
Temp_Conv = map(val, 0, 1023, 0, 255);

void setup()
{
    Serial.begin(115200);

    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);

    pinMode(ledPin, OUTPUT);
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
            digitalWrite(ledPin, HIGH);
        }
        else if (messageTemp == "off")
        {
            Serial.println("off");
            digitalWrite(ledPin, LOW);
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
        temperature = module.readCelsius()+10;
        dtostrf(temperature, 4, 2, temp);
        lastMsg = now;
        //     int DI[DI_total], DI_prev[DI_total], DO[DO_total];
        // unsigned int DI_counter[DI_total];
        //  String DI_topic = device_name + "/view/DI";
        //       String DO_topic = device_name + "/view/DO";
        //       String AI_topic = device_name + "/view/AI";
        //       //      String DI_json, DO_json, AI_json;
        //       String DI_json = "[ { \"temp\": " + (String)DI[0] + ", \"counter\": " + (String)DI_counter[0] + " }, { \"temp\": " + (String)DI[1] + ", \"counter\": " + (String)DI_counter[1] + " }, { \"temp\": " + (String)DI[2] + ", \"counter\": " + (String)DI_counter[2] + " }, { \"temp\": " + (String)DI[3] + ", \"counter\": " + (String)DI_counter[3] + " }, { \"temp\": " + (String)DI[4] + ", \"counter\": " + (String)DI_counter[4] + " }, { \"temp\": " + (String)DI[5] + ", \"counter\": " + (String)DI_counter[5] + " } ]";
        //       String DO_json = "[ { \"temp\": " + (String)DO[0] + " }, { \"temp\": " + (String)DO[1] + " }, { \"temp\": " + (String)DO[2] + " }, { \"temp\": " + (String)DO[3] + " } ]";
        //       String AI_json = "[{\"temp\":" + (String)AI[0] + ",\"raw\":" + (String)AI_raw[0] + "},{\"temp\":" + (String)AI[1] + ",\"raw\":" + (String)AI_raw[1] + "},{\"temp\":" + (String)AI[2] + ",\"raw\":" + (String)AI_raw[2] + "},{\"temp\":" + (String)AI[3] + ",\"raw\":" + (String)AI_raw[3] + "},{\"temp\":" + (String)AI[4] + ",\"raw\":" + (String)AI_raw[4] + "},{\"temp\":" + (String)AI[5] + ",\"raw\":" + (String)AI_raw[5] + "}]";
        String Test_json = "[{\"temp1\": \"123\"}]";
        String Temp_json = "[ { \"temp\": " + Temp_Mapped[0] + " }, { \"temp\": " + Temp_Mapped[1] + " }, { \"temp\": " + Temp_Mapped[2] + " }, { \"temp\": " + Temp_Mapped[3] + " }, { \"temp\": " + Temp_Mapped[4] + "}, { \"temp\": " + Temp_Mapped[5] + " } ]";

        // Serial.print("Temperature: ");
        // Serial.println(tempString);
        // client.publish("esp32/temperature", tempString);
        client.publish("esp32/temperature", Test_json.c_str());
        client.publish("esp32/temperature", Temp_json.c_str());


    }
}