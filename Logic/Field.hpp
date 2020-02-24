#pragma once
#include "IEntity.hpp"
#include <eigen3/Eigen/Geometry>

namespace Logic
{

class Field : public IEngine
{
    Eigen::Vector2d size_;
public:
    Field(const Eigen::Vector2d& size);
    void step();
};

};