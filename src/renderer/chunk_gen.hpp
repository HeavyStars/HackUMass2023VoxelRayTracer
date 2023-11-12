#pragma once
#ifndef Chunk_gen_hpp
#define Chunk_gen_hpp
#include "voxel.hpp"
#include "chunk.hpp"
#include "perlin.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>

inline void genChunkPerlin(Chunk & chunk) {
  const siv::PerlinNoise::seed_type seed = 123456u;

	const siv::PerlinNoise perlin{ seed };
	
  for (int z = 0; z < chunk.getSize(); z++) {
    for (int x = 0; x < chunk.getSize(); x++) {
      const double noise = perlin.octave2D_01((x), (z), 4);
      for (int y=0; y < chunk.getSize()*noise; y++) {
        Voxel newVox;
        newVox.setCol(sf::Glsl::Vec4(noise, 1.0-noise, 0.0, 1.0));
        newVox.setPos(sf::Glsl::Vec3(x, y, z));
        chunk.setVoxel(newVox);
      }
    }
  }
}

#endif
