#include <WiFi.h>
#include "secrets.h"

WiFiServer server(80);
String header;
const int DOOR_PIN = D10;
// How long the latch signal will be send to the controller in ms.
const long LATCH_TIME = 100;
// Request timeout in ms.
const long TIMEOUT = 2000;
unsigned long currentTime = millis();
unsigned long previousTime = 0;


void setup() {
  Serial.begin(115200);
  pinMode(DOOR_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  initWiFi();
  server.begin();
}


void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  keepAliveWiFi();
  WiFiClient client = server.available();  // listen for incoming clients

  if (client) {  // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");                                         // print a message out in the serial port
    String currentLine = "";                                               // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= TIMEOUT) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {  // if there's bytes to read from the client,
        char c = client.read();  // read a byte, then
        Serial.write(c);         // print it out the serial monitor
        header += c;
        if (c == '\n') {  // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            if (header.indexOf("GET /" + secretKey) >= 0) {
              digitalWrite(DOOR_PIN, HIGH);
              digitalWrite(LED_BUILTIN, LOW);
              delay(LATCH_TIME);
              digitalWrite(DOOR_PIN, LOW);
            }
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else {  // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

void keepAliveWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection lost.");
    Serial.print("Reconnecting to WiFi ..");
  }
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.disconnect();
    WiFi.reconnect();
    waitForWiFi(30000);
  }
}

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  waitForWiFi(0);
}

unsigned int wifiTimer;

void waitForWiFi(int connetionTimeout) {

  wifiTimer = millis();
  while (WiFi.status() != WL_CONNECTED && connetionTimeout != 0 && wifiTimer + connetionTimeout > millis()) {
    Serial.print('.');
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
  }
  if (WiFi.status() != WL_CONNECTED) {
    return;
  }
  Serial.println(" Done!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("RRSI: ");
  Serial.println(WiFi.RSSI());
}
