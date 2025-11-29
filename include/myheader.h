#pragma once

enum Mode{ MENU, POT, TRASHCAN };

// external global variables
inline Mode currentMode{MENU};
inline bool menuDisplayed{false};
inline bool modeSetup[2]{false, false};

// display and user input functions
void showMenu();
void getUserInput();

// setup and loop functions for the potentiometer-controlled servo mode
void pot_setup();
void pot_loop();

// setup and loop functions for the trashcan mode
void trashcan_setup();
void trashcan_loop();