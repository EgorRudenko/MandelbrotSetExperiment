#include <stdio.h>
#include <SDL2/SDL.h>

#ifndef M_PI
#define M_PI (3.14)
#endif

#define FREQ 44100

float normalDistribution(float, float, float, float);
float freqToNum(float);
void func_callback(void *, Uint8 *, int);
int dur = 120000;


int soundGen(int freq[][1000], int H) {
    SDL_Init(SDL_INIT_AUDIO);

    // the representation of our audio device in SDL:
    SDL_AudioDeviceID audio_device;

    // opening an audio device:
    SDL_AudioSpec audio_spec;
    SDL_zero(audio_spec);
    audio_spec.freq = FREQ;
    audio_spec.format = AUDIO_S16;
    audio_spec.channels = 1;
    audio_spec.samples = 1024;
    audio_spec.callback = NULL;

    audio_device = SDL_OpenAudioDevice(
        NULL, 0, &audio_spec, NULL, 0);

    // pushing 3 seconds of samples to the audio buffer:
    float x = 0;
    int shit = 0;
    for (int i = 0; i < audio_spec.freq*((float)dur/1000); i++) {
        x += .010f;
	int sx = i/(int)((int)FREQ*((float)dur/1000)/1500);
	if (shit != sx){
		printf("%d\n", sx);
		shit = sx;
	}
        // SDL_QueueAudio expects a signed 16-bit value
        // note: "5000" here is just gain so that we will hear something
	//printf("%f, %d\n", (1/(i+0.0001)-0.00001), )((-i+(44100*3))/14);
	//printf("%f\n", freqToNum(freq));
	int sound = 0;
	int toPlay[9] = {0,0,0,0,0,0,0,0,0};
	int counter = 0;
	for (int j = 0; j < H; j++){
		//if (freq[j] != 0){
		//}
		if (freq[sx][j]){
			counter += 1;
			if (j < H/3){
				//printf("fuck you\n");
				int newMax = H/3;
				if (j < newMax/3){
					toPlay[0] += 1;
					
				}else if (j < newMax*2/3) {
					toPlay[1] += 1;
				} else{
					toPlay[2] += 1;
				}
			} else if (j < 2*H/3){
				//printf("fuck you\n");
				int newMax = H/3;
				//printf("%d\n", j - H/3<newMax/3);
				if (j - H/3 < newMax/3){
					toPlay[3] += 1;
				}else if (j - H/3  < newMax*2/3) {
					toPlay[4] += 1;
				} else{
					toPlay[5] += 1;
				}
			}else{
				int newMax = H/3;
				if (j- 2*H/3 < newMax/3){
					toPlay[6] += 1;
				}else if (j-2*H/3 < newMax*2/3) {
					toPlay[7] += 1;
				} else{
					toPlay[8] += 1;
				}
			}
		}
	//sound = sin(x * freqToNum(400)) * 5000;
	//int fuckingSum = 0;
	//for (int hui = 0; hui < 9; hui++){
	//	fuckingSum += toPlay[hui];
	//}

	sound = (sin(x * freqToNum(250))*toPlay[0] + sin(x * freqToNum(500))*toPlay[1]+sin(x * freqToNum(750))*toPlay[2]+sin(x * freqToNum(300))*toPlay[3]+sin(x * freqToNum(600))*toPlay[4]+sin(x * freqToNum(900))*toPlay[5]+sin(x * freqToNum(350))*toPlay[6]+sin(x * freqToNum(700))*toPlay[7]+sin(x * freqToNum(1050))*toPlay[8])*20;
	//printf("%d %d /n",sound, toPlay[5]);
	//}
	//sample = sample / counter;
	//for (int j = 500; j < 1500; j += 50){
        //	sample += (sin(x * freqToNum(j)) * normalDistribution(0.4,100,1000,j)*((-i+(44100))/10))/5;
	}
	int16_t sample = sound;
			//printf("%d\n", sample);
        const int sample_size = sizeof(int16_t) * 1;
        SDL_QueueAudio(audio_device, &sample, sample_size);
    }
	printf("fuck");
    // unpausing the audio device (starts playing):
    SDL_PauseAudioDevice(audio_device, 0);

    SDL_Delay(dur);

    SDL_CloseAudioDevice(audio_device);
    SDL_Quit();

    return 0;
}

float normalDistribution(float o, float o1, float c, float x){
	float tmp = -0.5*(x-c)/o1;
	float ans = (1/(o*pow(x, 0.5)))*exp(pow(tmp, 2.0));
	return ans;	
}

float freqToNum(float freq){
	//float kof1 = M_PI*2*100;
	float ans = 2*M_PI*freq/441;
	return ans;

}

void func_callback(void *unused, Uint8 *stream, int len) {

    for (int i=0;i<len;i++) {
        stream[i] = i;
    }
}
