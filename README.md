# voiio Hodor!

## Getting started

You will need to create a `secrets.h` file, before you can deploy code to your board:

```hpp
// secrets.h
char ssid[] = "";       // your network SSID (name)
char pass[] = "";       // your network password
char secretKey[] = "";  // the path that needs to be called to trigger the door, like http://MY-IP/SECET_KEY
```
