/*
*   waveboard.ino
*   
*   Sketch for assignment 1 for ESP32C3 Dev Module
*   Nikolaus Scherwitzel (H00298068)
*   Created: 12/02/23
*/

#include "wavegen.h"

// Globals
uint8 switchActive;  // State of switch for turning on/off pulse stream
uint8 switchMode;    // State of switch for changing between 'normal' and 'modified' waveform
uint8 mode;          // State to tell what waveform to generate ('normal' or 'modified')

void setup() {
  Serial.begin(9600);

  // Inputs
  pinMode(SWITCHACT_PIN, INPUT);
  pinMode(SWITCHMODE_PIN, INPUT);

  // Outputs
  pinMode(SIGA_PIN, OUTPUT);
  pinMode(SIGB_PIN, OUTPUT);
}

void genSigA(uint16 pWidth, uint16 pSpace, uint8 pNum, uint16 pbGap, uint8 mode, uint8 pIter) {
  // Variables for controlling for loop
  int start;
  int end;
  int modifier;  
  switch (mode) {
    // Normal waveform
    case 1:
      start = 0;
      end = pNum;
      modifier = 1;
      break;
    // Generate inverted form of complete SigA waveform
    case 2:
      start = pNum - 1;
      end = -1;
      modifier = -1;
      break;
    // Insert an extra 3 pulses into pulse block
    case 3:
      break;
    // Half d and b time
    case 4:
      break;
  }

  // Generate pulse stream
  for (int i = start; i != end; i += modifier){
    digitalWrite(SIGA_PIN, HIGH);
    delayMicroseconds((i * pIter) + pWidth);
    digitalWrite(SIGA_PIN, LOW);
    delayMicroseconds(pSpace);
  }
  // Pulse train finished
  delayMicroseconds(pbGap);
}

void genSigB(uint16 pWidth, bool debug) {

  // Generate pulse
  digitalWrite(SIGB_PIN, HIGH);
  delayMicroseconds(pWidth);
  digitalWrite(SIGB_PIN, LOW);
}

void loop() {
  // Read input switches
  switchActive = digitalRead(SWITCHACT_PIN);
  switchMode = digitalRead(SWITCHMODE_PIN);

  // If mode switch on, create 'modified' waveform, otherwise 'normal'
  uint8 mode = 1;
  if (switchMode == HIGH) {
    mode = MODE;
  }

  // Generate signal A & B unless on/off switch is pressed
  if (switchActive == LOW) {
    genSigB(SIGBWIDTH);
    genSigA(PWIDTH, PSPACE, PNUM, PBGAP, mode, PITER);
  }

}
