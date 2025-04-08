# Hodor!

![hodor](https://media3.giphy.com/media/v1.Y2lkPTc5MGI3NjExYm5haXk1ZHdqdGdocW84cHhkNDE1NXc5anczY2h2Yms4Zm9mb21kayZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/1002qxOu222y0E/giphy.gif)

This ESP32 app shorts a door latch trigger via HTTP.

## Getting started

You will need to create a `secrets.h` file, before you can deploy code to your board:

```hpp
// secrets.h
const char* ssid = "";       // your network SSID (name)
const char* pass = "";       // your network password
const String secretKey = "";  // the path that needs to be called to trigger the door, like http://MY-IP/SECRET_KEY
```
