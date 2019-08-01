#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "config.h"

size_t array_size = 1<<25;
size_t num_times = 100;
size_t device_index = 0;
bool use_float = false;

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
			exit(EXIT_SUCCESS);
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
	set_target_device(device_index);
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
