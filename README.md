# CB350
This is an Arduino project to controll the electrical functions on a 1973 Honda CB350. It is a custom built bike that has everything converted to LEDs. I'm using an Adafruit Pro Trincket as the controller, three 12 channel LED drivers and 3 relays for the high current stuff. This does not interact with the engine's ignition or charging systems. The engine will still run and charge without the controller.

Inputs:
1. Headlight switch (low and high beam)
2. Turn signal switch (left and right)
3. Horn button
4. Brake switch
5. Neutral switch

Outputs:
1. LED drivers
2. Low beam relay
3. High beam relay
4. Horn relay

Update: I was having issues with TLC59711 led driver. When a channel would change state other channels would output a single blink (a few milliseconds duration). The fix for this was to change a few values in the Adafruit_TLC59711.cpp library. On lines 46 and 63 the value of 1000000 was changed to 200000. This stopped the unintentional blinking. 