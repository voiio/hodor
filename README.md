# voiio Hodor!

This ESP32 app shorts a door latch trigger via HTTP.

## Getting started

You will need to create a `secrets.h` file, before you can deploy code to your board:

```hpp
// secrets.h
const char* ssid = "";       // your network SSID (name)
const char* pass = "";       // your network password
const String secretKey = "";  // the path that needs to be called to trigger the door, like http://MY-IP/SECET_KEY
```
