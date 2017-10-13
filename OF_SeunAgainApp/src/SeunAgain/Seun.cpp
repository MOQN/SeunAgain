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
  setupSounds();
  setupGUI();
  
  texSyphonCenter.setName("SeunCENTER");
  texSyphonLeft.setName("SeunLEFT");
  texSyphonRight.setName("SeunRIGHT");
  
  fireworks.push_back( Firework() );
}


void Seun::update() {
  
  updateGUI();
  updateFBOs();
  updateSounds();
  
}


void Seun::draw() {
  
  switch (guiDisplayMode) {
      
    case 0 ... 1:
      ofPushStyle();
      // background
      ofSetColor(20);
      ofDrawRectangle(0, 0, ofGetWidth() - GUI_WIDTH, ofGetHeight());
      
      // draw fbos
      ofPushMatrix();
      ofTranslate(ofGetWidth()/2 - GUI_WIDTH/2, ofGetHeight()/2);
      
      if (guiDisplayMode == 0) {
        // fixed
        ofScale(0.3, 0.3);
      } else {
        // can be changed with the gui
        ofScale(guiScale, guiScale);
      }
      
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
      
    case 2:
      for (auto &f : fireworks) {
        f.update();
        f.display();
      }
      break;
  }
  
  mainGui.draw();
  
  if (RENDER_FBO_UNTIL) {
    renderFBOs();
  }
  
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
      log << "DisplayMode Changed";
      break;
    case 'a':
      sounds[0].play();
      sounds[0].setSpeed( ofRandom(0.5, 1.5) );
      sounds[0].setPan( ofRandom(-1, 1) );
      log << "Sound Triggered";
      break;
    case 's':
      sounds[1].play();
      sounds[1].setSpeed( ofRandom(0.5, 1.5) );
      sounds[1].setPan( ofRandom(-1, 1) );
      log << "Sound Triggered";
      break;
    default:
      log << "Okay...";
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


void Seun::setupSounds() {
  ofDirectory dir;
  string filepath, filename;
  
  // open the directory
  dir.open( "sounds" );
  dir.allowExt("wav");
  dir.listDir();
  
  for (int i=0; i<dir.size(); i++) {
    filepath = dir.getPath(i);
    filename = dir.getName(i);
    
    sounds.push_back( ofSoundPlayer() );
    sounds[i].load(filepath);
    sounds[i].setVolume(0.75f);
    sounds[i].setMultiPlay(true);
    cout << "SOUND LOADED: " << filename << endl;
  }
  cout << endl;
}

void Seun::updateSounds() {
  ofSoundUpdate();
}


void Seun::renderFBOs() {
  //   to save image
  static int fileIndex = 1000;
  ofPixels tempPixels;
  string filename;
  // center
  fboCenter.readToPixels(tempPixels);
  filename = "_Render/SeunCenter/seun_c_" + ofToString(fileIndex) + ".png";
  ofSaveImage(tempPixels, filename);
  // left
  fboLeft.readToPixels(tempPixels);
  filename = "_Render/SeunLeft/seun_l_" + ofToString(fileIndex) + ".png";
  ofSaveImage(tempPixels, filename);
  // right
  fboRight.readToPixels(tempPixels);
  filename = "_Render/SeunRight/seun_r_" + ofToString(fileIndex) + ".png";
  ofSaveImage(tempPixels, filename);
  
  fileIndex++;
  ofDrawBitmapString(fileIndex-999, 10, 40);
  
  if (fileIndex == RENDER_FBO_UNTIL + 1000 ) {
    cout << "renderFBOs: Done" << endl;
    ofExit();
  }
}


void Seun::setupGUI() {
  mainParameters.setName("Setting");
  mainParameters.add( guiDisplayMode.set("DisplayMode", 2, 0, 2) );
  mainParameters.add( guiScale.set("Scale", 0.3, 0.1, 1.0) );
  mainParameters.add( guiSyphonToggle.set("SyphonToggle", false) );
  
  mainGui.setup(mainParameters);
  mainGui.setPosition(ofGetWidth() - GUI_WIDTH, 0);
}

void Seun::updateGUI() {
  //mScale = ofLerp(mScale, guiScale, 0.005);
}














