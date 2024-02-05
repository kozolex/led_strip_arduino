#include <Adafruit_NeoPixel.h>
//#include <Bounce2.h>

#define PIN 6
#define NUM_LEDS 20
#define BUTTON_PIN 3
#define POT_PIN A4
#define DELAY 10
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
Bounce debouncer = Bounce();

int mode = 0;
int buttonState = 0;

void setup() {
  strip.begin();
  strip.show();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  //debouncer.attach(BUTTON_PIN);
  //debouncer.interval(1);
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(POT_PIN);
  int brightness = map(potValue, 0, 1023, 0, 255);
  strip.setBrightness(brightness);
  buttonState = digitalRead(BUTTON_PIN);
  //debouncer.update();
  if (buttonState == LOW) {
      mode = mode + 1;
      if (mode > 8){
        mode=0;
      }
      Serial.println(mode);
    } 
  switch (mode) {
    case 0:
      colorWipe(strip.Color(255, 255, 255), DELAY); // Cold white color
      break;
    case 1:
      colorWipe(strip.Color(255, 147, 41), DELAY); // Warm white color
      break;
    case 2:
      colorWipe(strip.Color(255, 0, 0), DELAY); // Red color
      break;
    case 3:
      colorWipe(strip.Color(0, 255, 0), DELAY); // Green color
      break;
    case 4:
      colorWipe(strip.Color(0, 0, 255), DELAY); // Blue color
      break;
    case 5:
      colorWipe(strip.Color(128, 0, 128), DELAY); // Purple color
      break;
    case 6:
      flameEffect(DELAY);
      break;
    case 7:
      knightRider(DELAY);
      break;
    case 8:
      rainbowCycle(DELAY);
      break;
    
  }
}

// Add your effect functions here
void turnOffLeds() {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
}

// Color wipe function
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

// Flame effect function
void flameEffect(int wait) {
  for(int i=0; i<NUM_LEDS; i++) {
    int flicker = random(0,95);
    int r1 = random(200,255);
    int g1 = random(100,160);
    int b1 = 0;
    r1=r1-flicker;
    g1=g1-flicker;  
    strip.setPixelColor(i, strip.Color(r1,g1,b1));
  }
  strip.show();
  delay(random(wait, wait+50)); 
}

// Rainbow cycle function
void rainbowCycle(int wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    //delay(wait);
  }
}

// Knight Rider effect function
void knightRider(int wait) {
  for(int i=0; i<NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(255, 0, 0));
    strip.show();
    delay(wait);
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }

  for(int i=NUM_LEDS-1; i>=0; i--) {
    strip.setPixelColor(i, strip.Color(255, 0, 0));
    strip.show();
    delay(wait);
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
}

// Wheel function for the rainbow cycle
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

