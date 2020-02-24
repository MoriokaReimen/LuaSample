#pragma once
#include "Robot.hpp"
#include "IEntity.hpp"

namespace Logic
{
class ScriptEngine
{
public:
    ScriptEngine();
    Command exec(const std::string& fpath, const Status& status);
};
};