#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<complex.h>
#include<omp.h>

#define n_site 4
#define n_mu 4
#define n_color 3
typedef float complex T_el;
typedef struct {T_el cmat[n_color][n_color];} T_mu;
typedef struct {T_mu mu[n_mu];} T_site;
typedef T_site T_field[n_site];

int
main(int argc, char **argv)
{
	const T_el zero = 0.0f + 0.0f*I;
	const T_el val = 1.0f + 1.0f*I;
	T_field f;
	for(size_t s = 0; s < n_site; ++s){
		for(size_t m = 0; m < n_mu; ++m){
			for(size_t a = 0; a < n_color; ++a){
				for(size_t b = 0; b < n_color; ++b){
					f[s].mu[m].cmat[a][b] += zero;
				}
			}
		}
	}
	#pragma omp target teams distribute parallel for map(tofrom:f[0:n_site])
	for(size_t s = 0; s < n_site; ++s){
		for(size_t m = 0; m < n_mu; ++m){
			for(size_t a = 0; a < n_color; ++a){
				for(size_t b = 0; b < n_color; ++b){
					f[s].mu[m].cmat[a][b] += val;
				}
			}
		}
	}
	printf("%.7g + %.7gi\n", creal(f[0].mu[0].cmat[0][0]), cimag(f[0].mu[0].cmat[0][0]));
	int ret = 0;
	if(f[0].mu[0].cmat[0][0] != val) ret = 1;
	return ret;
}
