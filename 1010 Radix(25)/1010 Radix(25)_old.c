#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define ASCII_COUNT		(256)
#define DIGIT_MAX_LEN	(10)

#define ASCII_TO_INT(a)	(map[(int)(a)])

#if 0
#define MAX(m, n)	({	\
	typeof(m) _m = (m);	\
	typeof(n) _n = (n);	\
	(void)(&_m == &_n);	\
	_m > _n ? _m : _n; })

#define MIN(m,n)	({	\
	typeof(m) _m = (m); \
	typoef(n) _n = (n);	\
	(void)(&_m == &_n);	\
	_m < _n ? _m : _n; })
#else
#define MAX(m,n)	((m) > (n) ? (m) : (n))
#define MIN(m,n)	((m) < (n) ? (m) : (n))
#endif

#define POWER(n)	(1LL << (n))


uint64_t map[ASCII_COUNT];

void init_map(void);

uint64_t convert_to_decimal(const char *str, uint64_t radix);
uint64_t get_largest_digit(const char *str);

uint64_t matching_radix_search(const char *str, uint64_t value);
uint64_t equation_radix_match(const char *left_str, const char *right_str, uint64_t radix);


void init_map(void)
{
	int i;

	for(i = '0'; i <= '9'; ++i)
		map[i] = i - '0';

	for(i = 'a'; i <= 'z'; ++i)
		map[i] = i - 'a' + 10;
}

uint64_t convert_to_decimal(const char *str, uint64_t radix)
{
	uint64_t rslt = 0;

	for(; *str != '\0'; ++str)
		rslt = rslt * radix + ASCII_TO_INT(*str);

	return rslt;
}

uint64_t get_largest_digit(const char *str)
{
	uint64_t rslt = 0;

	for(; *str != '\0'; ++str)
		rslt = MAX(ASCII_TO_INT(*str), rslt);

	return rslt + 1;
}

uint64_t matching_radix_search(const char *str, uint64_t value)
{
	uint64_t low, high, mid, tmp;
	unsigned int str_len = strlen(str);

	low = get_largest_digit(str);

	high = str_len <= 2 ? value + 1 : MIN(POWER(64 / (str_len - 1)), value + 1);

	while(low <= high) {
		mid = (low + high) / 2;
		tmp = convert_to_decimal(str, mid);

		if(tmp == value)
			return mid;

		else if(tmp < value)
			low = mid + 1;
		else
			high = mid - 1;
	}

	return 0;
}

uint64_t equation_radix_match(const char *left_str, const char *right_str, uint64_t radix)
{
	uint64_t left_value = 0;

	left_value = convert_to_decimal(left_str ,radix);

	return matching_radix_search(right_str, left_value);
}

int main(int argc, char *argv[])
{
	uint64_t tag, radix, rslt;
	char n1[DIGIT_MAX_LEN + 1], n2[DIGIT_MAX_LEN + 1];

	scanf("%s%s%lld%lld", n1, n2, &tag, &radix);

	init_map();

	rslt = 1 == tag ?
		equation_radix_match(n1, n2, radix) : equation_radix_match(n2, n1, radix);

	if(0 == rslt)
		printf("Impossible\n");
	else
		printf("%lld\n", rslt);

	return EXIT_SUCCESS;
}
