# Smart Building Sensor Graph

A C++ project that models a smart building sensor system using a directed weighted graph.

Developed as a coursework assignment for the Algorithms and Data Structures course at the School of Electrical Engineering (ETF), University of Belgrade.

## Implementation Details

- Linear Congruential Generator (LCG) for pseudo-random number generation
- Linearized adjacency list as the graph representation
- 
## Features

### Sensor Generation

- Generates a user-defined number of sensors
- Each sensor has a unique identifier
- Sensor processing speeds are generated in the range [1, 100]
- Supports printing all generated sensors

### Graph Construction

- Generates sensor connections using a probability threshold p
- Generates distances between sensors in the range [0.5, 30.0]
- Creates a directed weighted graph representing the sensor network
- Calculates edge weights using the formula:

  t[i,j] = d[i,j] + 100 - min(v[i], v[j])

- Supports displaying the generated connectivity matrix

### Graph Operations

- Add a new sensor manually
- Remove an existing sensor
- Display the graph representation
- Delete the graph from memory

### Network Analysis

- Breadth-First Search (BFS)
- Depth-First Search (DFS)
- Traversal starting from a selected sensor
- Shortest path between two sensors
- Eccentricity calculation for every sensor
- Determination of the central sensor in the network

## Technologies

- C++11 / C++14
- Directed Weighted Graphs
- Linearized Adjacency Lists
- Linear Congruential Generator (LCG)
- BFS
- DFS
- Dynamic Memory Management

## Build

Compile the project using a standard C++ compiler:

```bash
g++ *.cpp -o sensor_graph
