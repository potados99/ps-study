/**
 * BOJ 2206
 * Smash the wall.
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

typedef struct _ { int x, y, count, how_many_walls_did_you_break_to_get_here; } block;

int dx[] = { 0, 0, -1, 1 }; /* udlr */
int dy[] = { -1, 1, 0, 0 };

int map[1000][1000];
int n, m;

int shortest(int how_many_walls_may_I_break) {
    int visit[1000][1000] = {0, };
    
    std::queue<block> q;
        
    q.push({ 0, 0, 1, 0 });
    
    while (!q.empty()) {
        block cur = q.front();
        q.pop();

        int score = how_many_walls_may_I_break - cur.how_many_walls_did_you_break_to_get_here + 1;
        visit[cur.x][cur.y] = score;

        if (cur.x == n-1 && cur.y == m-1)
            return cur.count;
        
        // push 4 way!
        for (int i = 0; i < 4; ++i) {
            int x = cur.x + dx[i];
            int y = cur.y + dy[i];
            
            bool have_to_break_the_wall = (map[x][y] == 1);
            bool can_break_the_wall = (cur.how_many_walls_did_you_break_to_get_here < how_many_walls_may_I_break);
            bool in_map = (0 <= x && x <= n-1) && (0 <= y && y <= m-1);
            bool can_visit = (visit[x][y] < score);
            if (in_map && can_visit) {
                if (have_to_break_the_wall && !can_break_the_wall)
                    continue;
                
                q.push({
                    x,
                    y,
                    cur.count + 1,
                    cur.how_many_walls_did_you_break_to_get_here
                    +(have_to_break_the_wall && can_break_the_wall)
                });
                
                visit[x][y] = score - (have_to_break_the_wall && can_break_the_wall);
            }
        }
    }
    
    return -1;
}

int main(int argc, const char * argv[]) {
    std::ios_base::sync_with_stdio(0);
    
    std::string line;
    std::vector<uint32_t> v;

    // input
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        std::cin >> line;
        for (int j = 0; j < m; ++j) {
            map[i][j] = line[j] - '0';
        }
    }
 
    std::cout << shortest(1) << std::endl;

    return 0;
}


