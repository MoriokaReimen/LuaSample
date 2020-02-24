#include "IEntity.hpp"

namespace Logic
{

IEntity::IEntity(IEngine *engine)
{
    engine_ = engine;
}

Eigen::Vector2d IEntity::getPosition() const
{
    return this->status_.position;
}

void IEntity::setPosition(const Eigen::Vector2d &position)
{
    this->status_.position = position;
}

double IEntity::getRotation() const
{
    return this->status_.rotation;
}

void IEntity::setRotation(const double &rotation)
{
    this->status_.rotation = rotation;
}

ENTITY_TYPE IEntity::getType() const
{
    return this->status_.type;

}

void IEntity::setType(const ENTITY_TYPE &type)
{
    this->status_.type = type;
}

Status IEntity::getStatus() const
{
    return this->status_;
}

void IEntity::setStatus(const Status &status)
{
    this->status_ = status;
}

}; // namespace Logic