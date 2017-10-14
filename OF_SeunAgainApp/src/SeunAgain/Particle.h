//
//  Particle.h
//  SeunAgain
//
//  Created by MOQN on 10/6/17.
//

#pragma once

#include "Prefix.h"


class Particle {
public:
  Particle();
  Particle& position( ofPoint p );
  Particle& velocity( ofPoint v );
  Particle& radius( float r );
  Particle& angle( float a );
  
  ofPoint pos, vel, acc;
  float mass, rad, radOriginal, theta;
  float scaleLife, scaleSine, scaleSineFreq;
  bool isLarge;
  ofColor color;
  float h, s, b, a;
  float lifeSpan, lifeReduction;
  bool isDone;
  
  void update();
  void display();
  void applyForce( ofPoint force );
  void updateLifespan();
  void checkLifespan();
  void checkCollision( Particle* other );
  void checkBoundaries( float width, float height );
};
