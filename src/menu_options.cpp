#include "myheader.h"
#include <Arduino.h>

// function to display the menu, returns nothing
void showMenu() {
    Serial.println("\n***** MODE MENU SYSTEM *****\n");
    Serial.println("Enter mode of choice:");
    Serial.println("1. Potentiometer-controlled servo mode");
    Serial.println("2. Trashcan Mode");
    Serial.print("\nYour Choice: ");
}

// function to get user input, returns nothing
void getUserInput() {
    char userInput{};   // declare variable to store user input

    if (Serial.available() > 0) {       // If a character is waiting in the Serial input buffer, read it
        userInput = Serial.read();

        if (userInput == '\n' || userInput == '\r') {     // Serial input includes '\r' and '\n' after the user presses Enter; ignore them
            return;
        }

        switch(userInput) {               // switch statement for user input
            case '1': {                   // if the user chooses the blink mode, set to 1 because ASCII is 49
                currentMode = POT;      // set the current selected mode to blink (ASCII is 49)
                menuDisplayed = false;    // mark the menu as not displayed for redisplay
                break;
            }
            case '2': {                   // if user chooses the basic dimmer mode, set to 2 because ASCII is 50
                currentMode = TRASHCAN;  // set the current selected mode to basic dimmer (ASCII is 50)
                menuDisplayed = false;    // mark the menu as not displayed for redisplay
                break;
            }
            default: {                    // default case to protect against invalid input
                Serial.println("Invalid input! Enter 1, 2, or 3.");
                break;
            }
        }

        while (Serial.available() > 0) {
            Serial.read();              // flush the extra characters.
        }
    }
}