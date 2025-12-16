#include "myheader.h"
#include <Arduino.h>
#include <ESP32Servo.h>

static Servo controlServo{};
const int servoPin{10};

const int trigPin = 3;
const int echoPin = 4;

long duration{};
long distance{};
double soundSpeed{0.0343}; // speed of sound in centimeters per microseconds

static char input{};

void trashcan_setup() {

    controlServo.attach(servoPin);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.println("\n*** Ultrasonic Trashcan Mode ***");
    Serial.println("Ultrasonic Trashcan is ready for use. Type 'm' or 'M' + Enter to return to mode menu");
}

void trashcan_loop() {
    
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);      // returns total time it takes to go out and come back in microseconds
    distance = (duration * soundSpeed) / 2; // multiply the total time by the speed of sound and divide by 2 to get just the distance to an object in centimeters

    if (distance < 20) {
        Serial.println("Trashcan is opening!\n");
        controlServo.write(90); // open trashcan
        delay(5000); // wait 5 seconds before closing
        Serial.println("Trashcan is closing!\n");
        controlServo.write(0); // close trashcan
        delay(500); // wait for trashcan to close
    }

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