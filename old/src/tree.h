#ifndef TREE_H
#define TREE_H

template<typename T>
class Tree
{
private:
    T& const root;
    std::vector<T> children;
public:
    Tree() {}
    Tree(T& obj) { root = obj; }
    int size() const { return height; }
    T& getRoot() const { return root; }
    T& getRoot() { return root; }

    void setRoot(T& node) { root = node }
    extern Tree addChild(T& node);
    extern map(T apply, T cl);

    extern free();
};

#endif