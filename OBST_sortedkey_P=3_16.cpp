/*
Title: Write a C++ program to implement Optimal Binary Search Tree. 
Problem Statement: Given sequence k = k1<; k2<.... kn of n sorted keys, with a search 
probability pi for each key ki . Build the Binary search tree that has the least search cost given 
the access probability for each key. Test your program for following example 
p1 = 3, p2 = 3, p3 = 1, p4 = 1 
q0 = 2, q1 = 3, q2 = 1, q3= 1, q4 = 1 
1. Find optimal cost of tree 
2. Display root of tree
*/

#include <iostream>
#include <climits>
using namespace std;

// Function to calculate the optimal cost of a binary search tree
float optimalBSTCost(float p[], float q[], int n) {
    float cost[n + 1][n + 1];

    // Initialize the cost matrix
    for (int i = 1; i <= n + 1; i++) {
        cost[i][i - 1] = q[i - 1];
    }

    for (int len = 1; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            cost[i][j] = INT_MAX;
            float sum = 0;

            for (int k = i; k <= j; k++)
                sum += p[k];

            for (int k = i; k <= j; k++) {
                float temp = cost[i][k - 1] + cost[k + 1][j] + sum;
                if (temp < cost[i][j])
                    cost[i][j] = temp;
            }
        }
    }

    return cost[1][n];
}

// Function to display the root of the optimal binary search tree
void displayOptimalBST(float p[], float q[], int n) {
    float cost[n + 1][n + 1];

    // Initialize the cost matrix
    for (int i = 1; i <= n + 1; i++) {
        cost[i][i - 1] = q[i - 1];
    }

    int root[n + 1][n + 1];
    for (int i = 1; i <= n; i++) {
        root[i][i] = i;
    }

    for (int len = 1; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            cost[i][j] = INT_MAX;
            float sum = 0;

            for (int k = i; k <= j; k++)
                sum += p[k];

            for (int k = i; k <= j; k++) {
                float temp = cost[i][k - 1] + cost[k + 1][j] + sum;
                if (temp < cost[i][j]) {
                    cost[i][j] = temp;
                    root[i][j] = k;
                }
            }
        }
    }

    cout << "Root of the optimal binary search tree: " << root[1][n] << endl;
}

int main() {
    float p[] = {0, 3, 3, 1, 1}; // Search probabilities
    float q[] = {2, 3, 1, 1, 1}; // Access probabilities
    int n = sizeof(p) / sizeof(p[0]) - 1;

    float optimalCost = optimalBSTCost(p, q, n);
    cout << "Optimal cost of the binary search tree: " << optimalCost << endl;

    displayOptimalBST(p, q, n);

    return 0;
}
