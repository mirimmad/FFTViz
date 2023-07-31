#include "fft.h"
#include "common.h"
#include <raylib.h>




static int currFrames[1024];
int frameCount = 0;
static complex double currFFT[1024];
static unsigned int dbValues[1024];
static int channels;

void AudioCallBack(void * buffer, unsigned int Nframes) {
	//printf("%u ", Nframes);
	// 16-bit samples
	int32_t * buffer_c = (int32_t *) buffer;
	frameCount = Nframes;
	// Number of samples = Number of frames * Number of channels
	for (int i = 0; i < Nframes * channels; i++) {
		currFrames[i] = buffer_c[i];
	}
	
}



int main() {
   
	test_FFT();
	InitWindow(800, 500, "FFTViz");
	InitAudioDevice();
	
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();
	int BarWidth = screenWidth / 1024;

	const char * filename = "audio/bass.wav";
	Music m = LoadMusicStream(filename);
	//TODO : Handle possible errors from above
	int sampleSize = m.stream.sampleSize;
	channels = m.stream.channels;
	printf("Sample Size = %d\nChannles = %d\n", sampleSize, channels);
	FFTAssert(sampleSize == 32, "We are only looking at 32 bit sample sizes for now.");
	AttachAudioStreamProcessor(m.stream, AudioCallBack);
	PlayMusicStream(m);	

	// Set up the frequency bars
	Rectangle recs[1024];
	for (int i = 0; i < 1024; i++) {
		recs[i].width = (BarWidth > 1) ? BarWidth : 10; 
		recs[i].height = 0; // To be set later
		//recs[i].x = (0 + (i * BarWidth + 2));
		recs[i].x = i * recs[i].width + 2;
		recs[i].y = screenHeight / 2;
	}
	
	
	while(! WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		UpdateMusicStream(m);
		if (IsKeyDown(KEY_SPACE)) {
			PauseMusicStream(m);
		} else {

			ResumeMusicStream(m);
			//printFrames(currFrames, frameCount);
			//printf("%d ", frameCount);
			FFT(currFrames, currFFT, frameCount);
			dbScale(currFFT, dbValues, frameCount);
			//printValues(absoluteValues, frameCount);
			//printf("\n");

			// Draw the spectogram

			for (int i = 0 ; i < 1024; i++) {
				recs[i].height = -dbValues[i];
				DrawRectangleRec(recs[i], RAYWHITE);
			}

			
		}
		
		
		//DrawText("Hello", 190, 200, 20, RAYWHITE);
		EndDrawing();
	}

	CloseAudioDevice();
	CloseWindow(); 
	


    return 0; 
}
