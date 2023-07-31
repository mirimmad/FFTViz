#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


void printFrames(int* buffer, int Nframes);
void FFTAssert(int exp, const char * message);

#endif
