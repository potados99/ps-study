/**
 * BOJ 1756
 * f**king pizza in the oven.
 */

#include <stdio.h>
#include <stdbool.h>

int dia[300001];
int piz[300001];
int pass_max[300001];

#define min(a, b) (((a) > (b)) ? (b) : (a))

int main(int argc, const char * argv[]) {
    int depth, n;

    scanf("%d %d", &depth, &n);

    // read diameter
    for (int i = 1; i <= depth; ++i)
        scanf("%d", dia+i);

    // read pizza
    for (int i = 1; i <= n; ++i)
        scanf("%d", piz+i);

    // preprocess
    int min_dia = 1000000000;
    for (int i = 1; i <= depth; ++i) {
        min_dia = min(dia[i], min_dia);
        pass_max[i] = min_dia;
    }

    // process
    int last_pizza_depth = depth + 1;
    int piz_index = 1;
    bool piz_in = false;
    for (int i = last_pizza_depth; i > 0; --i) {
        if (piz_index == n+1) {
            piz_in = true;
            break;
        }
        if (piz[piz_index] <= pass_max[i-1]) {
            pass_max[i-1] = 0;
            piz_index++;
            last_pizza_depth = i - 1;
        }
    }

    printf("%d\n", piz_in ? last_pizza_depth : 0);

    return 0;
}


