
#include <math.h>
#include <complex.h>
#include <unistd.h>
#include <stdlib.h>

float module(float complex nb){
float x=crealf(nb);
float y=cimagf(nb);
return sqrt((x*x)+(y*y));
}


float** cepstral(complex float **segments, int trame, int fft_length){
float **result=malloc(sizeof(float*)*trame);
for(int i=0;i<trame;i++)
	result[i]=malloc(sizeof(float)*fft_length);
for(int i=0;i<trame;i++)
	for(int j=0; j<fft_length; j++)
	result[i][j]=module(segments[i][j])*module(segments[i][j]);
	//result[i][j]=module(segments[i][j])*module(segments[i][j]/analysis_window);	//periodogram estimate of the power spectrum
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

float mel_filterbank(int m, int k,int samplerate, int fft_length)
{
	float fft_bin_minus=fft_bin(m-1, samplerate, fft_length);
	float fft_bin_m=fft_bin(m,samplerate,fft_length);
	float fft_bin_plus=fft_bin(m+1, samplerate, fft_length);

	if(k<fft_bin_minus)
		return 0;
	if(k>=fft_bin_minus && k<=fft_bin_m)
		return (k-fft_bin_minus)/(fft_bin_m-fft_bin_minus);
	if(k<=fft_bin_plus && k>=fft_bin_m)
		return (fft_bin_plus-k)/(fft_bin_plus-fft_bin_m);
	else
		return 0;
}

double ** coef_cep(complex float **segments,int fft_length, int trame, int samplerate)
{
		float **power_spectrum=cepstral(segments, trame, fft_length);
		float **coef=malloc(sizeof(float*)*trame);
		float **coef_1=malloc(sizeof(float*)*trame);
		double **coef_final=malloc(sizeof(double*)*trame);
		for(int i=0; i<trame; i++){
			coef[i]=malloc(sizeof(float)*26);
			coef_1[i]=malloc(sizeof(float)*26);
			coef_final[i]=malloc(sizeof(double)*13);
		}
		for(int i=0; i<trame; i++){
			int m=0;
			int k=0;
			while(k<fft_length/2 && m<26)
				{
				coef[i][m]+=mel_filterbank(m+1,k,samplerate,fft_length)*power_spectrum[i][k];
				if(k>fft_bin(m+1,samplerate,fft_length))
					m++;
				k++;
				}
		}
		for(int i=0; i<trame;i++){
			coef[i][0]=log10f(coef[i][0]);
			for(int k=1; k<26;k++)
				for(int m=1; m<26; m++)
				coef_1[i][k]+=log10f(coef[i][m])*cos((M_PI*k/26)*(m-(1/2)));
		}
		for(int i=0; i<trame; i++)
			for(int j=0; j<13; j++)
			coef_final[i][j]=coef_1[i][j];


		for(int i=0;i<trame;i++){
			free(power_spectrum[i]);
			free(coef[i]);
			free(coef_1[i]);
		}
		free(power_spectrum);
		free(coef);
		free(coef_1);
		return coef_final;
}

	





