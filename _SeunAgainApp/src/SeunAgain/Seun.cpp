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
  
  // SOUND TRIGGER MODE
  pSystems.push_back( ParticleSystem( PS_MODE_SOUND, PS_SCREEN_CENTER )
                     .position( ofPoint(SCREEN_CENTER_WIDTH/2, SCREEN_CENTER_HEIGHT/2) )
                     .setBoundary( ofPoint(SCREEN_CENTER_WIDTH,
                                           SCREEN_CENTER_HEIGHT) )
                     .init()
                     );
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


void Seun::update() {
  
  updateGUI();
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
      
    case 3:
      // test?
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
  
  // info
  ofSetColor( 255 );
  stringstream info;
  info << "fps: " << int(ofGetFrameRate()) << endl << endl;;
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
  
  // update particles
  for (auto &ps : pSystems) {
    ps.update();
  }
  
  // draw them into fbos
  
  // CENTER
  
  fboCenter.begin();
  ofClear(0,0,0);
  
  if (guiDisplayMode != 2) ofSetColor(0);
  else ofSetColor(255,0,0);
  ofDrawRectangle(0, 0, fboCenter.getWidth(), fboCenter.getHeight());
  
  ofSetColor(255,50);
  imgBgCenter.draw(0,0);
  
  for (auto &ps : pSystems) {
    if (ps.screen == PS_SCREEN_CENTER) ps.display();
  }
  
  
  fboCenter.end();
  
  // LEFT
  
  fboLeft.begin();
  ofClear(0);
  
  if (guiDisplayMode != 2) ofSetColor(0);
  else ofSetColor(0,255,0);
  ofDrawRectangle(0, 0, fboLeft.getWidth(), fboLeft.getHeight());
  
  ofSetColor(255,50);
  imgBgLR.draw(0,0);
  
  for (auto &ps : pSystems) {
    if (ps.screen == PS_SCREEN_LEFT) ps.display();
  }
  
  fboLeft.end();
  
  // RIGHT
  
  fboRight.begin();
  ofClear(0);
  
  if (guiDisplayMode != 2) ofSetColor(0);
  else ofSetColor(0,0,255);
  ofDrawRectangle(0, 0, fboRight.getWidth(), fboRight.getHeight());
  
  ofSetColor(255,50);
  imgBgLR.draw(0,0);
  
  for (auto &ps : pSystems) {
    if (ps.screen == PS_SCREEN_RIGHT) ps.display();
  }
  
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
      mode = ofToInt(s);
    }
    else if ( s.length() == 8) {
      int hue = ofToInt(s.substr(0, 3));
      int sound = ofToInt(s.substr(3, 1));
      int x = ofToInt(s.substr(4, 2));
      int y = ofToInt(s.substr(6, 2));
      
      float mappedX = ofMap(x, 0, 99, -SCREEN_CENTER_WIDTH/2, SCREEN_CENTER_WIDTH/2);
      float mappedY = ofMap(y, 0, 99, -SCREEN_CENTER_HEIGHT/2, SCREEN_CENTER_HEIGHT/2);
      ofColor c = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
      c.setHueAngle(hue);
      
      pSystems[0].particles.push_back( Particle()
                                      .position( ofPoint(mappedX,mappedY) )
                                      .setColor( c )
                                      );
      //if (mode == 4)
      triggerSound(sound, 0.75, ofRandom(0.9, 1.1), ofRandom(-1,1));
    }
    
    
  }
}

void Seun::setupGUI() {
  mainParameters.setName("Setting");
  mainParameters.add( guiDisplayMode.set("DisplayMode", 1, 0, 2) );
  mainParameters.add( guiScale.set("Scale", 0.48, 0.3, 1.0) );
  mainParameters.add( guiSyphonToggle.set("SyphonToggle", false) );
  
  mainGui.setup(mainParameters);
  mainGui.setPosition(ofGetWidth() - GUI_WIDTH, 0);
}

void Seun::updateGUI() {
  //mScale = ofLerp(mScale, guiScale, 0.005);
}














