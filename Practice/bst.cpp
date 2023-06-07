#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int value)
    {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

class BST
{
private:
    Node *root;

public:
    BST()
    {
        root = nullptr;
    }

    Node *insertNode(Node *root, int value)
    {
        if (root == nullptr)
        {
            root = new Node(value);
            cout << "Node Inserted" << endl;
        }
        else if (root->data > value)
        {
            root->left = insertNode(root->left, value);
        }
        else if (root->data < value)
        {
            root->right = insertNode(root->right, value);
        }
        else
            cout << "Node already exists" << endl;
        return root;
    }

    void insert(int value)
    {
        root = insertNode(root, value);
    }

    Node *inOrder(Node *root)
    {
        if (root != nullptr)
        {
            inOrder(root->left);
            cout << root->data << " -> ";
            inOrder(root->right);
        }
    }

    void traverse()
    {
        inOrder(root);
        cout << endl;
    }

    int calcHeight(Node *node)
    {
        if (node == nullptr)
        {
            return -1;
        }

        int leftHeight = calcHeight(node->left);
        int rightHeight = calcHeight(node->right);

        return max(leftHeight, rightHeight) + 1;
    }
    void height()
    {
        int height = calcHeight(root);
        cout << "HEIGHT OF THE TREE IS : " << height << endl;
    }
};

int main()
{
    BST tree;
    tree.insert(46);
    tree.insert(40);
    tree.insert(54);
    tree.insert(4);
    tree.insert(45);
    tree.insert(22);
    tree.insert(32);
    tree.insert(49);
    tree.insert(54);
    tree.insert(48);
    tree.insert(20);
    tree.insert(94);
    tree.insert(37);
    tree.traverse();
    tree.height();
}