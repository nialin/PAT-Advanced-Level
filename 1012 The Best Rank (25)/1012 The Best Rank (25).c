#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


struct stu_st {
	char best;
	int id, score[4], best_rank;
};


int com_cmp(const void *a, const void *b);
int math_cmp(const void *a, const void *b);
int eng_cmp(const void *a, const void *b);
int avg_cmp(const void *a, const void *b);

const char map[] = "ACME";

int avg_cmp(const void *a, const void *b)
{
	return ((struct stu_st *)b)->score[0] - ((struct stu_st *)a)->score[0];
}

int com_cmp(const void *a, const void *b)
{
	return ((struct stu_st *)b)->score[1] - ((struct stu_st *)a)->score[1];
}

int math_cmp(const void *a, const void *b)
{
	return ((struct stu_st *)b)->score[2] - ((struct stu_st *)a)->score[2];
}

int eng_cmp(const void *a, const void *b)
{
	return ((struct stu_st *)b)->score[3] - ((struct stu_st *)a)->score[3];
}

int main()
{
	struct stu_st stus[2000];
	int i, j, stu_cnt, query_cnt, rank, query_id;
	int (*cmps[])(const void *, const void *) = {
		avg_cmp, com_cmp, math_cmp, eng_cmp
	};

	scanf("%d%d", &stu_cnt, &query_cnt);

	for(i = 0; i < stu_cnt; ++i) {
		scanf("%d%d%d%d", &stus[i].id, &stus[i].score[1], &stus[i].score[2], &stus[i].score[3]);

		stus[i].best_rank = INT_MAX;
		stus[i].score[0] = (stus[i].score[1] + stus[i].score[2] + stus[i].score[3]);
	}

	for(i = 0; i < 4; ++i) {
		qsort(stus, stu_cnt, sizeof(struct stu_st), cmps[i]);

		for(j = 0; j < stu_cnt; ++j) {
			if(!j || stus[j].score[i] != stus[j - 1].score[i])
				rank = j + 1;

			if(stus[j].best_rank > rank) {
				stus[j].best_rank = rank;
				stus[j].best = map[i];
			}
		}
	}

	for(i = 0; i < query_cnt; ++i) {
		scanf("%d", &query_id);

		for(j = 0; j < stu_cnt && query_id != stus[j].id; ++j)
			;

		if(j < stu_cnt)
			printf("%d %c\n", stus[j].best_rank, stus[j].best);
		else
			printf("N/A\n");
	}

	return 0;
}
