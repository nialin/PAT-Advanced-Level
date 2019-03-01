#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void my_strrev(char *buf);
void my_itoa(int num, char *buf, int index);

void format_print(int num);


void my_strrev(char *buf)
{
	char tmp;
	int i, len = strlen(buf);

	for(i = 0; i < len / 2; ++i) {
		tmp = buf[i];
		buf[i] = buf[len - 1 - i];
		buf[len - 1 - i] = tmp;
	}
}

void my_itoa(int num, char *buf, int index)
{
	int i = 0, sign = num < 0 ? 1 : 0;

	num = abs(num);

	do {
		buf[i++] = num % index + '0';
		num /= index;
	}while(num);

	if(sign)
		buf[i++] = '-';

	/* strrev(buf); */
	my_strrev(buf);
}

void format_print(int num)
{
	int i = 0, len;
	char buf[8] = {0}; 

	/* itoa(num, buf, 10); */
	my_itoa(num, buf, 10);
	len = strlen(buf);

	if('-' == buf[i])
		putchar(buf[i++]);

	while(i < len) {
		putchar(buf[i++]);

		if(i % 3 == len % 3 && i != len)
			putchar(',');
	}
}

int main()
{
	int a, b, sum;

	scanf("%d%d", &a, &b);

	sum = a + b;

	format_print(sum);

	return 0;
}
