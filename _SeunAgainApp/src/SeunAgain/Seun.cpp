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
  imgUrl.load("images/url.png");
}


void Seun::update() {
  
  updateGUI();
  initVisuals();
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
      ofTranslate(ofGetWidth()/2 + guiOffsetX, ofGetHeight()/2);
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
      // draw grid for mapping ***
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
  info << "Seq: " << sequence << endl << endl;;
  for (int i=0; i<pSystems.size(); i++) {
    info << i <<  ": " << pSystems[i].particles.size() << endl;
  }
  ofDrawBitmapString( info.str() , 10, 20);
  
  ofDrawBitmapString( bgmOpening.getPosition(), ofGetWidth()/2-150, 20 );
  ofDrawBitmapString( bgmClosing.getPosition(), ofGetWidth()/2+150, 20 );
}


void Seun::keyPressed( int key ) {
  keyCode = key;
  stringstream log;
  log << char(key) << ": ";
  
  switch (key) {
    case '0' ... '9':
      sequence = key - '0';
      log << "SequenceChanged: " << sequence;
      cout << log.str() << endl;
      break;
    case 'a':
      /*
       int soundIndex;
       soundIndex = key - '0';
       triggerSound(soundIndex, 0.75, ofRandom(0.9, 1.1), ofRandom(-1, 1) );
       log << "Sound Triggered";
       */
      break;
  }
}

