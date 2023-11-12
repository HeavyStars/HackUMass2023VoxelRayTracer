//renderer.hpp
#pragma once
#ifndef Renderer_hpp
#define Renderer_hpp
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Renderer{
public:
    Renderer(int width, int height);
    ~Renderer();
    void update();

    const sf::Texture & render();
private:
    int _width;
    int _height;
    sf::Shader _marcher;
    sf::RenderTexture _context;
    sf::VertexArray _marchDrawable;
};

#endif