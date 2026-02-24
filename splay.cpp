#include "splay.h"

SplayTree::SplayTree() 
{
    root = nullptr; 
}

// aka Zig
SplayTree::Node* SplayTree::rotateRight(Node* x) {
    Node* y = x->left;

    if(y != nullptr)
    {
        if(y->weight < x->weight)
        {
            return x;
        }
    }

    x->left = y->right;
    y->right = x;
    return y;
}

// aka Zag
SplayTree::Node* SplayTree::rotateLeft(Node* x) {
    Node* y = x->right;
    if(y!= nullptr)
    {
        if(y->weight < x->weight)
        {
         return x;
        }
    }

    x->right = y->left;
    y->left = x;
    return y;
}

// Splaying :)
SplayTree::Node* SplayTree::splay(Node* root, int key) {
    if(root == nullptr || root->key == key)
    {
        return root;
    }

    //depth
    int d = 0;

    if(key < root->key)
    {
        if(root->left == nullptr)
        {
            return root;
        }
        if(d < 2)
        {
        if(key < root->left->key)
        {
            root->left->left = splay(root->left->left, key);
            root = rotateRight(root);
        }
        else if(key > root->left->key)
        {
            root->left->right = splay(root->left->right, key);
            if(root->left->right != nullptr)
            {
                root->left = rotateLeft(root->left);
            }

        }
        if(root->left == nullptr)
        {
            return root;
        }
        d++;
        }
        else
        {
            return rotateRight(root);
        }
        
    }

    if(key > root->key)
    {
        if(root->right == nullptr)
        {
            return root;
        }
        if(d < 2)
        {
        if(key > root->right->key)
        {
            root->right->right = splay(root->right->right, key);
            root = rotateLeft(root);
        }
        else if(key < root->right->key)
        {
            root->right->left = splay(root->right->left, key);
            if(root->right->left != nullptr)
            {
                root->right = rotateRight(root->right);
            }

        }
        d++;
        }
        if(root->right == nullptr)
        {
            return root;
        }
        else
        {
            return rotateLeft(root);
        }
    }

}


SplayTree::Node* SplayTree::insertNode(Node* root, int key) {
    if(root == nullptr)
    {
        return new Node(key);
    }
    root = splay(root, key);
    
    if(root->key == key)
    {
        return root;
    }
    Node* newNode = new Node(key);
    if(key < root->key)
    {
        newNode->right = root;
        newNode->left = root->left;
        root->left == nullptr;
    }
    else
    {
        newNode->left = root;
        newNode->right = root->right;
        root->right = nullptr;
    }

    return newNode;
}



SplayTree::Node* SplayTree::deleteNode(Node* root, int key) {
    if(root == nullptr)
    {
        return root;
    }

    root = splay(root, key);

    if(root->key != key)
    {
        return root;
    }

    Node* tmp;

    if(root->left == nullptr)
    {
        tmp = root;
        root = root->right;
    }
    else
    {
        tmp = root;
        Node* newR = root->left;
        newR = splay(newR, key);
        newR->right = root->right;
        root = newR;
    }

    delete tmp;
    return root;

}


void SplayTree::insert(int key) {
    root = insertNode(root, key);
}


void SplayTree::remove(int key) {
    root = deleteNode(root, key);
}


bool SplayTree::search(int key) {
    if(root == nullptr)
    {
        return false;
    }

    root = splay(root, key);

    if(root->key != key)
    {
        return false;
    }

    root->weight++;

    return true;
    //root = splay(root, key);
    //return (root && root->key == key);
}


void SplayTree::printTree(Node* root, int space) {
    const int COUNT = 10; 

    if (root == nullptr) {
        return;
    }

    // Increase the distance between levels
    space += COUNT;

    // Print the right child first (to appear on top)
    printTree(root->right, space);

    // Print the current node after right child

    for (int i = COUNT; i < space; i++) {
        cout << " "; // Indentation for tree depth
    }
    cout << root->key << endl;

    // Print the left child
    printTree(root->left, space);
}

void SplayTree::display() {
    printTree(root, 0);
    cout << endl;
}
