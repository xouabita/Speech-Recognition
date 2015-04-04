#include "pretreatment.h"
#include <math.h>

float module(float complex nb){
float x=crealf(nb);
float y=cimagf(nb);
return sqrt((x*x)+(y*y));
}


float** cepstral(complex float **segments, int trame, int fft_length, int samplerate){
float **result=malloc(sizeof(segments));
for(int i=0;i<trame;i++)
	for(int j=0; j<fft_length; j++)
	result[i][j]=module(segment[i][j])*module(segment[i][j]/samplerate;	//periodogram estimate of the power spectrum
return result;
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

float mel_filterbank(int m, int k)
{
	if(k<fft_bin(m-1)
		return 0;
	if(k>=fft_bin(m-1) && k<=fft_bin(m))
		return (k-fft_bin(m-1))/(fft_bin(m)-fft_bin(m-1));
	if(k<=fft_bin(m+1) && k>=fft_bin(m))
		return (fft_bin(m+1)-k)/(fft_bin(m+1)-fft_bin(m));
	else
		return 0;
}

float ** coef_cep(float ** power_spectrum, int fft_length, int trame)
{
		float **coef=malloc(sizeof(float*)*trame);
		float **coef_1=malloc(sizeof(float*)*trame);
		float **coef_final=malloc(sizeof(float*)*trame);
		for(int i=0; i<trame; i++){
			coef[i]=malloc(sizeof(float)*26);
			coef_1[i]=malloc(sizeof(float)*26);
			coef_final[i]=malloc(sizeof(float)*13);
		}
		for(int i=0; i<trame; i++){
			int m=0;
			int k=0;
			while(k<fft_length/2 && m<26)
				{
				coef[i][m]+=mel_filterbank(m+1,k)*power_spectrum[i][k];
				if(k>fft_bin(m+1))
					m++;
				k++;
				}
		}
		for(int i=0; i<trame;i++)
			coef[i][0]=log10f(coef[i][0];
			for(int k=1; k<26;j++)
				for(int m=1; m<26; m++)
				coef_1[i][k]+=log10f(coef[i][m])*cos((M_PI*k/26)*(m-(1/2)));
		for(int i=0; i<trame; i++)
			for(int j=0; j<13; j++)
			coef_final[i][j]=coef_1[i][j];
		free(coef);
		free(coef_1);
		return coef_final;
}

	





