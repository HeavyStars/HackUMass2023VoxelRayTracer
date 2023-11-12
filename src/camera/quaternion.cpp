#include "quaternion.hpp"

Quaternion::Quaternion(float x, float y, float z, float w) :
_x = x, _y = y, _z = z, _w = w {
}

void Quaternion::setX(float x){
  _x = x;
}

void Quaternion::setY(float y){
  _y = y;
}

void Quaternion::setZ(float z){
  _z = z;
}

void Quaternion::setW(float w){
  _w = w;
}

float Quaternion::getX(){
  return _x;
}

float Quaternion::getY(){
  return _y;
}

float Quaternion::getZ(){
  return _z;
}

float Quaternion::getW(){
  return _w;
}

float Quaternion::squareQuat() const{
  float squared = (_w * _w) + (_x * _x) + (_y * _y) + (_z * _z);
  return squared;
}

float Quaternion::getMagnitude (float square) const{
  float magnitude = std::sqrt(square);
  return magnitude;
}

void Quaternion::normalizeQuat(){
  float square = squareQuat();
  float magnitude = getMagnitude(square);
  if (magnitude != 0){
    _w = _w / magnitude;
    _x = _x / magnitude;
    _y = _y / magnitude;
    _z = _z / magnitude;
  }
}

float Quaternion::dotProduct(const Quaternion& quat){
  return _w * quat.getW() + _x * quat.getX() + _y * quat.getY() + _z * quat.getZ();
}

