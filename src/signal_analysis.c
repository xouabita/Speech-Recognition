#include "pretreatment.h"
#include <math.h>

float module(float complex nb){
float x=crealf(nb);
float y=cimagf(nb);
return sqrt((x*x)+(y*y));
}


Segments cepstral(complex float **segments, int trame, int fft_length, int samplerate){
for(int i=0;i<trame;i++)
	for(int j=0; j<fft_length; j++)
	segments[i][j]=module(segment[i][j])*module(segment[i][j]/samplerate;	//periodogram estimate of the power spectrum
}

float hertz_to_mel (int i , int samplerate){
	float low_bound = 1125*log(1+20/700);
	float upper_bound = 1125*log(samplerate/2/700);
	float gap=(upper_bound-low_bound)/27;
	return (low_bound+(i*gap)); 
}

float mel_to_hertz(int samplerate, int i)
{
return 700*exp((hertz_to_mel(i,samplerate)/1125)-1);
}

float fft_bin(int i, int samplerate,int fft_length)
{
	return floorf(((fft_length+1)*mel_to_hertz(samplerate,i))/samplerate);
}


