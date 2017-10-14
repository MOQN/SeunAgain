//
//  Particle.cpp
//  SeunAgain
//
//  Created by MOQN on 10/6/17.
//

#include "Particle.h"


Particle::Particle() {
  // life
  lifeSpan = 1.0;
  scaleLife = 0;
  scaleSine = 1.0;
  scaleSineFreq = ofRandom(0.05, 0.08);
  // shape
  //isLarge = int( ofRandom(2) );
  if (isLarge) {
    mass = ofRandom(8, 10);
    rad = radOriginal = mass * 2.0;
    lifeReduction = 0.001;
  } else {
    mass = ofRandom(1, 3);
    rad = radOriginal = mass * 1.5;
    lifeReduction = ofRandom(0.0005,0.005);
  }
  // color
  h = ofRandom(255);
  s = ofRandom(255);
  b = ofRandom(150, 255);
  a = 255;
  color.setHsb(h, s, b, a);
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
  radOriginal = r;
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
  // radius
  scaleSine = 1.0 + mSin(ofGetFrameNum() * scaleSineFreq) * 0.15;
  rad = radOriginal * scaleLife * scaleSine;
  // angle
  
  // color
  color.setHsb(h, s, b, a);
  // life
  updateLifespan();
}


void Particle::display() {
  ofPushStyle();
  
  ofPushMatrix();
  ofTranslate( pos );
  ofRotate( theta );
  
  if (isLarge) {
    // outer circle
    ofSetColor( color );
    ofDrawCircle(0, 0, rad);
    // inner circle
    ofColor newColor;
    newColor.setHsb( ofWrap(h+30,0,255), s, b * 0.6 );
    ofSetColor( newColor );
    ofDrawCircle(0, 0, rad * 0.25);
  } else {
    // only small circle
    ofSetColor( color );
    ofDrawCircle(0, 0, rad);
  }
  ofPopMatrix();
  
  ofPopStyle();
}


void Particle::applyForce( ofPoint force ) {
  force /= mass;
  acc += force;
}


void Particle::updateLifespan() {
  lifeSpan = lifeSpan - lifeReduction;
  if (lifeSpan <= 0.0) {
    isDone = true;
    lifeSpan = 0.0;
  }
  float justBorn = 0.97;
  float dying = 0.1;
  if (lifeSpan >= justBorn) {
    // just born
    scaleLife = ofMap(lifeSpan, 1.0, justBorn, 0.0, 1.0);
  } else if (lifeSpan >= dying) {
    // live
    scaleLife = 1.0;
  } else {
    // dying
    scaleLife = ofMap(lifeSpan, dying, 0.0, 1.0, 0.0);
  }
}

void Particle::checkLifespan() {
  
}


void Particle::checkCollision( Particle* other ) {
  float distance = pos.distance( other->pos );
  
  if (distance < rad +  other->rad ) {
    // collided!
    
    // this to other
    ofPoint force = other->pos - this->pos;
    force.normalize();
    force *= other->vel.length() * 0.8;
    other->applyForce( force );
    // other to this
    force *= -1;
    force.normalize();
    force *= this->vel.length() * 0.8;
    this->applyForce( force );
  }
}


void Particle::checkBoundaries( float width, float height ) {
  if (pos.x < 0 || pos.x > width) {
    vel.x *= -1;
  }
  if (pos.y < 0 || pos.y > height) {
    vel.y *= -1;
  }
  pos.x = ofClamp(pos.x, 0, width);
  pos.y = ofClamp(pos.y, 0, height);
}











//
