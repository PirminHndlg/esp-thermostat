const char* ssid = "*******";
const char* password = "*******";

bool wifiLogin() {
  WiFi.mode(WIFI_STA);
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);

  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  unsigned long t = millis();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (t > 60000) {
      return false;
    }
  }
  Serial.println(" connected");
  Serial.print("local IP:");
  Serial.println(WiFi.localIP());

  return true;
}