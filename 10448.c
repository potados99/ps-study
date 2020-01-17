#include <stdio.h>
#include <stdlib.h>

/* T1 ~ T45 */
int T[45];
int N;

void init_T();
int read_input(int **buf_ptr);
void foreach_combination(
		int *pool, 								/* where to pick from */
		int pool_size, 							/* size of the pool(n) */
		int pick, 								/* pick how many(r) */
		int dups,								/* duplicates allowed? */
		int (*on_combination)(int *, int), 	/* do what with the combination. */
		int r_start, 							/* recursive: start index of the pool at current iteration */
		int r_count, 							/* recursive: currently picked */
		int *r_picked,							/* recursive: picked values */
		int *r_selected,						/* (optional)recursive: whether the element at the same index of the pool is selected or not */
		int *r_stop								/* recursive: stop sign */
);
int on_pick(int *picked, int size);

int main(int argc, char *argv[]) {	
	init_T();

	int selected[45] = {0, };
	int picked[3] = {0, };
	int stop = 0;

	int *nums;
	int n = read_input(&nums);

	for (int i = 0; i < n; ++i) {
		N = nums[i];
		foreach_combination(T, 45, 3, 1, on_pick, 0, 0, picked, selected, &stop);
		if (!stop) {
			printf("0\n");
		}
		stop = 0;
	}

	return 0;
}

void init_T() {
	for (int i = 1; i < sizeof(T)/sizeof(T[0]); ++i)
		T[i] = T[i-1] + i;
}

int read_input(int **buf_ptr) {
	int n_case;
	int *nums;
	int n;
	
	scanf("%d", &n_case);
	nums = (int *)malloc(sizeof(int) * n_case + 1);

	for (int i = 0; i < n_case; ++i) {
		scanf("%d", &n);
		nums[i] = n;
	}

	*buf_ptr = nums;

	return n_case;
}

void foreach_combination(
		int *pool, 								
		int pool_size, 						
		int pick, 								
		int dups,
		int (*on_combination)(int *, int), 	
		int r_start, 						
		int r_count, 						
		int *r_picked,
		int *r_selected,
		int *r_stop
) {
	if (*r_stop) return;

	if (r_count == pick) {
		if (!dups) {
			int idx = 0;
			for (int i = 0; i < pool_size; ++i) {
				if (r_selected[i]) {
					r_picked[idx++] = pool[i];
				}
			}
		}
		
		if (on_combination(r_picked, pick)) {
			*r_stop = 1;
		}

		return;
	}

	for (int i = r_start; i < pool_size; ++i) {
		if (!dups && r_selected[i]) continue;
		r_picked[r_count] = pool[i];

		if (!dups) r_selected[i] = 1;
		foreach_combination(pool, pool_size, pick, dups, on_combination, r_start, r_count + 1, r_picked, r_selected, r_stop);
		if (!dups) r_selected[i] = 0;
	}
}

int on_pick(int *picked, int size) {
	if (picked[0] * picked[1] * picked[2] >= 1 && picked[0] + picked[1] + picked[2] == N) {
		printf("1\n");
		return 1;
	} 
	else {
		return 0;
	}
}

