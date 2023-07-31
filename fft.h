#ifndef FFT_H
#define FFT_H

#include <math.h>
#include <complex.h>
#include "common.h"

void FFT(int * sig, complex double * out, int N);
void dbScale(complex double * z, unsigned int * out,  int N);
void printValues(int * absolutes, int N);
void test_FFT();

#endif
