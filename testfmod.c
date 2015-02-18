#include <stdio.h>
#include <fmodex/fmod.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
FMOD_SYSTEM *system;
FMOD_RESULT result;
FMOD_SOUND *tir;
FMOD_CHANNEL *channel;
FMOD_System_Create(&system);
FMOD_System_Init(system, 16, FMOD_INIT_NORMAL, NULL);
FMOD_System_GetChannel(system,FMOD_CHANNEL_FREE,&channel);
FMOD_System_CreateSound(system,"test.wav", FMOD_SOFTWARE, 0, &tir);
FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, tir, 0, &channel);
int sampleSize=512;
float spec[512];
float specLeft[512];
float specRight[512];
int isplaying=1;
while(isplaying)
{
FMOD_System_Update(system);
FMOD_System_GetSpectrum(system, specLeft, sampleSize, 0, FMOD_DSP_FFT_WINDOW_RECT);
FMOD_System_GetSpectrum(system, specRight, sampleSize, 1, FMOD_DSP_FFT_WINDOW_RECT);
for(int i=0; i<sampleSize; i++)
        {
        spec[i]= (specLeft[i]+specRight[i])/2;
        }

for(int j=0; j<64; j++)
	{
	printf("%f   %d\n",spec[j],j);
	j++;
	}
FMOD_Channel_IsPlaying(channel, &isplaying);
}
}

