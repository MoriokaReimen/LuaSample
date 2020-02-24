#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Logic.hpp"
#include "ArcShape.hpp"

class Graphic
{
    sf::RenderWindow window_;
    sf::Font font_;
    bool is_open_;
    void draw_debug(Logic::Field& field);
    void draw_scene(Logic::PENTITY& entity);
public:
    Graphic();
    void handleInput();
    void draw(Logic::Field& field);
    bool isOpen();
};
