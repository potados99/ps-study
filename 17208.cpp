/**
 * BOJ 17208
 * Cow burger
 */

#include <cstring>
#include <iostream>
#include <algorithm>

#define POTATO 301
#define BURGER 301

int n, burger, potato;
int map[BURGER][POTATO];
int buf[BURGER][POTATO];

void clear(int buffer[][POTATO]) {
    memset(buffer, 0, sizeof(int) * BURGER * POTATO);
}

void copy(int source[][POTATO], int dest[][POTATO]) {
    memcpy(dest, source, sizeof(int) * BURGER * POTATO);
}

int get_max(int buffer[][POTATO]) {
    int m = 0;
    for (int i = 1; i <= burger; ++i)
        for (int j = 1; j <= potato; ++j)
            m = std::max(buffer[i][j], m);
    
    return m;
}

void dump(int buffer[][POTATO]) {
    std::string space = "  ";
    
    std::cout << "\\" << space;
    for (int i = 1; i <= potato; ++i)
        std::cout << i << space;
    std::cout << std::endl;
    
    for (int i = 1; i <= burger; ++i) {
        std::cout << i << space;
        for (int j = 1; j <= potato; ++j)
            std::cout << buffer[i][j] << space;
        std::cout << std::endl;
    }
}

void update_map(int req_burger, int req_potato) {
    for (int row = 1; row <= burger; ++row) {
        for (int col = 1; col <= potato; ++col) {
            // We are going to mark map[row+req_burger][col+req_potato]
            // to map[row][col]+1 ONLY IF map[row][col] is over zero
            // and the new value is greater than or equal to the old one.
            
            bool is_not_zero = map[row][col] > 0;
            bool row_possible = (row + req_burger <= burger);
            bool col_possible = (col + req_potato <= potato);
            
            if (is_not_zero && row_possible && col_possible) {
                int the_old_one = map[row+req_burger][col+req_potato];
                int the_new_one = map[row][col] + 1;
                
                buf[row+req_burger][col+req_potato] = std::max(the_old_one, the_new_one);
            }
        }
    }
    
    buf[req_burger][req_potato] = std::max(map[req_burger][req_potato], 1);
    
    // commit the change.
    copy(buf/*source*/, map/*dest*/);
}

int main(int argc, const char *argv[]) {
    std::cin >> n >> burger >> potato;
    
    for (int i = 0, b, p; i < n; ++i) {
        std::cin >> b >> p;
        update_map(b, p);
    }
    
    std::cout << get_max(map) << std::endl;
        
    return 0;
}

