// A* implementation optimized for low end devices

#include <stdio.h>
#include  <vector>
#include <iostream>
#include <string>
#include <random>

class node{
public:
    int x;
    int y;
    bool is_start;
    bool is_obstacle;
    float g_cost;
    float h_cost;
    float f_cost;
    node* parent;

    node(int x,int y) : x(x), y(y), is_start(false), is_obstacle(false), g_cost(0), h_cost(0), f_cost(0), parent(nullptr) {
    }
    
};

std::vector<node> generate_grid(int rows, int cols) {
    std::vector<node> grid;
    grid.reserve(rows * cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid.emplace_back(i, j);
        }
    }

    return grid;
}

node* find_node(std::vector<node>& grid, int x, int y, int cols) {
    int index = x * cols + y;

    if (index < 0 || index >= grid.size()) {
        return nullptr;
    }

    return &grid[index];
}

int distance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}
int main() {

    //create a random number generator for obstacles and star/end randomization
    std::random_device rng;

    //grid is  10 by 15 to simulate a gba being chunked up into 16x16
    auto grid = generate_grid(10, 15);
    //create open and closed sets
    std::vector<node*> open_set;
    std::vector<node*> closed_set;
    //initialize start and end nodes
    node* start_node = find_node(grid, 0, 0, 15);
    node* end_node = find_node(grid, 9, 14, 15);
    node* test = find_node(grid, 5, 5, 15);

    std::cout << start_node->x << ", " << start_node->y << std::endl;
    std::cout << test->x << ", " << test->y << std::endl;
    std::cout << test->x << ", " << test->y << std::endl;

    return 0; 
}