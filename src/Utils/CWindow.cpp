#include "include/Utils/CWindow.h"


CWindow::CWindow(const sf::VideoMode mode, const std::string &window_caption)
{
    sf::String name = window_caption;
    renderWindow.create(mode, name);
}

CWindow::CWindow() : CWindow::CWindow(sf::VideoMode(800,600), "Teste")
{

}
CWindow::~CWindow(){

}

sf::RenderWindow* CWindow::getWindow()
{
    return &renderWindow;
}

sf::Vector2u CWindow::getSize() const
{
    return renderWindow.getSize();
}
