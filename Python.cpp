#include <iostream>
#include <string>

#include "Python.h"


class Test
{
// IMPORTANT:
// Remember to make these functions public
// otherwise they will not be handled by the library!
public:
    int __len__()
    {
        return 5;
    }
    
    size_t length()
    {
        return (size_t)(5);
    }

    std::string __repr__()
    {
        return "I like using python!";
    }
};

void new_assertion_fn(std::string msg)
{
    std::cout << "There's a error: " << msg << std::endl;
}


int main()
{
    std::string string "String text";
    py::print(py::len(string));

    Test test;
    py::print(test);
    py::print(py::len(test) + 1);
    
    py::DefaultAssertionFunctionPtr = new_assertion_fn;
    py::assert(2 + 2 == 5, "2+2 != 5 :(");

    return 0;
}