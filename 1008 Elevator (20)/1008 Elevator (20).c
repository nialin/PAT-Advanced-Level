#include <stdio.h>


int main()
{
	int i, n, last, cur, total;

	scanf("%d", &n);

	for(i = 0, last = total = 0; i < n; ++i, total += 5) {
		scanf("%d", &cur);

		if(cur - last > 0)
			total += (cur - last) * 6;
		else
			total += (last - cur) * 4;

		last = cur;
	}

	printf("%d\n", total);

	return 0;
}
