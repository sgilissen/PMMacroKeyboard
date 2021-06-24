/*
   Poor Man's Macro Keyboard


*/

#include <Keypad.h>
#include <Keyboard.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <U8g2_for_Adafruit_GFX.h> // u8g2 fonts are prettier
#include <Encoder.h>

#define KEY_KEYPAD_SUBTRACT 0x56
#define KEY_KEYPAD_ADD 0x57


unsigned long startMillis;
unsigned long currentMillis;
const unsigned long displayTimeout = 10000;

/* ---- START KEYMATRIX SETUP ---- */
const byte ROWS = 4; // 4 rows
const byte COLS = 4; // 4 columns

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};

byte rowPins[ROWS] = {10, 16, 14, 15}; //{9, 8, 7, 6}; // Pins to connect the rows
byte colPins[COLS] = {18, 19, 20, 21};//{5, 4, 3, 2}; // Pins to connect the columns

// Initialize the keymatrix
Keypad keyMatrix = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
/* ---- END KEYMATRIX SETUP ---- */

/* ---- START DESCRIPTIONS ---- */
const char* pageNames[] = {"A: Ctrl+(n)", "B: Ctrl+Alt+(n)", "C: Alt+(n)", "D: F13-F24"};
const char* pageDescr1[] = {"(n): Num, * or #", "(n): Num, * or #", "(n): Num, * or #", "Hidden F-keys"};
const char* pageDescr2[] = {"JOG: (n)=PgUp/Dn", "JOG: (Shft)Tab", "JOG: (n)=PgUp/Dn", "JOG: Workspaces"};
/* ---- END DESCRIPTIONS ---- */

/* ---- START OLED SETUP ---- */
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
U8G2_FOR_ADAFRUIT_GFX u8g2_display;
/* ---- END OLED SETUP ---- */

/* ---- START ROTARY ENCODER SETUP ---- */
Encoder RotEnc(6,7);
long posRotEnc  = -999;
/* ---- END ROTARY ENCODER SETUP ---- */

enum State_enum {PAGE_A, PAGE_B, PAGE_C, PAGE_D};

void state_machine_run(uint8_t states);
uint8_t state = PAGE_A;
char button = keyMatrix.getKey();


