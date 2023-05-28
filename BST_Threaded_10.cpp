/*
Title: Write a menu driven C++ program to implement Threaded Binary T with n nodes. 
Problem Statement: Create inorder threaded binary search tree and implement following 
operations 
1. Insert a new node 2. Inorder and preorder traversal 
3. Convert given binary search tree into threaded binary search tree.
*/

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    bool isThreaded; // Indicates if the right pointer is a thread
};

class TBST {
private:
    Node* root;

public:
    TBST() {
        root = nullptr;
    }

    Node* createNode(int data) {
        Node* newNode = new Node();
        newNode->data = data;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->isThreaded = false;
        return newNode;
    }

    Node* insertNode(Node* root, int data) {
        if (root == nullptr) {
            root = createNode(data);
            return root;
        }

        if (data < root->data) {
            root->left = insertNode(root->left, data);
            root->isThreaded = false;
        } else if (data > root->data) {
            if (root->isThreaded) {
                Node* newNode = createNode(data);
                newNode->left = root;
                newNode->right = root->right;
                root->right = newNode;
                root->isThreaded = false;
            } else {
                root->right = insertNode(root->right, data);
            }
        }

        return root;
    }

    void insertNode() {
        int data;
        cout << "Enter data to insert: ";
        cin >> data;

        root = insertNode(root, data);
        cout << "Node inserted successfully!" << endl;
    }

    Node* findLeftMost(Node* node) {
        if (node == nullptr)
            return nullptr;

        while (node->left != nullptr)
            node = node->left;

        return node;
    }

    void inorderTraversal() {
        Node* current = findLeftMost(root);

        while (current != nullptr) {
            cout << current->data << " ";

            if (current->isThreaded)
                current = current->right;
            else
                current = findLeftMost(current->right);
        }

        cout << endl;
    }

    void preorderTraversal() {
        Node* current = root;

        while (current != nullptr) {
            cout << current->data << " ";

            if (current->isThreaded)
                current = current->right;
            else {
                if (current->left != nullptr)
                    current = current->left;
                else
                    current = current->right;
            }
        }

        cout << endl;
    }

    Node* convertToThreaded(Node* root, Node* prev) {
        if (root == nullptr)
            return nullptr;

        root->left = convertToThreaded(root->left, prev);

        if (prev != nullptr && prev->right == nullptr) {
            prev->right = root;
            prev->isThreaded = true;
        }

        prev = root;

        root->right = convertToThreaded(root->right, prev);

        return root;
    }

    void convertToThreaded() {
        Node* prev = nullptr;
        root = convertToThreaded(root, prev);
        cout << "Binary search tree converted to threaded binary search tree!" << endl;
    }
};

int main() {
    TBST tbst;
    int choice;

    do {
        cout << "\n----- Threaded Binary Search Tree Menu -----";
        cout << "\n1. Insert a new node";
        cout << "\n2. Inorder traversal";
        cout << "\n3. Preorder traversal";
        cout << "\n4. Convert to threaded binary search tree";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                tbst.insertNode();
                break;
            case 2:
                cout << "Inorder traversal: ";
                tbst.inorderTraversal();
                break;
            case 3:
                cout << "Preorder traversal: ";
                tbst.preorderTraversal();
                break;
            case 4:
                tbst.convertToThreaded();
                break;
            case 5:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 5);

    return 0;
}
