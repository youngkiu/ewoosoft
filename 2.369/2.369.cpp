#include <stdio.h>

#define X_MIN	1
#define X_MAX	100000000

struct
{
	int digit_cnt;
	int accum_cnt;
} cnttable[9];	// 9 = log10(X_MAX) + 1

int log10(int x)
{
	int log = 0;

	while (x / 10) {
		x /= 10;
		log++;
	}

	return log;
}

int pow10(int x)
{
	int i;
	int pow = 1;

	for (i = 0; i < x; i++) {
		pow *= 10;
	}
	
	return pow;
}

void build369cnttable(int x)
{
	int log_x;
	int i;

	log_x = log10(x);

	cnttable[0].digit_cnt = 0;
	cnttable[0].accum_cnt = 3;
	for (i = 1; i < log_x; i++) {
		cnttable[i].digit_cnt = cnttable[i - 1].accum_cnt * 9 + pow10(i) * 3;
		cnttable[i].accum_cnt = cnttable[i].digit_cnt + cnttable[i - 1].accum_cnt;
	}
}

int get369cnt(int x, int issuper369digit, int super369digitcnt)
{
	int log_x;
	int pow_x;
	int digit_x;
	int accumul;

	log_x = log10(x);
	pow_x = pow10(log_x);

	digit_x = x / pow_x;

	if (issuper369digit == 1) {
		accumul = (digit_x + 1) * pow_x;
	}
	else {
		accumul = 0;
	}

	if (log_x == 0) {
		if (super369digitcnt > 1)
			accumul -= ((3 - (digit_x / 3)) * (super369digitcnt - 1));

		return (digit_x / 3) + accumul;
	}

	accumul += (digit_x * cnttable[log_x - 1].accum_cnt) + ((digit_x - 1) / 3 * pow_x);

	if ((digit_x == 3) || (digit_x == 6) || (digit_x == 9)) {
		issuper369digit = 1;
		super369digitcnt++;
	}
	else {
		issuper369digit = 0;
	}

	return accumul + get369cnt(x - (digit_x * pow_x), issuper369digit, super369digitcnt);
}

int main(void)
{
	int a, b;
	int a369cnt, b369cnt;

	scanf("%d %d", &a, &b);
	if ((a < X_MIN) ||
		(a > X_MAX) ||
		(b < X_MIN) ||
		(b > X_MAX) ||
		(a > b)) {
		return -1;
	}

	build369cnttable(b);

	a369cnt = get369cnt(a - 1, 0, 0);
	b369cnt = get369cnt(b,     0, 0);

	printf("%d \n", b369cnt - a369cnt);
	
	return 0;
}
