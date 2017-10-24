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
  Particle& setMass( float m );
  Particle& setAngle( float a );
  Particle& setColor( ofColor c );
  Particle& setSection( int s );
  Particle& setLifeReduction( float l );
  Particle& setScaleLifeTarget( float start, float end );
  Particle& setScaleSine( float freq, float amp );
  Particle& setScaleSineAmp( float amp );
  
  int section;
  ofPoint pos, vel, acc;
  float mass, rad, radOriginal, angle;
  float scaleLife, scaleLifeStart, scaleLifeTarget;
  float scaleSine, scaleSineFreq, scaleSineAmp;
  ofColor color;
  float h, s, b, a;
  float lifeSpan, lifeReduction;
  bool isDone;
  
  void update();
  void display();
  void applyForce( ofPoint force );
  void applyRestitution( float amount );
  void applyAttraction( ofPoint target, float amount );
  void applyGravitation( Particle &other, float G );
  void checkCollision( Particle &other, float restitution );
  void checkBoundaries( float width, float height );
  void updateLifespan();
  void reduceLifespan();
  
};
