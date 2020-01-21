/**
 * BOJ 1018
 * Paint chessboard.
 */

#include <iostream>
#include <cstdint>

int raw[50][50];
int preprocessed[50][50];
int answer_from_white[50][50];
int answer_from_black[50][50];
int change[50][50];
int prove[50][50];
int total = 2500;

char in() { char c; std::cin >> c; return c; }

int sum_preprocessed_8by8(int row, int col) {
    int sum = 0;
    for (int i = row; i < row + 8; ++i) {
        for (int j = col; j < col + 8; ++j) {
            sum += preprocessed[i][j];
        }
    }
    return sum;
}

int main(int argc, const char * argv[]) {
    int n, m, i, j, ii, jj, t = 1;
    
    int total_way1 = 0;
    int total_way2 = 0;

    std::cin >> n >> m;
        
    // get answer ready
    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            answer_from_white[i][j] = t;
            answer_from_black[i][j] = !t;
            t = !t;
        }
        if (m % 2 == 0) t = !t;
    }

    // store input
    for (i = 0; i < n; ++i)
        for (j = 0; j < m; ++j)
            raw[i][j] = (in() == 'W') ? 1 : 0; /* W: 1, B: 0 */
    
    // process
    for (i = 0; i <= n - 8; ++i) {
        for (j = 0; j <= m - 8; ++j) {
            
            total_way1 = 0;
            total_way2 = 0;
            
            for (ii = i; ii < i + 8; ++ii) {
                for (jj = j; jj < j + 8; ++jj) {
                    if (raw[ii][jj] != answer_from_white[ii][jj])
                        total_way1++;
                    else
                        total_way2++;
                }
            }
            
            t = ((total_way1 > total_way2) ? total_way2 : total_way1);
            
            if (t < total)
                total = t;
        }
    }
    
    
    // print
    std::cout << total << std::endl;
    
    return 0;
}

