#pragma once
#ifndef Oct_tree_node_hpp
#define Oct_tree_node_hpp

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
#include <stdexcept>
#include "voxel.hpp"
#include "memory/memory_pixel.hpp"
#include "memory/shader_memory_buffer.hpp"

class OctTreeNode {
public:
  OctTreeNode(bool isLeaf, bool isRoot, Pixel address);
  
  Pixel getAddress();

  bool hasChild(size_t childIndex);
  OctTreeNode * getChild(size_t childIndex);

  void setChild(size_t childIndex, OctTreeNode * child);
  void setVoxel(Voxel voxel);

  Voxel getVoxel();


  bool isLeaf();
  bool isRoot();
  bool hasChildren();

  void writeNode(sf::Uint8 * writeBuffer);

  void destroyAllChildren();

private:
  OctTreeNode * _children[8] = {NULL};
  Voxel _voxData;
  bool _isLeaf;
  bool _isRoot;

  Pixel _address;
  std::vector<Pixel> _params;
};

#endif