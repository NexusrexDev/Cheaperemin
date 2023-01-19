# Cheaperemin
An attempt to replicate the behavior of a Theremin using an Arduino.

## Info
**Current version:** 1.0

**Current scheme:**

<img src = "https://github.com/NexusrexDev/Cheapermin/blob/main/img/cheaperemin_v1.png" width = "500">

**Current components:**
- 1 Arduino UNO
- 2 Sharp IR Sensor (10-80cm) - GP2Y0A21YK0F
- 2 push buttons
- 2 10kΩ resistors
- 1 220Ω resistors
- 1 5V buzzer

## Goals
- [x] Create the base behavior of a theremin using the current components
- [ ] Use a proper audio output instead of the buzzer

## Notes
1. [Version 1 notes](https://github.com/NexusrexDev/Cheapermin/blob/main/docs/notes_v1.md)

## Acknowledgements and dependencies
Used libraries:
- Connor Nishijima's [**Volume Control library**](https://github.com/connornishijima/arduino-volume1) to control the volume of the buzzer.
- DrGFreeMan's [**SharpDistSensor library**](https://github.com/DrGFreeman/SharpDistSensor) to use the sensors.
- Arduino's *pitches.h* from the [**tone() tutorial**](https://docs.arduino.cc/built-in-examples/digital/toneMelody), although slightly modified to include the distance of every octave.
