#include <iostream>
#include "Tree.hpp"

int main(){
    Tree<int> t1(1);
    Tree<int> t2(2);
    t1.add_child(t2);
    t1[0] = 3;
    std::cout<<t2.self()<<std::endl;
    std::cout<<t1.child(0).self()<<std::endl;

    t2.self() = 5;
    std::cout<<t1.child(0).self()<<std::endl;
}