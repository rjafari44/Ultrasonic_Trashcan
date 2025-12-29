#include "myheader.h"
#include <Arduino.h>
#include <ESP32Servo.h>

// global variable declaration, made to only be used within this file
// servo variables
static Servo controlServo{};
const int servoPin{10};

// ultrasonic sensor variables
const int trigPin{3};
const int echoPin{4};
long duration{};
double distance{};
double soundSpeed{0.0343}; // speed of sound in centimeters per microseconds

// booloean variable to check if trashcan is open
bool trashOpen{1};

// menu variable
static char input{};

void trashcan_setup() {
    controlServo.attach(servoPin); // setup the servo pin
    controlServo.write(116);         // set the servo to default angle of 0 to ensure it is in position.
    pinMode(trigPin, OUTPUT);      // set the trigger pin of the ultrasonic sensor as output
    pinMode(echoPin, INPUT);       // set the echo pin of the ultrasonic sensor as input
    Serial.println("\n*** Ultrasonic Trashcan Mode ***");
    Serial.println("Ultrasonic Trashcan is ready for use. Type 'm' or 'M' + Enter to return to mode menu");
}

void trashcan_loop() {

    digitalWrite(trigPin, LOW);  // send out a low trigger pulse
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH); // send out a high trigger pulse
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);  // resend a low trigger pulse 

    duration = pulseIn(echoPin, HIGH, 30000); // returns total time it takes to go out and come back in microseconds, also has a added 30 ms timeout

    // if there is a echo time received
    if (duration > 0) {
        distance = (duration * soundSpeed) / 2.0;
    } else {
        return; // no echo received
    }

    // if detected object is less than 20 cm and trashcan is not open, open the trashcan
    if (distance < 20 && !trashOpen) {
    Serial.println("Trashcan is opening!");
    controlServo.write(18);
    delay(1000);
    trashOpen = true;
    }

    // if detected object is equal to or more than 20 cm and trashcan is open, close the trashcan
    if (distance >= 20 && trashOpen) {
    Serial.println("Trashcan is closing!");
    controlServo.write(116);
    delay(1000);
    trashOpen = false;
    }


    if (Serial.available() > 0) {        // If a character is waiting in the Serial input buffer, read it
        input = Serial.read();
        
        if (input == '\n' || input == '\r') {    // Serial input includes '\r' and '\n' after the user presses Enter; ignore them
            while (Serial.available() > 0) {
                Serial.read(); // flush buffer
            }
            return;
        }

        switch(input) {        // switch statement for returning to main menu
            case 'm':          // if user chooses lower case 'm', it will waterfall through due to no break to the next case
            case 'M': {        // if user chooses upper case 'M'
                currentMode = MENU;     // set current selected mode to menu
                modeSetup[1] = false;   // mark the current mode's setup as false so it runs again
                Serial.println("Trashcan is closing!\n");
                Serial.println("Returning to mode menu...");
                controlServo.write(116); // ensure servo gets set to angle of 0 as default.
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