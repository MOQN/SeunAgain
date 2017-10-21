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
  setupFireworks();
  setupGUI();
  
  texSyphonCenter.setName("SeunCENTER");
  texSyphonLeft.setName("SeunLEFT");
  texSyphonRight.setName("SeunRIGHT");
  
  imgBgCenter.load("images/bg_Center.jpg");
  imgBgLR.load("images/bg_LR.jpg");
}


void Seun::update() {
  
  updateGUI();
  updateVisuals();
  updateFBOs();
  updateSounds();
  
}


void Seun::draw() {
  
  switch (guiDisplayMode) {
      
    case 0 ... 2:
      ofPushStyle();
      // background
      ofSetColor(20);
      ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
      
      // draw fbos
      ofPushMatrix();
      ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
      ofSetColor(255);
      if (guiDisplayMode == 0) {
        // fixed
        ofScale(0.48, 0.48);
      } else {
        // can be changed with the gui
        ofScale(guiScale, guiScale);
      }
      
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
      
      ofPopStyle();
      break;
  }
  
  mainGui.draw();
  
  // to save the fbos as a PNG sequence
  if (RENDER_FBO_UNTIL) {
    renderFBOs();
  }
  
  // syphon
  if (guiSyphonToggle) {
    texSyphonCenter.publishTexture( &fboCenter.getTexture() );
    texSyphonLeft.publishTexture( &fboLeft.getTexture() );
    texSyphonRight.publishTexture( &fboRight.getTexture() );
  }
  
  // info
  ofSetColor( 255 );
  stringstream info;
  info << "fps: " << int(ofGetFrameRate()) << endl << endl;;
  info << "mode: " << mode << endl << endl;;
  for (int i=0; i<pSystems.size(); i++) {
    info << i <<  ": " << pSystems[i].particles.size() << endl;
  }
  ofDrawBitmapString( info.str() , 10, 20);
}


