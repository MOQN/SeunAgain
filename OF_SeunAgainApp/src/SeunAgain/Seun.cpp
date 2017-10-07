//
//  Seun.cpp
//  SeunAgain
//
//  Created by MOQN on 10/6/17.
//

#include "Seun.h"


void Seun::init() {
  ofSetWindowTitle("Seun Again");
  ofSetEscapeQuitsApp(false);
  ofBackground(0);
  ofSetCircleResolution(60);
  
  setupSinCos();
  setupFBOs();
  
  pSystems.push_back( ParticleSystem() );
}


void Seun::update() {
  
  updateMode();
  
}


void Seun::draw() {
  ofPushStyle();
  
  switch (displayMode) {
    case 0:
      ofSetColor(50);
      ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
      
      ofPushMatrix();
      ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
      FB
      
      
      ofPopMatrix();
      break;
    case 1:
      break;
    case 2:
      for (auto &f : pSystems) {
        f.update();
        f.display();
      }
      break;
  }
  
  
  ofPopStyle();
}


void Seun::keyPressed( int key ) {
  stringstream log;
  log << char(key) << ": ";
  
  switch (key) {
    case '0' ... '2':
      displayMode = key - '0';
      log << "Display Mode Changed";
      break;
    default:
      log << "Okay..";
      break;
  }
  
  cout << log.str() << endl;
}


void Seun::setupFBOs() {
  fboCenter.allocate(SCREEN_CENTER_WIDTH, SCREEN_CENTER_HEIGHT);
  fboLeft.allocate(SCREEN_LR_WIDTH, SCREEN_LR_HEIGHT);
  fboRight.allocate(SCREEN_LR_WIDTH, SCREEN_LR_HEIGHT);
  
  fboCenter.begin();
  ofClear(0);
  fboCenter.end();
  
  fboLeft.begin();
  ofClear(0);
  fboCenter.end();
  
  fboRight.begin();
  ofClear(0);
  fboCenter.end();
}


void Seun::updateMode() {
  //
}





















