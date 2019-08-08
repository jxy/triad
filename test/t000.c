#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<omp.h>

typedef struct {int64_t nteam; int64_t nthread;} tinfo;
int
main(int argc, char **argv)
{
	tinfo *t = (tinfo *)malloc(sizeof(tinfo));
	t->nteam = -1;
	t->nthread = -1;
	#pragma omp target teams map(t[0:1])
	{
		#pragma omp parallel
		{
			if(omp_get_team_num() == 0 && omp_get_thread_num() == 0){
				t->nteam = omp_get_num_teams();
				t->nthread = omp_get_num_threads();
			}
		}
	}
	printf("nteam: %ld  nthread: %ld\n", t->nteam, t->nthread);
	int ret = 0;
	if(t->nteam <= 0 || t->nthread <= 0) ret = 1;
	free(t);
	return ret;
}
