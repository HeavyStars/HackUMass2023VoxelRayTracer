#pragma once
#ifndef Window_hpp
#define Window_hpp
#include <string>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui-SFML.h"

class Window {
public:
    Window(int, int h, std::string title);
    ~Window();
    void run();

private:
    sf::RenderWindow *_window;
    bool _running;
    sf::Time deltaTime;
    sf::Time frameTime;
    sf::Time updateTime;
    sf::Time renderTime;
    sf::Clock deltaClock;
    int windowWidth;
    int windowHeight;

};
#endif