#include "fft.h"


void FFT_main(int * , complex double * , int);

void PrintVector(complex double * v, int N) {
  for (int i = 0; i < N; i++) {
    printf("(%f %fi) ", creal(v[i]), cimag(v[i]));
  }
  printf("\n");
}

void printValues(float * absolutes, int N) {
  for (int i = 0; i < N; i++) {
    printf("%d ", absolutes[i]);
  }
  printf("\n");
}



void FFT(float * sig, complex double * out, int N) {
    //FFTAssert(0, "N must be greater than 0.");
    if (N == 0) return;
    // N is assumed to be a power of two.
    if ( N == 1) {
        complex double p = sig[0] + 0i;
        out[0] = p;
        return;
    }

    complex double zeta = cexp((2 * M_PI * I) / N);

    // Separate even and odd indices of the signal.
    float Pe[N/2], Po[N/2];
    for (int i = 0; i < (N/2); i++) {
        Pe[i] = sig[2 * i];
        Po[i] = sig[(2 * i) + 1];
    }
    
    // Arrays that hold the DFTs of the "even" and "odd" signals.
    complex double Ye[N/2], Yo[N/2];
    
    // Here the polynomial is of the degree N / 2, hence reuducing the computation.
    FFT(Pe, Ye, N/2); 

    FFT(Po, Yo, N/2);

    for (int j = 0; j < N / 2; j++) {
      out[j] = Ye[j] + cpow(zeta, j) * Yo[j];
      out[j + (N / 2)] = Ye[j] - cpow(zeta, j) * Yo[j];
    }


}

void dbScale(complex double * z, float * out, int N) {
  // Calculate magnitude of the vectors and then
  // convert each to dB scale.

  for (int i = 0; i < N; i++) {
    float abs = cabs(z[i]);
    if (abs > 0.0f)
      out[i] = 20 * log10(abs);
    else 
      out[i] = 0;

  }
}

void test_FFT() {
    // Write C code here
    complex double x = 1 + 0i;
   // printf("Hello world %f", creal(x));
    float sig[8] = {5.0f,3.0f,2.0f,1.0f,-1.0f,-2.0f,-3.0f,-4.0f};
    int sig2[8] = {1, -1, 1, -1, 1, -1, 1, -1};
    int sig3[8] = {1,1,1,1,1,1,1,1};
    complex double out[8] = {0};
    FFT(sig, out, 8);
    PrintVector(out, 8);
    for (int i = 0 ; i < 8; i++) {
      printf("%f ", cabs(out[i]));
    }
    printf("\n");
}
