#include "SerialGCodeParser.h"

#define default_clock 3, 4 // Blue + white
#define default_syn 7, 8   // Orange + white
#define default_x 5, 6     // Brown + white
#define default_y 10, 9    // Green + white
#define default_pins default_clock, default_syn, default_x, default_y

XY2_100 *galvo;
SerialGCodeParser *parser;

void setup() {
  galvo = new XY2_100(default_pins);
  parser = new SerialGCodeParser(115200, galvo);
}

void loop() { parser->listen(); }
