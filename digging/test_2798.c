/**
 * BOJ 2798
 * Blackjack modified.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define UNCHECKED

int get_closest_sum_of_3(int numc, int *numv, int designated);
int get_closest_sum_of_3_alt(int numc, int *numv, int designated);

int main(int argc, char *argv[]) {
	int n_cards;
	int dealer_number;
	int *cards;

	int result_left = 0;
	int result_right = 0;

	// Do a random test.
	srand(time(NULL));

	while (result_left == result_right) {
		// Create N (3 to 100)
		n_cards = (rand() % 98) + 3;

		// Create M (10 to 300,000)
		dealer_number = (rand() % 299991) + 10;

		// Create cards
		cards = (int *)malloc(sizeof(int) * n_cards);
		for (int i = 0; i < n_cards; ++i) {
			cards[i] = rand() % 100001; // 0 to 100,000
		}

		printf("Test running at: 	N = %d	M = %d.\n", n_cards, dealer_number);

		result_left = get_closest_sum_of_3(n_cards, cards, dealer_number);
		result_right = get_closest_sum_of_3_alt(n_cards, cards, dealer_number);

		free(cards);
	}
	
	// Error spotted!
	printf("\n=================== ERROR CASE BEGIN ===================\n");

	printf("Wrong answer detected: should be %d but actually %d.\n", result_right, result_left);

	printf("N = %d, M = %d\n", n_cards, dealer_number);
	for (int i = 0; i < n_cards; ++i) {
		printf("%d ", cards[i]);
	}
	printf("\n");

	printf("=================== ERROR CASE END ===================\n");

	return 0;
}

static int desc_comparator(const void *first, const void *second) {
	if (*(int *)first < *(int *)second) return 1;
	else if (*(int *)first > *(int *)second) return -1;
	else return 0;
}

int get_closest_sum_of_3(int numc, int *numv, int designated) {
	// Idea: pick three cards starting from the biggest ones 
	// until the sum of them gets equal or less than designated sum.
	//
	// Limits: not extendable for arbitrary sized combinations.
	// this implementation only supports 3.

	qsort(numv, numc, sizeof(int), desc_comparator);

	int ni;
	int nj;
	int nk;
	int result = 0;

	// 3 to go.
	for (int i = 0; i < numc; ++i) {
		// Pick 1st.
		ni = numv[i];
		if (ni > designated) continue;
		for (int j = i+1; j < numc; ++j) {
			// Pick 2nd.
			nj = numv[j];
			if (ni + nj > designated) continue;
			for (int k = j+1; k < numc; ++k) {
				// Pick 3rd.
				nk = numv[k];
				if (ni + nj + nk > designated) continue;
				// There could be multiple values.
				// We choose the max one.
				if (ni + nj + nk > result) result = ni + nj + nk;
			} /* end of for k */
		} /* end of for j */
	} /* end of for i */

	return result;
}

int get_closest_sum_of_3_alt(int numc, int *numv, int designated) {
	int n = numc;
	int *arr = numv;
	int m = designated;

	int now = 0;
	for (int i = 0; i < n - 2; i++)
		for (int j = i + 1; j < n - 1; j++)
			for (int k = j + 1; k < n; k++)
				if (arr[i] + arr[j] + arr[k] <= m && m - (arr[i] + arr[j] + arr[k]) < m - now)
					now = arr[i] + arr[j] + arr[k];
 
	return now;
}

