## galvo-controller
 A library for allowing devices implementing the [XY2-100 protocol](https://github.com/georgemihaila/xy2-100) to be able to parse G-Code in order to control them in real time.

### Usage:

1. Initialize dependencies

```cpp
XY2_100 *galvo = new XY2_100(...);
Laser *laser new Laser(...);
SerialGCodeParser *parser = new SerialGCodeParser(115200, galvo, laser);
```

2. Make the parser listen continuously in the ```loop()``` method

```cpp
void loop() { 
  parser->listen();
}
```

That's all.