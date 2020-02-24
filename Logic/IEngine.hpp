#pragma once
#include "IEntity.hpp"
#include <memory>
#include <eigen3/Eigen/Geometry>
#include <functional>
#include <vector>

namespace Logic
{
class IEntity;
typedef std::shared_ptr<IEntity> PENTITY;
typedef std::function<void (PENTITY&)> EACH_ENTITY_FUNC;

class IEngine
{
protected:
    std::vector<PENTITY> entities_;

public:
    virtual ~IEngine();
    void registerEntity(PENTITY& entity);
    bool updatePosition(IEntity& self, const Eigen::Vector2d& position);
    bool updateRotation(IEntity& self, const double& rotation);
    void eachEntitiy(EACH_ENTITY_FUNC func);
};
}