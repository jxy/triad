// benchmark
void run_triad_float(size_t nt, size_t s);
void run_triad_double(size_t nt, size_t s);

// device functions
void list_devices();
void set_target_device(int dev);

// utils
void sys_fatal(const char *msg);

