#include <stdio.h>

int main()
{
	int i, j;
	const char map[] = "WTL";
	double odds[3], *max_odd_ptr, rslt;

	for(i = 0, rslt = 1.0; i < 3; ++i, rslt *= *max_odd_ptr) {
		for(j = 0, max_odd_ptr = odds; j < 3; ++j) {
			scanf("%lf", &odds[j]);

			if(*max_odd_ptr < odds[j])
				max_odd_ptr = &odds[j];
		}

		printf("%c ",map[max_odd_ptr - odds]);
	}

	printf("%.2lf\n", (rslt * 0.65 - 1) * 2);

	return 0;
}
