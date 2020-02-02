/**
 * BOJ 17208
 * Cow burger
 *  DP를 쓰자
 */

#include <iostream>
#include <algorithm>

typedef struct _tc {
    int req_burger;
    int req_potato;
} tc;

tc cases[100];
int n, burger, potato, answer;

void dfs(int count, int burger_sum, int potato_sum, int picks) {
    if (count == n) {
        if (burger_sum <= burger && potato_sum <= potato) {
            answer = std::max(answer, picks);
        }
        return;
    }
    
    dfs(count + 1, burger_sum, potato_sum, picks);
    dfs(count + 1, burger_sum + cases[count].req_burger, potato_sum + cases[count].req_potato, picks + 1);
}

int main(int argc, const char *argv[]) {
    std::cin >> n >> burger >> potato;
    
    for (int i = 0; i < n; ++i)
        std::cin >> cases[i].req_burger >> cases[i].req_potato;
    
    dfs(0, 0, 0, 0);
    
    std::cout << answer << std::endl;
    
    return 0;
}

