#include <FastLED.h>
#include <CapacitiveSensor.h>
// How many leds in your strip?
#define NUM_LEDS 14
// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN

#define DATA_PIN 12
int brightness = 5; // initialize brightness value of 5
int hue1 = 0; // initialize hue1 for row1 as red arbitrarily
int hue2 = 0; // initiliaze hue2 for row2 as red arbitrarily

int brightpin = A2; // define pin for brightness potentiometer
int hue1pin = A3; // pin for hue1 potentiometer (row 1)
int hue2pin = A4; // pin for hue2 potentiometer (row 2)

// Define the array of leds
CRGB leds[NUM_LEDS];

// instatiate capacitive touch sensors
// First row of panels for mon-sun
CapacitiveSensor   cs_1 = CapacitiveSensor(7, A0);
CapacitiveSensor   cs_2 = CapacitiveSensor(7, A1);
CapacitiveSensor   cs_3 = CapacitiveSensor(7, A5);
CapacitiveSensor   cs_4 = CapacitiveSensor(7, 11);
CapacitiveSensor   cs_5 = CapacitiveSensor(7, 10);
CapacitiveSensor   cs_6 = CapacitiveSensor(7, 9);
CapacitiveSensor   cs_7 = CapacitiveSensor(7, 8);
// Second row of panels for mon-sun
CapacitiveSensor   cs_8 = CapacitiveSensor(7, 2);
CapacitiveSensor   cs_9 = CapacitiveSensor(7, 3);
CapacitiveSensor   cs_10 = CapacitiveSensor(7, 4);
CapacitiveSensor   cs_11 = CapacitiveSensor(7, 5);
CapacitiveSensor   cs_12 = CapacitiveSensor(7, 6);
//CapacitiveSensor   cs_13 = CapacitiveSensor(7, A0);
//CapacitiveSensor   cs_14 = CapacitiveSensor(7, 0);

//define a value of 0 (off state) for each led state
int state1 = 0;
int state2 = 0;
int state3 = 0;
int state4 = 0;
int state5 = 0;
int state6 = 0;
int state7 = 0;
int state8 = 0;
int state9 = 0;
int state10 = 0;
int state11 = 0;
int state12 = 0;
int state13 = 0;
int state14 = 0;
long time = 0;
long debounce = 250; //time it takes to register a 'touch' in ms and time before changing value again

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(9600);
  cs_1.set_CS_AutocaL_Millis(0xFFFFFFFF);// turn off autocalibrate on channel 1 - just as an example
  cs_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_3.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_4.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_5.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_6.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_7.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_8.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_9.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_10.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_11.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_12.set_CS_AutocaL_Millis(0xFFFFFFFF);

  //set a timeout value of 200 ms, otherwise when there are errors it takes a whole 2 seconds to process anything on the arduino per sensor
  cs_1.set_CS_Timeout_Millis(200);
  cs_2.set_CS_Timeout_Millis(200);
  cs_3.set_CS_Timeout_Millis(200);
  cs_4.set_CS_Timeout_Millis(200);
  cs_5.set_CS_Timeout_Millis(200);
  cs_6.set_CS_Timeout_Millis(200);
  cs_7.set_CS_Timeout_Millis(200);
  cs_8.set_CS_Timeout_Millis(200);
  cs_9.set_CS_Timeout_Millis(200);
  cs_10.set_CS_Timeout_Millis(200);
  cs_11.set_CS_Timeout_Millis(200);
  cs_12.set_CS_Timeout_Millis(200);
  //cs_13.set_CS_Timeout_Millis(200); // not enough pins on a standard arduino :/
  //cs_14.set_CS_Timeout_Millis(200);
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  //  pinMode(13, OUTPUT);
  //  pinMode(0, INPUT);
}

