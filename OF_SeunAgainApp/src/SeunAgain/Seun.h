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
  ofxSyphonServer texSyphonCenter, texSyphonLeft, texSyphonRight;
  void setupFBOs();
  void updateFBOs();
  
  // Sound
  vector<ofSoundPlayer> sounds;
  void setupSounds();
  void updateSounds();
  
  
  
  
  // GUIs
  ofParameterGroup mainParameters;
  ofParameter<int> guiDisplayMode;
  ofParameter<float> guiScale;
  ofParameter<bool> guiSyphonToggle;
  ofxPanel mainGui;
  void setupGUI();
  void updateGUI();
  void updateMode();
  
  // Modes
  /**
   * displayMode
   * 0: normal
   * 1: zoom in/out
   * 2: testMode
   **/
};
