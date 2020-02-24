#pragma once
#include "IEntity.hpp"

namespace Logic
{

struct Command
{
    double turn;
    double throttle;
};

class Robot : public IEntity
{
public:
    Robot() = delete;
    Robot(IEngine* engine);
    virtual void step() override;
};

};