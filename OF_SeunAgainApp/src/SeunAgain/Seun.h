//
//  Seun.hpp
//  SeunAgain
//
//  Created by MOQN on 10/6/17.
//

#pragma once

#include "Prefix.h"
#include "ParticleSystem.h"



class Seun {
public:
  Seun() {}
  void init();
  void update();
  void draw();
  void keyPressed(int key);
  
  // paritcles
  vector<ParticleSystem> pSystems;
  // fbos
  ofFbo fboCenter, fboLeft, fboRight;
  void setupFBOs();
  // modes
  int displayMode = 0;
  /**
   * 0: normal
   * 1: zoom in/out
   * 2: testMode
   **/
  void updateMode();
  
  
  
  
};
