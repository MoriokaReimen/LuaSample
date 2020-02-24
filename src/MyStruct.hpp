#pragma once
#include <boost/python.hpp>
#include <string>

using namespace boost::python;

struct MyStruct
{
    int i;
    double f;
    std::string str;
};

BOOST_PYTHON_MODULE(MyModule)
{
    class_<MyStruct>("MyStruct")
    .def_readwrite("i", &MyStruct::i)
    .def_readwrite("f", &MyStruct::f)
    .def_readwrite("str", &MyStruct::str);
}