#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MIN(a,b) ((a) < (b) ? (a) : (b))


uint64_t my_atoi(const char *str, uint64_t radix);

uint64_t lowest_radix_get(const char *str);
uint64_t radix_get(const char *str, uint64_t tar);

uint64_t my_atoi(const char *str, uint64_t radix)
{
	uint64_t rslt;

	for(rslt = 0; *str; ++str) {
		rslt *= radix;

		if(*str >= '0' && *str <= '9')
			rslt += *str - '0';
		else
			rslt += *str - 'a' + 10;
	}

	return rslt;
}

uint64_t lowest_radix_get(const char *str)
{
	char max = 0;

	for(; *str; ++str)
		if(max < *str)
			max = *str;

	return (max >= 'a' && max <= 'z' ? max - 'a' + 10 : max - '0') + 1;
}

uint64_t radix_get(const char *str, uint64_t tar)
{
	uint64_t radix, low, high, tmp;

	low = lowest_radix_get(str);

	/* high = strlen(str) > 2 ? (int)pow(tar, (double)1 / (strlen(str) - 1)), tar + 1; */
	high = strlen(str) > 2 ? MIN(1ll << (64 / (strlen(str) - 1)), tar + 1) : tar + 1;

	while(low <= high) {
		radix = (low + high) / 2;
		tmp = my_atoi(str, radix);

		if(tmp == tar)
			return radix;

		if(tmp < tar)
			low = radix + 1;
		else
			high = radix - 1;
	}

	return -1;
}

int main()
{
	int tag;
	char n1[11], n2[11];
	uint64_t radix, rslt;

	scanf("%s%s%d%lld", n1, n2, &tag, &radix);

	if(1 == tag)
		rslt = radix_get(n2, my_atoi(n1, radix));
	else
		rslt = radix_get(n1, my_atoi(n2, radix));

	if(-1 == rslt)
		printf("Impossible\n");
	else
		printf("%lld\n", rslt);

	return 0;
}
