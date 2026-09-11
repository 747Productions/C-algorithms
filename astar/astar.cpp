// A* implementation optimized for low end devices

#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <optional>
class node {
public:
  std::optional<node *> parent;
  int x;
  int y;
  float g_cost;
  float h_cost;
  float f_cost;
  bool is_start;
  bool is_obstacle;

  node(int x, int y)
      : x(x), y(y), is_start(false), is_obstacle(false), g_cost(0), h_cost(0),
        f_cost(0), parent(std::nullopt) {}
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

std::optional<node *> find_node(std::vector<node> &grid, int x, int y,
                                int cols) {
  int index = x * cols + y;

  if (index < 0 || index >= grid.size()) {
    return std::nullopt;
  }

  return &grid[index];
}

int distance(int x1, int y1, int x2, int y2) {
  return abs(x1 - x2) + abs(y1 - y2);
}

int main() {
  // create a random number generator for obstacles and star/end randomization
  std::random_device rng;

  // grid is  10 by 15 to simulate a gba being chunked up into 16x16
  auto grid = generate_grid(10, 15);
  // create open and closed sets
  std::vector<node *> open_set;
  std::vector<node *> closed_set;
  // initialize start and end nodes
  auto start_node = find_node(grid, 0, 0, 15);
  auto end_node = find_node(grid, 9, 14, 15);
  assert(start_node && end_node
         "find_node() failed on start_node or end_node");

  std::cout << (*start_node)->x << ", " << (*start_node)->y << '\n';


  return 0;
}
