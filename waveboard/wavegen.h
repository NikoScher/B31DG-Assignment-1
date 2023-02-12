/*
*   wavegen.h
*   
*   Header file for assignment 1 for ESP-C3-M1-I-Kit
*   Nikolaus Scherwitzel (H00298068)
*   Created: 12/02/23
*/

#ifndef __WAVEGEN_H__
#define __WAVEGEN_H__

// Pin numbers
#define SIGA_PIN    0   // Signal A: Output to LED or oscilloscope
#define SIGB_PIN    1   // Signal B: Output, static waveform
#define SWITCH1_PIN 5   // Switch 1: Enable/disable pulse stream
#define SWITCH2_PIN 6   // Switch 2: Run normal/modified pulse stream

// Unique parameters to construct signal A
#define PWIDTH 800  // s = 8: 8 * 100us
#define PSPACE 300  // c = 3: 3 * 100us
#define PNUM   12   // h = 8: 8 + 4 pulses
#define PBGAP  2500 // e = 5: 5 * 500us
#define MODE   2    // r = 9: rem(9 / 4) + 1

#define DMOD   1000 // Debug modifier: Multiplies whole signal by constant

// Includes for debugging
//#include <stdio.h>
//#include <stdlib.h>

// Helpful typedefs
typedef unsigned char uint8;
typedef unsigned int uint16;

// Function prototypes to generate signal A & B
void genSigA(uint16 pWidth, uint16 pSpace, uint8 pNum, uint16 pbGap, uint8 mode);
void genSigB(uint16 pWidth);

#endif  // __WAVEGEN_H__