#include "shader_memory_buffer.hpp"

ShaderMemoryBuffer::ShaderMemoryBuffer(int itemsPerRow, int numRows, int itemSize, int id) {
    _itemSize = itemSize;
    _itemsPerRow = itemsPerRow;
    _memoryBufferResolutionX = itemsPerRow*itemSize;
    _memoryBufferResolutionY = numRows;

    _memoryBuffer.create(_memoryBufferResolutionX, _memoryBufferResolutionY);
    _memoryBuffer.setSmooth(false);

    for (int i = _memoryBufferResolutionX*_memoryBufferResolutionY-1; i>=0; i--) {
      _freeIndices.push_back(i);
    }
    _id = id;

    _writeArray = new sf::Uint8[_memoryBufferResolutionX*_memoryBufferResolutionY*4];
}

ShaderMemoryBuffer::~ShaderMemoryBuffer() {
  delete[] _writeArray;
}

Pixel ShaderMemoryBuffer::newItem() {
  if (_freeIndices.size() == 0) {
    throw std::overflow_error("Memory Buffer out of memory!");
  }
  int newIndex = _freeIndices.back();
  _freeIndices.pop_back();
  Pixel retPixel;
  retPixel.toPointer(newIndex, _id);
  return retPixel;
}

void ShaderMemoryBuffer::freeItem(int index) {
  if (std::find(_freeIndices.begin(), _freeIndices.end(), index) != _freeIndices.end()) {
    throw std::invalid_argument("The pointer " + std::to_string(index) + " was already free!");
    return;
  }
  
  _freeIndices.push_back(index);
}

void ShaderMemoryBuffer::writeItem(int index, sf::Uint8 * itemArray) {
  if (std::find(_freeIndices.begin(), _freeIndices.end(), index) != _freeIndices.end()) {
    throw std::invalid_argument("The pointer " + std::to_string(index) + " is free and you attempted to write to it!");
    return;
  }

  int memoryY = index/_itemsPerRow;
  int memoryX = (index-memoryY*_itemsPerRow)*_itemSize;

  _memoryBuffer.update(itemArray, _itemSize, 1, memoryX, memoryY);
}

void ShaderMemoryBuffer::bind(sf::Shader & shader, std::string bufferName) {
  shader.setUniform(bufferName, _memoryBuffer);
  shader.setUniform(bufferName+"BufferResolution", sf::Glsl::Vec2(_memoryBufferResolutionX, _memoryBufferResolutionY));
  shader.setUniform(bufferName+"ItemSize", _itemSize);
}

void ShaderMemoryBuffer::render(sf::RenderTexture & renderTarget) {
  sf::Sprite drawEnable;
  drawEnable.setTexture(_memoryBuffer);
  drawEnable.setTextureRect(sf::IntRect(0, 0, 300, 100));
  drawEnable.setPosition(sf::Vector2f(20, 20));
  sf::RectangleShape newRect(sf::Vector2f(300, 100));
  newRect.setPosition(sf::Vector2f(20, 20));
  newRect.setFillColor(sf::Color(255, 255, 255));
  renderTarget.draw(newRect);
  renderTarget.draw(drawEnable);
}
