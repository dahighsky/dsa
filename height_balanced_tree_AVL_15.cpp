/*
Title: Write a menu driven C++ program to implement Height Balanced Binary Tree (AVL 
Tree) 
Problem Statement: A Dictionary stores keywords & its meanings. Provide facility for 
1. Add new keyword 
2. Delete keyword 
3. Update values of any entry. 
4. Sort data in Ascending & Descending order. 
5. Find how many maximum comparisons may require for finding any keyword. 
*/

#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

// Structure to represent a node in the AVL tree
struct Node {
    string keyword;
    string meaning;
    int height;
    Node* left;
    Node* right;

    Node(string keyword, string meaning) {
        this->keyword = keyword;
        this->meaning = meaning;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

// Function to get the height of a node
int getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

// Function to calculate the balance factor of a node
int getBalanceFactor(Node* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to update the height of a node based on the heights of its children
void updateHeight(Node* node) {
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}

// Function to perform a right rotation on a node
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    return x;
}

// Function to perform a left rotation on a node
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    return y;
}

// Function to balance the AVL tree
Node* balance(Node* node, string keyword) {
    // Calculate the balance factor of the node
    int balanceFactor = getBalanceFactor(node);

    // Left Left case
    if (balanceFactor > 1 && keyword < node->left->keyword)
        return rotateRight(node);

    // Right Right case
    if (balanceFactor < -1 && keyword > node->right->keyword)
        return rotateLeft(node);

    // Left Right case
    if (balanceFactor > 1 && keyword > node->left->keyword) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left case
    if (balanceFactor < -1 && keyword < node->right->keyword) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    // No imbalance, return the node as it is
    return node;
}

// Function to insert a node into the AVL tree
Node* insert(Node* root, string keyword, string meaning) {
    // Perform standard BST insertion
    if (root == nullptr)
        return new Node(keyword, meaning);

    if (keyword < root->keyword)
        root->left = insert(root->left, keyword, meaning);
    else if (keyword > root->keyword)
        root->right = insert(root->right, keyword, meaning);
    else {
        cout << "Keyword already exists." << endl;
        return root;
    }

    // Update the height of the current node
    updateHeight(root);

    // Balance the tree
    return balance(root, keyword);
}

// Function to find the node with the minimum value in a subtree
Node* findMinNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// Function to delete a node from the AVL tree
Node* deleteNode(Node* root, string keyword) {
    // Perform standard BST delete
    if (root == nullptr)
        return root;

    if (keyword < root->keyword)
        root->left = deleteNode(root->left, keyword);
    else if (keyword > root->keyword)
        root->right = deleteNode(root->right, keyword);
    else {
        // Node to be deleted is found

        // Node with only one child or no child
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;

            // No child case
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            }
            // One child case
            else
                *root = *temp; // Copy the contents of the child node

            delete temp;
        } else {
            // Node with two children
            Node* temp = findMinNode(root->right);
            root->keyword = temp->keyword;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->keyword);
        }
    }

    // If the tree had only one node, return
    if (root == nullptr)
        return root;

    // Update the height of the current node
    updateHeight(root);

    // Balance the tree
    return balance(root, keyword);
}

// Function to update the meaning of a keyword in the AVL tree
void updateMeaning(Node* root, string keyword, string newMeaning) {
    if (root == nullptr)
        return;

    if (keyword < root->keyword)
        updateMeaning(root->left, keyword, newMeaning);
    else if (keyword > root->keyword)
        updateMeaning(root->right, keyword, newMeaning);
    else {
        root->meaning = newMeaning;
        return;
    }
}

// Function to perform an in-order traversal of the AVL tree and display the keywords and meanings
void inOrderTraversal(Node* root) {
    if (root == nullptr)
        return;

    inOrderTraversal(root->left);
    cout << root->keyword << ": " << root->meaning << endl;
    inOrderTraversal(root->right);
}

// Function to perform a reverse in-order traversal of the AVL tree and display the keywords and meanings
void reverseInOrderTraversal(Node* root) {
    if (root == nullptr)
        return;

    reverseInOrderTraversal(root->right);
    cout << root->keyword << ": " << root->meaning << endl;
    reverseInOrderTraversal(root->left);
}

// Function to find the maximum comparisons required for finding a keyword in the AVL tree
int findMaxComparisons(Node* root, string keyword) {
    int comparisons = 0;

    Node* current = root;
    while (current != nullptr) {
        comparisons++;
        if (keyword < current->keyword)
            current = current->left;
        else if (keyword > current->keyword)
            current = current->right;
        else
            break;
    }

    return comparisons;
}

int main() {
    Node* root = nullptr;

    int choice;
    string keyword, meaning;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add new keyword\n";
        cout << "2. Delete keyword\n";
        cout << "3. Update meaning of a keyword\n";
        cout << "4. Sort data in ascending order\n";
        cout << "5. Sort data in descending order\n";
        cout << "6. Find maximum comparisons for a keyword\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the keyword: ";
                cin >> keyword;
                cout << "Enter the meaning: ";
                cin >> meaning;
                root = insert(root, keyword, meaning);
                cout << "Keyword added successfully.\n";
                break;
            case 2:
                cout << "Enter the keyword to delete: ";
                cin >> keyword;
                root = deleteNode(root, keyword);
                cout << "Keyword deleted successfully.\n";
                break;
            case 3:
                cout << "Enter the keyword to update: ";
                cin >> keyword;
                cout << "Enter the new meaning: ";
                cin >> meaning;
                updateMeaning(root, keyword, meaning);
                cout << "Meaning updated successfully.\n";
                break;
            case 4:
                cout << "Sorted data in ascending order:\n";
                inOrderTraversal(root);
                break;
            case 5:
                cout << "Sorted data in descending order:\n";
                reverseInOrderTraversal(root);
                break;
            case 6:
                cout << "Enter the keyword to find maximum comparisons: ";
                cin >> keyword;
                cout << "Maximum comparisons required: " << findMaxComparisons(root, keyword) << endl;
                break;
            case 7:
                cout << "Exiting program...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}
