#include "Field.hpp"

namespace Logic
{
Field::Field(const Eigen::Vector2d& size) : IEngine(), size_(size)
{

}

Field::~Field()
{

}

void Field::step()
{
    this->eachEntitiy([](auto entity){entity->step();});
}
};