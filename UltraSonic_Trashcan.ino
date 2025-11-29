#include <Arduino.h>
#include <ESP32Servo.h>

const int servoPin{10};
const int trigPin{3};
const int echoPin{4};
Servo controlServo{};

void setup() {
    Serial.begin(115200);
    delay(1000);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    controlServo(servoPin);
}

void loop() {

}