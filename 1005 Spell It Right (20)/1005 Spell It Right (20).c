#include <stdio.h>


const char *words[] = {
	"zero", "one", "two", "three", "four",
	"five", "six", "seven", "eight", "nine"
};

void format_print(int sum, int flg);

void format_print(int sum, int flg)
{
	if(0 == sum) {
		if(0 == flg)
			printf("zero\n");

		return ;
	}

	format_print(sum / 10, flg + 1);
	printf("%s%s", words[sum % 10], flg ? " " : "");
}

int main()
{
	int i, sum;
	char str[100] = {0};

	scanf("%s", str);

	for(i = 0, sum = 0; str[i]; ++i)
		sum += str[i] - '0';

	format_print(sum, 0);

	return 0;
}
