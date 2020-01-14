/**
 * BOJ 5597
 * Who missed the assignments...?
 */

#include <stdio.h>
#include <stdint.h>

#define setb(_bits, _offset) do { (_bits) |= (1 << (_offset)); } while(0)
#define getb(_bits, _offset) ((_bits) & (1 << (_offset)))

int main(int argc, char *argv[]) {
	int 		num;
	uint32_t 	checked;
	
	for (int i = 0; i < 28; ++i) {
		scanf("%d", &num);
		setb(checked, num);
	}

	for (int i = 1; i <= 30; ++i) {
		if (!getb(checked, i)) {
			printf("%d\n", i);
		}
	}

	return 0;
}
