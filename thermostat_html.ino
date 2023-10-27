#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Arduino.h>
#include <DHT.h>
#include <AccelStepper.h>
#include <ArduinoJson.h>
#include <FS.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "index.h"
#include "calibrate.h"
#include "wifi.h"
#include "extensions.h"

#define motorPin1 D8
#define motorPin2 D7
#define motorPin3 D6
#define motorPin4 D5
#define DHTPIN D2
#define DHTTYPE DHT11
#define checkInterval 50000

#define fileTimeplan "/timeplan.json"
#define fileNormtemp "/normtemp.txt"
#define fileTempOffset "/tempoffset.txt"
#define fileStepperEnd "/stepperend.txt"
#define fileCurrentStepperPos "/stepperpos.txt"

#define HALFSTEP 8
#define utcOffsetInSeconds 7200

DHT dht(DHTPIN, DHTTYPE);
ESP8266WebServer server(80);
AccelStepper stepper(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

<<<<<<< HEAD
String processor(const String& var) {
  if (var == "TEMPERATURE") {
    return String(dht.readTemperature());
  } else if (var == "HUMIDITY") {
    return String(dht.readHumidity());
  }
  return String();
}

void setTemperature() {
}
=======
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

DynamicJsonDocument doc(1024);

int close = -20024;

float temp = 18;
float tempOffset = 0.0;
unsigned long lastCheck = -checkInterval;

void handleRoot() {
  String s = index_html;
  server.send(200, "text/html", s);
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

void handeCalibrate() {
  String s = calibrate_html;
  server.send(200, "text/html", s);
}

void handleGet() {
  String key = server.argName(0);
  String value = String(server.arg(0));

  Serial.print("get: " + key + " - " + value + ": ");

  if (key == "value") {
    String s = "";
    if (value == "ipadress") {
      const IPAddress& ipAddress = WiFi.localIP();
      s = String(ipAddress[0]) + String(".") + String(ipAddress[1]) + String(".") + String(ipAddress[2]) + String(".") + String(ipAddress[3]);
    } else if (value == "wifi") {
      s = String(ssid);
    } else if (value == "currenttemp") {
      s = String(dht.readTemperature() + tempOffset, 1) + "°C";
    } else if (value == "humidity") {
      s = String(int(dht.readHumidity())) + "%";
    } else if (value == "estimatedtemp") {
      s = String(temp, 1);
    } else if (value == "timeplan") {
      serializeJson(doc, s);
      Serial.println(s);
    } else if (value == "normaltemp") {
      File file = SPIFFS.open(fileNormtemp, "r");
      s = String(file.readStringUntil('\r').toFloat(), 1);
      file.close();
    } else if (value == "tempoffset") {
      s = String(tempOffset, 1);
    } else if (value == "pos") {
      s = String(stepper.currentPosition());
    } else if (value == "endpos") {
      s = String(close);
    }

    Serial.println(s);
    server.send(200, "text/plain", s);
  } else {
    server.send(404, "text/plain", "error");
  }
}

void handleSet() {

  if (server.args() == 0) {
    server.send(404, "text/plain", "error");
  }

  String key = server.argName(0);
  String value = server.arg(0);
  Serial.println("set: " + key + " - " + value);

  if (key == "temp") {
    temp = value.toInt();
    lastCheck = 0;
    if (stepper.distanceToGo() != 0) {
      stepper.moveTo(stepper.currentPosition());
    }
  } else if (key == "normaltemp") {
    File file = SPIFFS.open(fileNormtemp, "w");
    file.println(String(value));
    file.close();
  } else if (key == "pos") {
    if (value == "end") {
      stepper.moveTo(close);
    } else {
      stepper.moveTo(value.toInt());
    }
  } else if (key == "tempoffset") {
    tempOffset = value.toFloat();
    File file = SPIFFS.open(fileTempOffset, "w");
    file.println(String(value));
    file.close();
  } else if (key == "newend") {
    close = value.toInt();
    File file = SPIFFS.open(fileStepperEnd, "w");
    file.println(String(close));
    file.close();
  } else if (key == "newpos") {
    stepper.setCurrentPosition(value.toInt());
  } else if (key == "stepper") {
    if (value == "stop") {
      stepper.moveTo(stepper.currentPosition());
    }
  } else {
    server.send(404, "text/plain", "error");
  }
  server.send(200, "text/plain", "success");
}

void handleTimeplan() {
  if (server.argName(0) == "action" && server.arg(0) == "new") {
    doc.clear();
    Serial.println("clear");
    serializeJson(doc, Serial);
    Serial.println();
  } else if (server.args() > 1) {
    StaticJsonDocument<256> newdoc;
    newdoc["activ"] = toBoolean(server.arg("activ"));
    newdoc["start"] = server.arg("start");
    newdoc["end"] = server.arg("end");
    newdoc["temp"] = server.arg("temp");
    newdoc["days"] = serialized(server.arg("days"));
>>>>>>> 5f764b5 (files added)

doc[server.arg("n")] = newdoc;
serializeJson(newdoc, Serial);
Serial.println();
serializeJson(doc, Serial);
Serial.println();
}

File file = SPIFFS.open(fileTimeplan, "w");
serializeJson(doc, file);
file.close();

server.send(200, "text/plain", "success");
}

void setupServer() {
  server.on("/", handleRoot);
  server.on("/get", handleGet);
  server.on("/set", handleSet);
  server.on("/timeplan", handleTimeplan);
  server.on("/calibrate", handeCalibrate);
  server.onNotFound(handle_NotFound);

  server.begin();  //Start server
  Serial.println("HTTP server started");
}

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

void setup() {
  Serial.begin(115200);

  delay(200);

  stepper.setMaxSpeed(400);
  stepper.setAcceleration(200.0);
  stepper.setSpeed(100);

  pinMode(DHTPIN, INPUT);
  dht.begin();

  Serial.println("Mounting FS...");
  if (SPIFFS.begin()) {

    if (SPIFFS.exists(fileTimeplan)) {

      File file = SPIFFS.open(fileTimeplan, "r");
      delay(10);
      String file_content = file.readString();

      auto error = deserializeJson(doc, file_content);
      if (error) {
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(error.c_str());
        File file = SPIFFS.open(fileTimeplan, "a+");
        serializeJson(doc, file);
        file.close();
        serializeJson(doc, Serial);
      }
      serializeJson(doc, Serial);
      file.close();
    } else {
      File file = SPIFFS.open(fileTimeplan, "a+");
      serializeJson(doc, file);
      file.close();
      Serial.printf("New %s File Created...\n", fileTimeplan);
    }
  }

  if (SPIFFS.exists(fileNormtemp)) {
    File file = SPIFFS.open(fileNormtemp, "r");
    temp = file.readStringUntil('\r').toFloat();
    file.close();
  } else {
    File file = SPIFFS.open(fileNormtemp, "a+");
    file.println(temp);
    Serial.printf("New %s File Created...\n", fileNormtemp);
    file.close();
  }

  if (SPIFFS.exists(fileStepperEnd)) {
    File file = SPIFFS.open(fileStepperEnd, "r");
    close = file.readStringUntil('\r').toInt();
    file.close();
  } else {
    File file = SPIFFS.open(fileStepperEnd, "a+");
    file.println(close);
    Serial.printf("New %s File Created...\n", fileStepperEnd);
    file.close();
  }

  if (SPIFFS.exists(fileTempOffset)) {
    File file = SPIFFS.open(fileTempOffset, "r");
    tempOffset = file.readStringUntil('\r').toFloat();
    file.close();
  } else {
    File file = SPIFFS.open(fileTempOffset, "a+");
    file.println(0);
    Serial.printf("New %s File Created...\n", fileTempOffset);
    file.close();
  }

  if (SPIFFS.exists(fileCurrentStepperPos)) {
    File file = SPIFFS.open(fileCurrentStepperPos, "r");
    stepper.setCurrentPosition(file.readStringUntil('\r').toInt());
    file.close();
  } else {
    File file = SPIFFS.open(fileCurrentStepperPos, "a+");
    file.println(0);
    Serial.printf("New %s File Created...\n", fileCurrentStepperPos);
    file.close();
  }

  if (wifiLogin())
    setupServer();
}


void loop() {
  server.handleClient();

  if (millis() - lastCheck > checkInterval && stepper.distanceToGo() == 0) {
    //für aktuelle zeit nach temp checken
    timeClient.update();

    int j = 0;
    while (true) {
      if (!doc.containsKey(String(j)) || j > 99)
        break;

      Serial.println("____");

      serializeJson(doc, Serial);
      Serial.println();

      StaticJsonDocument<512> newdoc = doc[String(j)];

      if (!toBoolean(newdoc["activ"])) {
        continue;
      }

      serializeJson(newdoc, Serial);
      Serial.println();

      serializeJson(newdoc["days"], Serial);
      Serial.println();

      JsonArray days = newdoc["days"].as<JsonArray>();

      for (const auto& v : days) {
        int day = v.as<int>();
        Serial.println(day);

        if (day == timeClient.getDay()) {

          Serial.println("right day");
          serializeJson(newdoc["start"], Serial);
          Serial.println();

          if (newdoc["start"] == (String(timeClient.getHours()) + ":" + String(timeClient.getMinutes()))) {
            temp = float(newdoc["temp"]);
            Serial.println("new temp");
            Serial.println(temp);
            break;
          } else if (newdoc["end"] == (String(timeClient.getHours()) + ":" + String(timeClient.getMinutes()))) {
            File file = SPIFFS.open(fileNormtemp, "r");
            temp = file.readStringUntil('\r').toFloat();
            file.close();

            Serial.println("normtemp");
            Serial.println(temp);
            break;
          }

          continue;
        }
      }

      j++;
    }

    float currentTemp = dht.readTemperature() + tempOffset;
    Serial.print("currentTemp: ");
    Serial.println(currentTemp, 1);
    Serial.print("temp: ");
    Serial.println(temp);

    if (temp - currentTemp > 0.5) {  // zu kalt
      if (stepper.currentPosition() != 0) {
        Serial.println("Thermostat öffnen");
        stepper.moveTo(0);
      }
    } else if (currentTemp - temp > 2.5) {  //zu warm
      if (stepper.currentPosition() != close) {
        Serial.println("Thermostat schliessen");
        stepper.moveTo(close);
      }
    } else if (currentTemp - temp > 0.5) {
      if (stepper.currentPosition() != close / 2) {
        Serial.println("Thermostat halb öffnen");
        stepper.moveTo(close / 2);
      }
    }

    lastCheck = millis();
  }

  if (stepper.distanceToGo() != 0) {
    stepper.run();
    if (stepper.distanceToGo() == 0) {
      stepper.run();
      File file = SPIFFS.open(fileCurrentStepperPos, "w");
      file.println(String(stepper.currentPosition()));
      file.close();
    }
  }
}
