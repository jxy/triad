#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<omp.h>

typedef struct {int64_t nteam; int64_t mthread;} tinfo;
int
main(int argc, char **argv)
{
	const int h = omp_get_initial_device();
	const int d = omp_get_default_device();
	const size_t s = sizeof(tinfo);
	tinfo *t = (tinfo *)malloc(s);
	if(!t){
		perror("malloc error");
		exit(1);
	}
	t->nteam = -1;
	t->mthread = -1;
	tinfo *p = (tinfo *)omp_target_alloc(s, d);
	if(!p){
		perror("omp_target_alloc error");
		exit(1);
	}
	omp_target_memcpy(p, t, s, 0, 0, d, h);
	#pragma omp target teams is_device_ptr(p)
	{
		if(omp_get_team_num() == 0)
			p->nteam = omp_get_num_teams();
			p->mthread = omp_get_max_threads();
	}
	omp_target_memcpy(t, p, s, 0, 0, h, d);
	printf("nteam: %ld  mthread: %ld\n", t->nteam, t->mthread);
	int ret = 0;
	if(t->nteam <= 0 || t->mthread <= 0) ret = 1;
	omp_target_free(p, d);
	free(t);
	return ret;
}
