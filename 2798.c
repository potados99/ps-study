/**
 * BOJ 2798
 * Blackjack modified.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNCHECKED

int get_closest_sum_of_3(int numc, int *numv, int designated);

int main(int argc, char *argv[]) {
	int n_cards;
	int dealer_number;
	int *cards;

	scanf("%d %d", &n_cards, &dealer_number);
	
#ifndef UNCHECKED
	if (n_cards < 3 || n_cards > 100) return -1;
	if (dealer_number < 10 || dealer_number > 300000) return -1;
#endif
	
	cards = (int *)malloc(sizeof(int) * n_cards + 1/*padding*/);
	for (int i = 0; i < n_cards; ++i) {
		scanf("%d", cards + i);
	}

	return !printf("%d\n", get_closest_sum_of_3(n_cards, cards, dealer_number));
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
				// Ya here!
				return ni + nj + nk;
			} /* end of for k */
		} /* end of for j */
	} /* end of for i */

	// Every possible sum of three cards
	// exceeds the designated sum: wrong input.
	return -1;
}
