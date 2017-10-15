//
//  ParticleSystem.hpp
//  SeunAgain
//
//  Created by MOQN on 10/7/17.
//

#pragma once

#include "Prefix.h"
#include "Particle.h"


class FireworkData {
public:
  int number = 0;
  vector<ofPoint> pos;
  vector<ofColor> colors;
  
  FireworkData() {}
  FireworkData( ofImage* image ) {
    ofPixels pixels = image->getPixels();
    
    int resolution = 3;
    int w = image->getWidth();
    int h = image->getHeight();
    
    for (int y = 0; y < h; y += resolution) {
      for (int x=0; x < w; x += resolution) {
        int index = (w*y + x) * 4;
        
        float r = pixels[index+0];
        float g = pixels[index+1];
        float b = pixels[index+2];
        
        if (r+g+b < 245*3 && ofRandom(1.0) < 0.3) {
          //if this is not white color and 30% chance
          pos.push_back( ofPoint(x - w/2 ,y - h/2) );
          colors.push_back( ofColor(r,g,b) );
          number++;
        }
      }
    }
  }
};


class ParticleSystem {
public:
  PSystemMode mode;
  ofPoint boundary;
  
  ofPoint pos;
  ofColor color;
  
  
  
  float gravity;
  
  int numOfParticles;
  vector<Particle> particles;
  
  ParticleSystem( PSystemMode mode );
  ParticleSystem& position( ofPoint p );
  ParticleSystem& setBoundary( ofPoint b );
  ParticleSystem& addFireworkData( FireworkData f );
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
  
  void slowDown( float amount );
  
  // Firework
  FireworkData firework;
  ofPoint posExplosion;
  void explode();
  
};
