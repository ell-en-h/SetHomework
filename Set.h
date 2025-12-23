#pragma once
#include <initializer_list>
#include <stack>
#include <iterator>

class Set {
private:
    struct Node {
        int value;
        int height;
        Node* left;
        Node* right;
        Node(int v) : value(v), height(1), left(nullptr), right(nullptr) {}
    };
    Node* root;
    int m_size;
public:
    Set();
    Set(std::initializer_list<int> init);
    Set(const Set& other);
    ~Set();
    Set& operator=(const Set& other);

    bool empty() const;
    int size() const;
    bool contains(int value) const;

    void insert(int value);
    void erase(int value);

    bool operator==(const Set& other) const;
    bool operator!=(const Set& other) const;
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = int;
        using difference_type = std::ptrdiff_t;
        using pointer = const int*;
        using reference = const int&;

        iterator() = default;
        reference operator*() const;

        iterator& operator++();     
        iterator operator++(int); 

        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;
    private:
        std::stack<Node*> st;
        void pushLeft(Node* node);

        iterator(Node* root);
        friend class Set;
    };
    iterator begin();
    iterator end();
    iterator find(int value);
    iterator lower_bound(int value);
    iterator upper_bound(int value);
    iterator erase(iterator pos);
private:
    int height(Node* n) const;
    int balance(Node* n) const;

    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);

    Node* insert(Node* node, int value);
    Node* erase(Node* node, int value);
    Node* minNode(Node* node) const;

    Node* copy(Node* node);
    void clear(Node* node);

    bool equals(Node* a, Node* b) const;
};
