#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<omp.h>

#define n_site 4
#define n_mu 4
typedef float T_mu;
typedef struct {T_mu mu[n_mu];} T_site;
typedef T_site T_field[n_site];

int
main(int argc, char **argv)
{
	const T_mu val = 1.0f;
	T_field f;
	f[0].mu[0] = 0.0f;
	#pragma omp target map(f[0:1])
	{
		f[0].mu[0] += val;
	}
	printf("%.7g\n", f[0].mu[0]);
	int ret = 0;
	if(f[0].mu[0] != val) ret = 1;
	return ret;
}
