/* ESP8266 TO PY: LOCAL
 * Written by Junicchi
 * https://github.com/Kebablord 
 *Edited and modified to transfer full duplex
 *https://github.com/wahajmurtaza/

 * MAP
 - start(ssid,password)---> Starts the connection with given username and password
 - waitUntilNewReq() -----> Waits until a request is received from python
 - returnThisInt(data) ---> sends your Integer data to localhost
 - returnThisStr(data) ---> sends your String data to localhost
 - getPath() -------------> gets the request's path as string, ex: https://192.113.133/here -> "/here"
*/

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>

// OUR SERVER'S PORT, 80 FOR DEFAULT
WiFiServer server(80);
WiFiClient client;
String rule;

void start(String ssid, String pass){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(),pass.c_str());

  Serial.println("");
// Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  if (!MDNS.begin("esp8266")) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");
  server.begin();
  Serial.println("TCP server started");
  MDNS.addService("http", "tcp", 80);
}

bool isReqCame = false;

bool CheckNewReq(){
  client = server.available();
  if (!client) {
    return 0;
  }
/*
  while (client.connected() && !client.available()) {
    delay(1);
  }*/           //to make data transfer fast
  String req = client.readStringUntil('\r');
  int addr_start = req.indexOf(' ');
  int addr_end = req.indexOf(' ', addr_start + 1);
  if (addr_start == -1 || addr_end == -1) {
    Serial.print("Invalid request: ");
    Serial.println(req);
    return 0;
  }
  req = req.substring(addr_start + 1, addr_end);

  
  rule = req; 
  isReqCame = true;
  
  client.flush();
  return 1;
}
void waitUntilNewReq(){
  do {CheckNewReq();} while (!isReqCame);
  isReqCame = false;
}

void returnThisStr(String final_data){
  String s;
  client.print(final_data);
}
void returnThisInt(int final_data){
  returnThisStr(String(final_data));
}

String getPath(){
  return rule;
}
