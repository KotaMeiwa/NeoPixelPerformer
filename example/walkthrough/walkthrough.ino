// SPDX-FileCopyrightText: 2023 Kota Meiwa
// SPDX-License-Identifier: MIT

#if defined(ARDUINO_ARCH_SPRESENSE) //for Sony Spresense environment
  #include <Adafruit_NeoPixel_Spresense.h>	//managed by nepils
  typedef Adafruit_NeoPixel_Spresense NEOPIXEL_CLASS;
#else                               //Other Almost Arduino platforms are supported by Adafruit library
  #include <Adafruit_NeoPixel.h>	          //managed by Adafruit
  typedef Adafruit_NeoPixel NEOPIXEL_CLASS;
#endif  //ARDUINO_ARCH_SPRESENSE

#include <NeoPixelPerformer.h>

const uint16_t NUM_PIXELS = 12;
const uint16_t PIN = 6;

NEOPIXEL_CLASS neopixel(NUM_PIXELS, PIN);
CNeoPixelPerformer<NEOPIXEL_CLASS> performer(&neopixel);

void setup()
{
    Serial.begin(115200);
    delay(1000);

  neopixel.begin();

  Serial.println("serial console start!");
}

void loop()
{
  uint32_t rgb0 = 0;
  uint32_t rgb1 = 0;

  //Blink
  performer.blink(500, neopixel.Color(64, 16, 0), neopixel.Color(64, 0, 0));

  //Transition
  rgb0 = Adafruit_NeoPixel::Color(16, 16, 0);
  rgb1 = Adafruit_NeoPixel::Color(16, 0, 16);
  performer.transition_2colors(3000, rgb0, rgb1, false);
  performer.transition_2colors(3000, rgb0, rgb1, true);

  //Moving Block
  rgb0 = Adafruit_NeoPixel::Color(16, 16, 0);
  rgb1 = Adafruit_NeoPixel::Color(0, 16, 16);
  performer.moving_block(1000, 3, rgb0, rgb1, false);
  performer.moving_block(1000, 3, rgb0, rgb1, true);

  //Water flow
  rgb0 = Adafruit_NeoPixel::Color(16, 16, 0);
  rgb1 = Adafruit_NeoPixel::Color(0, 16, 16);
  performer.water_flow(1500, rgb0, rgb1, false);
  performer.water_flow(1500, rgb0, rgb1, true);

  //Center to Edge
  rgb0 = Adafruit_NeoPixel::Color(16, 16, 0);
  rgb1 = Adafruit_NeoPixel::Color(0, 0, 0);
  performer.center2edge(500, rgb0, rgb1, false);
  performer.center2edge(1000, rgb0, rgb1, true);

  //Fountain
  rgb0 = Adafruit_NeoPixel::Color(16, 16, 0);
  rgb1 = Adafruit_NeoPixel::Color(0, 0, 0);
  performer.fountain(2000, 2, 3, rgb0, rgb1);
}
