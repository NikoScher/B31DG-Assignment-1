#include "wavegen.h"

// Globals
uint8 switch1;  // State of switch 1 for turning on/off pulse stream
uint8 switch2;  // State of switch 2 for changing between 'normal' and 'modified' waveform
uint8 debug;    // Debug state: Debug mode multiplies all signal lengths by DMOD (found in wavegen.h)
uint8 mode;     // State to tell what waveform to generate ('normal' or 'modified')

void setup() {
  Serial.begin(9600);
  debug = 0;

  // Inputs
  pinMode(SWITCH1_PIN, INPUT);
  pinMode(SWITCH2_PIN, INPUT);

  // Outputs
  pinMode(SIGA_PIN, OUTPUT);
  pinMode(SIGB_PIN, OUTPUT);
}

void genSigA(uint16 pWidth, uint16 pSpace, uint8 pNum, uint16 pbGap, uint8 mode, uint8 pIter, bool debug) {
  int start;
  int end;
  int modifier;  
  switch (mode) {
    case 0:
      start = 0;
      end = pNum;
      modifier = 1;
      break;
    case 2:
      start = pNum - 1;
      end = -1;
      modifier = -1;
      break;
  }

  for (int i = start; i != end; i += modifier){
    digitalWrite(SIGA_PIN, HIGH);
    delayMicroseconds((i * pIter) + pWidth);
    digitalWrite(SIGA_PIN, LOW);
    delayMicroseconds(pSpace);
  }
  delayMicroseconds(pbGap);
}

void genSigB(uint16 pWidth, bool debug) {
  // Check for debug
  uint16 widthTotal = pWidth;
  if (debug) {
    widthTotal *= DMOD;
  }

  // Generate pulse
  digitalWrite(SIGB_PIN, HIGH);
  delayMicroseconds(widthTotal);
  digitalWrite(SIGB_PIN, LOW);
}

void loop() {
  // Read input switches
  switch1 = digitalRead(SWITCH1_PIN);
  switch2 = digitalRead(SWITCH2_PIN);

  // If both switches on then use debug mode
  if (switch1 && switch2) {
    debug = 1;
  }

  // If switch 2 on, create 'modified' waveform, otherwise 'normal'
  uint8 mode = 0;
  if (switch2 == HIGH) {
    mode = MODE;
  }

  // Generate waveforms unless switch 1 is pressed
  if (switch1 == LOW) {
    genSigB(SIGBWIDTH, debug);
    genSigA(PWIDTH, PSPACE, PNUM, PBGAP, mode, PITER, debug);
  }

}
