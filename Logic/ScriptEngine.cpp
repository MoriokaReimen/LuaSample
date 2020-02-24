#include "ScriptEngine.hpp"

#include <iostream>
#include <cstdlib>
#include <boost/python.hpp>
#include <Python.h>
#include "Robot.hpp"
#include "IEntity.hpp"

namespace Logic
{
#   define INIT_MODULE PyInit_MyModule
extern "C" PyObject* INIT_MODULE();

ScriptEngine::ScriptEngine()
{
    PyImport_AppendInittab((char*)"MyModule", INIT_MODULE);
    Py_Initialize();
}

Command ScriptEngine::exec(const std::string& fpath, const Status& status)
{
    Command command;

    boost::python::object main_module =boost::python::import("__main__");
    boost::python::object main_namespace = main_module.attr("__dict__");
    main_namespace["status"] = Status(status);
    main_namespace["command"] = boost::python::object(boost::python::ptr(&command));
    boost::python::exec_file("script/brain.py", main_namespace);

    return command;
}
};