void Seun::keyPressed( int key ) {
  stringstream log;
  log << char(key) << ": ";
  
  switch (key) {
    case '0' ... '9':
      //guiDisplayMode = key - '0';
      //log << "DisplayMode Changed";
      int soundIndex;
      soundIndex = key - '0';
      triggerSound(soundIndex, 0.75, ofRandom(0.9, 1.1), ofRandom(-1, 1) );
      log << "Sound Triggered";
      break;
    case 'a':
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
  
  // draw them into fbos
  
  // CENTER
  
  fboCenter.begin();
  ofClear(0,0,0);
  
  if (guiDisplayMode != 2) ofSetColor(0);
  else ofSetColor(255,0,0);
  ofDrawRectangle(0, 0, fboCenter.getWidth(), fboCenter.getHeight());
  
  ofSetColor(255,50);
  imgBgCenter.draw(0,0);
  
  displayVisuals( PS_SCREEN_CENTER );
  
  fboCenter.end();
  
  // LEFT
  
  fboLeft.begin();
  ofClear(0);
  
  if (guiDisplayMode != 2) ofSetColor(0);
  else ofSetColor(0,255,0);
  ofDrawRectangle(0, 0, fboLeft.getWidth(), fboLeft.getHeight());
  
  ofSetColor(255,50);
  imgBgLR.draw(0,0);
  
  displayVisuals( PS_SCREEN_LEFT );
  
  fboLeft.end();
  
  // RIGHT
  
  fboRight.begin();
  ofClear(0);
  
  if (guiDisplayMode != 2) ofSetColor(0);
  else ofSetColor(0,0,255);
  ofDrawRectangle(0, 0, fboRight.getWidth(), fboRight.getHeight());
  
  ofSetColor(255,50);
  imgBgLR.draw(0,0);
  
  displayVisuals( PS_SCREEN_RIGHT );
  
  fboRight.end();
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

void Seun::triggerSound(int index, float volume, float speed, float pan) {
  sounds[index].play();
  sounds[index].setVolume( volume );
  sounds[index].setSpeed( speed );
  sounds[index].setPan( pan );
}

void Seun::setupFireworks() {
  ofDirectory dir;
  string filepath, filename;
  
  // open the directory
  dir.open( "fireworks" );
  dir.allowExt("png");
  dir.listDir();
  
  for (int i=0; i<dir.size(); i++) {
    filepath = dir.getPath(i);
    filename = dir.getName(i);
    ofImage image;
    image.load( filepath );
    fireworks.push_back( FireworkData( &image ) );
    
    cout << "FIREWORK IMAGE LOADED: " << filename << endl;
  }
  cout << endl;
}

void Seun::wsDataReceived( string incoming ) {
  vector<string> subStr = ofSplitString(incoming, ",");
  for(string s : subStr) {
    if ( s.length() == 2) {
      resetMode();
      mode = ofToInt(s);
    }
    else if ( s.length() == 10) {
      int strH = ofToInt(s.substr(0, 3));
      int strS = ofToInt(s.substr(3, 1));
      int strB = ofToInt(s.substr(4, 1));
      int sound = ofToInt(s.substr(5, 1));
      int strX = ofToInt(s.substr(6, 2));
      int strY = ofToInt(s.substr(8, 2));
      
      float hue = ofMap(strH, 0, 359, 0, 255);
      float sat = ofMap(strS, 0, 9, 0, 255);
      float bri = ofMap(strB, 0, 9, 255 * 0.3, 255 * 0.8);
      float x = ofMap(strX, 0, 99, -SCREEN_CENTER_WIDTH/2, SCREEN_CENTER_WIDTH/2);
      float y = ofMap(strY, 0, 99, -SCREEN_CENTER_HEIGHT/2, SCREEN_CENTER_HEIGHT/2);
      
      ofColor c;
      c.setHsb(hue, sat, bri);
      if (mode == 6) {
        if (pSystems.size() > 2) {
          pSystems[0].particles.push_back( Particle()
                                          .position( ofPoint(x,y) )
                                          //.velocity( ofPoint(ofRandom(-1,1),ofRandom(-1,1)) )
                                          .setColor( c )
                                          );
          float newX = SOUND_CIRCLE_PITCH * -2 + SOUND_CIRCLE_PITCH * floor(hue / (255/5));
          pSystems[1].particles.push_back( Particle()
                                          .position( ofPoint(newX,0) )
                                          .velocity( ofPoint(ofRandom(-0.1,0.1),ofRandom(-0.1,0.1)) )
                                          .setColor( c )
                                          );
          pSystems[2].particles.push_back( Particle()
                                          .position( ofPoint(newX,0) )
                                          .velocity( ofPoint(ofRandom(-0.1,0.1),ofRandom(-0.1,0.1)) )
                                          .setColor( c )
                                          );
        }
      }
      if (mode == 4) triggerSound(sound, 0.75, ofRandom(0.9, 1.1), ofRandom(-1,1));
    }
    
    
  }
}

void Seun::setupGUI() {
  mainParameters.setName("Setting");
  mainParameters.add( guiDisplayMode.set("DisplayMode", 1, 0, 2) );
  mainParameters.add( guiScale.set("Scale", 0.48, 0.35, 1.0) );
  mainParameters.add( guiSyphonToggle.set("SyphonToggle", false) );
  
  mainGui.setup(mainParameters);
  mainGui.setPosition(ofGetWidth() - GUI_WIDTH, 0);
}

void Seun::updateGUI() {
  //mScale = ofLerp(mScale, guiScale, 0.005);
}












///// Sequence Methods /////
void Seun::updateVisuals() {
  switch (mode) {
    case 0:
      if (modeChanged) modeReady_init();
      modeReady_update();
      break;
    case 1:
      if (modeChanged) modeTouchShake_init();
      modeTouchShake_update();
      break;
    case 2:
      if (modeChanged) modeTouchShake_init();
      modeTouchShake_update();
      break;
    case 3:
      if (modeChanged) modeMelody_init();
      modeMelody_update();
      break;
    case 4:
      if (modeChanged) modeSeunSori_init();
      modeSeunSori_update();
      break;
    case 5:
      if (modeChanged) modeFinale_init();
      modeFinale_update();
      break;
    case 6:
      if (modeChanged) modeTest_init();
      modeTest_update();
      break;
  }
  // update particles
  for (auto &ps : pSystems) {
    ps.update();
  }
}

void Seun::displayVisuals( PSystemScreen screen ) {
  switch (mode) {
    case 0:
      modeReady_display( screen );
      break;
    case 1:
      modeTouchShake_display( screen );
      break;
    case 2:
      modeTouchShake_display( screen );
      break;
    case 3:
      modeMelody_display( screen );
      break;
    case 4:
      modeSeunSori_display( screen );
      break;
    case 5:
      modeFinale_display( screen );
      break;
    case 6:
      modeTest_display( screen );
      break;
  }
  // draw particles
  for (auto &ps : pSystems) {
    if (ps.screen == screen) ps.display();
  }
}

void Seun::resetMode() {
  modeChanged = true;
  pSystems.clear();
}


// Mode: Ready
void Seun::modeReady_init() {
  modeChanged = false;
  // CENTER
  pSystems.push_back( ParticleSystem( PS_MODE_FIREWORK, PS_SCREEN_CENTER )
                     .addFireworkData( fireworks[0] )
                     .position( ofPoint(SCREEN_CENTER_WIDTH/2, SCREEN_CENTER_HEIGHT) )
                     .init()
                     );
  /*
   pSystems.push_back( ParticleSystem( PS_MODE_NORMAL )
   .position( ofPoint(SCREEN_CENTER_WIDTH/2, SCREEN_CENTER_HEIGHT/2) )
   .setBoundary( ofPoint(SCREEN_CENTER_WIDTH,
   SCREEN_CENTER_HEIGHT) )
   .init()
   );
   */
  // LEFT
  pSystems.push_back( ParticleSystem( PS_MODE_NORMAL, PS_SCREEN_LEFT )
                     .position( ofPoint(SCREEN_LR_WIDTH/2, SCREEN_LR_HEIGHT/2) )
                     .setBoundary( ofPoint(SCREEN_LR_WIDTH,
                                           SCREEN_LR_HEIGHT) )
                     .init()
                     );
  // RIGHT
  pSystems.push_back( ParticleSystem( PS_MODE_NORMAL, PS_SCREEN_RIGHT )
                     .position( ofPoint(SCREEN_LR_WIDTH/2, SCREEN_LR_HEIGHT/2) )
                     .setBoundary( ofPoint(SCREEN_LR_WIDTH,
                                           SCREEN_LR_HEIGHT) )
                     .init()
                     );
}
void Seun::modeReady_update() {
  
}
void Seun::modeReady_display( PSystemScreen screen ) {
  switch ( screen ) {
    case PS_SCREEN_CENTER:
      break;
    case PS_SCREEN_LEFT:
      break;
    case PS_SCREEN_RIGHT:
      break;
    case PS_SCREEN_LR:
      break;
  }
}

// Mode: Touch & Shake
void Seun::modeTouchShake_init() {
  modeChanged = false;
}
void Seun::modeTouchShake_update() {
  
}
void Seun::modeTouchShake_display( PSystemScreen screen ) {
  switch ( screen ) {
    case PS_SCREEN_CENTER:
      break;
    case PS_SCREEN_LEFT:
      break;
    case PS_SCREEN_RIGHT:
      break;
    case PS_SCREEN_LR:
      break;
  }
}

// Mode: Touch & Shake
void Seun::modeMelody_init() {
  modeChanged = false;
}
void Seun::modeMelody_update() {
  
}
void Seun::modeMelody_display( PSystemScreen screen ) {
  switch ( screen ) {
    case PS_SCREEN_CENTER:
      break;
    case PS_SCREEN_LEFT:
      break;
    case PS_SCREEN_RIGHT:
      break;
    case PS_SCREEN_LR:
      break;
  }
}

// Mode: SeunSori
void Seun::modeSeunSori_init() {
  modeChanged = false;
}
void Seun::modeSeunSori_update() {
  
}
void Seun::modeSeunSori_display( PSystemScreen screen ) {
  switch ( screen ) {
    case PS_SCREEN_CENTER:
      break;
    case PS_SCREEN_LEFT:
      break;
    case PS_SCREEN_RIGHT:
      break;
    case PS_SCREEN_LR:
      break;
  }
}

// Mode: Finale
void Seun::modeFinale_init() {
  modeChanged = false;
}
void Seun::modeFinale_update() {
  
}
void Seun::modeFinale_display( PSystemScreen screen ) {
  switch ( screen ) {
    case PS_SCREEN_CENTER:
      break;
    case PS_SCREEN_LEFT:
      break;
    case PS_SCREEN_RIGHT:
      break;
    case PS_SCREEN_LR:
      break;
  }
}

// Mode: Finale
void Seun::modeTest_init() {
  modeChanged = false;
  // SOUND TRIGGER MODE
  // CENTER
  pSystems.push_back( ParticleSystem( PS_MODE_SOUND, PS_SCREEN_CENTER )
                     .position( ofPoint(SCREEN_CENTER_WIDTH/2, SCREEN_CENTER_HEIGHT/2) )
                     .init()
                     );
  // LEFT
  pSystems.push_back( ParticleSystem( PS_MODE_SOUND, PS_SCREEN_LEFT )
                     .position( ofPoint(SCREEN_LR_WIDTH/2, SCREEN_LR_HEIGHT/2) )
                     .init()
                     );
  // RIGHT
  pSystems.push_back( ParticleSystem( PS_MODE_SOUND, PS_SCREEN_RIGHT )
                     .position( ofPoint(SCREEN_LR_WIDTH/2, SCREEN_LR_HEIGHT/2) )
                     .init()
                     );
  
}
void Seun::modeTest_update() {
  
}
void Seun::modeTest_display( PSystemScreen screen ) {
  
  switch ( screen ) {
    case PS_SCREEN_CENTER:
      break;
    default:
      ofPushStyle();
      ofPushMatrix();
      ofTranslate(SCREEN_LR_WIDTH/2, SCREEN_LR_HEIGHT/2);
      
      ofNoFill();
      ofSetColor(255, 100);
      int gap = 280;
      for (int x = gap * -2; x <= gap * 2; x += gap) {
        ofDrawCircle(x, 0, 100);
      } 
      
      ofPopMatrix();
      ofPopStyle();
      break;
  }
}








//
