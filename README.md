EtherLED
========

Arduino web enabled contraption to interface with an LED matrix driver

Tested and working with the following components:
  - Arduino UNO R3
  - Official Arduino Ethernet shield
  - Embedded Adventures' PLT-1001 LED matrix driver
  - Embedded Adventures' LDP-8008 8x80 LED matrix

Instructions:
  - Connect Arduino pins 0 and 1 to the PLT-1001's TTL rx/tx pins
  - Connect ground from Arduino to PLT-1001's TTL ground pin
  - Connect 5v from Arduino to PLT-1001's TTL 5v pin
  - Change the IP address variable to work on your local LAN subnet
  - Load up the webpage by going to http://YourIP
  - Enter text to display in the text box and hit "PAINT"
  - Watch as the pretty text scrolls across the display
