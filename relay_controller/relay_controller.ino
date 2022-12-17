#include <ArduinoJson.h>

#include <WiFi.h>
#include <PubSubClient.h>

//WIFI Config
const char *ssid = "LT 1C";
const char *password = "kost3";

// Set your Static IP address
// IPAddress staticIP(192, 168, 11, 132);
//Set your Gateway IP address
// IPAddress gateway(192, 168, 11, 254);
// IPAddress subnet(255, 255, 255, 0);
// IPAddress dns(210, 145, 254, 162);   //optional

//MQTT Config
const char *mqtt_server = "utilitydemo.colinn.id";
const char *mqtt_username = "demo";
const char *mqtt_password = "demo123";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];

// Heater Pin
const int HeaterPin[6] = {23,22,21,4,2,15};
const int TempControlPin[6] = {32,33,25,26,27,14};



void setup()
{
    Serial.begin(115200);

    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);

    for (uint8_t i = 0; i <= 6; i++)
    {
        pinMode(HeaterPin[i], OUTPUT);
//        digitalWrite(HeaterPin[i], HIGH);
        
        pinMode(TempControlPin[i], OUTPUT);
//        digitalWrite(TempControlPin[i], HIGH);
    }
//    for (uint8_t i = 0; i <= 6; i++)
//    {
//        pinMode(TempControlPin[i], OUTPUT);
//        digitalWrite(HeaterPin[0], LOW);
//    }
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

    //Heater
    if (String(topic) == "sensbey/st1")
    {
        if (messageTemp == "ON")
        {
            digitalWrite(HeaterPin[0], LOW);
            Serial.print("Nyala 1");
        }
        else if (messageTemp == "OFF")
        {
            digitalWrite(HeaterPin[0], HIGH);
        }
    }
    if (String(topic) == "sensbey/st2")
    {
        if (messageTemp == "ON")
        {
            digitalWrite(HeaterPin[1], LOW);
            Serial.print("Nyala 2");
        }
        else if (messageTemp == "OFF")
        {
            digitalWrite(HeaterPin[1], HIGH);
        }
    }
    if (String(topic) == "sensbey/st3")
    {
        if (messageTemp == "ON")
        {
            digitalWrite(HeaterPin[2], LOW);
            Serial.print("Nyala 3");
        }
        else if (messageTemp == "OFF")
        {
            digitalWrite(HeaterPin[2], HIGH);
        }
    }
    if (String(topic) == "sensbey/st4")
    {
        if (messageTemp == "ON")
        {
            digitalWrite(HeaterPin[3], LOW);
            Serial.print("Nyala 4");
        }
        else if (messageTemp == "OFF")
        {
            digitalWrite(HeaterPin[3], HIGH);
        }
    }
    if (String(topic) == "sensbey/st5")
    {
        if (messageTemp == "ON")
        {
            digitalWrite(HeaterPin[4], LOW);
            Serial.print("Nyala 5");
        }
        else if (messageTemp == "OFF")
        {
            digitalWrite(HeaterPin[4], HIGH);
        }
    }
    if (String(topic) == "sensbey/st6")
    {
        if (messageTemp == "ON")
        {
            digitalWrite(HeaterPin[5], LOW);
            Serial.print("Nyala 6");
        }
        else if (messageTemp == "OFF")
        {
            digitalWrite(HeaterPin[5], HIGH);
        }
    }
    //Temp control module
    if (String(topic) == "sensbey/digitalTempControl1")
    {
        if (messageTemp == "ON")
        {
            digitalWrite(TempControlPin[0], LOW);
        }
        else if (messageTemp == "OFF")
        {
            digitalWrite(TempControlPin[0], HIGH);
        }
    }
    if (String(topic) == "sensbey/digitalTempControl2")
    {
        if (messageTemp == "ON")
        {
            digitalWrite(TempControlPin[1], LOW);
        }
        else if (messageTemp == "OFF")
        {
            digitalWrite(TempControlPin[1], HIGH);
        }
    }
    if (String(topic) == "sensbey/digitalTempControl3")
    {
        if (messageTemp == "ON")
        {
            digitalWrite(TempControlPin[2], LOW);
        }
        else if (messageTemp == "OFF")
        {
            digitalWrite(TempControlPin[2], HIGH);
        }
    }
    if (String(topic) == "sensbey/digitalTempControl4")
    {
        if (messageTemp == "ON")
        {
            digitalWrite(TempControlPin[3], LOW);
        }
        else if (messageTemp == "OFF")
        {
            digitalWrite(TempControlPin[3], HIGH);
        }
    }
    if (String(topic) == "sensbey/digitalTempControl5")
    {
        if (messageTemp == "ON")
        {
            digitalWrite(TempControlPin[4], LOW);
        }
        else if (messageTemp == "OFF")
        {
            digitalWrite(TempControlPin[4], HIGH);
        }
    }
    if (String(topic) == "sensbey/digitalTempControl6")
    {
        if (messageTemp == "ON")
        {
            digitalWrite(TempControlPin[5], LOW);
        }
        else if (messageTemp == "OFF")
        {
            digitalWrite(TempControlPin[5], HIGH);
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
            client.subscribe("sensbey/output");
            client.subscribe("sensbey/st1");
            client.subscribe("sensbey/st2");
            client.subscribe("sensbey/st3");
            client.subscribe("sensbey/st4");
            client.subscribe("sensbey/st5");
            client.subscribe("sensbey/st6");
            
            client.subscribe("sensbey/digitalTempControl1");
            client.subscribe("sensbey/digitalTempControl2");
            client.subscribe("sensbey/digitalTempControl3");
            client.subscribe("sensbey/digitalTempControl4");
            client.subscribe("sensbey/digitalTempControl5");
            client.subscribe("sensbey/digitalTempControl6");
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

        lastMsg = now;

    }
}
