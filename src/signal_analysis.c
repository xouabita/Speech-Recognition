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


