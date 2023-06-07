#include <bits/stdc++.h>
using namespace std;

struct Node
{
    char data;
    int frequency;
    Node *left;
    Node *right;

    Node(char d, int f)
    {
        data = d;
        frequency = f;
        left = nullptr;
        right = nullptr;
    }
};

struct Compare
{
    bool operator()(Node *a, Node *b)
    {
        return a->frequency > b->frequency;
    }
};

Node *buildTree(const unordered_map<char, int> &frequencies)
{
    priority_queue<Node *, vector<Node *>, Compare> pq;

    for (const auto &pair : frequencies)
    {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1)
    {
        Node *left = pq.top();
        pq.pop();

        Node *right = pq.top();
        pq.pop();

        Node *parent = new Node('$', (left->frequency + right->frequency));
        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }

    return pq.top();
}