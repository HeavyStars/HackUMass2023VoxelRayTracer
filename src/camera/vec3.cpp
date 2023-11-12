#include "vec3.hpp"

Vec3::Vec3(float x, float y, float z) {
  _x = x;
  _y = y;
  _z = z;
}

void Vec3::setX(int x){
  _x = x;
}

void Vec3::setY(int y){
  _y = y;
}

void Vec3::setZ(int z){
  _z = z;
}

float Vec3::getX() const {
  return _x;
}

float Vec3::getY() const {
  return _y;
}

float Vec3::getZ() const {
  return _z;
}

Vec3 Vec3::crossProduct(const Vec3& vector){
  float newX = _y * vector.getZ() - _z * vector.getY();
  float newY = _z * vector.getX() - _x * vector.getZ();
  float newZ = _x * vector.getY() - _y * vector.getX();
  return Vec3(newX, newY, newZ);
}

float Vec3::dotProduct(const Vec3& vector) const {
  return _x * vector.getX() + _y * vector.getY() + _z * vector.getZ();
}

void Vec3::scalarMultiplication(float scalar){
  _x = _x * scalar;
  _y = _y * scalar;
  _z = _z * scalar;
}

float Vec3::squareVector() const{
  float squaredLength = (_x * _x) + (_y * _y) + (_z * _z);
  return squaredLength;
}

float Vec3::getMagnitude(float squared) const{
  float magnitude = std::sqrt(squared);
  return magnitude;
}

void Vec3::normalizeVector(){
  float squared = squareVector();
  float magnitude = getMagnitude(squared);
  if (magnitude != 0){
    _x = _x / magnitude;
    _y = _y / magnitude;
    _z = _z / magnitude;
  }
}

float Vec3::operator*(const Vec3& vector) const {
  return 0;
}

void Vec3::operator*(float scalar){
  scalarMultiplication(scalar);
}

void Vec3::operator-(const Vec3& vector){
  _x -= vector.getX();
  _y -= vector.getY();
  _z -= vector.getZ();
}

void Vec3::operator+(const Vec3& vector){
  _x += vector.getX();
  _y += vector.getY();
  _z += vector.getZ();
}


