#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<omp.h>

typedef struct {int64_t nteam; int64_t nthread; int64_t team_n; int64_t thread_n;} tinfo;
int
main(int argc, char **argv)
{
	const int64_t narr = 1 << 10;
	tinfo tinit = {-1, -1, -1, -1};
	tinfo *t = (tinfo *)aligned_alloc(1 << 22, sizeof(tinfo)*narr);
	for(int64_t i = 0; i < narr; ++i) t[i] = tinit;
	#pragma omp target teams distribute parallel for simd map(t[0:narr]) aligned(t) num_teams(32)
	for(int64_t i = 0; i < narr; ++i){
		t[i].nteam = omp_get_num_teams();
		t[i].nthread = omp_get_num_threads();
		t[i].team_n = omp_get_team_num();
		t[i].thread_n = omp_get_thread_num();
	}
	for(int64_t i = 0; i < narr; ++i){
		printf("%4ld:  nteam: %ld  nthread: %ld  team_n: %ld  thread_n: %ld\n",
			i, t[i].nteam, t[i].nthread, t[i].team_n, t[i].thread_n);
	}
	int ret = 0;
	//if(t->nteam <= 0 || t->nthread <= 0) ret = 1;
	free(t);
	return ret;
}
