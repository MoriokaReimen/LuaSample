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
    Robot(IEngine* engine);
    ~Robot() override;
    Robot() = delete;
    virtual void step() override;
};

};