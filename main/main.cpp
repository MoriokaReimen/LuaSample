#include "Logic.hpp"
#include <cstdlib>
#include <memory>
#include "Graphic.hpp"
#include <functional>

#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>
#include "Graphic.hpp"

int main()
{
    boost::mt19937 gen;
    boost::random::uniform_int_distribution<> dist_x(0, 2000);
    boost::random::uniform_int_distribution<> dist_y(0, 1000);
    boost::random::uniform_int_distribution<> dist_angle(-180, 180);
    Graphic graphic;
    Logic::Field field(Eigen::Vector2d(1000, 2000));
    Logic::PENTITY robot = std::make_shared<Logic::Robot>(&field);
    robot->setPosition(Eigen::Vector2d(500, 500));
    robot->setRotation(45);
    field.registerEntity(robot);

    // run the program as long as the window is open
    while (graphic.isOpen())
    {
        graphic.handleInput();
        graphic.draw(field);
        field.step();
        sf::sleep(sf::milliseconds(1));
    }

    return EXIT_SUCCESS;
}
