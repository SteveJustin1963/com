#include <stdio.h>
#include <stdlib.h>

#define MAX_WEIGHT 100 // maximum weight of the knapsack
#define MAX_ITEMS 50 // maximum number of items

// Structure for an item
typedef struct {
  int weight; // weight of the item
  int value; // value of the item
} Item;

// Function prototypes
int knapsack(Item items[], int num_items, int weight_limit);

int main(int argc, char *argv[]) {
  // Read in the items
  Item items[MAX_ITEMS];
  int num_items = 0;
  while (scanf("%d %d", &items[num_items].weight, &items[num_items].value) == 2) {
    num_items++;
  }

  // Solve the knapsack problem
  int max_value = knapsack(items, num_items, MAX_WEIGHT);
  printf("Maximum value: %d\n", max_value);

  return 0;
}

// Function to solve the knapsack problem using dynamic programming
int knapsack(Item items[], int num_items, int weight_limit) {
  // Initialize the table for
// Initialize the table for storing the maximum value of each subproblem
int table[MAX_ITEMS + 1][MAX_WEIGHT + 1];
for (int i = 0; i <= num_items; i++) {
  for (int j = 0; j <= weight_limit; j++) {
    table[i][j] = 0;
  }
}

// Loop over the items and weights
for (int i = 1; i <= num_items; i++) {
  for (int j = 0; j <= weight_limit; j++) {
    // If the weight of the current item exceeds the weight limit, skip it
    if (items[i - 1].weight > j) {
      table[i][j] = table[i - 1][j];
    }
    // Otherwise, consider including the current item in the knapsack
    else {
      // Calculate the maximum value of including the current item in the knapsack
      int value_including = items[i - 1].value + table[i - 1][j - items[i - 1].weight];

      // Update the maximum value for the current subproblem
      table[i][j] = max(table[i - 1][j], value_including);
    }
  }
}

// Return the maximum value for the final subproblem
return table[num_items][weight_limit];
}
