#include <iostream>
#include <cstdlib>
#include "MyStruct.hpp"
#include <boost/python.hpp>
#include <Python.h>

#   define INIT_MODULE PyInit_MyModule
extern "C" PyObject* INIT_MODULE();

int main()
{
    MyStruct mystruct;
    PyImport_AppendInittab((char*)"MyModule", INIT_MODULE);
    Py_Initialize();
    boost::python::object main_module =boost::python::import("__main__");
    boost::python::object main_namespace = main_module.attr("__dict__");
    boost::python::object mymodule = boost::python::import("MyModule");
    main_namespace["hoge"] = MyStruct{100, 200, "hoge"};
    main_namespace["fuga"] = boost::python::object(boost::python::ptr(&mystruct));
    mystruct.i = 999;
    boost::python::exec("import MyModule\nprint('%d', hoge.i)\nfuga.i = 300", main_namespace);


    std::cout << "mysturct:" << mystruct.i << std::endl;


    return EXIT_SUCCESS;
}