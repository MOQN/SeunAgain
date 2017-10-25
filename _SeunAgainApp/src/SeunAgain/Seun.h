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
  
  // Cam
  ofEasyCam camCenter, camLeft, camRight;
  ofPoint rotationAngle = ofPoint(0,0,0);
  
  // Save PNGs
  void renderFBOs();
  
  // Sound
  ofSoundPlayer bgmOpening;
  ofSoundPlayer bgmClosing;
  vector<ofSoundPlayer> sounds;
  void setupSounds();
  void updateSounds();
  void triggerSound(int index, float volume, float speed, float pan);
  
  // Image
  ofImage imgBgCenter;
  ofImage imgBgLR;
  ofImage imgUrl;
  
  // Firework Data
  vector<FireworkData> fireworks;
  void setupFireworks();
  
  // Websocket Data Received
  void wsDataReceived( string incoming );
  
  // Mapped Mouse X Y
  ofPoint getScaledMouse();
  
  // GUIs
  ofParameterGroup mainParameters;
  ofParameter<int> guiMainMode;
  int prevMainMode = -1;
  ofParameter<bool> guiWebsocketToggle;
  ofParameter<bool> guiSyphonToggle;
  ofParameter<int> guiDisplayMode;
  ofParameter<float> guiScale;
  ofParameter<float> guiOffsetX;
  // Opening
  ofParameter<float> guiAttraction;
  ofParameter<float> guiGravity;
  // Closing
  ofParameter<float> guiDepth;
  ofParameter<float> guiAlpha;
  ofParameter<float> guiBallRad;
  ofParameter<float> guiBallAttraction;
  ofParameter<float> guiBallCollision;
  ofParameter<float> guiRotationVelX;
  ofParameter<float> guiRotationVelY;
  
  ofxPanel mainGui;
  void setupGUI();
  void updateGUI();
  
  // Mode & Sequence
  int mode = INIT_MODE;
  int sequence = 0;
  int prevSequence = 0;
  int count = 0;
  int keyCode = 0;
  bool modeChanged = false;
  void changeMode( int m );
  
  void initVisuals();
  void displayVisuals( PSystemScreen screen );
  
  void modeReady_init();
  void modeReady_display( PSystemScreen screen );
  
  void modeTouchShake_init();
  void modeTouchShake_display( PSystemScreen screen );
  void modeTouchShake_getWSData( int x, int y, ofColor c );
  
  void modeMelody_init();
  void modeMelody_display( PSystemScreen screen );
  
  void modeSeunSori_init();
  void modeSeunSori_display( PSystemScreen screen );
  void modeSeunSori_getWSData( int x, int y, ofColor c, int section);
  
  void modeTest_init();
  void modeTest_display( PSystemScreen screen );
  
  void modeOpening_init();
  void modeOpening_display( PSystemScreen screen );
  void modeOpening_seq1_rectNoise( PSystemScreen screen );
  void modeOpening_seq2_rectRythm( PSystemScreen screen );
  void modeOpening_seq3_circleRythm( PSystemScreen screen );
  void modeOpening_seq4_circleAttraction( PSystemScreen screen );
  void modeOpening_seq5_circleRepultion( PSystemScreen screen );
  void modeOpening_seq6_fireworks( PSystemScreen screen );
  
  void modeClosing_init();
  void modeClosing_display( PSystemScreen screen );
  
};










//
