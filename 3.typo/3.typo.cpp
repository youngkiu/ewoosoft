#include <stdio.h>

#define N_MIN	1
#define N_MAX	100000

int N = 0;
char brackets[N_MAX];

int calculate_bracket_state(int i, int state_value)
{
	int j;

	for (j = i; j < N; j++) {
		if (brackets[j] == '(')
			state_value++;
		else if (brackets[j] == ')')
			state_value--;
	}

	return state_value;
}

int get_balaced_bracket_cnt()
{
	int i;
	int state_value;
	int balance_cnt;

	balance_cnt = 0;
	state_value = 0;
	for (i = 0; i < N; i++) {
		if ((brackets[i] == '(') && (state_value > 0)) {
			if (calculate_bracket_state(i + 1, state_value - 1) == 0) {
				balance_cnt++;
			}
		}
		else if ((brackets[i] == ')') && (state_value < (N / 2))) {
			if (calculate_bracket_state(i + 1, state_value + 1) == 0) {
				balance_cnt++;
			}
		}

		if (brackets[i] == '(') {
			state_value++;
		}
		else if (brackets[i] == ')') {
			state_value--;
		}

		if ((state_value < 0) || (state_value > (N / 2)))
			break;
	}

	return balance_cnt;
}

int main(void)
{
	int i;
	int balance_cnt;

	for (i = 0; i < N_MAX; i++) {
		brackets[i] = getchar();

		if (brackets[i] == '\n')
			break;

		if ((brackets[i] != '(') &&
			(brackets[i] != ')')) {
			return -1;
		}
	}
	if ((i % 2) != 0)
		return -1;

	N = i;

	balance_cnt = get_balaced_bracket_cnt();

	printf("%d \n", balance_cnt);

	return 0;
}

