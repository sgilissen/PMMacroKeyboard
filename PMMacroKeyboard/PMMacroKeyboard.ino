/*
 * Poor Man's Macro Keyboard
 * 
 * 
 */

#include <Keypad.h>
#include <Keyboard.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

unsigned long startMillis;
unsigned long currentMillis;
const unsigned long displayTimeout = 8000;

/* ---- START KEYMATRIX SETUP ---- */
const byte ROWS = 4; // 4 rows
const byte COLS = 4; // 4 columns

char keys[ROWS][COLS] = { 
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};

char dispHeader[] = "CURRENT PAGE: ";
const char* pageNames[] = {"Page A", "Page B", "Page C", "Page D"};
char lastKeypress[8];

byte rowPins[ROWS] = {10, 16, 14, 15}; //{9, 8, 7, 6}; // Pins to connect the rows
byte colPins[COLS] = {18, 19, 20, 21};//{5, 4, 3, 2}; // Pins to connect the columns

// Initialize the keymatrix
Keypad keyMatrix = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
/* ---- END KEYMATRIX SETUP ---- */                                                                                                      


/* ---- START OLED SETUP ---- */
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
/* ---- END OLED SETUP ---- */


enum State_enum {PAGE_A, PAGE_B, PAGE_C, PAGE_D};
void state_machine_run(uint8_t states);
uint8_t state = PAGE_A;
char button = keyMatrix.getKey();

void setup() {
  Serial.begin(9600);
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(1000);
  Keyboard.begin();
  display.clearDisplay();
  display.setCursor(10,0);
  write_display();
  

}

void loop() {
  // Get the character from the keymatrix
  button = keyMatrix.getKey();
  read_func_btns();
  state_machine_run(button);
  

  // Display timeout (we don't want to burn out our OLED display)
  currentMillis = millis();
  if (currentMillis - startMillis >= displayTimeout) {
    display.clearDisplay();
    display.display();
  } else {
    write_display();
  }

}

void state_machine_run(char button)
{
  //char button = keyMatrix.getKey();
  switch(state)
  {
    case PAGE_A:
      if(button){
        //Serial.println(button);
        if(button == '1'){
          Keyboard.press(KEY_F13);
          delay(20);
          Keyboard.releaseAll();
          strcpy(lastKeypress, "F13");
        } else if (button == '2') {
          Keyboard.press(KEY_F14);
          delay(20);
          Keyboard.releaseAll();
          strcpy(lastKeypress, "F14");
        } else if (button == '3') {
          Keyboard.press(KEY_F15);
          delay(20);
          Keyboard.releaseAll();
          strcpy(lastKeypress, "F15");
        } else if (button == '4') {
          Keyboard.press(KEY_F16);
          delay(20);
          Keyboard.releaseAll();
          strcpy(lastKeypress, "F16");
        } else if (button == '5') {
          Keyboard.press(KEY_F17);
          delay(20);
          Keyboard.releaseAll();
          strcpy(lastKeypress, "F17");
        } else if (button == '6') {
          Keyboard.press(KEY_F18);
          delay(20);
          Keyboard.releaseAll();
          strcpy(lastKeypress, "F18");
        } else if (button == '7') {
          Keyboard.press(KEY_F19);
          delay(20);
          Keyboard.releaseAll();
          strcpy(lastKeypress, "F19");
        } else if (button == '8') {
          Keyboard.press(KEY_F20);
          delay(20);
          Keyboard.releaseAll();
          strcpy(lastKeypress, "F20");
        } else if (button == '9') {
          Keyboard.press(KEY_F21);
          delay(20);
          Keyboard.releaseAll();
          strcpy(lastKeypress, "F21");
        } else if (button == '*') {
          Keyboard.press(KEY_F22);
          delay(20);
          Keyboard.releaseAll();
          strcpy(lastKeypress, "F22");
        } else if (button == '0') {
          Keyboard.press(KEY_F23);
          delay(20);
          Keyboard.releaseAll();
          strcpy(lastKeypress, "F23");
        } else if (button == '#') {
          Keyboard.press(KEY_F24);
          delay(20);
          Keyboard.releaseAll();
          strcpy(lastKeypress, "F24");
        }
      }

      break;
      
    case PAGE_B:    
      if(button){
        Serial.println(button);
      }

      break;
    case PAGE_C:
      if(button){
        Serial.println(button);
      }

      break;
    case PAGE_D:
      if(button){
        Serial.println(button);
      }

      break;
  }
}


void read_func_btns() {
  //char button = keyMatrix.getKey();
  if(button == 'A') {
    state = PAGE_A;
  } else if (button == 'B') {
    state = PAGE_B;
  } else if (button == 'C') {
    state = PAGE_C;
  } else if (button == 'D') {
    state = PAGE_D;
  } 
  if (button) {
    startMillis = currentMillis; // If any button is pressed, reset the millis to turn on the display
  }
}

void write_display() {
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(2); 
    display.setCursor(10, 0);
    display.println(pageNames[state]);
    display.setTextSize(1); 
    display.setCursor(10, 20);
    display.println("Last keypress: ");
    display.println(lastKeypress);
    display.display();
}
