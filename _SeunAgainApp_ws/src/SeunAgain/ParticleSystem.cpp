//
//  ParticleSystem.cpp
//  SeunAgain
//
//  Created by MOQN on 10/7/17.
//

#include "ParticleSystem.h"


ParticleSystem::ParticleSystem( PSystemMode _mode ) {
  mode = _mode;
  stage = 0;
  boundary = ofPoint(3000,3000);
}
ParticleSystem& ParticleSystem::position( ofPoint p ) {
  pos = p;
  return *this;
}
ParticleSystem& ParticleSystem::setBoundary( ofPoint b ) {
  boundary = b;
  return *this;
}
ParticleSystem& ParticleSystem::addFireworkData( FireworkData f ) {
  firework = f;
  return *this;
}
ParticleSystem& ParticleSystem::init() {
  switch ( mode ) {
    case PS_MODE_NORMAL :
      normal_init();
      break;
    case PS_MODE_FIREWORK :
      firework_init();
      break;
  }
  return *this;
}
void ParticleSystem::update() {
  switch ( mode ) {
    case PS_MODE_NORMAL :
      normal_update();
      break;
    case PS_MODE_FIREWORK :
      firework_update();
      break;
  }
}
void ParticleSystem::display() {
  normal_display();
  
  switch ( mode ) {
    case PS_MODE_NORMAL :
      //normal_display();
      break;
    case PS_MODE_FIREWORK :
      //firework_display();
      break;
  }
}


void ParticleSystem::normal_init() {
  int num = 0;
  while( num < 100 ) {
    particles.push_back( Particle()
                        .position( ofPoint( ofRandom(-boundary.x/2, boundary.x/2), ofRandom(-boundary.y/2, boundary.y/2) ) )
                        .velocity( ofPoint( ofRandom(-5,5),ofRandom(-5,5) ) )
                        );
    num++;
  }
}
void ParticleSystem::normal_update() {
  for (int i = particles.size()-1; i>=0; i--) {
    Particle* p = &particles[i];
    p->update();
    p->checkBoundaries( boundary.x, boundary.y );
  }
}
void ParticleSystem::normal_display() {
  ofPushStyle();
  ofPushMatrix();
  ofTranslate( pos );
  
  
  for (auto &p : particles) {
    p.display();
  }
  
  
  ofPopMatrix();
  ofPopStyle();
}





void ParticleSystem::cell_update() {
  //updateStage();
  
  for (int i = particles.size()-1; i>=0; i--) {
    Particle* p = &particles[i];
    p->update();
    p->checkBoundaries( ofGetWidth(), ofGetHeight() );
  }
}



void ParticleSystem::firework_init() {
  gravity = 0.05;
  
  for (int i=0; i<firework.number; i++) {
    particles.push_back( Particle()
                        .position( ofPoint(0,0) )
                        .velocity( ofPoint( 0, -11) )
                        .setColor( firework.colors[i] )
                        );
  }
}
void ParticleSystem::firework_update() {
  if (particles.size() == 0) return;
  updateStage();
  for (int i = particles.size()-1; i>=0; i--) {
    Particle* p = &particles[i];
    p->update();
  }
}
void ParticleSystem::updateStage() {
  if (particles.size() == 0) return;
  switch( stage ) {
    case 0:
      applyGravity();
      if (particles[0].vel.y > 2) {
        gravity = 0;
        explode();
        nextStage();
      }
      break;
    case 1:
      slowDown( 0.90 );
      for (int i=0; i<particles.size(); i++) {
        ofPoint destination = firework.pos[i]*2 + posExplosion;
        particles[i].pos = mLerp( particles[i].pos, destination, 0.2);
      }
      if (count > 300) {
        explode();
        nextStage();
      }
      break;
    case 2:
      gravity = ofLerp(gravity, 0.5, 0.01);
      applyGravity();
      break;
    case 3:
      
      break;
    case 4:
      break;
  }
  count++;
}

void ParticleSystem::nextStage() {
  count = 0;
  stage++;
}

void ParticleSystem::applyGravity() {
  for (auto &p : particles) {
    p.applyForce( ofPoint(0, gravity * p.mass) );
  }
}

void ParticleSystem::slowDown( float amount ) {
  for (auto &p : particles) {
    p.vel *= amount;
  }
}

void ParticleSystem::explode() {
  if (particles.size() == 0) return;
  posExplosion = particles[0].pos;
  for (auto &p : particles) {
    float randomAngle = ofRandom(TWO_PI);
    float randomStrength = ofRandom(8*3,15*3);
    float x = mCos(randomAngle) * randomStrength;
    float y = mSin(randomAngle) * randomStrength;
    ofPoint force = ofPoint(x,y);
    p.applyForce( force );
  }
}










