#include "Robot.hpp"
#include <cmath>
#include <eigen3/Eigen/Geometry>

namespace Logic
{
Robot::Robot(IEngine* engine) : IEntity(engine)
{

}

Robot::~Robot()
{

}

void Robot::step()
{
    Command command;
    Status status = getStatus();

    /* set rotation */
    auto turn = std::clamp(command.turn, -1.0, 1.0);
    auto rotation = status.rotation + turn;

    /* set Position */
    auto position = status.position;
    command.throttle = std::clamp(command.throttle, -1.0, 1.0);
    position += Eigen::Rotation2D(rotation) * ( command.throttle * Eigen::Vector2d::UnitY());
    engine_->updatePosition(*this, position);
    engine_->updateRotation(*this, rotation);
}
};