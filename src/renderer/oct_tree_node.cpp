#include "oct_tree_node.hpp"

OctTreeNode::OctTreeNode(bool isLeaf, bool isRoot, Pixel address) {
  _isLeaf = isLeaf;
  _isRoot = isRoot;

  _address = address;

  for (int i = 0; i < 9; i++) {
    Pixel defaultParam;
    _params.push_back(defaultParam);
  }
}

Pixel OctTreeNode::getAddress() {
  return _address;
}

bool OctTreeNode::hasChild(size_t childIndex) {
  if (childIndex > 7) {
    throw std::invalid_argument("Error, checking a child which is too high");
  }

  return _children[childIndex] == NULL ? false : true;
}

OctTreeNode * OctTreeNode::getChild(size_t childIndex) {
  if (!hasChild(childIndex)) {
    throw std::invalid_argument("Error! Attempted to get a child that is NULL");
  }

  return _children[childIndex];
}

void OctTreeNode::setChild(size_t childIndex, OctTreeNode * child) {
  if (childIndex > 7) {
    throw std::invalid_argument("Error, writing a child which is too high");
  }

  if (isLeaf()) {
    throw std::invalid_argument("Error, cannot add a child to a leaf node!");
  }

  _children[childIndex] = child;
}

void OctTreeNode::setVoxel(Voxel voxel) {
  if (!isLeaf()) {
    throw std::invalid_argument("Error, cannot set a voxel for a node!");
  }

  _voxData = voxel;
}

Voxel OctTreeNode::getVoxel() {
  if (!isLeaf()) {
    throw std::invalid_argument("Error, cannot get a voxel for a node!");
  }

  return _voxData;
}

bool OctTreeNode::isLeaf() {
  return _isLeaf;
}

bool OctTreeNode::isRoot() {
  return _isRoot;
}

bool OctTreeNode::hasChildren() {
  for (int i = 0; i < 8; i++) {
    if (hasChild(i)) {
      return true;
    }
  }
  return false;
}

void OctTreeNode::writeNode(sf::Uint8 * writeBuffer) {
  if (!_isLeaf) {
    _params[0].toBool(false);
    for (int i = 0; i < 8; i++) {
      if (hasChild(i)) {
        _params[i+1].toPointer(_children[i]->getAddress().pointerIndex(), 1);
      } else {
        Pixel defaultParam;
        _params[i+1] = defaultParam;
      }
    }
  } else {
    _params[0].toBool(true);
    _params[1].to4Color(_voxData.getCol());
    sf::Glsl::Vec3 voxPos = _voxData.getPos();
    _params[6].toInt(voxPos.x);
    _params[7].toInt(voxPos.y);
    _params[8].toInt(voxPos.z);
  }

  for (int i = 0; i < _params.size(); i++) {
    _params[i].writeToArray(i, writeBuffer, 9);
  }
}

void OctTreeNode::destroyAllChildren() {
  for (size_t i = 0; i < 8; i++) {
    if (hasChild(i)) {
      if (_children[i]->hasChildren()) {
        _children[i]->destroyAllChildren();
      }

      delete _children[i];
      _children[i] = NULL;
    }
  }
}