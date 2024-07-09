#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HEIGHT 28
#define WIDTH 50

// 1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
// 2. Any live cell with two or three live neighbours lives on to the next generation.
// 3. Any live cell with more than three live neighbours dies, as if by overpopulation.
// 4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

char states[] = " @";
int grid[HEIGHT][WIDTH] = {0};
int nextGrid[HEIGHT][WIDTH] = {0};

int nextState[2][9] = {
                        {0, 0, 0, 1, 0, 0, 0, 0, 0},
                        {0, 0, 1, 1, 0, 0, 0, 0, 0}
                      };

int neighbors[8][2] = { {-1, -1}, {-1, 0}, {-1, 1},
                        { 0, -1}, { 0, 1},
                        { 1, -1}, { 1, 0}, { 1, 1}
                      };

int random_state() {
    float x = (float)rand()/(float)RAND_MAX;
    return (x > 0.5f) ? 1 : 0;
}

void compute_live_neighbors(int y, int x, int *c) {
    for (size_t i = 0; i < sizeof(neighbors)/sizeof(neighbors[0]); i++) {
        if (grid[(y + neighbors[i][0] + HEIGHT) % HEIGHT][(x + neighbors[i][1] + WIDTH) % WIDTH]) *c = *c + 1;
    }
}

void display_grid() {
    for (size_t y = 0; y < HEIGHT; y++) {
        for (size_t x = 0; x < WIDTH; x++) {
            printf("%c ", states[grid[y][x]]);
        }
        printf("\n");
    }
}

void compute_next_grid() {
    int liveNeighbor = 0;
    for (size_t y = 0; y < HEIGHT; y++) {
        for (size_t x = 0; x < WIDTH; x++) {
            compute_live_neighbors(y, x, &liveNeighbor);
            nextGrid[y][x] = nextState[grid[y][x]][liveNeighbor];
            liveNeighbor = 0;
        }
    }

    for (size_t y = 0; y < HEIGHT; y++) {
        for (size_t x = 0; x < WIDTH; x++) {
            grid[y][x] = nextGrid[y][x];
        }
    }
}

void init_grid() {
    srand(time(NULL));
    for (size_t y = 0; y < HEIGHT; y++) {
        for (size_t x = 0; x < WIDTH; x++) {
            grid[y][x] = random_state();
        }
    }

    // a glider
    // grid[12][25] = 1;
    // grid[11][25] = 1;
    // grid[10][25] = 1;
    // grid[10][24] = 1;
    // grid[11][23] = 1;

    display_grid();
}

void delay(int n) {
    int tn = 1000 * n;
    clock_t start_time = clock();
 
    while (clock() < start_time + tn);
}

int main() {
    init_grid();

    while (1) {
        delay(125);
        compute_next_grid();
        display_grid();
    }

    return 0;
}

