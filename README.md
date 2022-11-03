# Sensbey Temperature Control Module

Simple IOT Module to control 6 heaters (Relays) based on ESP32
Monitor 6 temperature sensors using MAX6675 modules, split into 2 SPI Buses

### GPIO Pins
- Digital Out: 

        Heater 1 = 23
        Heater 2 = 22
        Heater 3 = 21
        Heater 4 = 4 
        Heater 5 = 2
        Heater 6 = 15
- SPI 1, 3 sensors:

        CLK = 18
        SO = 19
        CS1 = 5
        CS2 = 17
        CS3 = 16
- SPI 2, 3 sensors:

        H_CLK = 14
        H_SO = 12
        CS4 = 27
        CS5 = 26
        CS6 = 25
        
## Installation

Please install prerequisite 
- Grafana, >= 8.5.4
- MySQL (Or use existing MySQL Server)
- MQTT Broker (Or use existing MQTT Broker)
- Docker

### Grafana Installation
```sh
sudo apt update
sudo apt install -y adduser libfontconfig1
wget https://dl.grafana.com/enterprise/release/grafana-enterprise-rpi_8.5.11_armhf.deb
sudo dpkg -i grafana-enterprise-rpi_8.5.11_armhf.deb
```

open <IP_ADDRESS>:3000 on your browser
default username/password : admin/admin
Feel free to change default password at this step, make sure not to lose the new password


### MySQL Installation
```sh
sudo apt install mariadb-server
```
Run the following command to begin the MySQL securing process.

```sh
sudo mysql_secure_installation
```
Just follow the prompts to set a password for the root user and to secure your MySQL installation.
For a more secure installation, you should answer “Y” to all prompts when asked to answer “Y” or “N“.
**Make sure you write down the password you set during this process!**

### MQTT Installation
Follow installation steps on this [PAGE]

[PAGE]: <https://randomnerdtutorials.com/how-to-install-mosquitto-broker-on-raspberry-pi/>

### Docker (Raspbian)
Uninstall older version Docker is installed
```sh
sudo apt-get remove docker docker-engine docker.io containerd runc
```
Install using convenience script
```sh
curl -fsSL https://get.docker.com -o get-docker.sh
DRY_RUN=1 sudo sh ./get-docker.sh
```
Grant root level privileges to docker
```sh
sudo groupadd docker
sudo usermod -aG docker $USER
newgrp docker
```
Verify you can start docker withot sudo
```sh
docker run hello-world
```
### Download and Run Sensbey-Nodered
**This will download, install and configure nodered and the flows**
```sh
docker run -itd -p 1880:1880 --name Sensbey-Nodered michaeljuan97/sensbey_temp-monitoring
```

## Configuration
Make sure you can access Nodered (port 1880) and Grafana (port 3000)
- Nodered
    1.  Configure MQTT Broker, Topic, and MYSQL server

- Grafana
    1. Login with your username and password
    2. Import Grafana Dashboard JSON
    3. Edit Control Panel, change with IP address of Nodered
