#include "common.h"

void printSampleValues(int * buffer, int Nframes) {

    for (int i = 0; i < Nframes; i++) {
		int sample = buffer[i];
		printf("%d ", sample);
	}
	printf("\n"); 
}

void FFTAssert(int exp, const char * message) {
    if (! exp) {
        printf("%s\n", message);
        exit(0);
    }
}