// A* implementation optimized for low end devices

#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <optional>
#include <cmath>
#include <algorithm>
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
std::optional<node *> lowest_f(const std::vector<node *> &nodeset) {
  if (nodeset.empty()) {
    return std::nullopt;
  }
  
  auto lowest = nodeset[0];
  for (const auto &node : nodeset) {
    if (node->f_cost < lowest->f_cost) {
      lowest = node;
    }
  }
  
  return lowest;
}
std::optional<node *> find_node(std::vector<node> &grid, int x, int y,
  int cols) {
    int index = x * cols + y;
    
    if (index < 0 || index >= grid.size()) {
      return std::nullopt;
    }
    
    return &grid[index];
  }
  std::vector<node *> getNeighbors(node *current, const std::vector<node> &grid, int cols) {
    std::vector<node *> neighbors;
    int x = current->x;
    int y = current->y;
    
    // Check the four possible neighbors (up, down, left, right)
    if (x > 0) {
      auto neighbor = find_node(const_cast<std::vector<node>&>(grid), x - 1, y, cols);
      if (neighbor && !neighbor.value()->is_obstacle) {
        neighbors.push_back(neighbor.value());
      }
    }
    if (x < grid.size() / cols - 1) {
      auto neighbor = find_node(const_cast<std::vector<node>&>(grid), x + 1, y, cols);
      if (neighbor && !neighbor.value()->is_obstacle) {
        neighbors.push_back(neighbor.value());
      }
    }
    if (y > 0) {
      auto neighbor = find_node(const_cast<std::vector<node>&>(grid), x, y - 1, cols);
      if (neighbor && !neighbor.value()->is_obstacle) {
        neighbors.push_back(neighbor.value());
      }
    }
    if (y < cols - 1) {
      auto neighbor = find_node(const_cast<std::vector<node>&>(grid), x, y + 1, cols);
      if (neighbor && !neighbor.value()->is_obstacle) {
        neighbors.push_back(neighbor.value());
      }
    }
    
    return neighbors;
  }
  bool includes(const std::vector<node *> &nodeset, node *node) {
    return std::find(nodeset.begin(), nodeset.end(), node) != nodeset.end();
  }
  
  
  int h(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
  }
  
  int main() {
    // grid is  10 by 15 to simulate a gba being chunked up into 16x16
    auto grid = generate_grid(10, 15);
    // create a random number generator for obstacles and star/end randomization
    std::random_device rng;
    //generate open and closed sets
    std::vector<node *> open_set;
    std::vector<node *> closed_set;
    
    
    //generate start and end nodes
    auto start_node = find_node(grid, 0, 0, 15);
    start_node.value()->is_start = true;
    auto end_node = find_node(grid, 9, 14, 15);
    //place start node inside of open set
    open_set.emplace_back(*start_node);
    
    
    //set default values for g and f scores
    auto camefrom =  std::nullopt;
    float g_score = INFINITY;
    float f_score = INFINITY;
    start_node.value()->f_cost = h(start_node.value()->x, start_node.value()->y, end_node.value()->x, end_node.value()->y);
    // initialize start and end nodes
    
    
    while(open_set.size() != 0 ){
      auto current = lowest_f(open_set);
      if (current == end_node) {
        std::cout << "Path found!\n";
        break;
      }
      open_set.erase(std::remove(open_set.begin(), open_set.end(), *current), open_set.end());
      auto neighbors = getNeighbors(*current, grid, 15);
      for (auto neighbor : neighbors) {
        // Process neighbors
        auto tentative_g_score = (*current)->g_cost + h((*current)->x, (*current)->y, neighbor->x, neighbor->y);
        if(tentative_g_score < neighbor->g_cost) {
          neighbor->parent = *current;
          neighbor->g_cost = tentative_g_score;
          neighbor->f_cost = neighbor->g_cost + h(neighbor->x, neighbor->y, end_node.value()->x, end_node.value()->y);
        }
        if(!includes(open_set, neighbor)) {
          open_set.push_back(neighbor);
        }
        
      }
    }
    
    std::cout << (*start_node)->x << ", " << (*start_node)->y << '\n';
    
    
    return 0;
  }
  