#pragma once
#ifndef Quaternion_hpp
#define Quaternion_hpp

#include "vec3.hpp"
#include <math.h>

class Quaternion{
public:
  Quaternion(float x, float y, float z, float w);

  void setX(float x);
  void setY(float y);
  void setZ(float z);
  void setW(float w);

  float getX() const;
  float getY() const;
  float getZ() const;
  float getW() const;

  
  float dotProduct(const Quaternion& quat) const;
  float squareQuat() const;
  float getMagnitude(float square) const;
  void normalizeQuat();
  



private:
  float _x;
  float _y;
  float _z;
  float _w;


};


#endif