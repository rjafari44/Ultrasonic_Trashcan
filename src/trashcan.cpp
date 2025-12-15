#include "myheader.h"
#include <Arduino.h>
#include <ESP32Servo.h>
#include <WiFi.h>

const char* ssid = "ssid";
const char* password = "password";

static Servo controlServo{};
const int servoPin{10};

const int trigPin = 3;
const int echoPin = 4;

static char input{};

void trashcan_setup() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected!");
    Serial.println(WiFi.localIP());
    }
    else {
    Serial.println("Not connected");
    }

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void trashcan_loop() {

    // 

    if (Serial.available() > 0) {        // If a character is waiting in the Serial input buffer, read it
        input = Serial.read();
        
        if (input == '\n' || input == '\r') {    // Serial input includes '\r' and '\n' after the user presses Enter; ignore them
            return;
        }

        switch(input) {        // switch statement for returning to main menu
            case 'm':          // if user chooses lower case 'm', it will waterfall through due to no break to the next case
            case 'M': {        // if user chooses upper case 'M'
                currentMode = MENU;     // set current selected mode to menu
                modeSetup[1] = false;   // mark the current mode's setup as false so it runs again
                Serial.println("Returning to mode menu...");
                break;
            }
            default:      // default case to protect against invalid input
            Serial.println("Unknown command. Type 'm' or 'M' to return to main menu.");
            break;
        }

        while (Serial.available() > 0) {
            Serial.read();              // flush the extra characters.
        }
    }
}