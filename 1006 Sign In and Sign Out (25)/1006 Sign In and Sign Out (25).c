#include <stdio.h>
#include <string.h>


struct time_st {
	int HH, MM, SS;
};


int time_compare(const struct time_st *a, const struct time_st *b);

int time_compare(const struct time_st *a, const struct time_st *b)
{
	if(a->HH != b->HH)
		return a->HH - b->HH;

	if(a->MM != b->MM)
		return a->MM - b->MM;

	return a->SS - b->SS;
}

int main()
{
	int i, record_cnt;
	char unlock[16] = {0}, lock[16] = {0}, id[16];
	struct time_st unlock_time = {23, 59, 59}, lock_time = {0, 0, 0}, sign_in_time, sign_out_time;

	scanf("%d", &record_cnt);

	for(i = 0; i < record_cnt; ++i) {
		scanf("%s", id);
		scanf("%d:%d:%d", &sign_in_time.HH, &sign_in_time.MM, &sign_in_time.SS);
		scanf("%d:%d:%d", &sign_out_time.HH, &sign_out_time.MM, &sign_out_time.SS);

		if(time_compare(&sign_in_time, &unlock_time) < 0) {
			strcpy(unlock, id);
			memcpy(&unlock_time, &sign_in_time, sizeof(struct time_st));
		}

		if(time_compare(&sign_out_time, &lock_time) > 0) {
			strcpy(lock, id);
			memcpy(&lock_time, &sign_out_time, sizeof(struct time_st));
		}
	}

	printf("%s %s\n", unlock, lock);

	return 0;
}
