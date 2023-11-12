#pragma once
#ifndef Voxel_hpp
#define Voxel_hpp
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Voxel {
public:
  void setPos(sf::Glsl::Vec3 pos) {
    _pos = pos;
  }
  void setCol(sf::Glsl::Vec4 col) {
    _col = col;
  }

  sf::Glsl::Vec3 getPos() {
    return _pos;
  }
  sf::Glsl::Vec4 getCol() {
    return _col;
  }
private:
  sf::Glsl::Vec3 _pos;
  sf::Glsl::Vec4 _col;
};
#endif