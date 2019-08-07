#include <omp.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

#include "config.h"

const size_t array_alignment = 2*1024*1024;

// Array values
const double start_a = 0.1;
const double start_b = 0.2;
const double start_c = 0.3;
const double start_scalar = 0.4;

#ifdef MANUAL_SCHEDULE
#define DEVICE_MEMORY
#endif
#ifdef DEVICE_MEMORY
	#define T double
	#include "triad_omp_mem_c.in"
	#undef T
	#define T float
	#include "triad_omp_mem_c.in"
	#undef T
#else
	#define T double
	#include "triad_omp_c.in"
	#undef T
	#define T float
	#include "triad_omp_c.in"
	#undef T
#endif

void
list_devices()
{
	int i = omp_get_initial_device();
	int n = omp_get_num_devices();
	int d = omp_get_default_device();
	printf("initial_device = %d\n", i);
	printf("num_devices = %d\n", n);
	printf("default_device = %d\n", d);
}

void
set_target_device(int dev)
{
	omp_set_default_device(dev);
	printf("Using device %d\n", omp_get_default_device());
}

