//
//  Seun_Websocket.cpp
//  SeunAgain
//
//  Created by MOQN on 10/25/17.
//

#include "Seun.h"


void Seun::wsDataReceived( string incoming ) {
  if (!guiWebsocketToggle) return;
  
  vector<string> subStr = ofSplitString(incoming, ",");

  for(string s : subStr) {
    if ( s.length() == 2) {
      changeMode( ofToInt(s) );
    }
    else if ( s.length() == 9) {
      int strH = ofToInt(s.substr(0, 3));
      int strS = ofToInt(s.substr(3, 1));
      int strB = ofToInt(s.substr(4, 1));
      int strX = ofToInt(s.substr(5, 2));
      int strY = ofToInt(s.substr(7, 2));
      
      float hue = ofMap(strH, 0, 359, 0, 255);
      float sat = ofMap(strS, 0, 9, 255 * 0.5, 255);
      float bri = ofMap(strB, 0, 9, 255 * 0.5, 255);
      float x = ofMap(strX, 0, 99, -SCREEN_CENTER_WIDTH/2, SCREEN_CENTER_WIDTH/2);
      float y = ofMap(strY, 0, 99, -SCREEN_CENTER_HEIGHT/2, SCREEN_CENTER_HEIGHT/2);
      
      ofColor c;
      c.setHsb(hue, sat, bri);
      
      
      // generate particles
      int section = floor(strH / (360/5));
      
      switch (mode) {
        case 0:
          // ready
          break;
        case 1:
          // touch & shake
          modeTouchShake_getWSData( x, y, c );
          break;
        case 2:
          // melody
          break;
        case 3:
          modeSeunSori_getWSData( x, y, c, section );
          break;
        case 4:
          break;
        case 5:
          if (TEST_MODE == 1) modeSeunSori_getWSData( x, y, c, section );
          break;
        default:
          break;
      }
      
      if (mode == 3 || mode == 5) {
        // trigger sound
        int soundIndex = floor( ofRandom(section * 6, (section+1) * 6) );
        switch (section) {
          case 0:
            // 0: Environment long
            triggerSound(soundIndex, ofRandom(0.2, 0.5), ofRandom(0.95, 1.05), ofRandom(-1,1));
            break;
          case 1:
            // 1: Environment short
            triggerSound(soundIndex, ofRandom(0.5, 0.9), ofRandom(0.9, 1.1), ofRandom(-1,1));
            break;
          case 2:
            // 2: Perccusion
            triggerSound(soundIndex, ofRandom(0.9, 1.0), ofRandom(0.5, 1.5), ofRandom(-1,1));
            break;
          case 3:
            // 3: Futuristic
            triggerSound(soundIndex, ofRandom(0.4, 0.6), ofRandom(0.5, 1.5), ofRandom(-1,1));
            break;
          case 4:
            // 4: Old Seun
            triggerSound(soundIndex, ofRandom(0.6, 0.9), ofRandom(0.95, 1.05), ofRandom(-1,1));
            break;
        }
        // other
        if (ofRandom(1) < 0.02) {
          soundIndex = int(ofRandom(30,36));
          triggerSound(soundIndex, ofRandom(0.3, 0.5), 1.0, ofRandom(-1,1));
        }
      }
    }
  }
}



void Seun::modeTouchShake_getWSData( int x, int y, ofColor c ) {
  // generate particles
  if (pSystems.size() > 2) {
    if (pSystems[0].particles.size() < 500) {
      pSystems[0].particles.push_back( Particle()
                                      .position( ofPoint(x,y) )
                                      .setColor( c )
                                      .velocity( ofPoint(ofRandom(-1.5,1.5),ofRandom(-1.5,1.5)) )
                                      .setMass( ofRandom(3,6) )
                                      .setLifeReduction( ofRandom(0.007, 0.008) )
                                      .setScaleLifeTarget( 0.0, ofRandom(10.0,20.0) )
                                      .setScaleSine(0.0, 0.0)
                                      );
      pSystems[1].particles.push_back( Particle()
                                      .position( ofPoint(SCREEN_LR_WIDTH/2,0) )
                                      .setColor( c )
                                      .velocity( ofPoint(ofRandom(-3,-6),ofRandom(-2,2)) )
                                      .setMass( ofRandom(5,30) )
                                      .setLifeReduction( ofRandom(0.001, 0.01) )
                                      .setScaleSineAmp(0.2)
                                      );
      pSystems[2].particles.push_back( Particle()
                                      .position( ofPoint(-SCREEN_LR_WIDTH/2,0) )
                                      .setColor( c )
                                      .velocity( ofPoint(ofRandom(3,6),ofRandom(-2,2)) )
                                      .setMass( ofRandom(5,30) )
                                      .setLifeReduction( ofRandom(0.001, 0.01) )
                                      .setScaleSineAmp(0.2)
                                      );
    }
  }
}


void Seun::modeSeunSori_getWSData( int x, int y, ofColor c, int section) {
  
  // generate particles
  if (pSystems.size() > 2) {
    if (pSystems[0].particles.size() < 800) {
      pSystems[0].particles.push_back( Particle()
                                      .position( ofPoint(0,0) )
                                      .velocity( ofPoint(ofRandom(-5,5),ofRandom(-5,5)) )
                                      .setColor( c )
                                      .setMass( ofRandom(50, 80) )
                                      .setScaleLifeTarget(1.0, 0.1)
                                      .setScaleSineAmp(0.3)
                                      );
    }
    float newX = SOUND_CIRCLE_PITCH * -2 + SOUND_CIRCLE_PITCH * section;
    if (pSystems[1].particles.size() < 250) {
      pSystems[1].particles.push_back( Particle()
                                      .position( ofPoint(newX,0) )
                                      .velocity( ofPoint(ofRandom(-3,3),ofRandom(-3,3)) )
                                      .setMass( ofRandom(5,12) )
                                      .setColor( c )
                                      .setSection( section )
                                      .setLifeReduction( 0.001 )
                                      .setScaleSineAmp(0.4)
                                      );
    }
    if (pSystems[2].particles.size() < 250) {
      pSystems[2].particles.push_back( Particle()
                                      .position( ofPoint(newX,0) )
                                      .velocity( ofPoint(ofRandom(-3,3),ofRandom(-1,3)) )
                                      .setMass( ofRandom(5,12) )
                                      .setColor( c )
                                      .setSection( section )
                                      .setLifeReduction( 0.001 )
                                      .setScaleSineAmp(0.4)
                                      );
    }
  }
  
}






