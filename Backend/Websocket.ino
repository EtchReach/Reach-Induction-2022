#include <WiFi.h>
#include <WebSocketClient.h>
#include "Credentials.h"
 
const char* ssid     = mySSID;
const char* password = myPASSWORD;
 
char path[] = "/echo";
char host[] = "172.20.10.3";
 
WebSocketClient webSocketClient;
WiFiClient client;

void connnect(){
   if (client.connect(host, 5000)) {
    Serial.println("Connected");
  } else {
    Serial.println("Connection failed.");
  }
 
  webSocketClient.path = path;
  webSocketClient.host = host;
  if (webSocketClient.handshake(client)) {
    Serial.println("Handshake successful");
  } else {
    Serial.println("Handshake failed.");
  }
}
void setup() {
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 
  delay(5000);
 
 connnect();
 
}
 
void loop() {
  String data;
 
  if (client.connected()) {
 
//    webSocketClient.sendData("Info to be echoed back");
 
    webSocketClient.getData(data);
    if (data.length() > 0) {
      Serial.print("Received data: ");
      Serial.println(data);
    }
 
  } else {
    Serial.println("Client disconnected.");
    connnect();
  }
 
  delay(3000);
 
}
