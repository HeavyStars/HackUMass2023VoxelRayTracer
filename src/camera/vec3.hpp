#pragma once
#ifndef Vec3_hpp
#define Vec3_hpp

#include <math.h>

class Vec3{
public:
  Vec3(float x, float y, float z);
  

  void setX(int x);
  void setY(int y);
  void setZ(int z);

  float getX() const;
  float getY() const;
  float getZ() const;
  
  Vec3 crossProduct(const Vec3& vector);
  float dotProduct(const Vec3& vector) const;
  float scalarMultiplication(float scalar);
  float squareVector() const;
  float getMagnitude(float squared) const;
  void normalizeVector();

  float operator*(const Vec3& vector) const;
  float operator*(float scalar);
  void operator-(const Vec3& vector);
  void operator+(const Vec3& vector);


private:
  float _x;
  float _y;
  float _z;


};

#endif