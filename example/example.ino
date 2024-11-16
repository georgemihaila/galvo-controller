#include "SerialGCodeParser.h"

#define default_clock 3, 4 // Blue + white
#define default_syn 7, 8   // Orange + white
#define default_x 5, 6     // Brown + white
#define default_y 10, 9    // Green + white
#define default_pins default_clock, default_syn, default_x, default_y

XY2_100 *galvo;
Laser *laser;
SerialGCodeParser *parser;

void setup() {
  galvo = new XY2_100(default_pins);
  laser = new Laser(11, 5, 1000, 0.5);
  parser = new SerialGCodeParser(9600, galvo, laser);
}

void loop() { parser->listen(); }
