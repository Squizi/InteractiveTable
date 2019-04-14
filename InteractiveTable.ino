// DON'T USE D0 and D1


#include <FastLED.h>

#define NUM_SEGMENTS 45 //

CRGB leds[NUM_SEGMENTS];
CRGB normalLedColor = 0x040000;
CRGB overLedColor = 0x000004;


/*================== IR Sensors =================================*/
#define FIRST_SENSOR_PIN  2
#define LAST_SENSOR_PIN FIRST_SENSOR_PIN+NUM_SEGMENTS

int stateIR[NUM_SEGMENTS];

void initIRSensors() {
  for (int i = FIRST_SENSOR_PIN; i < LAST_SENSOR_PIN+1; i++) {
    pinMode(i, INPUT);
    stateIR[i - FIRST_SENSOR_PIN] = 1;
  }
}

void readIRState () {
    for (int i = 0; i < sizeof(stateIR); i++) {
    bool state = digitalRead(FIRST_SENSOR_PIN+i);
    if (state == LOW) {
      stateIR[i] = 0;
      leds[stateIR[i]] = overLedColor;
    } else {
      stateIR[i] = 1;
      leds[stateIR[i]] = normalLedColor;
    }
  }
  FastLED.show();  
}

/*===============================================================*/

/*================== LED strip =================================*/

#define DATA_PIN 48




void initLEDstrip(){ 
  pinMode(DATA_PIN, OUTPUT);
  for(int i = 0; i < NUM_SEGMENTS; i++){
    leds[i] = normalLedColor;
  }
    FastLED.show();
}

/*================================================================*/


void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_SEGMENTS);
  initIRSensors();
  initLEDstrip();
}

void loop() {
  readIRState();
}
