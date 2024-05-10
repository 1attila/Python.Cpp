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

std::string new_assertion_fn(std::string msg)
{
    return std::string("There's a error: ") + msg;
}


int main()
{
    std::string string = "String text";
    py::print(py::length(string));
    
    Test test;
    py::print(test);
    py::print(py::len(test) + 1);
    
    py::DefaultAssertionFunctionPtr = new_assertion_fn;
    try
    {
        py::assert(2 + 2 == 5, "2+2 != 5 :(");
    }
    catch(const py::AssertionError& e)
    {
        py::print(e);
    }
    
    return 0;
}
