# Air quality meter
Air quality meter using of-the-shelf components to measure dust particles, CO2, benzene and other nasty stuff.

# Prerequisites
- [Visual Studio Community](https://www.visualstudio.com/vs/community/)
- [Visual Micro](http://www.visualmicro.com)
- [Arduino core for ESP8266](https://github.com/esp8266/Arduino)

# Hardware
- [Wemos D1 Mini Lite](https://www.tinytronics.nl/shop/nl/arduino/wemos/wemos-d1-mini-lite-esp8285-ch340)
- [SDS-011 dust sensor](https://www.tinytronics.nl/shop/nl/sensoren/temperatuur-lucht-vochtigheid/nova-sds011-hoge-precisie-laser-stofsensor?search=sds011)
- [3x TM1637 4-digit display](https://www.tinytronics.nl/shop/nl/verlichting/led-segment-display/robotdyn-segmenten-display-module-4-karakters-decimalen-wit-tm1637?search=tm1637)
- [MQ-135 gas sensor](https://www.tinytronics.nl/shop/nl/sensoren/temperatuur-lucht-vochtigheid/mq-135-gas-sensor-module?search=mq-135)
- breadboard
- wires, [male to male](https://www.tinytronics.nl/shop/nl/kabels/prototype-draden/dupont-jumper-draad-male-male-10cm-10-draden) and [male to female](https://www.tinytronics.nl/shop/nl/kabels/prototype-draden/dupont-jumper-draad-male-female-10cm-10-draden)
- enclosure, I used a cardboard box of 8cm x 21cm x 15cm
- power bank, with a USB cable that ends in a micro-USB connector
- stuff to attach the MQ-135 and displays to the enclosure. I used some electric wire (see photos).

# Schematic

![Fritzing](https://github.com/samegens/airqualitymeter/raw/master/Fritzing/fritzing.png "Fritzing")

# Software

1. Open AirQualityMeter.sln in Visual Studio.
2. Adjust the brightness of the digits to your liking (search for `setBacklight` in AirQualityMeter.ino).
3. If you're using different pins than indicated in the schematic, change the the pin definitions in AirQualityMeter.ino.
4. Select 'Wemos D1 mini Lite' in the board drop-down.
5. Select the correct COM port.
6. Build and upload. You might need to remove the D1 from the breadboard when uploading, I sometimes got a sync error with the D1 on the breadboard and everything connected.

# End result

![front](https://github.com/samegens/airqualitymeter/raw/master/images/front.jpg "Front")

![side](https://github.com/samegens/airqualitymeter/raw/master/images/side.jpg "Side")

![inside](https://github.com/samegens/airqualitymeter/raw/master/images/inside.jpg "Inside")
