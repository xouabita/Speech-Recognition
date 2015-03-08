#include "pretreatment.h"
#include <math.h>

float complexlog(float complex nb){
float x=crealf(nb);
float y=cimagf(nb);
return logf(sqrt((x*x)+(y*y)));
}


Segments cepstral(complex float **segments, int trame, int samplerate){
for(int i=0;i<trame;i++)
	for(int j=0; j<samplerate; j++)
	segments[i][j]=complexlog(segment[i][j]);
	
fft_inverse(segments);
for(int i=0;i<trame;i++)
	for(int j=0;j<samplerate;j++)
	segments[i][j]*=1+(samplerate/2)*sinf(M_PI*(j+1)/samplerate);


}

