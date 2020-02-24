#pragma once
#include "IEngine.hpp"
#include <memory>
#include <eigen3/Eigen/Geometry>
namespace Logic
{
enum ENTITY_TYPE
{
    ROBOT
};

enum COLLISION
{
    NO_COLLIDE,
    WALL
};

struct Status
{
    Eigen::Vector2d position;
    double rotation;
    COLLISION collision;
    ENTITY_TYPE type;
};

class IEntity;
typedef std::shared_ptr<IEntity> PENTITY;
class IEngine;
class IEntity
{
protected:
    IEngine* engine_;
    Status status_;
public:
    IEntity() = delete;
    IEntity(IEngine* engine);
    virtual ~IEntity();
    Eigen::Vector2d getPosition() const;
    void setPosition(const Eigen::Vector2d& position);
    double getRotation() const;
    void setRotation(const double& rotation);
    ENTITY_TYPE getType() const;
    void setType(const ENTITY_TYPE& type);
    Status getStatus() const;
    void setStatus(const Status& status);
    virtual void step() = 0;
};
}
