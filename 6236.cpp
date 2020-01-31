/**
 * BOJ  6236
 * 현우야 돈좀 그만써
 */

#include <iostream>
#include <algorithm>

int n, m;
int *req;

int how_many_withdrawals_are_needed(int withdrawal_unit) {
    int count = 1; // at least onece
    int sum = 0;
    
    for (int i = 0; i < n; ++i) {
        if (sum + req[i] > withdrawal_unit) {
            count++;
            sum = req[i];
        } else {
            sum += req[i];
        }
    }
    
    return count;
}

int main(int argc, const char *argv[]) {
    std::cin >> n >> m;
    req = new int[n] {0, };
    
    int req_max = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> req[i];
        req_max = std::max(req[i], req_max);
    }
    
    int left = req_max;
    int right = 1e9;
    int mid;
    
    while (left < right) {
        if (how_many_withdrawals_are_needed(mid = (left + right) / 2) > m)
            left = mid + 1; // go right, increase withdrawal count (to decrease k)
        else
            right = mid; // go left, decrease withdrawal count (to increase k)
    }
    
    std::cout << left << std::endl;
    
    return 0;
}

