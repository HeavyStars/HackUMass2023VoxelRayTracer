#pragma once
#ifndef Memory_Pixel
#define Memory_Pixel
#include <stdexcept>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include <string>

struct Pixel {
  sf::Uint8 r = 0;
  sf::Uint8 g = 0;
  sf::Uint8 b = 0;
  sf::Uint8 a = 0;

  void toInt(int value) {
    if (value > 8388607 || value < -8388608) {
      throw std::invalid_argument("Int value: Received value outside of range: " + std::to_string(value));
    }

    int setVal = value;
    if (setVal < 0) {
      setVal += 16777216;
    }

    r = setVal/(256*256);
    setVal -= r*256*256;

    g = setVal/256;
    setVal -= g*256;

    b = setVal;
  }


  void toNum(double value) {
    if (value > 32767.0 || value < -32768.0) {
      throw std::invalid_argument("Num value: Received value outside of range: " + std::to_string(value));
    }

    int setVal = value;
    int setMantissa = 65535*std::abs(value-setVal);

    //handle int
    if (setVal < 0) {
      setVal += 65536;
    }

    if (value < 0 && value > -1) {
      setVal = setMantissa;
      setMantissa = 65535;
    }

    r = setVal/256;
    setVal -= r*256;

    g = setVal;

    //handle mantissa
    b = setMantissa/256;
    setMantissa -= b*256;

    a = setMantissa;
  }

  void toHighFloat(double value) {
    if (value > 127 || value < -128) {
      throw std::invalid_argument("HighFloat value: Received value outside of range: " + std::to_string(value));
    }

    int setVal = value;
    int setMantissa = 16777215*std::abs(value-setVal);

    //handle int
    if (setVal < 0) {
      setVal += 256;
    }

    r = setVal;

    //handle mantissa

    g = setMantissa/(256*256);
    setMantissa -= g*256*256;

    b = setMantissa/256;
    setMantissa -= b*256;

    a = setMantissa;
  }

  void toDInt(int value1, int value2) {
    if (value1 > 32767.0 || value1 < -32768.0) {
      throw std::invalid_argument("DInt value 1: Received value outside of range: " + std::to_string(value1));
    }

    if (value2 > 32767.0 || value2 < -32768.0) {
      throw std::invalid_argument("DInt value 2: Received value outside of range: " + std::to_string(value2));
    }

    int setVal1 = value1;
    int setVal2 = value2;

    //handle int
    if (setVal1 < 0) {
      setVal1 += 65536;
    }

    r = setVal1/256;
    setVal1 -= r*256;

    g = setVal1;

    //handle int
    if (setVal2 < 0) {
      setVal2 += 65536;
    }

    b = setVal2/256;
    setVal2 -= b*256;

    a = setVal2;
  }

  void toIBool(bool truth, int value) {
    if (value > 8388607 || value < -8388608) {
      throw std::invalid_argument("IBool value: Received value outside of range: " + std::to_string(value));
    }

    int setVal = value;
    if (setVal < 0) {
      setVal += 16777216;
    }

    r = setVal/(256*256);
    setVal -= r*256*256;

    g = setVal/256;
    setVal -= g*256;

    b = setVal;

    a = (truth) ? 255 : 0;
  }

  void toBool(bool truth) {
    r = (truth) ? 255 : 0;
  }

  void toColor(sf::Glsl::Vec3 color) {
    r = color.x*255;
    g = color.y*255;
    b = color.z*255;
    a = 255;
  }

  void to4Color(sf::Glsl::Vec4 color) {
    r = color.x*255;
    g = color.y*255;
    b = color.z*255;
    a = color.w*255;
  }

  void toPointer(int pointerIndex, int type) {
    if (pointerIndex > 16777215) {
      throw std::invalid_argument("Error, attempted to write pointer " + std::to_string(pointerIndex) + ", which is out of range.");
    }
    if (type > 255) {
      throw std::invalid_argument("Error, pointer type " + std::to_string(type) + " too high!");
    }

    int setVal = pointerIndex;

    r = setVal/(256*256);
    setVal -= r*256*256;

    g = setVal/256;
    setVal -= g*256;

    b = setVal;

    a = type;
  }

  int pointerIndex() {
    return ((r << 16) + (g << 8) + b);
  }

  void writeToArray(int paramIndex, sf::Uint8 * updateArray, int itemSize) {

    if (paramIndex > itemSize) {
      throw std::invalid_argument("Error, attempted to write pixel to out of bounds area.");
    }

    int index = paramIndex*4;    

    updateArray[index] = r;
    updateArray[index+1] = g;
    updateArray[index+2] = b;
    updateArray[index+3] = a;
  }
};

#endif