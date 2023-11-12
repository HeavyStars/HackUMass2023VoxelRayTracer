#include "oct_tree.hpp"

OctTree::OctTree(int memoryBufferId, int resolution) : 
_memoryBuffer(250, 3500, 9, memoryBufferId) {
  _resolution = resolution;
  _writeBuffer = new sf::Uint8[9*4];
  Pixel _rootAddress = _memoryBuffer.newItem();
  _root = new OctTreeNode(false, true, _rootAddress);
  _root->writeNode(_writeBuffer);
  _memoryBuffer.writeItem(_root->getAddress().pointerIndex(), _writeBuffer);
}

OctTree::~OctTree() {
  delete[] _writeBuffer;
  _root->destroyAllChildren();
  delete _root;
  _root = NULL;
}

void OctTree::bind(sf::Shader & shader, std::string bufferName) {
  _memoryBuffer.bind(shader, bufferName);
}

void OctTree::writeNewNode(OctTreeNode * node, OctTreeNode * item, int depth) {
  int currentBoxSize = _resolution/(2*(depth+1));
  sf::Glsl::Vec3 voxData = item->getVoxel().getPos();

  int octant = 0;
  if (voxData.x >= currentBoxSize) {
    octant = 1;
  }

  if (voxData.y >= currentBoxSize) {
    octant += 2;
  }

  if (voxData.z >= currentBoxSize) {
    octant += 4;
  }


  if (!node->hasChild(octant)) {
    node->setChild(octant, item);
    node->writeNode(_writeBuffer);
    _memoryBuffer.writeItem(_root->getAddress().pointerIndex(), _writeBuffer);
    return;
  }

  OctTreeNode * child = node->getChild(octant);

  if (child->isLeaf()) {
    sf::Glsl::Vec3 childPosData = item->getVoxel().getPos();
    if (childPosData == voxData) {
      child->setVoxel(item->getVoxel());
      child->writeNode(_writeBuffer);
      _memoryBuffer.writeItem(child->getAddress().pointerIndex(), _writeBuffer);
      return;
    }

    Pixel newAddress = _memoryBuffer.newItem();
    OctTreeNode * newContainer = new OctTreeNode(false, false, newAddress);
    newContainer->writeNode(_writeBuffer);
    _memoryBuffer.writeItem(newAddress.pointerIndex(), _writeBuffer);

    node->setChild(octant, newContainer);
    node->writeNode(_writeBuffer);
    _memoryBuffer.writeItem(node->getAddress().pointerIndex(), _writeBuffer);

    writeNewNode(newContainer, child, depth+1);
    writeNewNode(newContainer, item, depth+1);
    return;
  }

  writeNewNode(child, item, depth+1);
}

void OctTree::clear() {
  _root->destroyAllChildren();
  _root->writeNode(_writeBuffer);
  _memoryBuffer.writeItem(_root->getAddress().pointerIndex(), _writeBuffer);
}

void OctTree::writeVoxel(Voxel voxel) {
  Pixel newAddress = _memoryBuffer.newItem();
  OctTreeNode * newNode = new OctTreeNode(true, false, newAddress);
  newNode->setVoxel(voxel);
  newNode->writeNode(_writeBuffer);
  _memoryBuffer.writeItem(newAddress.pointerIndex(), _writeBuffer);
  writeNewNode(_root, newNode, 0);
}
