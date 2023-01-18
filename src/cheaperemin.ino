#include <pitches.h>

#include <MedianFilter.h>
#include <SharpDistSensor.h>

#include <Volume.h>

//Pin constants
#define volPin A0
#define pitchPin A1
#define incOctavePin 7
#define decOctavePin 8

//Previous click variables for single click buttons
uint8_t prevIncOctave;
uint8_t prevDecOctave;

// Window size of the median filter (odd number, 1 = no filtering)
const byte medianFilterWindowSize = 5;

//Starting pitches and octave difference references (The instrument's range is from C3->C6, One octave at a time)
const int startPitches[] = {NOTE_C4, NOTE_C5, NOTE_C6};
const int octaveDiff[] = {OCTAVE_4, OCTAVE_5, OCTAVE_6};

int currentOctave = 0;

//IR Sensor objects
SharpDistSensor volSensor = SharpDistSensor(volPin, medianFilterWindowSize); //Volume IR sensor, goes in pin A0
SharpDistSensor pitchSensor = SharpDistSensor(pitchPin, medianFilterWindowSize); //Pitch IR sensor, goes in pin A1

//Volume object, buzzer/speaker goes in pin 5
Volume vol;

void setup() {
  Serial.begin(9600);
  //Setting the buttons to read from
  pinMode(incOctavePin, INPUT);
  pinMode(decOctavePin, INPUT);

  //Reading in the previous variables
  prevIncOctave = digitalRead(incOctavePin);
  prevDecOctave = digitalRead(decOctavePin);

  //Setting the models for the sensor objects
  volSensor.setModel(SharpDistSensor::GP2Y0A21F_5V_DS);
  pitchSensor.setModel(SharpDistSensor::GP2Y0A21F_5V_DS);

  //Starting the volume object
  vol.begin();
}

void loop() {
  if (volumeControl() > 0.0 && pitchControl() != 0) {
    vol.setMasterVolume(volumeControl());
    vol.tone(pitchControl(),255);
  } else {
    vol.setMasterVolume(0);
  }

  octaveSwitch();
}

//Switches octaves through clicking the octave up/down buttons
void octaveSwitch() {
  uint8_t incOctave = digitalRead(incOctavePin);
  uint8_t decOctave = digitalRead(decOctavePin);

  if (incOctave == LOW && prevIncOctave == HIGH) {
    if (currentOctave < 2) {
      currentOctave++;
      Serial.println(currentOctave);
    }
  }

  if (decOctave == LOW && prevDecOctave == HIGH) {
    if (currentOctave > 0) {
      currentOctave--;
      Serial.println(currentOctave);
    }
  }

  prevIncOctave = digitalRead(incOctavePin);
  prevDecOctave = digitalRead(decOctavePin);
}

//Sets the volume of the buzzer/speaker in range [8, 16] cm
float volumeControl() {
  float distance = volSensor.getDist() / 10.0;
  if (distance >= 7.9 && distance <= 9.9) { //[1.00, 0.88] for the first 2 cm
    return constrain((8.0 / distance) * 1.1, 0.0, 1.0);
  } else if (distance >= 10.0 && distance <= 11.9) { //[0.64, 0.54] for the next 2 cm
    return constrain(8.0 / (distance * 1.25), 0.0, 1.0);
  } else if (distance >= 12.0 && distance <= 13.9) { //[0.33, 0.28] for the next 2 cm
    return constrain(8.0 / (distance * 2), 0.0, 1.0);
  } else if (distance >= 14.0 && distance <= 16.1) { //[0.14, 0.12] for the last 2 cm
    return constrain(8.0 / (distance * 4), 0.0, 1.0);
  } else {
    return 0.0;
  }
}

//Sets the pitch of the buzzer/speaker in range [10, 30] cm
int pitchControl() {
  int distance = pitchSensor.getDist();
  if (distance >= 99 && distance <= 301) {
    int mappedPitch = map(distance, 100, 300, startPitches[currentOctave], startPitches[currentOctave] + octaveDiff[currentOctave]);
    return constrain(mappedPitch, startPitches[currentOctave], startPitches[currentOctave] + octaveDiff[currentOctave]);
  } else {
    return 0.0;
  }
}