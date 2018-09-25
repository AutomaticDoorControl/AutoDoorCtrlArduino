#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

#define WIFI_SSID "DESKTOP-ELJ762L 6621"
#define WIFI_PASSWORD "1e52;25P"

#define FIREBASE_HOST "rcosdoor.firebaseio.com"
#define FIREBASE_AUTH "0LuUzlDQghDNSYUwIEDXkyI5CEDq4CDDTl58BY0V"

int ledPin = 16;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected at ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int doorStatus = Firebase.getInt("doorStatus");
  Serial.println(doorStatus);
  if(doorStatus == 1)
  {
    digitalWrite(ledPin, LOW);
  }
  else
  {
    digitalWrite(ledPin, HIGH);
  }
  delay(2000);
}
