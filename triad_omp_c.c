#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <float.h>
#include <math.h>
#include <omp.h>

const size_t array_alignment = 2*1024*1024;

// Array values
const double start_a = 0.1;
const double start_b = 0.2;
const double start_c = 0.3;
const double start_scalar = 0.4;

size_t array_size = 1<<25;
size_t num_times = 100;
size_t device_index = 0;
bool use_float = false;

// device functions
void list_devices(void);

// utils
void sys_fatal(const char *msg);

#define CONCAT(a,b,c) a##b##c
#define template(a,b) CONCAT(a,_,b)

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

#undef template
#undef CONCAT

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

int
parse_int(const char *str, size_t *out)
{
	char *n;
	*out = strtoll(str, &n, 10);
	return !strlen(n);
}

void
parse_args(int argc, char **argv)
{
	for(int i = 1; i < argc; i++){
		if(!strcmp("-d", argv[i])){
			if(++i >= argc || !parse_int(argv[i], &device_index))
				sys_fatal("Invalid device index.");
		}else if(!strcmp("-s", argv[i])){
			if(++i >= argc || !parse_int(argv[i], &array_size))
				sys_fatal("Invalid array size.");
		}else if(!strcmp("-n", argv[i])){
			if(++i >= argc || !parse_int(argv[i], &num_times))
				sys_fatal("Invalid number of repeats.");
		}else if(!strcmp("-f", argv[i])){
			use_float = true;
		}else if(!strcmp("-h", argv[i])){
			printf(
				"Usage: %s [OPTIONS]\n"
				"Options:\n"
				"	-h          Print the help message\n"
				"	-d  INDEX   Select device number INDEX\n"
				"	-s  SIZE    Use SIZE elements in the array\n"
				"	-n  NUM     Run the test NUM times\n"
				"	-f          Use single precision float (default double)\n",
				argv[0]);
		}else{
			sys_fatal("Unrecognized argument (see '-h')");
		}
	}
}

int
main(int argc, char **argv)
{
	list_devices();
	parse_args(argc, argv);
	omp_set_default_device(device_index);
	printf("Using device %d\n", omp_get_default_device());
	if(use_float)
		run_triad_float(num_times, array_size);
	else
		run_triad_double(num_times, array_size);
}

void
sys_fatal(const char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(EXIT_FAILURE);
}
