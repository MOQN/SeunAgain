//
//  Particle.cpp
//  SeunAgain
//
//  Created by MOQN on 10/6/17.
//

#include "Particle.h"


Particle::Particle() {
  // shape
  mass = ofRandom(1, 5);
  rad = mass * 2;
  // color
  h = ofRandom(255);
  s = ofRandom(255);
  b = ofRandom(255);
  a = 255;
  color.setHsb(h, s, b, a);
  // life
  lifeSpan = 1.0;
  lifeReduction = 0.001;
}
Particle& Particle::position( ofPoint p ) {
  pos = p;
  return *this;
}
Particle& Particle::velocity( ofPoint v ) {
  vel = v;
  return *this;
}
Particle& Particle::radius( float r ) {
  rad = r;
  return *this;
}
Particle& Particle::angle( float a ) {
  theta = a;
  return *this;
}

void Particle::update() {
  // physics
  vel += acc;
  pos += vel;
  acc *= 0;
  // angle

  // color
  color.setHsb(h, s, b, a);
  // life
  lifeSpan = lifeSpan - lifeReduction;
  if (lifeSpan <= 0.0) {
    isDone = true;
    lifeSpan = 0.0;
  }
}


void Particle::display() {
  ofPushStyle();
  
  ofPushMatrix();
  ofTranslate( pos );
  ofRotate( theta );
  ofSetColor( color );
  ofDrawCircle(0, 0, rad);
  ofPopMatrix();
  
  ofPopStyle();
}


void Particle::applyForce( ofPoint force ) {
  force /= mass;
  acc += force;
}


void Particle::checkLifespan() {
  //if (life)
}














