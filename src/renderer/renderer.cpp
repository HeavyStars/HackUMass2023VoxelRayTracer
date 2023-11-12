//renderer.cpp
#include "renderer.hpp"

Renderer::Renderer(int width, int height) : 
_marchDrawable(sf::Quads, 4),
_mainChunk(256),
_renderTree(1, 256) {

  if (!_marcher.loadFromFile("src/glsl/render_shader.frag", sf::Shader::Fragment)) {

  }
  sf::Vector2f uResolution(width, height);
  _context.create(width, height);
  _context.setSmooth(false);
  _width = width;
  _height = height;

  uTime = sf::seconds(0.f);

  _marcher.setUniform("u_resolution", uResolution);
  _marcher.setUniform("u_time", uTime.asSeconds());

  genChunkPerlin(_mainChunk);

  _renderTree.bind(_marcher, "OctTree");
  _mainChunk.writeToTree(_renderTree);

  _marchDrawable[0].position = sf::Vector2f(0, 0);
  _marchDrawable[1].position = sf::Vector2f(uResolution.x, 0);
  _marchDrawable[2].position = sf::Vector2f(uResolution.x, uResolution.y);
  _marchDrawable[3].position = sf::Vector2f(0, uResolution.y);
  _marchDrawable[0].color = sf::Color(0, 0, 250, 0);
  _marchDrawable[1].color = sf::Color(80, 24, 100, 0);
  _marchDrawable[2].color = sf::Color(0, 80, 80, 0);
  _marchDrawable[3].color = sf::Color(180, 0, 75, 0);
}

Renderer::~Renderer(){

}

void Renderer::update(sf::Time deltaTime){
  uTime += deltaTime;
  _marcher.setUniform("u_time", uTime.asSeconds());
}

const sf::Texture & Renderer::render(){
  _context.clear();
  _context.draw(_marchDrawable, &_marcher);
  _context.display();
  return _context.getTexture();
}