ofPoint Seun::getScaledMouse() {
  float x = ofMap( ofGetMouseX()-ofGetWidth()/2 , -SCREEN_CENTER_WIDTH/2 * guiScale, SCREEN_CENTER_WIDTH/2 * guiScale, -SCREEN_CENTER_WIDTH/2, SCREEN_CENTER_WIDTH/2);
  float y = ofMap( ofGetMouseY()-ofGetHeight()/2 , -SCREEN_CENTER_HEIGHT/2 * guiScale, SCREEN_CENTER_HEIGHT/2 * guiScale, -SCREEN_CENTER_HEIGHT/2, SCREEN_CENTER_HEIGHT/2);
  
  if (x < -SCREEN_CENTER_WIDTH/2 - SCREEN_GAP) {
    x = x + SCREEN_LR_WIDTH/2 + SCREEN_CENTER_WIDTH/2 + SCREEN_GAP;
    return ofPoint(x,y,1);
  }
  else if (x > SCREEN_CENTER_WIDTH/2 + SCREEN_GAP) {
    x = x - SCREEN_LR_WIDTH/2 - SCREEN_CENTER_WIDTH/2 - SCREEN_GAP;
    return ofPoint(x,y,2);
  } else {
    return ofPoint(x,y,0);
  }
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
  // load bgms
  bgmOpening.load("bgms/opening.wav");
  bgmOpening.setVolume(0.0f);
  bgmOpening.setMultiPlay(false);
  bgmClosing.load("bgms/closing.wav");
  bgmClosing.setVolume(0.0f);
  bgmClosing.setMultiPlay(false);
  
  // load sounds
  ofDirectory dir;
  string filepath, filename;
  
  // open the directory
  dir.open( "sounds" );
  dir.allowExt("wav");
  dir.listDir();
  dir.sort();
  
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
  
  // closing bgm
  if (mode == 4) {
    if ( !bgmClosing.isPlaying() ) {
      bgmClosing.play();
    }
    float volume = ofLerp(bgmClosing.getVolume(), 1.0, 0.05);
    bgmClosing.setVolume(volume);
    if (bgmClosing.getPosition() > 0.995) {
      mode = 5;
    }
  } else {
    if ( bgmClosing.isPlaying() ) {
      if ( bgmClosing.getVolume() > 0.005 ) {
        float volume = ofLerp(bgmClosing.getVolume(), 0.0, 0.02);
        bgmClosing.setVolume(volume);
      } else {
        bgmClosing.stop();
      }
    }
  }
  // opening bgm
  if (mode == 6) {
    if ( !bgmOpening.isPlaying() ) {
      bgmOpening.play();
    }
    float volume = ofLerp(bgmOpening.getVolume(), 1.0, 0.05);
    bgmOpening.setVolume(volume);
    if (bgmOpening.getPosition() > 0.995) {
      mode = 5;
    }
  } else {
    if ( bgmOpening.isPlaying() ) {
      if ( bgmOpening.getVolume() > 0.005 ) {
        float volume = ofLerp(bgmOpening.getVolume(), 0.0, 0.02);
        bgmOpening.setVolume(volume);
      } else {
        bgmOpening.stop();
      }
    }
  }
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





///// Sequence Methods /////
void Seun::initVisuals() {
  switch (mode) {
    case 0:
      if (modeChanged) modeReady_init();
      break;
    case 1:
      if (modeChanged) modeTouchShake_init();
      break;
    case 2:
      if (modeChanged) modeMelody_init();
      break;
    case 3:
      if (modeChanged) modeSeunSori_init();
      break;
    case 4:
      if (modeChanged) modeClosing_init();
      break;
    case 5:
      if (modeChanged) modeTest_init();
      
      break;
    case 6:
      if (modeChanged) modeOpening_init();
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
      modeMelody_display( screen );
      break;
    case 3:
      modeSeunSori_display( screen );
      break;
    case 4:
      modeClosing_display( screen );
      break;
    case 5:
      modeTest_display( screen );
      break;
    case 6:
      modeOpening_display( screen );
      break;
  }
  // draw particles
  for (auto &ps : pSystems) {
    if (ps.screen == screen && ps.mode != PS_MODE_3D) ps.display();
  }
}

void Seun::changeMode( int m ) {
  modeChanged = true;
  mode = m;
  sequence = 0;
  count = 0;
  pSystems.clear();
}


// Mode: Ready
void Seun::modeReady_init() {
  modeChanged = false;
  // nothing!
}
void Seun::modeReady_display( PSystemScreen screen ) {
  switch ( screen ) {
    case PS_SCREEN_CENTER:
      ofSetColor(255);
      imgUrl.draw(0,SCREEN_CENTER_HEIGHT/2 + URL_IMAGE_ADJUSTMENT);
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
  // CENTER
  pSystems.push_back( ParticleSystem( PS_MODE_NORMAL, PS_SCREEN_CENTER )
                     .position( ofPoint(SCREEN_CENTER_WIDTH/2, SCREEN_CENTER_HEIGHT/2) )
                     );
  pSystems.push_back( ParticleSystem( PS_MODE_NORMAL, PS_SCREEN_LEFT )
                     .position( ofPoint(SCREEN_LR_WIDTH/2, SCREEN_LR_HEIGHT/2) )
                     .setBoundary( ofPoint(SCREEN_LR_WIDTH, SCREEN_LR_HEIGHT) )
                     );
  pSystems.push_back( ParticleSystem( PS_MODE_NORMAL, PS_SCREEN_RIGHT )
                     .position( ofPoint(SCREEN_LR_WIDTH/2, SCREEN_LR_HEIGHT/2) )
                     .setBoundary( ofPoint(SCREEN_LR_WIDTH, SCREEN_LR_HEIGHT) )
                     );
  
}
void Seun::modeTouchShake_display( PSystemScreen screen ) {
  switch ( screen ) {
    case PS_SCREEN_CENTER:
    {
      ParticleSystem &ps = pSystems[0];
      for (auto &p : ps.particles) {
        p.updateLifespan();
        p.reduceLifespan();
        p.update();
      }
      ps.removeParticles();
      break;
    }
    case PS_SCREEN_LEFT:
    {
      ParticleSystem &ps = pSystems[1];
      for (auto &p : ps.particles) {
        p.updateLifespan();
        p.reduceLifespan();
        p.update();
      }
      ps.removeParticles();
      break;
    }
    case PS_SCREEN_RIGHT:
    {
      ParticleSystem &ps = pSystems[2];
      for (auto &p : ps.particles) {
        p.updateLifespan();
        p.reduceLifespan();
        p.update();
      }
      ps.removeParticles();
      break;
    }
    case PS_SCREEN_LR:
      break;
  }
}

// Mode: Melody
void Seun::modeMelody_init() {
  modeChanged = false;
  pSystems.push_back( ParticleSystem( PS_MODE_NORMAL, PS_SCREEN_CENTER )
                     .position( ofPoint(SCREEN_CENTER_WIDTH/2, SCREEN_CENTER_HEIGHT/2) )
                     );
  pSystems.push_back( ParticleSystem( PS_MODE_NORMAL, PS_SCREEN_LEFT )
                     .position( ofPoint(SCREEN_LR_WIDTH/2, SCREEN_LR_HEIGHT/2) )
                     .setBoundary( ofPoint(SCREEN_LR_WIDTH, SCREEN_LR_HEIGHT) )
                     );
  pSystems.push_back( ParticleSystem( PS_MODE_NORMAL, PS_SCREEN_RIGHT )
                     .position( ofPoint(SCREEN_LR_WIDTH/2, SCREEN_LR_HEIGHT/2) )
                     .setBoundary( ofPoint(SCREEN_LR_WIDTH, SCREEN_LR_HEIGHT) )
                     );
}
void Seun::modeMelody_display( PSystemScreen screen ) {
  
  // update
  if (pSystems.size() > 2) {
    if (pSystems[0].particles.size() < 500 && ofRandom(1) < 0.1) {
      pSystems[0].particles.push_back( Particle()
                                      .position( ofPoint(ofRandom(-SCREEN_CENTER_WIDTH/2,SCREEN_CENTER_WIDTH/2),
                                                         ofRandom(-SCREEN_CENTER_HEIGHT/2,SCREEN_CENTER_HEIGHT/2) ) )
                                      .velocity( ofPoint(ofRandom(-1.5,1.5),ofRandom(-1.5,1.5)) )
                                      .setMass( ofRandom(5,10) )
                                      .setLifeReduction( ofRandom(0.007, 0.008) )
                                      .setScaleSineAmp(0.2)
                                      .setScaleLifeTarget(1.0, 0.0)
                                      );
      pSystems[1].particles.push_back( Particle()
                                      .position( ofPoint(SCREEN_LR_WIDTH/2,ofRandom(-SCREEN_LR_WIDTH/2,SCREEN_LR_WIDTH/2)) )
                                      .velocity( ofPoint(ofRandom(-3,-6), ofRandom(-2,2)) )
                                      .setMass( ofRandom(3,10) )
                                      .setLifeReduction( ofRandom(0.001, 0.01) )
                                      .setScaleSineAmp(0.2)
                                      );
      pSystems[2].particles.push_back( Particle()
                                      .position( ofPoint(-SCREEN_LR_WIDTH/2,ofRandom(-SCREEN_LR_WIDTH/2,SCREEN_LR_WIDTH/2)) )
                                      .velocity( ofPoint(ofRandom(3,6), ofRandom(-2,2)) )
                                      .setMass( ofRandom(3,10) )
                                      .setLifeReduction( ofRandom(0.001, 0.01) )
                                      .setScaleSineAmp(0.2)
                                      );
    }
  }
  
  switch ( screen ) {
    case PS_SCREEN_CENTER:
    {
      ParticleSystem &ps = pSystems[0];
      for (auto &p : ps.particles) {
        p.updateLifespan();
        p.reduceLifespan();
        p.update();
      }
      ps.removeParticles();
      break;
    }
    case PS_SCREEN_LEFT:
    {
      ParticleSystem &ps = pSystems[1];
      for (auto &p : ps.particles) {
        p.updateLifespan();
        p.reduceLifespan();
        p.update();
      }
      ps.removeParticles();
      break;
    }
    case PS_SCREEN_RIGHT:
    {
      ParticleSystem &ps = pSystems[2];
      for (auto &p : ps.particles) {
        p.updateLifespan();
        p.reduceLifespan();
        p.update();
      }
      ps.removeParticles();
      break;
    }
    case PS_SCREEN_LR:
      break;
  }
}

// Mode: SeunSori
void Seun::modeSeunSori_init() {
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
void Seun::modeSeunSori_display( PSystemScreen screen ) {
  switch ( screen ) {
    case PS_SCREEN_CENTER:
      break;
    default:
      ofPushStyle();
      ofPushMatrix();
      ofTranslate(SCREEN_LR_WIDTH/2, SCREEN_LR_HEIGHT/2);
      
      for (int x = SOUND_CIRCLE_PITCH * -2; x <= SOUND_CIRCLE_PITCH * 2; x += SOUND_CIRCLE_PITCH) {
        ofColor c;
        float h = ofMap(x , SOUND_CIRCLE_PITCH * -2, SOUND_CIRCLE_PITCH * 3, 0, 255) + 255/10;
        c.setHsb(h, 255, 255, 50);
        ofSetColor( c );
        ofDrawCircle(x, 0, 80);
      }
      
      ofPopMatrix();
      ofPopStyle();
      break;
  }
}

// Mode: Test
void Seun::modeTest_init() {
  modeChanged = false;
  if (TEST_MODE == 0) return;
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
void Seun::modeTest_display( PSystemScreen screen ) {
  if (TEST_MODE == 0) return;
  switch ( screen ) {
    case PS_SCREEN_CENTER:
      break;
    default:
      ofPushStyle();
      ofPushMatrix();
      ofTranslate(SCREEN_LR_WIDTH/2, SCREEN_LR_HEIGHT/2);
      
      for (int x = SOUND_CIRCLE_PITCH * -2; x <= SOUND_CIRCLE_PITCH * 2; x += SOUND_CIRCLE_PITCH) {
        ofColor c;
        float h = ofMap(x , SOUND_CIRCLE_PITCH * -2, SOUND_CIRCLE_PITCH * 3, 0, 255) + 255/10;
        c.setHsb(h, 255, 255, 50);
        ofSetColor( c );
        ofDrawCircle(x, 0, 80);
      }
      
      ofPopMatrix();
      ofPopStyle();
      break;
  }
}





//
