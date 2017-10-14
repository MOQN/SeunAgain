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
  ofPoint pos;
  ofColor color;
  ofImage img;
  
  float gravity;
  
  int numOfParticles;
  vector<Particle> particles;
  
  ParticleSystem();
  ParticleSystem& position( ofPoint p );
  //ParticleSystem& color( ofPoint c );
  
  void update();
  void display();
  
  int stage, count;
  void updateStage();
  void nextStage();
  
  void applyGravity();
  void explode();
  void slowDown( float amount );
  
};
