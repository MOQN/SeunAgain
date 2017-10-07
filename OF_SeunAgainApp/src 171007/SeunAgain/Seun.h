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
  
  // Paritcles
  vector<ParticleSystem> pSystems;
  
  // FBOs
  ofFbo fboCenter, fboLeft, fboRight;
  void setupFBOs();
  void updateFBOs();
  
  // Modes
  /**
   * displayMode
   * 0: normal
   * 1: zoom in/out
   * 2: testMode
   **/
  
  
  
  // GUIs
  ofParameterGroup mainParameters;
  ofParameter<int> guiDisplayMode;
  ofParameter<float> guiScale;
  ofxPanel mainGui;
  void setupGUI();
  void updateGUI();
  void updateMode();
  
};
