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
  lifeReduction = ofRandom(0.0005,0.005);
  scaleLife = 0.0;
  scaleSine = 1.0;
  scaleSineFreq = ofRandom(0.05, 0.08);
  // shape
  mass = ofRandom(1, 3);
  rad = radOriginal = mass * 3;
  // color
  h = ofRandom(255);
  s = ofRandom(255);
  b = ofRandom(150, 255);
  a = 255;
  color.setHsb(h, s, b, a);
  // other
  section = -1;
}
Particle& Particle::position( ofPoint p ) {
  pos = p;
  return *this;
}
Particle& Particle::velocity( ofPoint v ) {
  vel = v;
  return *this;
}
Particle& Particle::setMass( float m ) {
  mass = m;
  rad = radOriginal = mass * 3;
  return *this;
}
Particle& Particle::setAngle( float a ) {
  angle = a;
  return *this;
}
Particle& Particle::setColor( ofColor c ) {
  color = c;
  return *this;
}
Particle& Particle::setSection( int s ) {
  section = s;
  return *this;
}
Particle& Particle::setLifeReduction( float l ) {
  lifeReduction = l;
  return *this;
}

void Particle::update() {
  // physics
  vel += acc;
  pos += vel;
  acc *= 0;
  vel.limit(20);
  // radius
  scaleSine = 1.0 + mSin(ofGetFrameNum() * scaleSineFreq) * 0.15;
  rad = radOriginal * scaleLife * scaleSine;
  // angle
  
  // color
  //color.setHsb(h, s, b, a);
  // life
  updateLifespan();
}


void Particle::display() {
  ofPushStyle();
  ofPushMatrix();
  ofTranslate( pos );
  
  ofRotate( angle );
  
  ofSetColor( color );
  ofDrawCircle(0, 0, rad);
  
  ofPopMatrix();
  ofPopStyle();
}


void Particle::applyForce( ofPoint force ) {
  force /= mass;
  acc += force;
}

void Particle::applyRestitution( float amount ){
  vel *= amount;
}

void Particle::applyAttraction( ofPoint target, float amount ) {
  ofPoint vector =  target - pos;
  vector *= amount;
  applyForce( vector );
}

void Particle::applyGravitation( Particle &other, float G ) {
  float distance = pos.distance( other.pos );
  if (distance > rad + other.rad) {
    ofPoint vector =  other.pos - pos;
    vector.normalize();
    float strength = (G * mass * other.mass) / (distance * distance);
    // if G is positive, they attract each other
    // if not, they repel by themselves
    vector *= strength;
    applyForce( vector );
  }
}


void Particle::checkCollision( Particle &other, float restitution ) {
  float distance = pos.distance( other.pos );
  
  if (distance < rad +  other.rad ) {
    // collided!
    
    // this to other
    ofPoint force = other.pos - pos;
    force.normalize();
    force *= other.vel.length() * restitution;
    other.applyForce( force );
    // other to this
    force *= -1;
    force.normalize();
    force *= vel.length() * restitution;
    this->applyForce( force );
  }
}


void Particle::checkBoundaries( float width, float height ) {
  if (pos.x < -width/2 || pos.x > width/2) {
    vel.x *= -1;
  }
  if (pos.y < -height/2 || pos.y > height/2) {
    vel.y *= -1;
  }
  pos.x = ofClamp(pos.x, -width/2 + 1, width/2 - 1);
  pos.y = ofClamp(pos.y, -height/2 + 1, height/2 - 1);
}




void Particle::updateLifespan() {
  
  float dying = 0.1;
  if (lifeSpan >= dying) {
    // born & live
    if (scaleLife > 0.99) {
      scaleLife = 1.0;
    } else {
      scaleLife = ofLerp( scaleLife, 1.0, ofRandom(0.001, 0.01) );
    }
  } else {
    // dying
    scaleLife = ofMap(lifeSpan, dying, 0.0, 1.0, 0.0);
  }
}

void Particle::reduceLifespan() {
  lifeSpan = lifeSpan - lifeReduction;
  if (lifeSpan <= 0.0) {
    isDone = true;
    lifeSpan = 0.0;
  }
}











//
