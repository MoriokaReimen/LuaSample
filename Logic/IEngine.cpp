#include "IEngine.hpp"
namespace Logic
{

IEngine::~IEngine()
{

}

void IEngine::registerEntity(PENTITY &entity)
{
    this->entities_.push_back(entity);
}

bool IEngine::updatePosition(IEntity& self, const Eigen::Vector2d &position)
{
    COLLISION collision = NO_COLLIDE;

    if(position.x() < 0.0 || position.x() > 2000.0)
    {
        collision = WALL;
    }

    if(position.y() < 0.0 || position.y() > 1000.0)
    {
        collision = WALL;
    }

    if(collision == NO_COLLIDE)
    {
        self.setPosition(position);
    }

    self.setCollision(collision);
    return collision == NO_COLLIDE;
}

bool IEngine::updateRotation(IEntity& self, const double &rotation)
{
    double wrapped = std::fmod(rotation, 360.0);
    if(wrapped < 0)
        wrapped += 360;

    self.setRotation(wrapped);
    return true;
}

void IEngine::eachEntitiy(EACH_ENTITY_FUNC func)
{
    std::for_each(entities_.begin(), entities_.end(), func);
}
};