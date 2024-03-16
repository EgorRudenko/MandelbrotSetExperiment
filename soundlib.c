#include <stdio.h>
#include <SDL2/SDL.h>

#ifndef M_PI
#define M_PI (3.14)
#endif

#define FREQ 44100

float normalDistribution(float, float, float, float);
float freqToNum(float);


int soundGen(int freq, float dur) {
    SDL_Init(SDL_INIT_AUDIO);

    // the representation of our audio device in SDL:
    SDL_AudioDeviceID audio_device;

    // opening an audio device:
    SDL_AudioSpec audio_spec;
    SDL_zero(audio_spec);
    audio_spec.freq = FREQ;
    audio_spec.format = AUDIO_S16SYS;
    audio_spec.channels = 1;
    audio_spec.samples = 1024;
    audio_spec.callback = NULL;

    audio_device = SDL_OpenAudioDevice(
        NULL, 0, &audio_spec, NULL, 0);

    // pushing 3 seconds of samples to the audio buffer:
    float x = 0;
    for (int i = 0; i < audio_spec.freq*dur; i++) {
        x += .010f;
	
        // SDL_QueueAudio expects a signed 16-bit value
        // note: "5000" here is just gain so that we will hear something
	//printf("%f, %d\n", (1/(i+0.0001)-0.00001), )((-i+(44100*3))/14);
	//printf("%f\n", freqToNum(freq));
	int16_t sample = (sin(x * freqToNum(freq)) * (-0.5*i+(audio_spec.freq*dur))/10);

	//for (int j = 500; j < 1500; j += 50){
        //	sample += (sin(x * freqToNum(j)) * normalDistribution(0.4,100,1000,j)*((-i+(44100))/10))/5;
	//}
        const int sample_size = sizeof(int16_t) * 1;
        SDL_QueueAudio(audio_device, &sample, sample_size);
    }

    // unpausing the audio device (starts playing):
    SDL_PauseAudioDevice(audio_device, 0);

    SDL_Delay(dur*1000);

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
	float ans = 2*M_PI/((1/freq)*441);
	return ans;

}
