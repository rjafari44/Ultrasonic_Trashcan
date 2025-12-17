#include "myheader.h"
#include <Arduino.h>
#include <ESP32Servo.h>

// global variable declaration, made to only be used within this file
// servo variabless
const int servoPin{10};
static Servo controlServo{};
static int hardAngle{};

// potentiometer variables
const int potReadPin{4};
static int potValue{};

// menu variable
static char input{};

void pot_setup() {
    pinMode(servoPin, OUTPUT);
    controlServo.attach(servoPin);
    Serial.println("\n*** Potentiometer-Controlled Servo Mode ***");
    Serial.println("Servo is ready to be controlled by potentiometer. Type 'm' or 'M' + Enter to return to mode menu");
}

void pot_loop() {

    potValue = analogRead(potReadPin);                // get potentiometer value in range of 0-4095
    hardAngle = (potValue * 180) / 4095;              // convert 0-4095 range down to 0-180
    controlServo.write(hardAngle);                    // wite the angle to the servo

    Serial.print("Angle is: ");
    Serial.println(hardAngle); // display the angle
    delay(20);

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
                modeSetup[0] = false;   // mark the current mode's setup as false so it runs again
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