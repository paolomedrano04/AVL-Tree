#ifndef HW4_AVL_H
#define HW4_AVL_H

#include <iostream>

struct Node {
    int value;
    Node* left;
    Node* right;
    int balanceFactor;

    Node(int val) : value(val), left(nullptr), right(nullptr), balanceFactor(0) {}
};

int height(Node* node) {
    if (node == nullptr) {
        return -1;
    }
    return 1 + std::max(height(node->left), height(node->right));
}

void updateBalanceFactor(Node* node) {
    node->balanceFactor = height(node->right) - height(node->left);
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    updateBalanceFactor(x);
    updateBalanceFactor(y);
    return y;
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    updateBalanceFactor(y);
    updateBalanceFactor(x);
    return x;
}

Node* rotateLeftThenRight(Node* n) {
    n->left = rotateLeft(n->left);
    return rotateRight(n);
}

Node* rotateRightThenLeft(Node* n) {
    n->right = rotateRight(n->right);
    return rotateLeft(n);
}

Node* balance(Node* node) {
    updateBalanceFactor(node);

    if (node->balanceFactor == -2) {
        if (node->left->balanceFactor <= 0) {
            return rotateRight(node);
        } else {
            return rotateLeftThenRight(node);
        }
    } else if (node->balanceFactor == 2) {
        if (node->right->balanceFactor >= 0) {
            return rotateLeft(node);
        } else {
            return rotateRightThenLeft(node);
        }
    }

    return node;
}

Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);
    }

    if (value < root->value) {
        root->left = insert(root->left, value);
    } else if (value > root->value) {
        root->right = insert(root->right, value);
    }

    return balance(root);
}

Node* findMin(Node* node) {
    Node* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

Node* remove(Node* root, int value) {
    if (root == nullptr) {
        return root;
    }

    if (value < root->value) {
        root->left = remove(root->left, value);
    } else if (value > root->value) {
        root->right = remove(root->right, value);
    } else {
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            Node* temp = findMin(root->right);
            root->value = temp->value;
            root->right = remove(root->right, temp->value);
        }
    }

    if (root == nullptr) {
        return root;
    }

    return balance(root);
}

void preOrder(Node* root) {
    if (root == nullptr) return;
    std::cout << root->value << " ";
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(Node* root) {
    if (root == nullptr) return;
    inOrder(root->left);
    std::cout << root->value << " ";
    inOrder(root->right);
}

void postOrder(Node* root) {
    if (root == nullptr) return;
    postOrder(root->left);
    postOrder(root->right);
    std::cout << root->value << " ";
}

void clear(Node* node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

class AVLTREE {
private:
    Node* root;

public:
    AVLTREE() : root(nullptr) {}

    ~AVLTREE() {
        ::clear(root);
    }

    void insert(int value) {
        root = ::insert(root, value);
    }

    void remove(int value) {
        root = ::remove(root, value);
    }

    void preOrder() const {
        ::preOrder(root);
        std::cout << std::endl;
    }

    void inOrder() const {
        ::inOrder(root);
        std::cout << std::endl;
    }

    void postOrder() const {
        ::postOrder(root);
        std::cout << std::endl;
    }

    void clear() {
        ::clear(root);
        root = nullptr;
    }
};

#endif // HW4_AVL_H
