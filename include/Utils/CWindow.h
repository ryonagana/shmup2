#pragma once
#include <iostream>
#include <cstdlib>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imconfig-SFML.h>
#include <imgui-SFML.h>

class CWindow {

private:
    sf::RenderWindow renderWindow;
public:
    CWindow();
    CWindow(const sf::VideoMode mode, const std::string &window_caption);
    sf::RenderWindow* getWindow();
    sf::Vector2u getSize() const;
    ~CWindow();
};
