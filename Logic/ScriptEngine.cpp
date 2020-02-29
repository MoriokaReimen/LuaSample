#include "ScriptEngine.hpp"

#include <iostream>
#include <cstdlib>
#include "Robot.hpp"
#include "IEntity.hpp"
#include <eigen3/Eigen/Geometry>
#include <sol/sol.hpp>

namespace Logic
{

ScriptEngine* ScriptEngine::instance_ = 0;
sol::state ScriptEngine::sol_state_;

ScriptEngine* ScriptEngine::getInstance()
{
    if(instance_ == 0)
    {
        instance_ = new ScriptEngine();
    }

    return instance_;
}

ScriptEngine::ScriptEngine()
{
}

Command ScriptEngine::exec(const std::string& fpath, const Status& status)
{
    Command command;
    sol_state_["X"] = status.position.x();
    sol_state_["Y"] = status.position.y();
    sol_state_["turn"] = 0.0;
    sol_state_["throttle"] = 0.0;
    sol_state_.script_file("script/brain.lua");
    command.throttle = sol_state_["throttle"];
    command.turn = sol_state_["turn"];

    return command;
}
};
