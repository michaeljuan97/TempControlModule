# Sensbey Temperature Control Module

Simple IOT Module to control 6 heaters (Relays) based on ESP32
Monitor 6 temperature sensors using MAX6675 modules, split into 2 SPI Buses

### GPIO Pins
- Digital Out: 

        Heater 1 : 23
        Heater 2 : 22
        Heater 3 : 21
        Heater 4 : 4 
        Heater 5 : 2
        Heater 6 : 15
- SPI 1, 3 sensors (SAME CLK & SO PIN):

        CLK : 18
        SO : 19
        CS1 : 5
        CS2 : 17
        CS3 : 16
- SPI 2, 3 sensors (SAME H_CLK & H_SO PIN):

        H_CLK : 14
        H_SO : 12
        CS4 : 27
        CS5 : 26
        CS6 : 25
