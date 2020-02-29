#pragma once
#include "Robot.hpp"
#include "IEntity.hpp"
#include <sol/sol.hpp>

namespace Logic
{
class ScriptEngine
{
private:
    static ScriptEngine* instance_;
    static sol::state sol_state_;
    ScriptEngine();
public:
    static ScriptEngine* getInstance();
    Command exec(const std::string& fpath, const Status& status);
};
};