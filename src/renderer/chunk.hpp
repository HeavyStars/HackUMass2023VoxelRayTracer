#pragma once
#ifndef Chunk_hpp
#define Chunk_hpp
#include <unordered_map>
#include <iostream>
#include "voxel.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <stdexcept>
#include "oct_tree.hpp"

class Chunk {
public:
  Chunk(int size);
  ~Chunk();

  void setVoxel(Voxel voxel);
  bool hasVoxel(sf::Glsl::Vec3 pos);
  void clearVoxel(sf::Glsl::Vec3 pos);
  Voxel getVoxel(sf::Glsl::Vec3 pos);

  void writeToTree(OctTree & writeTree);

private:
  int _maxSize;
  std::unordered_map<int, Voxel> voxels;
};
#endif