void loop() {
  brightness = map(analogRead(brightpin), 0, 1023, 0, 255); //map the brighness value to the sliding potentiometer value
  hue1 = map(analogRead(hue1pin), 0, 1023, 0, 255); // mape the hue value of row1 to the value of the dial potentiometer
  hue2 = map(analogRead(hue2pin), 0, 1023, 0, 255);
  
  //the number in the paranthesis indicates byte samples
  long sensor1 = cs_1.capacitiveSensor(50);
  long sensor2 = cs_2.capacitiveSensor(50);
  long sensor3 = cs_3.capacitiveSensor(50);
  long sensor4 = cs_4.capacitiveSensor(50);
  long sensor5 = cs_5.capacitiveSensor(50);
  long sensor6 = cs_6.capacitiveSensor(50);
  long sensor7 = cs_7.capacitiveSensor(50);

  long sensor8 = cs_8.capacitiveSensor(50);
  long sensor9 = cs_9.capacitiveSensor(50);
  long sensor10 = cs_10.capacitiveSensor(50);
  long sensor11 = cs_11.capacitiveSensor(50);
  long sensor12 = cs_12.capacitiveSensor(50);
  //  long sensor13 = cs_13.capacitiveSensor(50);
  //  long sensor14 = cs_14.capacitiveSensor(50);

  int sensorThresh = 500; //threshold that we'll use to trigger a 'touch' and change the state of an LED

  // LED 1
  if (state1 == 0) {
    leds[0] = CRGB::Black;
    FastLED.show();
    if (sensor1 > sensorThresh && state1 == 0 && millis() - time > debounce) {
      state1 = 1;
      time = millis();
    }
  }
  if (state1 == 1) {
    leds[0] = CHSV( hue1, 255, brightness);
    FastLED.show();
    if (sensor1 > sensorThresh && state1 == 1 && millis() - time > debounce) {
      state1 = 0;
      time = millis();
    }
  }
  // LED 2
  if (state2 == 0) {
    leds[1] = CRGB::Black;
    FastLED.show();
    if (sensor2 > sensorThresh && state2 == 0 && millis() - time > debounce) {
      state2 = 1;
      time = millis();
    }
  }
  if (state2 == 1) {
    leds[1] = CHSV( hue1, 255, brightness);
    FastLED.show();
    if (sensor2 > sensorThresh && state2 == 1 && millis() - time > debounce) {
      state2 = 0;
      time = millis();
    }
  }
  // LED 3
  if (state3 == 0) {
    leds[2] = CRGB::Black;
    FastLED.show();
    if (sensor3 > sensorThresh && state3 == 0 && millis() - time > debounce) {
      state3 = 1;
      time = millis();
    }
  }
  if (state3 == 1) {
    leds[2] = CHSV( hue1, 255, brightness);
    FastLED.show();
    if (sensor3 > sensorThresh && state3 == 1 && millis() - time > debounce) {
      state3 = 0;
      time = millis();
    }
  }
  // LED 4
  if (state4 == 0) {
    leds[3] = CRGB::Black;
    FastLED.show();
    if (sensor4 > sensorThresh && state4 == 0 && millis() - time > debounce) {
      state4 = 1;
      time = millis();
    }
  }
  if (state4 == 1) {
    leds[3] = CHSV( hue1, 255, brightness);
    FastLED.show();
    if (sensor4 > sensorThresh && state4 == 1 && millis() - time > debounce) {
      state4 = 0;
      time = millis();
    }
  }
  // LED 5
  if (state5 == 0) {
    leds[4] = CRGB::Black;
    FastLED.show();
    if (sensor5 > sensorThresh && state5 == 0 && millis() - time > debounce) {
      state5 = 1;
      time = millis();
    }
  }
  if (state5 == 1) {
    leds[4] = CHSV( hue1, 255, brightness);
    FastLED.show();
    if (sensor5 > sensorThresh && state5 == 1 && millis() - time > debounce) {
      state5 = 0;
      time = millis();
    }
  }
  // LED 6
  if (state6 == 0) {
    leds[5] = CRGB::Black;
    FastLED.show();
    if (sensor6 > sensorThresh && state6 == 0 && millis() - time > debounce) {
      state6 = 1;
      time = millis();
    }
  }
  if (state6 == 1) {
    leds[5] = CHSV( hue1, 255, brightness);
    FastLED.show();
    if (sensor6 > sensorThresh && state6 == 1 && millis() - time > debounce) {
      state6 = 0;
      time = millis();
    }
  }
  // LED 7
  if (state7 == 0) {
    leds[6] = CRGB::Black;
    FastLED.show();
    if (sensor7 > sensorThresh && state7 == 0 && millis() - time > debounce) {
      state7 = 1;
      time = millis();
    }
  }
  if (state7 == 1) {
    leds[6] = CHSV( hue1, 255, brightness);
    FastLED.show();
    if (sensor7 > sensorThresh && state7 == 1 && millis() - time > debounce) {
      state7 = 0;
      time = millis();
    }
  }
  // LED 8
  if (state8 == 0) {
    leds[13] = CRGB::Black;
    FastLED.show();
    if (sensor8 > sensorThresh && state8 == 0 && millis() - time > debounce) {
      state8 = 8;
      time = millis();
    }
  }
  if (state8 == 1) {
    leds[13] = CHSV( hue2, 255, brightness);
    FastLED.show();
    if (sensor8 > sensorThresh && state8 == 1 && millis() - time > debounce) {
      state8 = 0;
      time = millis();
    }
  }
  // LED 9
  if (state9 == 0) {
    leds[12] = CRGB::Black;
    FastLED.show();
    if (sensor9 > sensorThresh && state9 == 0 && millis() - time > debounce) {
      state9 = 1;
      time = millis();
    }
  }
  if (state9 == 1) {
    leds[12] = CHSV( hue2, 255, brightness);
    FastLED.show();
    if (sensor9 > sensorThresh && state9 == 1 && millis() - time > debounce) {
      state9 = 0;
      time = millis();
    }
  }
  // LED 10
  if (state10 == 0) {
    leds[11] = CRGB::Black;
    FastLED.show();
    if (sensor10 > sensorThresh && state10 == 0 && millis() - time > debounce) {
      state10 = 1;
      time = millis();
    }
  }
  if (state10 == 1) {
    leds[11] = CHSV( hue2, 255, brightness);
    FastLED.show();
    if (sensor10 > sensorThresh && state10 == 1 && millis() - time > debounce) {
      state10 = 0;
      time = millis();
    }
  }
  // LED 11
  if (state11 == 0) {
    leds[10] = CRGB::Black;
    FastLED.show();
    if (sensor11 > sensorThresh && state11 == 0 && millis() - time > debounce) {
      state11 = 1;
      time = millis();
    }
  }
  if (state11 == 1) {
    leds[10] = CHSV( hue2, 255, brightness);
    FastLED.show();
    if (sensor11 > sensorThresh && state11 == 1 && millis() - time > debounce) {
      state11 = 0;
      time = millis();
    }
  }
  // LED 12
  if (state12 == 0) {
    leds[9] = CRGB::Black;
    FastLED.show();
    if (sensor12 > sensorThresh && state12 == 0 && millis() - time > debounce) {
      state12 = 1;
      time = millis();
    }
  }
  if (state12 == 1) {
    leds[9] = CHSV( hue2, 255, brightness);
    FastLED.show();
    if (sensor12 > sensorThresh && state12 == 1 && millis() - time > debounce) {
      state12 = 0;
      time = millis();
    }
  }

  // Output the values in a readable format for troubleshooting
  Serial.print(sensor1);
  Serial.print("    ");
  Serial.print(sensor2);
  Serial.print("    ");
  Serial.print(sensor3);
  Serial.print("    ");
  Serial.print(sensor4);
  Serial.print("    ");
  Serial.print(sensor5);
  Serial.print("    ");
  Serial.print(sensor6);
  Serial.print("    ");
  Serial.print(sensor7);
  Serial.print("         ");
  Serial.print(sensor8);
  Serial.print("    ");
  Serial.print(sensor9);
  Serial.print("    ");
  Serial.print(sensor10);
  Serial.print("    ");
  Serial.print(sensor11);
  Serial.print("    ");
  Serial.print(sensor12);
  Serial.print("    ");
  //  Serial.print(sensor13);
  Serial.print("    ");
  // Serial.print(sensor14);
  //create newline
  Serial.println();

}
