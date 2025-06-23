#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define GRID_HEIGHT 40
#define GRID_WIDTH 80   

void clear_screen();

void display_grid(char** grid, int rows, int cols);

void init_grid(char** grid, int rows, int cols);

void compute_next_gen(char** current_grid, char** next_grid, int rows, int cols);

int count_live_neighbours(char** grid, int rows, int cols, int r, int c);

int main(int argc, char* argv[]) {
    char** current = malloc(sizeof(char*) * GRID_HEIGHT);
    if (current == NULL) {
        exit(1);
    }
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        current[i] = malloc(sizeof(char) * GRID_WIDTH);
        if (current[i] == NULL) {
            exit(2);
        }
    }

    char** next = malloc(sizeof(char*) * GRID_HEIGHT);
    if (next == NULL) {
        exit(1);
    }
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        next[i] = malloc(sizeof(char) * GRID_WIDTH);
        if (next[i] == NULL) {
            exit(2);
        }
    }

    init_grid(current, GRID_HEIGHT, GRID_WIDTH);

    while (1) {
        clear_screen();
        display_grid(current, GRID_HEIGHT, GRID_WIDTH);
        compute_next_gen(current, next, GRID_HEIGHT, GRID_WIDTH);
        for (int i = 0; i < GRID_HEIGHT; ++i) {
            for (int j = 0; j < GRID_WIDTH; ++j) {
                current[i][j] = next[i][j];
            }
        }
        usleep(100000);
    }
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        free(current[i]);
        free(next[i]);
    }
    free(current);
    free(next);
    return 0;

}

void clear_screen() {
    printf("\e[1;1H\e[2J");
}

void display_grid(char** grid, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
}

void init_grid(char** grid, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (rand() % 6 == 0) {
                grid[i][j] = '#';
            }
            else {
                grid[i][j] = ' ';
            }
        }
    }
}

void compute_next_gen(char** current_grid, char** next_grid, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int neighbours = count_live_neighbours(current_grid, rows, cols, i, j);
            // Live cell
            if (current_grid[i][j] == '#') { 
                if (neighbours < 2 || neighbours > 3) 
                    next_grid[i][j] = ' ';
                else 
                    next_grid[i][j] = '#';
            } else { 
                if (neighbours == 3)
                    next_grid[i][j] = '#';
                else
                    next_grid[i][j] = ' ';
            }
        }
    }
}

int count_live_neighbours(char** grid, int rows, int cols, int r, int c) {
    int neighbours = 0;
    int x_pos[8] = {0, 0, 1, 1, 1, -1, -1, -1};
    int y_pos[8] = {1, -1, 0, 1, -1, 0, 1, -1};
    for (int i = 0; i < 8; ++i) {
        int x = r + x_pos[i];
        int y = c + y_pos[i];
        if (x >= 0 && x < GRID_HEIGHT && y >= 0 && y < GRID_WIDTH) {
            if (grid[x][y] == '#') {
                neighbours++;
            }
        }
    }
    return neighbours;
}
