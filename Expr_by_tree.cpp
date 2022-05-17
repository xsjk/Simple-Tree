
#include <string>
#include <cmath>
#include <iostream>
#include <functional>
#include "Tree.hpp"
using std::string;

#define DEF_OPERATOR(op) \
friend Expr operator op (const Expr& a,const Expr& b) {\
    auto result = Expr({a,b},\
        [](const Expr& e)->double{ return e[0].eval() op e[1].eval(); }, \
        [](const Expr& e)->string{ return '(' + e[0].to_string() + " " #op " " + e[1].to_string() + ')'; }\
        );\
    result.add_child(a).add_child(b);\
    return result;\
}

#define DEF_FUNCTION(name) \
friend Expr name (const Expr& a) {\
    auto result = Expr({a},\
        [](const Expr& e)->double{ return name(e[0].eval()); }, \
        [](const Expr& e)->string{ string s = e[0].to_string(); return s[0] == '(' ? #name + s : string(#name) + '(' + s + ')';}\
        );\
    result.add_child(a);\
    return result;\
}

class Expr;
using Fdouble = std::function<double(const Expr&)>;
using Fstring = std::function<string(const Expr&)>;

class Expr: public Tree<Expr> {
    using List = const std::initializer_list<Expr>&;
    Fdouble get_val;
    Fstring get_str;
    Expr(List children, Fdouble f, Fstring g): Tree(children), get_val(f), get_str(g) {}
    public:
        Expr(double v): get_val([v](const Expr&){ return v; }), 
                        get_str([v](const Expr&){ return v<0 ? '(' + std::to_string(v) + ')' : std::to_string(v);}) {}
        double eval() const { return get_val(*this); }
        string to_string() const { return get_str(*this); }

    DEF_OPERATOR(+)   DEF_OPERATOR(-)   DEF_OPERATOR(*)   DEF_OPERATOR(/)
    DEF_FUNCTION(sin) DEF_FUNCTION(cos) DEF_FUNCTION(tan) DEF_FUNCTION(exp) DEF_FUNCTION(log)
};




std::ostream& operator<<(std::ostream &os, const Expr &e) {
    std::cout << e.to_string() << " = " << e.eval();
    return os;
}

int main(){
    Expr e1 = Expr(1);
    Expr e2 = e1 + Expr(3);
    std::cout << e2 << std::endl;
    e1 = Expr(5);
    std::cout << e2 << std::endl;
    return 0;
}
