#include <iostream>
#include <memory>
#include <string>


/*
 * Brief: demonstrate how to convert shared point of classes between parent and child
 * Author: Lei-Albert, Wang
 * EMail: wangleicnbj@gmail.com
 * 
 */

// the base class, whose name could be changed in runtime, default is "B",
// its member function func will tell something when being called
class B
{
    public:
        B():val("B")
        {
            std::cout << "class B" << std::endl;
        }
        ~B(){}
        void ChangeName(const std::string& n){val = n;}
        virtual void func(){ std::cout << "function called within B: " << val << std::endl; }
    protected:
        std::string val;
};

// the deriving class, a subclass of B its default name is "D",
// it overrides function func will tell its calling point when being called
class D : public B
{
    public:
        D(){std::cout << "class D" << std::endl;}
        ~D(){}

        void func() override {std::cout << "function called with D: " << val << std::endl;}
};



int main(int argc, char** argv)
{
    std::cout << "argc: " << argc << std::endl;
    // print out all arguments passed to this process
    for(auto i = 0; i < argc; ++i)
        std::cout << "argv" << i << ": " << argv[i] << std::endl;


    // show how to convert a shared point of deriving class to that of the base class 
    std::cout << "dynamic_point_cast: " << std::endl;
    
    std::shared_ptr<B> p_b = std::make_shared<D>();
    std::cout << "ouput of default func call: " << std::endl;
    p_b->func();

    // convert the shared point to its origional type and call its member function
    std::cout << "output of actural func call: "  << std::endl;
    std::dynamic_pointer_cast<D>(p_b)->func();

    std::shared_ptr<const B> pc_b = p_b;
    
    // call it write function and then check what will happed
    std::cout << "const_point_cast: " << std::endl;
    std::cout << "ouput of default none const func call: " << std::endl;
    std::const_pointer_cast<B>(pc_b)->ChangeName(std::string("changed"));
    std::const_pointer_cast<B>(pc_b)->func();
    
    return 0;   
}
