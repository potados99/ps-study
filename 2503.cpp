/**
 * BOJ 2503
 * Numeric baseball
 */

#include <iostream>
#include <vector>

int N;
int answer;
int matches[999];

int nums[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int visited[9];
int selected[3];

void split(int combined, /* out */int *buf) {
    buf[0] = combined / 100;
    buf[1] = (combined / 10) % 10;
    buf[2] = combined % 10;
}

void check(int left, int right, /* out */int *strikes, /* out */int *balls) {
    int strk = 0;
    int bl = 0;
    int _left[3] = {0,};
    int _right[3] = {0,};

    split(left, _left);
    split(right, _right);
    
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (_left[i] == _right[j]) {
                if (i == j) strk++;
                else bl++;
            }
        
    *strikes = strk;
    *balls = bl;
}


void on_every_pick(int picked, int num, int strikes, int balls) {
    int strk = 0;
    int bl = 0;
    
    check(picked, num, &strk, &bl);
     
     if (strk == strikes && bl == balls)
         if (++matches[picked] >= N)
             answer++;
         
}

void try_all(int count, void (*on_pick)(int, int, int, int), int arg1, int arg2, int arg3) {
    if (count == 3) {
        on_pick(selected[0]*100 + selected[1]*10 + selected[2], arg1, arg2, arg3);
        return;
    }
    
    for (int i = 0; i < 9; ++i) {
        if (visited[i]) continue; // no dups
        
        selected[count] = nums[i];

        visited[i] = true;
        try_all(count + 1, on_pick, arg1, arg2, arg3);
        visited[i] = false;
    }
}

void update(int n, int strikes, int balls) {
    try_all(/* from nothing */0, on_every_pick, n, strikes, balls);
}

int main(int argc, const char *argv[]) {
    std::cin >> N;
    
    for (int i = 0; i < N; ++i) {
        int n, strk, bl;
        std::cin >> n >> strk >> bl;
        
        update(n, strk, bl);
    }
    
    std::cout << answer << std::endl;
    
    return 0;
}

