# SmartCoaster
When I'm working, I get so focused that I forget to drink water. It's not that I'm not thirsty—oh, I am—but I'll get a glass of water, put it down on my desk, and forget all about it for hours.

The Smart Coaster is meant to help with that bad habit by giving me an easy visualization of how long it's been since I last took a drink. It does this simply by running through a program that changes the color and brightness of LEDs over time, with a momentary switch that is pressed down by the weight of a glass on top of it. When I pick up a glass and put it back down, it resets the timer. If it's been way too long since I last took a sip, the lights will blink until I do something about it.

This device isn't meant to track consumption, log data, or help achieve any quantity goals. It's just here to remind me, once in a while, to reach over and take a sip.

## Board Design
The lights are driven by a small Arduino board, like the Micro or Adafruit ItsyBitsy—it's developed on and tested with Atmel 32U4-based boards, but just about any controller should work.

**V1**
The first prototype coaster uses four WS2812B RGB LED chips and the Adafruit NeoPixel Arduino library. They're tied into pin 6 of the microcontroller and fed instructions to change color based on the counter value.

**V2**
The second prototype uses four-pin common cathode RGB LEDs connected to three PWM pins on the microcontroller. Color values are set by directly analogWriting to the R, G and B pins. Since all the lights are showing the same color value, this seems like a simpler solution.

V2 also introduced a potentiometer control for setting the alert time.
