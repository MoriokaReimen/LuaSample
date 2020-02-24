#pragma once
#include "IEntity.hpp"
#include "IEngine.hpp"
#include <eigen3/Eigen/Geometry>

namespace Logic
{

class Field : public IEngine
{
    Eigen::Vector2d size_;
public:
    Field(const Eigen::Vector2d& size);
    ~Field() override;
    void step();
};

};