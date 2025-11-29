#include "myheader.h"
#include <Arduino.h>

// function for setting up the serial monitor
void setup() {
    Serial.begin(115200);
    delay(1000);
}

// main loop for running the program
void loop() {
    switch(currentMode) {                // switch statement for selected mode
        case MENU: {                     // if user selects to display the menu, this is the default case at the beginning
            if (!menuDisplayed) {        // if the menu hasn't been displayed yet
                showMenu();              // display the menu
                menuDisplayed = true;    // mark menu as displayed
            }
            getUserInput();              // get user input
            break;
        }
        case POT: {                   // if the user chooses blink mode
            if (!modeSetup[0]) {        // if the potentiomer-controlled servo mode setup hasn't run yet
                pot_setup();          // run the potentiomer-controlled servo setup function
                modeSetup[0] = true;    // mark the setup as complete
            }
            pot_loop();               // perform the potentiomer-controlled servo loop function
            break;
        }
        case TRASHCAN: {              // if the user chooses basic dimmer mode
            if (!modeSetup[1]) {       // if the trashcan setup hasn't run yet
                trashcan_setup();        // run the tashcan setup function
                modeSetup[1] = true;   // mark the setup as complete
            }
            trashcan_loop();             // perform the trashcan loop function
            break;
        }
        default: {                   // default statement for safety
            currentMode = MENU;         // set the current selected mode back to menu
            menuDisplayed = false;   // mark the menu as not displayed yet to enable redesplay
            break;
        }
    }
}