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
    sol_state_.open_libraries(sol::lib::base);
    sol_state_.new_usertype<Command>("Command",
        "turn", &Command::turn,
        "throttle", &Command::throttle);

    sol_state_.new_enum("COLLISION",
        "NO_COLLIDE", COLLISION::NO_COLLIDE,
        "WALL", COLLISION::WALL);
    sol_state_.new_enum("ENTITY_TYPE",
        "ROBOT", ENTITY_TYPE::ROBOT);

    sol_state_.new_usertype<Status>("Status",
        "rotation", &Status::rotation,
        "collision", &Status::collision,
        "type",      &Status::type);
    sol_state_["Status"]["x"] = 0.0;
    sol_state_["Status"]["y"] = 0.0;
}

Command ScriptEngine::exec(const std::string& fpath, const Status& status)
{
    Command command;
    sol_state_["status"] = &status;
    sol_state_["status"]["x"] =status.position.x();
    sol_state_["status"]["y"] =status.position.y();
    sol_state_["command"] = &command;
    sol_state_.script_file("script/brain.lua");

    return command;
}
};
