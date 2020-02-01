/**
 * BOJ 16551
 * Potato Sacks!
 */

#include <iostream>
#include <algorithm>

typedef struct _tc {
    int id;
    int cap;
    int weights[10];
    
    int counts[4];
} tc;

tc cases[100];

bool can_fill(tc *c) {
    for (int threes = 0; threes <= c->counts[3]; ++threes)
        for (int twos = 0; twos <= c->counts[2]; ++twos) {
            int ones = c->cap - (3 * threes) - (2 * twos);
            if (0 <= ones && ones <= c->counts[1])
                return true;
        }
    
    return false;
}

int main(int argc, const char *argv[]) {
    int p;
    std::cin >> p;
    
    for (int i = 0; i < p; ++i) {
        std::cin >> cases[i].id >> cases[i].cap;
        
        for (int j = 0; j < 10; ++j) {
            std::cin >> cases[i].weights[j];
            cases[i].counts[cases[i].weights[j]]++;
        }
    }
    
    for (int i = 0; i < p; ++i)
        std::cout << cases[i].id << " " << (can_fill(&cases[i]) ? "YES" : "NO") << std::endl;
}


