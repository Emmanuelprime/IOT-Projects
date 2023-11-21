#include <WiFi.h>

char ssid[] = "Starlink Of Rain"; 
char psw[] = "Rainigeria.";  
const char* flask_server_ip = "192.168.1.56";
int led_pin = 1;
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid,psw);
  while(WiFi.status()!= WL_CONNECTED){
    delay(1000);
    Serial.println("Connecting to Wifi .....");
  }
  Serial.println("Connected to Wifi");
  pinMode(led_pin,OUTPUT);
  digitalWrite(led_pin,LOW);

}

void loop() {
  if (request_to_server(flask_server_ip, "/toggle")) {
    delay(5000); 
  }
}

bool request_to_server(const char* server, const char* endpoint) {
  WiFiClient client;

  if (!client.connect(server, 5000)) {
    Serial.println("Failed to connect to the given server");
    return false;
  }
  client.print("POST ");
  client.print(endpoint);
  client.println(" HTTP/1.1");
  client.println("Host: " + String(server));
  client.println("Connection: close");
  client.println();

  Serial.println("Request sent to server");
  while (client.connected()) {
    if (client.available()) {
      String response = client.readStringUntil('\r');
      Serial.println(response);
      if (response.indexOf("200 OK") != -1) {
        int led_state = digitalRead(led_pin);
        digitalWrite(led_pin, !led_state);
        return true;
      }
    }
  }

  Serial.println("Server did not respond properly");
  return false;
}
