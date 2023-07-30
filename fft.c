

#include "common.h"
#include "fft.h"


void FFT_main(int * , complex double * , int);

void PrintVector(complex double * v, int N) {
  for (int i = 0; i < N; i++) {
    printf("(%f %fi) ", creal(v[i]), cimag(v[i]));
  }
  printf("\n");
}


// pre-compute powers of e^((2 * pi * i) / N)
static complex double * zeta_power_table;
void ComputeZetaPowerTable(int N) {
  complex double * mem = malloc(sizeof(complex double) * (N / 2));
  complex double zeta = cexp((-2 * M_PI * I) / N);
  for (int i = 0; i < N / 2; i++) {
    mem[i] = cpow(zeta, i);
  }
  zeta_power_table = mem;
}



void FFT(int * sig, complex double * out, int N) {
  ComputeZetaPowerTable(N);
  FFT_main(sig, out, N);
}


void FFT_main(int * sig, complex double * out, int N) {
    // N is assumed to be a power of two.
    if ( N == 1) {
        complex double p = sig[0] + 0i;
        out[0] = p;
        return;
    }
    // Separate even and odd indices of the signal.
    int Pe[N/2], Po[N/2];
    for (int i = 0; i < (N/2); i++) {
        Pe[i] = sig[2 * i];
        Po[i] = sig[(2 * i) + 1];
    }
    
    // Arrays that hold the DFTs of the even and odd indices.
    complex double Ye[N/2], Yo[N/2];
    
    // Here the polynomial is of the degree N / 2, hence reuducing the computation.
    FFT_main(Pe, Ye, N/2); 

    FFT_main(Po, Yo, N/2);

    for (int j = 0; j < N / 2; j++) {
      out[j] = Ye[j] + zeta_power_table[j] * Yo[j];
      out[j + (N / 2)] = Ye[j] - zeta_power_table[j] * Yo[j];
    }


}

void test_FFT() {
    // Write C code here
    complex double x = 1 + 0i;
   // printf("Hello world %f", creal(x));
    int sig[4] = {5,3,2,1};
    complex double out[4] = {0};
    FFT(sig, out, 4);
    PrintVector(out, 4);
}
