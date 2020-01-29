/**
 * BOJ 17825
 * FUCKING DICE
 */

#include <iostream>

enum color {
    black = 1,
    blue = 2,
    red = 3
};

typedef struct _node {
    int             num;
    enum color      color;
    struct _node    *next;
    struct _node    *special;
} node;

typedef struct _map {
    struct _node    *start;
    struct _node    *last;
} map;

typedef struct _player {
    struct _node    *current;
    int             score;
    bool            finished;
} player;

typedef struct _context {
    struct _map     *map;
    struct _player  *players[];
} context;

typedef void (*callback)(context *, int *);

int nums[10];
int max;

node *create_node(int num, enum color color, node *next=nullptr, node *special=nullptr) {
    node *n = new node;
    
    n->num = num;
    n->color = color;
    n->next = next;
    n->special = special;
    
    return n;
}

node *attach(node *root, int num, enum color color, bool special) {
    node *new_node = create_node(num, color);
    if (special) {
        root->special = new_node;
    } else {
        root->next = new_node;
    }
    
    return new_node;
}

node *attach_line(node *root, int numc, int *numv, bool special) {
    if (numc == 0) return nullptr;
    
    node *last = attach(root, numv[0], black, special);
    
    for (int i = 1; i < numc; ++i) {
        node *new_node = attach(last, numv[i], black, false);
        last = new_node;
    }
    
    return last;
}

map *get_map() {
    node *start_node = create_node(0, black);
        
    node *node10 = attach_line(start_node, 5, new int[5] {2, 4, 6, 8, 10}, false);
    node *node20 = attach_line(node10, 5, new int[5] {12, 14, 16, 18, 20}, false);
    node *node30 = attach_line(node20, 5, new int[5] {22, 24, 26, 28, 30}, false);
    node *node40 = attach_line(node30, 5, new int[5] {32, 34, 36, 38, 40}, false);
    node10->color = node20->color = node30->color = blue;
    
    node *node25 = create_node(25, black);
    attach_line(node10, 3, new int[3] {13, 16, 19}, true)->next = node25;
    attach_line(node20, 2, new int[2] {22, 24}, true)->next = node25;
    attach_line(node30, 3, new int[3] {28, 27, 26}, true)->next = node25;
    attach_line(node25, 2, new int[2] {30, 35}, false)->next = node40;
        
    map *new_map = new map;
    new_map->start = start_node;
    new_map->last = node40;
    
    return new_map;
}

context *init() {
    context *c = new context;
    map *m = get_map();
    
    c->map = m;
        
    for (int i = 0; i < 4; ++i) {
        player *p = new player;
        p->current = m->start;
        p->score = 0;
        p->finished = false;
        
        c->players[i] = p;
    }
    
    return c;
}

bool is_end(context *c, node *here) {
    return (here == c->map->last);
}

int how_many_are_there(context *c, node *here) {
    if (here == nullptr) return 0;
    
    int count = 0;
    
    for (int i = 0; i < 4; ++i) {
        if (c->players[i]->current == here) count++;
    }
    
    return count;
}

void move(context *c, int player_index, int how_many) {
    if (how_many < 1) return;
    if (c->players[player_index]->finished) return;
    if (c->players[player_index]->current == nullptr) return;
    
    player *p = c->players[player_index];
    node *cursor = p->current;
  
    cursor = (cursor->color == blue) ? cursor->special : cursor->next;
    how_many--;

    // now go the next.
    for (int i = 0; i < how_many; ++i) {
        if (cursor == nullptr) break;
        cursor = cursor->next;
    }
    
    if (cursor == nullptr) {
        p->current = nullptr;
        p->finished = true;
        return;
    }
        
    bool valid = (how_many_are_there(c, cursor) < 1);
    
    p->score += valid ? cursor->num : 0;
    p->current = valid ? cursor : p->current;
}

void reset(context *c) {
    for (int i = 0; i < 4; ++i) {
        c->players[i]->current = c->map->start;
        c->players[i]->score = 0;
        c->players[i]->finished = false;
    }
}

int get_score(context *c, int player_index) {
    return c->players[player_index]->score;
}

int get_max_score(context *c) {
    int score = 0;
    
    for (int i = 0; i < 4; ++i) {
        score += get_score(c, i);
    }
    
    return score;
}

void dfs(int count, int *selected, callback on_pick, context *c) {
    if (count == 10) {
        on_pick(c, selected);
        return;
    }
    
    for (int i = 0; i < 4; ++i) {
        selected[count] = i;
        dfs(count + 1, selected, on_pick, c);
    }
}

void for_each_permutation(callback on_pick, context *c) {
    dfs(0, new int[10] {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, on_pick, c);
}

void do_on_pick(context *c, int *selected) {
    for (int i = 0; i < 10; ++i) {
        move(c, selected[i], nums[i]);
    }
    
    int local_max = get_max_score(c);
    if (local_max > max) {
        max = local_max;
    }
    
    reset(c);
}

int main(int argc, const char *argv[]) {
    context *c = init();

    for (int i = 0; i < 10; ++i) {
        std::cin >> nums[i];
    }
    
    for_each_permutation(do_on_pick, c);

    std::cout << max << std::endl;
    
    return 0;
}

