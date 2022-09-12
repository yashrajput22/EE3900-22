#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>
#include <time.h>

complex *myfft(int n, complex *a) {
	if (n == 1) return a;
	complex *g = (complex *)malloc(n/2*sizeof(complex));
	complex *h = (complex *)malloc(n/2*sizeof(complex));
	for (int i = 0; i < n; i++) { 
		if (i%2) h[i/2] = a[i];
		else g[i/2] = a[i];
	}
	g = myfft(n/2, g);
	h = myfft(n/2, h);
	for (int i = 0; i < n; i++) a[i] = g[i%(n/2)] + cexp(-I*2*M_PI*i/n)*h[i%(n/2)];
	free(g); free(h);
	return a;
}

complex *myifft(int n, complex *a) { 
	if (n == 1) return a;
	complex *g = (complex *)malloc(n/2*sizeof(complex));
	complex *h = (complex *)malloc(n/2*sizeof(complex));
	for (int i = 0; i < n; i++) { 
		if (i%2) h[i/2] = a[i];
		else g[i/2] = a[i];
	}
	g = myifft(n/2, g);
	h = myifft(n/2, h);
	for (int i = 0; i < n; i++) {
		a[i] = g[i%(n/2)] + cexp(I*2*M_PI*i/n)*h[i%(n/2)];
		a[i] /= 2;
	}
	free(g); free(h);
	return a;
}

complex *convolve(complex *h, complex *x, int n) { 
	complex *a = (complex *)calloc(n, sizeof(complex));
	for (int i = 0; i < n; i++) for (int j = 0; j <= i; j++) a[i] += h[j]*x[i - j];
	return a;
}

int main() { 
	FILE *f1 = fopen("fft.txt", "w");
	FILE *f2 = fopen("ifft.txt", "w");
	FILE *f3 = fopen("conv.txt", "w");
	for (int j = 0; j <= 20; j++) {
		srand(time(0));
		int n = 1 << j;
		complex *a = (complex *)malloc(sizeof(complex)*n);
		for (int i = 0; i < n; i++) a[i] = random()/(1.0*RAND_MAX);
		// FFT Simulations
		clock_t fft_begin = clock();
		a = myfft(n, a);
		clock_t fft_end = clock();
		// End FFT simulation
		// IFFT simulation
		clock_t ifft_begin = clock();
		a = myifft(n, a);
		clock_t ifft_end = clock();
		// End IFFT simulation
		fprintf(f1, "%lf\n", 1000*(double)(fft_end - fft_begin)/CLOCKS_PER_SEC);
		fprintf(f2, "%lf\n", 1000*(double)(ifft_end - ifft_begin)/CLOCKS_PER_SEC);
		free(a);
	}
	for (int j = 10; j <= 1000; j+=10) {
		int n = j;
		complex *h = (complex *)malloc(sizeof(complex)*n);
		for (int i = 0; i < n; i++) h[i] = random()/(1.0*RAND_MAX);
		complex *x = (complex *)malloc(sizeof(complex)*n);
		for (int i = 0; i < n; i++) x[i] = random()/(1.0*RAND_MAX);
		// Convolution simulation
		clock_t conv_begin = clock();
		complex *y = convolve(h, x, n);
		clock_t conv_end = clock();
		// End convolution simulation
		fprintf(f3, "%lf\n", 1000*(double)(conv_end - conv_begin)/CLOCKS_PER_SEC);
		free(x); free(h);
	}
	fclose(f1); fclose(f2); fclose(f3);
	return 0;
}