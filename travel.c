#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_CITIES 100

// Struct to represent a city
typedef struct {
  int x;
  int y;
} City;

// Struct to represent a solution to the TSP
typedef struct {
  int path[MAX_CITIES];
  int cost;
} TSPSolution;

// Calculates the distance between two cities
int cityDistance(City city1, City city2) {
  int dx = city1.x - city2.x;
  int dy = city1.y - city2.y;
  return (int)sqrt(dx*dx + dy*dy);
}

// Recursive function to find the shortest path through all cities
TSPSolution findShortestPath(int n, bool visited[MAX_CITIES], int currCity, int endCity, int cost, int path[MAX_CITIES], int distances[MAX_CITIES][MAX_CITIES]) {
  TSPSolution minSolution, newSolution;
  minSolution.cost = INT_MAX;

  // Mark the current city as visited
  visited[currCity] = true;

  // Add the current city to the path
  path[n] = currCity;

  // If all cities have been visited, check if the path is complete
  if (n == MAX_CITIES - 1) {
    // If the path is complete, calculate the cost
    if (distances[currCity][endCity] != 0) {
      int newCost = cost + distances[currCity][endCity];
      TSPSolution completeSolution;
      for (int i = 0; i < MAX_CITIES; i++) {
        completeSolution.path[i] = path[i];
      }
      completeSolution.cost = newCost;
      return completeSolution;
    } else {
      // If the path is not complete, return an invalid solution with a high cost
      TSPSolution invalidSolution;
      invalidSolution.cost = INT_MAX;
      return invalidSolution;
    }
  }

  // Try every city that hasn't been visited yet and find the shortest path
  for (int i = 0; i < MAX_CITIES; i++) {
    if (!visited[i] && distances[currCity][i] != 0) {
      newSolution = findShortestPath(n+1, visited, i, endCity, cost + distances[currCity][i], path, distances);
      if (newSolution.cost < minSolution.cost) {
        minSolution = newSolution;
      }
    }
  }

  // Mark the current city as not visited
  visited[currCity] = false;

  return minSolution;
}

int main(int argc, char **argv) {
  // Read in the city data from a file
  City cities[MAX_CITIES];
  int numCities;
  FILE *cityFile = fopen("cities.txt", "r");
  if (cityFile == NULL) {
    printf("Error opening cities file\n");
    return 1;
  }
  fscanf(cityFile, "%d", &numCities);
  for (int i = 0; i < numCities; i++) {
    fscanf(cityFile, "%d %d", &cities[i].x, &cities[i].y);
  }
  fclose(cityFile);

  // Calculate the distances between all cities
  int distances[MAX_CITIES][MAX_CITIES];
  for (int i = 0; i < numCities; i++) {
    for (int j = 0; j < numCities; j++) {
      distances[i][j] = cityDistance(cities[i], cities[j]);
    }
  }

  // Find the shortest path through all cities
  int startCity = 0;
  int endCity = numCities - 1;
  bool visited[MAX_CITIES];
  for (int i = 0; i < numCities; i++) {
    visited[i] = false;
  }
  int path[MAX_CITIES];
  TSPSolution solution = findShortestPath(0, visited, startCity, endCity, 0, path, distances);

  // Print the shortest path and cost
  printf("Shortest path: ");
  for (int i = 0; i < numCities; i++) {
    printf("%d ", solution.path[i]);
  }
  printf("\nTotal cost: %d\n", solution.cost);

  return 0;
}
