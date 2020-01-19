#include <iostream>
#include <cstdint>

int raw[50][50];
int preprocessed[50][50];
int change[50][50];
int prove[50][50];

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

void dump(int arr[][50], int n, int m) {
    // dump
    std::cout << std::endl;
    int i, j;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, const char * argv[]) {
    int n, m, i, j;
    int up, down, left, right, mid = -1;
    int up_r, down_r, left_r, right_r, mid_r = -1;
    int cur, i_start, j_start, max = 0;
    
    int total = 0;
    
    std::cin >> n >> m;
    
    // store input
    for (i = 0; i < n; ++i)
        for (j = 0; j < m; ++j)
            raw[i][j] = (in() == 'W') ? 1 : 0; /* W: 1, B: 0 */
        
    // preprocess
    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            mid     = raw[i][j];
            up      = (i > 0)       ? raw[i-1][j] : !mid;
            down    = (i < n - 1)   ? raw[i+1][j] : !mid;
            left    = (j > 0)       ? raw[i][j-1] : !mid;
            right   = (j < m - 1)   ? raw[i][j+1] : !mid;
            
            preprocessed[i][j] = (mid ^ up) && (mid ^ down) && (mid ^ left) && (mid ^ right);
        }
    }
        
    // specify 8x8 frame
    i_start = 0;
    j_start = 0;
    for (i = 0; i <= n - 8; ++i) {
        for (j = 0; j <= m - 8; ++j) {
            cur = sum_preprocessed_8by8(i, j);
            if (cur > max) {
                max = cur;
                i_start = i;
                j_start = j;
            }
        }
    }
    dump(preprocessed, n, m);

    // process
    for (i = i_start; i < i_start + 8; ++i) {
        for (j = j_start; j < j_start + 8; ++j) {
            mid     = preprocessed[i][j];
            
            if (mid != 0) continue;
            
            up      = (i > i_start)       ? preprocessed[i-1][j] : 0;
            down    = (i < i_start + 7)   ? preprocessed[i+1][j] : 0;
            left    = (j > j_start)       ? preprocessed[i][j-1] : 0;
            right   = (j < j_start + 7)   ? preprocessed[i][j+1] : 0;

            mid_r   = raw[i][j];
            up_r    = (i > i_start)       ? raw[i-1][j] : mid_r;
            down_r  = (i < i_start + 7)   ? raw[i+1][j] : mid_r;
            left_r  = (j > j_start)       ? raw[i][j-1] : mid_r;
            right_r = (j < j_start + 7)   ? raw[i][j+1] : mid_r;
            
            bool four_way_no_combo = (up == 0 && down == 0 && left == 0 && right == 0);
            bool center_change_will_fix = (mid_r == up_r && mid_r == down_r && mid_r == left_r && mid_r == right_r);
            
            if (four_way_no_combo && center_change_will_fix) {
                total++;
                change[i][j] = 1;
            }
        }
    }
    dump(change, n, m);

    
    // prove
    for (i = i_start; i < i_start + 8; ++i)
        for (j = j_start; j < j_start + 8; ++j)
            prove[i][j] = (change[i][j] ? !raw[i][j] : raw[i][j]);
    
    dump(prove, n, m);
    
    std::cout << "total " << total << " changes" << std::endl;

    return 0;
}


/**
 

 BBBBBBBBWBWBW
 BBBBBBBBBWBWB
 BBBBBBBBWBWBW
 BBBBBBBBBWBWB
 BBBBBBBBWBWBW
 BBBBBBBBBWBWB
 BBBBBBBBWBWBW
 BBBBBBBBBWBWB
 WWWWWWWWWWBWB
 WWWWWWWWWWBWB
 
                                                     0 0 0 0 0 0 0 0 1 1 1 1 1
                                                     0 0 0 0 0 0 0 0 0 1 1 1 1
                                                     0 0 0 0 0 0 0 0 1 1 1 1 1
                                                     0 0 0 0 0 0 0 0 0 1 1 1 1
                                                     0 0 0 0 0 0 0 0 1 1 1 1 1
                                                     0 0 0 0 0 0 0 0 0 1 1 1 1
                                                     0 0 0 0 0 0 0 0 1 1 1 1 1
                                                     0 0 0 0 0 0 0 0 0 0 0 0 0
                                                     0 0 0 0 0 0 0 0 0 0 0 0 0
                                                     0 0 0 0 0 0 0 0 0 0 0 0 0
 
 
 
 */

