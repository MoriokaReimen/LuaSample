#include <iostream>
#include <cstdlib>
#include "MyStruct.hpp"

int main()
{
    MyStruct mystruct;
    mystruct.i = 12;
    mystruct.f = 3.14;
    mystruct.str = "hello";

    std::cout << "i" << mystruct.i << std::endl;


    return EXIT_SUCCESS;
}