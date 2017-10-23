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
  
  // Save PNGs
  void renderFBOs();
  
  // Sound
  vector<ofSoundPlayer> sounds;
  void setupSounds();
  void updateSounds();
  void triggerSound(int index, float volume, float speed, float pan);
  
  // Image
  ofImage imgBgCenter;
  ofImage imgBgLR;
  
  // Firework Data
  vector<FireworkData> fireworks;
  void setupFireworks();
  
  // Websocket Data Received
  void wsDataReceived( string incoming );
  
  // GUIs
  ofParameterGroup mainParameters;
  ofParameter<int> guiSequenceMode;
  int prevSequenceMode = -1;
  ofParameter<bool> guiWebsocketToggle;
  ofParameter<bool> guiSyphonToggle;
  ofParameter<int> guiDisplayMode;
  ofParameter<float> guiScale;
  ofParameter<float> guiOffsetX;
  
  
  ofxPanel mainGui;
  void setupGUI();
  void updateGUI();
  
  // Sequence (Mode)
  int mode = 0;
  bool modeChanged = false;
  void updateVisuals();
  void displayVisuals( PSystemScreen screen );
  void resetMode();
  void modeReady_init();
  void modeReady_update();
  void modeReady_display( PSystemScreen screen );
  void modeTouchShake_init();
  void modeTouchShake_update();
  void modeTouchShake_display( PSystemScreen screen );
  void modeMelody_init();
  void modeMelody_update();
  void modeMelody_display( PSystemScreen screen );
  void modeSeunSori_init();
  void modeSeunSori_update();
  void modeSeunSori_display( PSystemScreen screen );
  void modeFinale_init();
  void modeFinale_update();
  void modeFinale_display( PSystemScreen screen );
  void modeTest_init();
  void modeTest_update();
  void modeTest_display( PSystemScreen screen );
  
};
