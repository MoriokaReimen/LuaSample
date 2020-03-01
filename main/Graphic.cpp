#include "Graphic.hpp"
#include <exception>
#include <boost/format.hpp>

Graphic::Graphic() :
    window_(sf::VideoMode(sf::VideoMode(2000, 1000)), "Life"),
    is_open_(true)
{
    if(!font_.loadFromFile("resource/Sarai.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }
}

void Graphic::handleInput()
{
    sf::Event event;
    while (window_.pollEvent(event))
    {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
        {
            is_open_ = false;
            window_.close();
        }
    }
}

void Graphic::draw(Logic::Field& field)
{
    window_.clear();
    std::function<void (Logic::PENTITY& )> func =
            std::bind(&Graphic::draw_scene, this,  std::placeholders::_1);
    field.eachEntitiy(func);
    draw_debug(field);
    window_.display();

}

void Graphic::draw_scene(Logic::PENTITY& entity)
{

    switch(entity->getType())
    {
        case Logic::ROBOT : {
            auto robot_pos = entity->getPosition();
            auto status = entity->getStatus();
            ArcShape sight(60, 100);
            sf::CircleShape prey_body(10);
            double rotation = entity->getRotation();

            sight.setPosition(robot_pos.x(), robot_pos.y());
            sight.setRotation(rotation + 60.0);
            sight.setFillColor(sf::Color(255, 255, 0, 100));

            prey_body.setPosition(robot_pos.x() - 10.0, robot_pos.y() - 10.0);

            window_.draw(sight);
            window_.draw(prey_body);
            break;
        }
    }
}

void Graphic::draw_debug(Logic::Field& field)
{
}

bool Graphic::isOpen()
{
    return is_open_;
}