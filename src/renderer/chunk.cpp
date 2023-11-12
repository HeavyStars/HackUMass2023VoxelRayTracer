#include "chunk.hpp"
Chunk::Chunk(int size) {
  _maxSize = size;
}

Chunk::~Chunk() {

}

void Chunk::setVoxel(Voxel voxel) {
  if (voxel.getPos().x > _maxSize-1 || voxel.getPos().y > _maxSize-1 || voxel.getPos().z > _maxSize-1) {
    std::cout << "Logic error in Chunk::setVoxel" << std::endl;
    return;
  }

  voxels[voxel.getPos().z*_maxSize*_maxSize+voxel.getPos().y*_maxSize+voxel.getPos().x] = voxel;
}

bool Chunk::hasVoxel(sf::Glsl::Vec3 pos) {
  if (pos.x > _maxSize-1 || pos.y > _maxSize-1 || pos.z > _maxSize-1) {
    return false;
  }

  int findPos = pos.z*_maxSize*_maxSize+pos.y*_maxSize+pos.x;
  if (voxels.find(findPos) == voxels.end()) {
    return false;
  }
  return true;
}

void Chunk::clearVoxel(sf::Glsl::Vec3 pos) {
  if (!hasVoxel(pos)) {
    throw std::invalid_argument("Cannot clear voxel that does not exist!");
  }

  voxels.erase(pos.z*_maxSize*_maxSize+pos.y*_maxSize+pos.x);
}

Voxel Chunk::getVoxel(sf::Glsl::Vec3 pos) {
  if (!hasVoxel(pos)) {
    throw std::invalid_argument("logic error in getVoxel, pos did not exist!");
  }

  return voxels[pos.z*_maxSize*_maxSize+pos.y*_maxSize+pos.x];
}

void Chunk::writeToTree(OctTree & writeTree) {
  writeTree.clear();
  for (const auto &element : voxels) {
    Voxel myElement = element.second;
    sf::Glsl::Vec3 voxPos = myElement.getPos();
    sf::Glsl::Vec3 voxUp = sf::Glsl::Vec3(voxPos.x, voxPos.y+1, voxPos.z);
    sf::Glsl::Vec3 voxDown = sf::Glsl::Vec3(voxPos.x, voxPos.y-1, voxPos.z);
    sf::Glsl::Vec3 voxLeft = sf::Glsl::Vec3(voxPos.x+1, voxPos.y, voxPos.z);
    sf::Glsl::Vec3 voxRight = sf::Glsl::Vec3(voxPos.x-1, voxPos.y, voxPos.z);
    sf::Glsl::Vec3 voxFront = sf::Glsl::Vec3(voxPos.x, voxPos.y, voxPos.z+1);
    sf::Glsl::Vec3 voxBack = sf::Glsl::Vec3(voxPos.x, voxPos.y, voxPos.z-1);
    if (!hasVoxel(voxUp) && !hasVoxel(voxDown) &&
    !hasVoxel(voxLeft) && !hasVoxel(voxRight) && 
    !hasVoxel(voxFront) && !hasVoxel(voxBack)) {
      writeTree.writeVoxel(element.second);
    }
  }
}
