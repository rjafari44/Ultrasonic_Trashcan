#include "myheader.h"
#include <Arduino.h>
#include <ESP32Servo.h>

// servo variables
static Servo controlServo{};
const int servoPin{10};

// ultrasonic sensor variables
const int trigPin = 3;
const int echoPin = 4;
long duration{};
long distance{};
double soundSpeed{0.0343}; // speed of sound in centimeters per microseconds

// menu variable
static char input{};

void trashcan_setup() {

    pinMode(servoPin, OUTPUT);
    controlServo.attach(servoPin); // setup the servo pin
    controlServo.write(0);         // set the servo to default angle of 0 to ensure it is in position.
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

    duration = pulseIn(echoPin, HIGH);      // returns total time it takes to go out and come back in microseconds
    distance = (duration * soundSpeed) / 2; // multiply the total time by the speed of sound and divide by 2 to get just the distance to an object in centimeters

    // if statement to trigger trashcan functionality whenver the distance to an object is less than 20 cm
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
                Serial.println("Returning to mode menu...");
                controlServo.write(0); // ensure servo gets set to angle of 0 as default.
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