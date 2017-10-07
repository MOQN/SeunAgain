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
  setupGUI();
  
  texSyphonCenter.setName("SeunCENTER");
  texSyphonLeft.setName("SeunLEFT");
  texSyphonRight.setName("SeunRIGHT");
  
  pSystems.push_back( ParticleSystem() );
}


void Seun::update() {
  
  updateGUI();
  updateMode();
  updateFBOs();
  
}


void Seun::draw() {
  
  switch (guiDisplayMode) {
      
    case 0:
      ofPushStyle();
      // background
      ofSetColor(20);
      ofDrawRectangle(0, 0, ofGetWidth() - GUI_WIDTH, ofGetHeight());
      
      // draw fbos
      ofPushMatrix();
      ofTranslate(ofGetWidth()/2 - GUI_WIDTH/2, ofGetHeight()/2);
      ofScale(guiScale, guiScale);
      
      ofSetColor(255);
      ofDrawRectangle(0, 0, 100, 100);
      
      int x, y, w, h, gap;
      gap = 30;
      x = -fboCenter.getWidth()/2;
      y = -fboCenter.getHeight()/2;
      fboCenter.draw(x,y);
      w = fboLeft.getWidth() * 2;
      w = fboLeft.getHeight() * 2;
      x = -fboLeft.getWidth() - fboCenter.getWidth()/2 - gap;
      y = -fboLeft.getHeight()/2;
      fboLeft.draw(x,y);
      x = fboCenter.getWidth()/2 + gap;
      y = -fboRight.getHeight()/2;
      fboRight.draw(x,y);
      
      ofPopMatrix();
      
      //cout << fboCenter.getWidth() << endl;
      
      ofPopStyle();
      break;
      
    case 1:
      //
      break;
      
    case 2:
      for (auto &f : pSystems) {
        f.update();
        f.display();
      }
      break;
  }
  
  mainGui.draw();
  
  if (guiSyphonToggle) {
    texSyphonCenter.publishTexture( &fboCenter.getTexture() );
    texSyphonLeft.publishTexture( &fboLeft.getTexture() );
    texSyphonRight.publishTexture( &fboRight.getTexture() );
  }
}


void Seun::keyPressed( int key ) {
  stringstream log;
  log << char(key) << ": ";
  
  switch (key) {
    case '0' ... '2':
      guiDisplayMode = key - '0';
      log << "Display Mode Changed";
      break;
    default:
      log << "Okay..";
      break;
  }
  
  cout << log.str() << endl;
}


void Seun::setupFBOs() {
  // GL_RGBA32F_ARB?
  fboCenter.allocate(SCREEN_CENTER_WIDTH, SCREEN_CENTER_HEIGHT);
  fboLeft.allocate(SCREEN_LR_WIDTH, SCREEN_LR_HEIGHT);
  fboRight.allocate(SCREEN_LR_WIDTH, SCREEN_LR_HEIGHT);
  
  fboCenter.begin();
  ofClear(255,0,0);
  fboCenter.end();
  
  fboLeft.begin();
  ofClear(0);
  fboCenter.end();
  
  fboRight.begin();
  ofClear(0);
  fboCenter.end();
}


void Seun::updateFBOs() {
  fboCenter.begin();
  ofClear(0);
  ofSetColor(255,0,0);
  ofDrawRectangle(0, 0, fboCenter.getWidth(), fboCenter.getHeight());
  fboCenter.end();
  
  fboLeft.begin();
  ofClear(0);
  ofSetColor(0,255,0);
  ofDrawRectangle(0, 0, fboLeft.getWidth(), fboLeft.getHeight());
  fboLeft.end();
  
  fboRight.begin();
  ofClear(0);
  ofSetColor(0,0,255);
  ofDrawRectangle(0, 0, fboRight.getWidth(), fboRight.getHeight());
  fboRight.end();
}

void Seun::updateMode() {
  //
}


void Seun::setupGUI() {
  mainParameters.setName("Setting");
  mainParameters.add( guiDisplayMode.set("DisplayMode", 0, 0, 2) );
  mainParameters.add( guiScale.set("Scale", 0.3, 0.1, 1.0) );
  mainParameters.add( guiSyphonToggle.set("Syphon") );
  
  mainGui.setup(mainParameters);
  mainGui.setPosition(ofGetWidth() - GUI_WIDTH, 0);
}

void Seun::updateGUI() {
  //mScale = ofLerp(mScale, guiScale, 0.005);
}
















