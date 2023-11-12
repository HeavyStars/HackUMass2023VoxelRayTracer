#pragma once
#ifndef Oct_tree_hpp
#define Oct_tree_hpp
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
#include "voxel.hpp"
#include "oct_tree_node.hpp"
#include "memory/memory_pixel.hpp"
#include "memory/shader_memory_buffer.hpp"

class OctTree {
public:
  OctTree(int memoryBufferId, int resolution);
  ~OctTree();

  void bind(sf::Shader & shader, std::string bufferName);

  void writeNewNode(OctTreeNode * node, OctTreeNode * item, int depth);
  void clear();

  void writeVoxel(Voxel voxel);
private:
  OctTreeNode * _root;

  sf::Uint8 * _writeBuffer;

  int _resolution;

  ShaderMemoryBuffer _memoryBuffer;
};

#endif