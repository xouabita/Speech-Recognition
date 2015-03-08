#include "pretreatment.h"
#include <math.h>

complex float complexlog(float complex nb){
float x=crealf(nb);
float y=cimagf(nb);
return logf(x) * cosf(y) + I * logf(y) * sinf(y);
}
Segments cepstral(complex float ** segments, int trame, int samplerate){
for(int i=0;i<trame;i++)
	for(int j=0; j<samplerate; j++)
	if(segments[i][j]<=0){
	segments[i][j]=complexlog(-segment[i][j]);
	}
	else{
	segments[i][j]=complexlog(segment[j][j]);
	}
	
}
