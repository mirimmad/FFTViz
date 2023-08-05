#include "fft.h"
#include "common.h"
#include <raylib.h>




static float currValues[1024];
int frameCount = 0;
static complex double currFFT[1024];
static int channels;

void AudioCallBack(void * buffer, unsigned int frames) {
	float * samples = (float *) buffer;
	float left;
	float right;
	frameCount = frames;
	for (int frame = 0; frame < frames; frame++) {
		left = samples[frame * 2 + 0];
		right = samples[frame * 2 + 1];
		//printf("%f ", fabsf(left));
		currValues[frame] = left;
	}	
	
	//printf("\n\n");
}



int main() {
   
	test_FFT();
	InitWindow(800, 500, "FFTViz");
	InitAudioDevice();
	
	int screenWidth = GetRenderWidth();
	int h = GetRenderHeight();
	float BarWidth;

	const char * filename = "audio/melody.wav";
	Music m = LoadMusicStream(filename);
	//TODO : Handle possible errors from above
	int sampleSize = m.stream.sampleSize;
	channels = m.stream.channels;
	printf("Sample Size = %d\nChannles = %d\n", sampleSize, channels);
	FFTAssert(sampleSize == 32, "We are only looking at 32 bit sample sizes for now.");
	AttachAudioStreamProcessor(m.stream, AudioCallBack);
	PlayMusicStream(m);	
	
	
	while(! WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		UpdateMusicStream(m);
		if (IsKeyDown(KEY_SPACE)) {
			PauseMusicStream(m);
		} else {

			ResumeMusicStream(m);
			//printFrames(currValues, frameCount);
			//printf("%d ", frameCount);
			FFT(currValues, currFFT, frameCount);
			//PrintVector(currFFT, frameCount);
			//dbScale(currFFT, dbValues, frameCount);
			//printValues(dbValues, frameCount);
			//printf("\n");

			// Draw the spectogram

			BarWidth = (float)screenWidth / frameCount;
			for (int i = 0; i < frameCount; i++) {

				//printf("%f, ", cabs(currFFT[i])) * h/2;
				float t = cabs(currFFT[i]);
				//if (!((i >=10 & i <= 400) && (h / 2 * t > 100) ))
				DrawRectangle(i * BarWidth, h / 2 - h/2 * t, BarWidth,  h/2  * t, RAYWHITE);
				//DrawRectangle(i * BarWidth, h / 2 - t, BarWidth, t, RAYWHITE);
			

			}
			//printf("\n\n");

			
		}
		
		
		
		EndDrawing();
	}

	CloseAudioDevice();
	CloseWindow(); 
	


    return 0; 
}
