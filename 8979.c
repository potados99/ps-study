/**
 * BOJ 8979
 * Olympic!
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct country {
	int 					id;
	int 					gold;
	int 					silver;
	int 					bronze;
};

struct input_format {
	int 					n_country; 			/* N */
	int 					target_country_id; 	/* K */
	struct country			*countries;
};

struct input_format 		*collect();
int 						process(struct input_format *input);
int 						announce(int rank);
#ifdef DEBUG
void						dump(struct input_format *input);
#endif

int main(int argc, char *argv[]) {
	return announce(process(collect()));
}

struct input_format *collect() {
	// Allocate input struct.
	struct input_format *input = (struct input_format *)malloc(sizeof(struct input_format) + 1/*padding*/);
	memset(input, 0, sizeof(struct input_format));

	// How many country do we need to allocate?
	scanf("%d %d", &input->n_country, &input->target_country_id);

	// Allocate spaces for countires.
	input->countries = (struct country *)malloc(sizeof(struct country) * input->n_country + 1/*padding*/);
	memset(input->countries, 0, sizeof(struct country) * input->n_country);

	// Fill.
	for (int i = 0; i < input->n_country; ++i) {
		struct country *current = &input->countries[i];
		scanf("%d %d %d %d", &current->id, &current->gold, &current->silver, &current->bronze);
	}

#ifdef DEBUG
	dump(input);
#endif

	// Mission clear.
	return input;
}

/**
 * Compare two countries by medals.
 * 
 * @return	 1 if left > right
 *			-1 if left < right
 *			 0 if left == right
 */
static inline int score_cmp(struct country *left, struct country *right) {
	if (left->gold > right->gold) 			return 1;
	else if (left->gold < right->gold) 		return -1;

	if (left->silver > right->silver) 		return 1;
	else if (left->silver < right->silver)	return -1;

	if (left->bronze > right->bronze) 		return 1;
	else if (left->bronze < right->bronze)	return -1;

	return 0;
}

int process(struct input_format *input) {
	int 				rank = 1; /* minimun 1 */
	struct country 		*target = NULL;

	// Find target country.
	for (int i = 0; i < input->n_country; ++i) {
		if (input->countries[i].id == input->target_country_id) {
			// It must be happened for once.
			target = &input->countries[i];
		}
	}

	// Find countries over the target.
	for (int i = 0; i < input->n_country; ++i) {
		if (score_cmp(target, &input->countries[i]) < 0) {
			++rank;
		}
	}

	return rank;
}

int announce(int rank) {
	printf("%d\n", rank);
	return 0;
}

#ifdef DEBUG
void dump(struct input_format *input) {
	printf("countries: %d, target: %d.\n", 
			input->n_country, 
			input->target_country_id);

	for (int i = 0; i < input->n_country; ++i) {
		printf("country %d: %d golds, %d silvers, %d bronze.\n", 
				input->countries[i].id, 
				input->countries[i].gold, 
				input->countries[i].silver, 
				input->countries[i].bronze);
	}
}
#endif
