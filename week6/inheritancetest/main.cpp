#include <iostream>

class A {
    public:
        A(int data) : m_data(data) { std::cout << "cstor A" << std::endl; }
        virtual ~A() { std::cout << "dstor A" << std::endl; }
        void foo() { std::cout << "foo()" << std::endl; }
        int m_data;
};

class Left : public virtual A {
    public:
        Left() : A(1) { std::cout << "cstor Left" << std::endl; }
        virtual ~Left() { std::cout << "dstor Left" << std::endl; }
};

class Right : public virtual A {
public:
    Right() : A(2) { std::cout << "cstor Righ" << std::endl; }
    virtual ~Right() { std::cout << "dstor Right" << std::endl; }
};

struct Hybrid : public Left, public Right {
    public:
        Hybrid()
            : A(4)
        { std::cout << "cstor Hybrid" << std::endl; }
        virtual ~Hybrid() { std::cout << "dstor Hybrid" << std::endl; }
};

int main() {
    Hybrid x;
    std::cout << x.m_data << std::endl;
    x.foo();
}
