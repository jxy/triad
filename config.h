#define template_helper_(t,name) name##_##t##_
#define template(t,name) template_helper_(t,name)

// benchmark
void template(float,run_triad)(size_t nt, size_t s);
void template(double,run_triad)(size_t nt, size_t s);

// device functions
void list_devices(void);
void set_target_device(int dev);

// utils
void sys_fatal(const char *msg);

