#ifndef TREE
#define TREE
#include <memory>
#include <vector>
#include <initializer_list>

template<typename T> class Tree {

    std::shared_ptr<T> obj_ptr;
    std::vector<Tree> child_trees;

    public:
        Tree() = default;
        Tree(const T& o): obj_ptr(std::make_shared<T>(o)) {}
        Tree(const std::initializer_list<T> children) { add_child(children);}
        
        size_t size() const { return child_trees.size(); }

        T& operator[](size_t i) const { return child(i).self(); }
        const Tree& child(size_t i) const { return child_trees[i]; }
        T& self() const { return *obj_ptr; }

        Tree& add_child(const Tree& child){
            child_trees.emplace_back(child);
            return *this;
        }

        Tree& add_child(const T& child){
            add_child(Tree<T>(child));
            return *this;
        }

        Tree& add_child(const std::initializer_list<T>& children){
            for(auto& t: children)
                add_child(t);
            return *this;
        }

        
        Tree& del_child(size_t i){
            child_trees.erase(child_trees.begin() + i);
            return *this;
        }
        
};

#endif