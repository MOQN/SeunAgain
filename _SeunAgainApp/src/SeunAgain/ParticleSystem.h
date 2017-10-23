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
    int numOfColor = pixels.size() / (w * h);
    
    for (int y = 0; y < h; y += resolution) {
      for (int x=0; x < w; x += resolution) {
        int index = (w*y + x) * numOfColor;
        
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
  PSystemScreen screen;
  ofPoint boundary;
  
  ofPoint pos;
  ofColor color;
  
  
  
  float gravity;
  
  int numOfParticles;
  vector<Particle> particles;
  
  ParticleSystem( PSystemMode psMode, PSystemScreen psScreen );
  ParticleSystem& position( ofPoint p );
  ParticleSystem& setBoundary( ofPoint b );
  ParticleSystem& addFireworkData( FireworkData f );
  ParticleSystem& init();
  
  void update();
  void display();
  
  // Firework
  FireworkData firework;
  ofPoint posExplosion;
  
  int stage, count;
  void updateStage();
  void nextStage();
  
  void removeParticles();
  void applyGravity();
  void explode();
  void slowDown( float amount );
  
  void normal_init();
  void normal_update();
  void cell_init();
  void cell_update();
  void sound_init();
  void sound_update();
  void firework_init();
  void firework_update();
  void firework_updateStage();
  
};
