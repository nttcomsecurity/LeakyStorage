# LeakyStorage
A USB key based on a Teensy 2, a SD adaptor and an ESP8266. Aim is to leak files on the USB key on a CNC.

# Installation

On Arduino: solder an SD Adaptor () on Teensy 2 or Teensy 2++ (). Then solder an ESP8266.
On Arduino computer: install Teensyduino () and ESP8266AT.
On CNC Server: install PHP and put upload.php file on it.

For demo you can use a Raspberry Pi as CNC server and Wi-Fi access point. For access point follow this instructions : https://learn.adafruit.com/setting-up-a-raspberry-pi-as-a-wifi-access-point/install-software. For CNC server : sudo apt-get install apache php5.
 
