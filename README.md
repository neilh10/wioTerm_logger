# wioTerm_ntp
An example of using NTP to set a RTC on a Wio Terminal.   
This fork uses the internatl RTC

This example based on the Arduino WifiUdpNtpClient code. NTP servers can be called via name or ip address, use only servers that can
repsond to IPv4 requests. This is related to the Wifi stack on the Wio Terminal. 

This fork uses the IDE  PlatformIo 5 on VSC with 
https://docs.platformio.org/en/latest/boards/atmelsam/seeed_wio_terminal.html?utm_medium=piohome&utm_source=platformio

Orginal code was tested using the Arduino 1.8.13 IDE version.

## Dependencies
- Adafruit RTClib  - this fork removes external DS3231 requirements and uses internal RTC    

- millisDelay - needs to be installed in lib

    a library to provide non-blocking delays, primarily used inside the main loop. 
Details can be found here:  https://www.forward.com.au/pfod/ArduinoProgramming/TimingDelaysInArduino.html
