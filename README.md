# NeoPixelPerformer
Making performance with NeoPixel LED strup on Arduino platform, this utilizes adafruit / Adafruit_NeoPixel as a library for handling of NeoPixel.

## Version history
| Version # | Release date  | Changes                                               |
| ---        | ---         | ---                                                              |
| Ver. 0.1.0     | 2023-05-01  | First release                                          |

## Installation
**For minimum setup to use this library with adafruit / Adafruit_NeoPixel**

First of all installation of adafruit / Adafruit_NeoPixel
1. Go to the Releases page.
1. Download [the latest release](https://github.com/adafruit/Adafruit_NeoPixel/releases) (select ZIP type package).
1. In the Arduino IDE, go to the menu "Sketch > Include Library > Add .ZIP Library"

Next, installation of this library. Same operation of above installation.
1. Go to the Releases page.
1. Download [the latest release](https://github.com/KotaMeiwa/NeoPixelPerformer/releases) (select ZIP type package).
1. In the Arduino IDE, go to the menu "Sketch > Include Library > Add .ZIP Library"

## API
- void blink(ulong interval, uint32_t color_front, uint32_t color_back = 0)
- void transition_2colors(ulong duration, uint32_t rgb0, uint32_t rgb1, bool reverse=false)
- void moving_block(ulong duration, uint16_t width, uint32_t color_front, uint32_t color_back=0, bool reverse=false)
- void water_flow(ulong duration, uint32_t color_front, uint32_t color_back=0, bool reverse=false)

## Supported Arduino board
It depends on the library for NeoPixel which is used in your software. If you use adafruit / Adafruit_NeoPixel, see also Readme.md in [the repository](https://github.com/adafruit/Adafruit_NeoPixel).

## License
This software is distributed under MIT license, in detail see also [LICENSE](/LICENSE).

## Copyright
Copyright 2023 Kota Meiwa
