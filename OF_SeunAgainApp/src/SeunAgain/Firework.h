//
//  Firework.hpp
//  SeunAgain
//
//  Created by MOQN on 10/7/17.
//

#pragma once

#include "Prefix.h"
#include "Particle.h"



class Firework {
public:
  ofPoint pos;
  ofColor color;
  
  float gravity;
  
  int numOfParticles;
  vector<Particle> particles;
  
  Firework();
  Firework& position( ofPoint p );
  //Firework& color( ofPoint c );
  
  void update();
  void display();
  
  int stage, count;
  void updateStage();
  void nextStage();
  
  void applyGravity();
  void explode();
  void slowDown( float amount );
  
};
