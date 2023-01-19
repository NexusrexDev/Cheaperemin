# Version 1 notes

## Current components
<img src = "https://github.com/NexusrexDev/Cheapermin/blob/main/img/cheaperemin_v1.png" width = "500">

## Current scheme
- 1 Arduino UNO
- 2 Sharp IR Sensor (10-80cm) - GP2Y0A21YK0F
- 2 push buttons
- 2 10kΩ resistors
- 1 220Ω resistors
- 1 5V buzzer

## How it works
- The IR sensor on the left, controls volume, aiming upwards. Ranging from 10-16 cms, volume increases as the hand gets closer.
- The IR sensor on the right, controls pitch, aiming sideways. Ranging from 10-30 cms, pitch increases as the hand gets farther.
- The push button on the right increases the pitch range by an octave, the one on the left decreases the pitch. (Starting pitches are C4, C5, C6)

## Notes
- Consider to replace the buzzer with a speaker or a headphone jack, buzzer's too low and it doesn't sound as good when switching to lower volumes.
- Try to use a capacitor/lowpass filter along with the sensors to lower the noise.
- Try to clean the code up if possible.
