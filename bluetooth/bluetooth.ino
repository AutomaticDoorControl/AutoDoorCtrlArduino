#include <SoftwareSerial.h>
#include "outgoingCommands.h"

#define DOOR_PIN 5
#define txPin 11
#define rxPin 10

SoftwareSerial adc(rxPin, txPin);


#pragma mark - function prototypes

void processData2();

#pragma mark - main arduino methods

void setup() {
    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);
    pinMode(DOOR_PIN, OUTPUT);
    Serial.begin(9600);
    adc.begin(9600);
}

void loop() {
    processData();
}

# pragma mark - helper methods

void processData() {
    if (adc.available()) {
        char data = adc.read();
        Serial.println(data);
        if (data == 'a') {
            adc.print(onCommand);
            digitalWrite(DOOR_PIN, HIGH);
            delay(2000);
            digitalWrite(DOOR_PIN, LOW);
            delay(20000);
            adc.print(offCommand);
        }
    }
}