void setup() {
  Serial.begin(9600);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Clear the display, initiate u8g2 fonts
  display.clearDisplay();
  u8g2_display.begin(display);
  display.setCursor(10, 0);
  write_display();

  // Initiate Keyboard library
  Keyboard.begin();
  

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
  long newPosRotEnc = RotEnc.read()/4;
  
  switch (state)
  {
    case PAGE_A:
      if (newPosRotEnc != posRotEnc && newPosRotEnc > posRotEnc) {
        posRotEnc = newPosRotEnc;
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_PAGE_UP);
        delay(20);
        Keyboard.releaseAll();
        resetMillis();
        } 
      if (newPosRotEnc != posRotEnc && newPosRotEnc < posRotEnc) {
        posRotEnc = newPosRotEnc;
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_PAGE_DOWN);
        delay(20);
        Keyboard.releaseAll();
        resetMillis();
        } 
      
      if (button) {
        //Serial.println(button);
        if (button == '1') {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('1');
          delay(20);
          Keyboard.releaseAll();
          //lastKeypress = ;
          

        } else if (button == '2') {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('2');
          delay(20);
          Keyboard.releaseAll();
          

        } else if (button == '3') {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('3');
          delay(20);
          Keyboard.releaseAll();
          

        } else if (button == '4') {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('4');
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '5') {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('5');
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '6') {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('6');
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '7') {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('7');
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '8') {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('8');
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '9') {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('9');
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '*') {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('*');
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '0') {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('0');
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '#') {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('#');
          delay(20);
          Keyboard.releaseAll();

        } 
        
      }
      

      break;

    case PAGE_B:
      if (newPosRotEnc != posRotEnc && newPosRotEnc > posRotEnc) {
        posRotEnc = newPosRotEnc;
        Keyboard.press(KEY_TAB);
        delay(20);
        Keyboard.releaseAll();
        resetMillis();
        } 
      if (newPosRotEnc != posRotEnc && newPosRotEnc < posRotEnc) {
        posRotEnc = newPosRotEnc;
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_TAB);
        delay(20);
        Keyboard.releaseAll();
        resetMillis();
        } 
        
      if (button) {
        if (button == '1') {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('1');
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '2') {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('2');
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '3') {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('3');
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '4') {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('4');
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '5') {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('5');
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '6') {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('6');
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '7') {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('7');
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '8') {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('8');
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '9') {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('9');
          delay(20);
          Keyboard.releaseAll();
          
        } else if (button == '*') {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('*');
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '0') {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('0');
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '#') {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('#');
          delay(20);
          Keyboard.releaseAll();

        }
      }

      break;
    
    case PAGE_C:
      if (newPosRotEnc != posRotEnc && newPosRotEnc > posRotEnc) {
        posRotEnc = newPosRotEnc;
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_PAGE_UP);
        delay(20);
        Keyboard.releaseAll();
        resetMillis();
        } 
      if (newPosRotEnc != posRotEnc && newPosRotEnc < posRotEnc) {
        posRotEnc = newPosRotEnc;
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_PAGE_DOWN);
        delay(20);
        Keyboard.releaseAll();
        resetMillis();
        } 
        
      if (button) {
        if (button == '1') {
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('1');
          delay(20);
          Keyboard.releaseAll();
          //lastKeypress = ;
          

        } else if (button == '2') {
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('2');
          delay(20);
          Keyboard.releaseAll();
          

        } else if (button == '3') {
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('3');
          delay(20);
          Keyboard.releaseAll();
          

        } else if (button == '4') {
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('4');
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '5') {
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('5');
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '6') {
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('6');
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '7') {
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('7');
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '8') {
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('8');
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '9') {
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('9');
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '*') {
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('*');
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '0') {
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('0');
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '#') {
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('#');
          delay(20);
          Keyboard.releaseAll();

        }
      }
      break;
      case PAGE_D:
      if (newPosRotEnc != posRotEnc && newPosRotEnc > posRotEnc) {
        posRotEnc = newPosRotEnc;
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_RIGHT_ARROW);
        delay(20);
        Keyboard.releaseAll();
        resetMillis();
        } 
      if (newPosRotEnc != posRotEnc && newPosRotEnc < posRotEnc) {
        posRotEnc = newPosRotEnc;
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_LEFT_ARROW);
        delay(20);
        Keyboard.releaseAll();
        resetMillis();
        } 
        
      if (button) {
        if (button == '1') {
          Keyboard.press(KEY_F13);
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '2') {
          Keyboard.press(KEY_F14);
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '3') {
          Keyboard.press(KEY_F15);
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '4') {
          Keyboard.press(KEY_F16);
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '5') {
          Keyboard.press(KEY_F17);
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '6') {
          Keyboard.press(KEY_F18);
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '7') {
          Keyboard.press(KEY_F19);
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '8') {
          Keyboard.press(KEY_F20);
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '9') {
          Keyboard.press(KEY_F21);
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '*') {
          Keyboard.press(KEY_F22);
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '0') {
          Keyboard.press(KEY_F23);
          delay(20);
          Keyboard.releaseAll();

        } else if (button == '#') {
          Keyboard.press(KEY_F24);
          delay(20);
          Keyboard.releaseAll();

        }
      }

      break;
  }
}


void read_func_btns() {
  //char button = keyMatrix.getKey();
  
  if (button == 'A') {
    state = PAGE_A;
  } else if (button == 'B') {
    state = PAGE_B;
  } else if (button == 'C') {
    state = PAGE_C;
  } else if (button == 'D') {
    state = PAGE_D;
  }

  
  if (button) {
    //startMillis = currentMillis; // If any button is pressed, reset the millis to turn on the display
    resetMillis();
  }
  
}


void resetMillis() {
  startMillis = currentMillis; // If any button is pressed, reset the millis to turn on the display
}

void write_display() {
  display.clearDisplay();
  u8g2_display.begin(display);
  u8g2_display.setFontMode(1);
  display.fillRect(0, 0, 128, 12, WHITE);
  u8g2_display.setForegroundColor(BLACK);
  u8g2_display.setBackgroundColor(WHITE);
  u8g2_display.setFont(u8g2_font_pressstart2p_8f);
  u8g2_display.setCursor(10, 10);
  u8g2_display.print(F("Current Page:"));
  u8g2_display.setForegroundColor(WHITE);
  u8g2_display.setBackgroundColor(BLACK);
  u8g2_display.setFont(u8g2_font_tenfatguys_tf);
  u8g2_display.setCursor(0, 24);
  u8g2_display.print(pageNames[state]);
  u8g2_display.setFontMode(1);
  display.fillRect(0, 26, 128, 12, WHITE);
  u8g2_display.setForegroundColor(BLACK);
  u8g2_display.setBackgroundColor(WHITE);
  u8g2_display.setFont(u8g2_font_pressstart2p_8f);
  u8g2_display.setCursor(10, 36);
  u8g2_display.print(F("Description:"));
  u8g2_display.setForegroundColor(WHITE);
  u8g2_display.setBackgroundColor(BLACK);
  u8g2_display.setCursor(0, 48);
  u8g2_display.print(pageDescr1[state]);
  u8g2_display.setCursor(0, 60);
  u8g2_display.print(pageDescr2[state]);
  display.display();
}
