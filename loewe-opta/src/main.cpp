#include <Arduino.h>

#include "TEA5767.h"
#include "Adafruit_SSD1306.h"
#include "switch_debounce_helper.h"

#define SMALL_BUTTON 4
#define BIG_BUTTON 2

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

uint16_t delay_local{100};

SwitchDebounceHelper btn_forward(BIG_BUTTON);
SwitchDebounceHelper btn_backward(SMALL_BUTTON);

TEA5767 Radio;

unsigned char buf[5];
int stereo;
int signal_level, signal_level_privious;
double current_freq;

int search_mode = 0;
int search_direction;

bool new_ui_data_available{true};

void displayTextLines(String line1="", String line2="")
{
  display.clearDisplay(); // Clear the buffer
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(line1);
  display.setTextSize(2); // Draw 2X-scale text
  display.setCursor(0, 18);
  display.println(line2);
  display.display();      // Show text
};

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  Radio.init();
  Radio.set_frequency(10.0); 

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  displayTextLines("Lowa-Opta");
  delay(2000);
}

void loop() {
  if (Radio.read_status(buf) == 1) {
    current_freq =  floor (Radio.frequency_available (buf) / 100000 + .5) / 10;
    signal_level = Radio.signal_level(buf);

    if (new_ui_data_available)
    {
      displayTextLines("FM:"+String(current_freq), "Signal:"+String(signal_level));
    }

    if (signal_level != signal_level_privious)
    {
      new_ui_data_available = true;
    } else 
    {
      new_ui_data_available = false;
    }

    signal_level_privious = signal_level;
  }

  if (search_mode == 1) {
      if (Radio.process_search (buf, search_direction) == 1) {
          search_mode = 0;
      }

      new_ui_data_available = true;
  }

  if (btn_forward.SwitchPressed()) {
    //last_pressed = current_millis;
    search_mode = 1;
    search_direction = TEA5767_SEARCH_DIR_UP;
    Radio.search_up(buf);
    delay(300);

    new_ui_data_available = true;
  }
  
  if (btn_backward.SwitchPressed()) {
    //last_pressed = current_millis;
    search_mode = 1;
    search_direction = TEA5767_SEARCH_DIR_DOWN;
    Radio.search_down(buf);
    delay(300);

    new_ui_data_available = true;
  } 

  delay(50);
}