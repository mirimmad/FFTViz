#ifndef FFT_H
#define FFT_H

#include <math.h>
#include <complex.h>
#include "common.h"

void FFT(float * sig, complex double * out, int N);
void dbScale(complex double * z, float * out,  int N);
void printValues(float * absolutes, int N);
void PrintVector(complex double * v, int N);
void test_FFT();

#endif
