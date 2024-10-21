#include <WiFi.h>

const char* ssid = "Pari";
const char* password = "12344321";
const char* host = "198.168.1.100";
const int port = 80;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  WiFiClient client;
  if (client.connect(host, port)) {
    int wifi_rssi = WiFi.RSSI();
    float radio_rssi = wifi_rssi - 10 * log10(20) + 2.15; // convert to radio RSSI
    Serial.print("WiFi RSSI: ");
    Serial.print(wifi_rssi);
    Serial.print(" dBm, Radio RSSI: ");
    Serial.print(radio_rssi);
    Serial.println(" dBm");
  }
  else {
    Serial.println("Connection failed");
  }
   delay(1000);
}
