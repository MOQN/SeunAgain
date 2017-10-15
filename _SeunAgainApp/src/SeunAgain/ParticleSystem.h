//
//  ParticleSystem.hpp
//  SeunAgain
//
//  Created by MOQN on 10/7/17.
//

#pragma once

#include "Prefix.h"
#include "Particle.h"



class ParticleSystem {
public:
  PSystemMode mode;
  ofPoint boundary;
  
  ofPoint pos;
  ofColor color;
  ofImage img;
  
  float gravity;
  
  int numOfParticles;
  vector<Particle> particles;
  
  ParticleSystem( PSystemMode mode );
  ParticleSystem& position( ofPoint p );
  ParticleSystem& setBoundary( ofPoint b );
  ParticleSystem& applyImage( ofImage i );
  ParticleSystem& init();
  
  void update();
  void display();
  
  void normal_init();
  void normal_update();
  void normal_display();
  
  void cell_init();
  void cell_update();
  void cell_display();
  
  void firework_init();
  void firework_update();
  void firework_display();
  
  int stage, count;
  void updateStage();
  void nextStage();
  
  void applyGravity();
  void explode();
  void slowDown( float amount );
  
};
