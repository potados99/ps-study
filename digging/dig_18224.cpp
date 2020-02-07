/**
 * BOJ 18224
 * Gun-wo in the maze...
 */

#include <algorithm>
#include <iostream>
#include <queue>

typedef struct _ { int x, y, count; } block;
enum _day { DAY = 1, NIGHT = 0 };

int dx[] = { 0, 0, -1, 1 }; /* udlr */
int dy[] = { -1, 1, 0, 0 };

int n, m;
int map[500][500];
int visit[500][500];
int cnt[500][500];

bool wall_ends_in_map(block cur, int dx, int dy, int *x_after_wall, int *y_after_wall) {
    int x = cur.x + dx;
    int y = cur.y + dy;
    
    // while in map
    while ((0 <= x && x <= n-1) && (0 <= y && y <= n-1)) {
        if (map[x][y] == 0) {
            *x_after_wall = x;
            *y_after_wall = y;
            return true;
        }
        
        x += dx;
        y += dy;
    }
    
    return false;
}

int get_sun_status(int count, int half_day_length) {
    return ((count / half_day_length) + 1) % 2;
}

int get_day(int count, int half_day_length) {
    return (count / half_day_length) / 2 + 1;
}

std::string get_sun_string(int sun) {
    switch (sun) {
        case DAY: return "sun";
        case NIGHT: return "night";
    }
    return "";
}

bool next_place_I_should_go(block cur, int dx, int dy, int *dest_x, int *dest_y) {
    int sun = get_sun_status(cur.count, m);
    
    int x = cur.x + dx;
    int y = cur.y + dy;

    bool in_map = (0 <= x && x <= n-1) && (0 <= y && y <= n-1);
    
    if (!in_map) return false;

    bool is_a_wall = (map[x][y] == 1);
    bool is_night = (sun == NIGHT);

    // If this way leads to the end of the wall, check the end point and move to it.
    if (is_a_wall) {
        if (!is_night) return false;
        
        int x_after_wall = -1;
        int y_after_wall = -1;
        if (wall_ends_in_map(cur, dx, dy, &x_after_wall, &y_after_wall)) {
            x = x_after_wall;
            y = y_after_wall;
        } else {
            return false;
        }
    }

    // x and y in map asserted.
    bool is_visited = (visit[x][y] == 1);
    
    if (!is_visited) {
        *dest_x = x;
        *dest_y = y;
        return true;
    } else {
        return false;
    }
}

void dump() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << cnt[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

}

bool is_surrounded_by_walls(block cur) {
    for (int i = 0; i < 4; ++i) {
        int x = cur.x + dx[i];
        int y = cur.y + dy[i];

        bool in_map = (0 <= x && x <= n-1) && (0 <= y && y <= n-1);

        if (in_map && map[x][y] != 1)
            return false;
    }
    return true;
}

void unvisit5(block cur) {
    for (int i = 0; i < 4; ++i) {
        visit[cur.x+dx[i]][cur.y+dy[i]] = 0;
    }
    
    visit[cur.x][cur.y] = 0;
}

bool go_back(block cur) {
    // If surrounded by walls, cannot go back.
    if (is_surrounded_by_walls(cur))
        return false;
    
    unvisit5(cur);
        
    return true;
}

int shortest() {
    std::queue<block> q;

    q.push({0, 0, 0});
    visit[0][0] = 1;
    
    while (!q.empty()) {
        //dump();

        block cur = q.front();
        q.pop();
        
        if (cur.x == n - 1 && cur.y == n - 1) {
            return cur.count;
        }
        
        bool can_go_nowhere = true;
        for (int i = 0; i < 4; ++i) {
            int x, y;
            if (!next_place_I_should_go(cur, dx[i], dy[i], &x, &y)) continue;
            
            visit[x][y] = 1;
            cnt[x][y] = cur.count + 1;
            q.push({x, y, cur.count + 1});
            can_go_nowhere = false;
        }
        
        // I give you a chance.
        if (can_go_nowhere) {
            if (go_back(cur)) {
                q.push(cur);
            } else {
                return -1;
            }
        }
    }
    
    return -1;
}


int main(int argc, const char *argv[]) {
    std::cin >> n >> m;
    
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            std::cin >> map[i][j];
    
    int count = shortest();
    if (count == -1) {
        std::cout << -1 << std::endl;
    } else {
        std::cout << get_day(count, m) << " " << get_sun_string(get_sun_status(count, m)) << std::endl;
    }
    
    //std::cout << count << std::endl;
    
    return 0;
}

/**
6 2
0 0 1 0 1 0
0 1 1 0 1 0
1 1 1 1 1 1
0 0 1 0 1 0
1 1 1 1 1 1
0 0 1 0 1 0
*/

