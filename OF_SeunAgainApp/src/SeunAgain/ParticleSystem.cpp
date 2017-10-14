//
//  ParticleSystem.cpp
//  SeunAgain
//
//  Created by MOQN on 10/7/17.
//

#include "ParticleSystem.h"


ParticleSystem::ParticleSystem() {
  stage = 0;
  gravity = 0.05;
  
  //pos = ofPoint( ofGetWidth()/2, ofGetHeight() );
  pos = ofPoint( 0,0 );
  
  int num = 0;
  while( num < 100 ) {
    particles.push_back( Particle()
                        .position( ofPoint( ofRandom(ofGetWidth()),ofRandom(ofGetWidth()) ) )
                        .velocity( ofPoint( ofRandom(-5,5),ofRandom(-5,5) ) )
                        );
    num++;
  }
  
  /*
   img.load("images/test.png");
   ofPixels pixels = img.getPixels();
   
   int resolution = 3;
   for (int y=0; y<img.getHeight(); y += resolution) {
   for (int x=0; x<img.getWidth(); x += resolution) {
   int index = (img.getWidth()*y + x) * 4;
   
   float r = pixels[index+0];
   float g = pixels[index+1];
   float b = pixels[index+2];
   
   if (r+g+b < 245*3 && ofRandom(1.0) < 0.3) {
   //if this is not white color and 30% chance
   particles.push_back( Particle()
   .position( ofPoint(x,y) )
   );
   }
   }
   }
   */
  
  //  numOfParticles = int( ofRandom(100,200) );
  //
  //  for (int i=0; i<numOfParticles; i++) {
  //    particles.push_back( Particle()
  //                        .position( ofPoint(0,0) )
  //                        //.velocity( ofPoint( 0, -9) )
  //                        );
  //  }
}

void ParticleSystem::update() {
  //updateStage();
  
  for (int i = particles.size()-1; i>=0; i--) {
    Particle* p = &particles[i];
    p->update();
    p->checkBoundaries( ofGetWidth(), ofGetHeight() );
  }
}

void ParticleSystem::display() {
  ofPushStyle();
  
  ofPushMatrix();
  ofTranslate( pos );
  for (auto &p : particles) {
    p.display();
  }
  ofPopMatrix();
  
  ofSetColor( 255 );
  ofDrawBitmapString(particles.size(), 10, 20);
  
  ofPopStyle();
}

void ParticleSystem::updateStage() {
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
      slowDown( 0.9 );
      if (particles[0].vel.length() < 0.01) {
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

void ParticleSystem::explode() {
  for (auto &p : particles) {
    float randomAngle = ofRandom(TWO_PI);
    float randomStrength = ofRandom(12,15);
    float x = mCos(randomAngle) * randomStrength;
    float y = mSin(randomAngle) * randomStrength;
    ofPoint force = ofPoint(x,y);
    p.applyForce( force );
  }
}

void ParticleSystem::slowDown( float amount ) {
  for (auto &p : particles) {
    p.vel *= amount;
  }
}








