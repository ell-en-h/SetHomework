#include "Set.h"
#include <algorithm>
#include <initializer_list> 

Set::Set() : root(nullptr), m_size(0) {}
Set::Set(std::initializer_list<int> init) : root(nullptr), m_size(0) {
    for (int v : init)
        insert(v);
}
Set::Set(const Set& other) : root(nullptr), m_size(other.m_size) {
    root = copy(other.root);
}
Set::~Set() {
    clear(root);
}
Set& Set::operator=(const Set& other) {
    if (this != &other) {
        clear(root);
        root = copy(other.root);
        m_size = other.m_size;
    }
    return *this;
}
bool Set::empty() const { return m_size == 0; }
int Set::size() const { return m_size; }

bool Set::contains(int value) const {
    Node* cur = root;
    while (cur) {
        if (value < cur->value) cur = cur->left;
        else if (value > cur->value) cur = cur->right;
        else return true;
    }
    return false;
}

int Set::height(Node* n) const { return n ? n->height : 0; }
int Set::balance(Node* n) const { return height(n->left) - height(n->right); }

Set::Node* Set::rotateRight(Node* y) {
    Node* x = y->left;
    Node* t = x->right;
    x->right = y;
    y->left = t;
    y->height = 1 + std::max(height(y->left), height(y->right));
    x->height = 1 + std::max(height(x->left), height(x->right));
    return x;
}

Set::Node* Set::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* t = y->left;
    y->left = x;
    x->right = t;
    x->height = 1 + std::max(height(x->left), height(x->right));
    y->height = 1 + std::max(height(y->left), height(y->right));
    return y;
}
void Set::insert(int value) {
    if (!contains(value)) {
        root = insert(root, value);
        ++m_size;
    }
}
Set::Node* Set::insert(Node* node, int value) {
    if (!node) return new Node(value);
    if (value < node->value)
        node->left = insert(node->left, value);
    else
        node->right = insert(node->right, value);

    node->height = 1 + std::max(height(node->left), height(node->right));
    int b = balance(node);

    if (b > 1 && value < node->left->value) return rotateRight(node);
    if (b < -1 && value > node->right->value) return rotateLeft(node);
    if (b > 1 && value > node->left->value) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (b < -1 && value < node->right->value) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}
void Set::erase(int value) {
    if (contains(value)) {
        root = erase(root, value);
        --m_size;
    }
}
Set::Node* Set::erase(Node* node, int value) {
    if (!node) return nullptr;
    if (value < node->value) node->left = erase(node->left, value);
    else if (value > node->value) node->right = erase(node->right, value);
    else {
        if (!node->left || !node->right) {
            Node* tmp = node->left ? node->left : node->right;
            delete node;
            return tmp;
        }
        Node* min = minNode(node->right);
        node->value = min->value;
        node->right = erase(node->right, min->value);
    }
    node->height = 1 + std::max(height(node->left), height(node->right));
    int b = balance(node);

    if (b > 1 && balance(node->left) >= 0) return rotateRight(node);
    if (b > 1 && balance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (b < -1 && balance(node->right) <= 0) return rotateLeft(node);
    if (b < -1 && balance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}
Set::Node* Set::minNode(Node* node) const {
    while (node->left) node = node->left;
    return node;
}
Set::iterator::iterator(Node* root) { pushLeft(root); }
void Set::iterator::pushLeft(Node* node) {
    while (node) {
        st.push(node);
        node = node->left;
    }
}
Set::iterator::reference Set::iterator::operator*() const { return st.top()->value; }
Set::iterator& Set::iterator::operator++() {
    Node* n = st.top(); st.pop();
    if (n->right) pushLeft(n->right);
    return *this;
}
Set::iterator Set::iterator::operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

bool Set::iterator::operator==(const iterator& other) const {
    if (st.empty() && other.st.empty()) return true;
    if (st.empty() || other.st.empty()) return false;
    return st.top() == other.st.top();
}
bool Set::iterator::operator!=(const iterator& other) const { return !(*this == other); }

Set::iterator Set::begin() { return iterator(root); }
Set::iterator Set::end() { return iterator(nullptr); }

Set::iterator Set::find(int value) {
    for (auto it = begin(); it != end(); ++it)
        if (*it == value) return it;
    return end();
}
Set::iterator Set::lower_bound(int value) {
    for (auto it = begin(); it != end(); ++it)
        if (*it >= value) return it;
    return end();
}
Set::iterator Set::upper_bound(int value) {
    for (auto it = begin(); it != end(); ++it)
        if (*it > value) return it;
    return end();
}
Set::iterator Set::erase(iterator pos) {
    int v = *pos;
    iterator next = pos; ++next;
    erase(v);
    return next;
}
Set::Node* Set::copy(Node* node) {
    if (!node) return nullptr;
    Node* n = new Node(node->value);
    n->left = copy(node->left);
    n->right = copy(node->right);
    n->height = node->height;
    return n;
}
void Set::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

bool Set::operator==(const Set& other) const { return equals(root, other.root); }
bool Set::operator!=(const Set& other) const { return !(*this == other); }

bool Set::equals(Node* a, Node* b) const {
    if (!a && !b) return true;
    if (!a || !b) return false;
    return a->value == b->value &&
           equals(a->left, b->left) &&
           equals(a->right, b->right);
}

