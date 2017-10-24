//
//  Seun_Opening.cpp
//  SeunAgain
//
//  Created by MOQN on 10/23/17.
//

#include "Seun.h"


// Mode: Opening
void Seun::modeOpening_init() {
  modeChanged = false;
  pSystems.push_back( ParticleSystem( PS_MODE_NORMAL, PS_SCREEN_CENTER )
                     .position( ofPoint(SCREEN_CENTER_WIDTH/2, SCREEN_CENTER_HEIGHT/2) )
                     .setBoundary( ofPoint(SCREEN_CENTER_WIDTH, SCREEN_CENTER_HEIGHT) )
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
void Seun::modeOpening_update() {
  //
}
void Seun::modeOpening_display( PSystemScreen screen ) {
  ofPushStyle();
  
  switch (sequence) {
    case 1:
      modeOpening_seq1_rectNoise( screen );
      break;
    case 2:
      modeOpening_seq2_rectRythm( screen );
      break;
    case 3:
      modeOpening_seq3_circleRythm( screen );
      break;
    case 4:
      modeOpening_seq4_circleAttraction( screen );
      break;
    case 5:
      modeOpening_seq5_circleRepultion( screen );
      break;
    case 6:
      modeOpening_seq6_fireworks( screen );
      break;
  }
  
  ofPopStyle();
  prevSequence = sequence;
}

void Seun::modeOpening_seq1_rectNoise( PSystemScreen screen ) {
  
  ofSetRectMode(OF_RECTMODE_CENTER);
  
  float mouseX, mouseY, alpha, rectSize;
  mouseX = ofClamp( ofMap(ofGetMouseX(), ofGetWidth() * 0.3, ofGetWidth() * 0.7, 100, 1), 1, 100);
  rectSize = floor(SCREEN_CENTER_HEIGHT / mouseX);
  alpha = ofClamp( ofMap(ofGetMouseY(), ofGetHeight() * 0.3, ofGetHeight() * 0.7, 255, 0), 0, 255);
  
  switch ( screen ) {
    case PS_SCREEN_CENTER:
    {
      ofPushMatrix();
      ofTranslate( SCREEN_CENTER_WIDTH/2, SCREEN_CENTER_HEIGHT/2);
      for (int y = -SCREEN_CENTER_HEIGHT/2; y < SCREEN_CENTER_HEIGHT/2 + rectSize; y += rectSize) {
        for (int x = -SCREEN_CENTER_WIDTH/2; x < SCREEN_CENTER_WIDTH/2 + rectSize; x += rectSize) {
          ofColor c;
          if ( ofGetKeyPressed() ) {
            c.setHsb( ofRandom(255), ofRandom(100,255), ofRandom(100,255), alpha );
          } else {
            c.setHsb( ofRandom(255), 0, ofRandom(255), alpha );
          }
          ofSetColor(c);
          ofDrawRectangle(x, y, rectSize*2, rectSize*2);
        }
      }
      ofPopMatrix();
      break;
    }
      
    case PS_SCREEN_LEFT:
    {
      ofPushMatrix();
      ofTranslate( SCREEN_LR_WIDTH/2, SCREEN_LR_HEIGHT/2);
      for (int y = -SCREEN_LR_HEIGHT/2; y < SCREEN_LR_HEIGHT/2 + rectSize; y += rectSize) {
        for (int x = -SCREEN_LR_WIDTH/2; x < SCREEN_LR_WIDTH/2 + rectSize; x += rectSize) {
          ofColor c;
          if ( ofGetKeyPressed() ) {
            c.setHsb( ofRandom(255), ofRandom(100,255), ofRandom(100,255), alpha );
          } else {
            c.setHsb( ofRandom(255), 0, ofRandom(255), alpha );
          }
          ofSetColor(c);
          ofDrawRectangle(x, y, rectSize*2, rectSize*2);
        }
      }
      ofPopMatrix();
      break;
    }
      
    case PS_SCREEN_RIGHT:
    {
      ofPushMatrix();
      ofTranslate( SCREEN_LR_WIDTH/2, SCREEN_LR_HEIGHT/2);
      for (int y = -SCREEN_LR_HEIGHT/2; y < SCREEN_LR_HEIGHT/2 + rectSize; y += rectSize) {
        for (int x = -SCREEN_LR_WIDTH/2; x < SCREEN_LR_WIDTH/2 + rectSize; x += rectSize) {
          ofColor c;
          if ( ofGetKeyPressed() ) {
            c.setHsb( ofRandom(255), ofRandom(100,255), ofRandom(100,255), alpha );
          } else {
            c.setHsb( ofRandom(255), 0, ofRandom(255), alpha );
          }
          ofSetColor(c);
          ofDrawRectangle(x, y, rectSize*2, rectSize*2);
        }
      }
      ofPopMatrix();
      break;
    }
    default:
      break;
  }
}


void Seun::modeOpening_seq2_rectRythm( PSystemScreen screen ) {
  // init
  static bool init = true;
  static vector<ofColor> colors;
  static float keyCount = 8;
  static int keyInterval = 50;
  
  if (init) {
    init = false;
    for (int y = -SCREEN_CENTER_HEIGHT/2; y < SCREEN_CENTER_HEIGHT/2; y += 4) {
      for (int x = -SCREEN_CENTER_WIDTH/2; x < SCREEN_CENTER_WIDTH/2; x += 4) {
        ofColor c;
        c.setHsb( ofRandom(255), ofRandom(50,255), ofRandom(50,255) );
        colors.push_back( c );
      }
    }
  }
  
  // draw
  float rectSize = SCREEN_CENTER_WIDTH*2 / keyCount;
  
  if (ofGetKeyPressed() && keyInterval <= 0) {
    keyInterval = 50;
    keyCount /= 2;
    if (keyCount == 0.5) {
      keyCount = 8;
    }
    rectSize = SCREEN_CENTER_WIDTH*2 / keyCount;
    colors.clear();
    for (int y = -SCREEN_CENTER_HEIGHT/2; y < SCREEN_CENTER_HEIGHT/2 + rectSize; y += rectSize) {
      for (int x = -SCREEN_CENTER_WIDTH/2; x < SCREEN_CENTER_WIDTH/2 + rectSize; x += rectSize) {
        ofColor c;
        c.setHsb( ofRandom(255), ofRandom(50,255), ofRandom(50,255) );
        colors.push_back( c );
      }
    }
  }
  
  if (keyInterval > 0) {
    keyInterval--;
  } else {
    keyInterval = 0;
  }
  
  
  switch ( screen ) {
    case PS_SCREEN_CENTER:
    {
      ofPushMatrix();
      ofTranslate( SCREEN_CENTER_WIDTH/2, SCREEN_CENTER_HEIGHT/2);
      int index = 0;
      for (int y = -SCREEN_CENTER_HEIGHT/2; y < SCREEN_CENTER_HEIGHT/2 + rectSize; y += rectSize) {
        for (int x = -SCREEN_CENTER_WIDTH/2; x < SCREEN_CENTER_WIDTH/2 + rectSize; x += rectSize) {
          ofSetColor( colors[index] );
          ofDrawRectangle(x, y, rectSize*2, rectSize*2);
          index++;
        }
      }
      ofPopMatrix();
      break;
    }
    case PS_SCREEN_LEFT:
    {
      ofPushMatrix();
      ofTranslate( SCREEN_LR_WIDTH/2, SCREEN_LR_HEIGHT/2);
      int index = 0;
      for (int y = -SCREEN_LR_HEIGHT/2; y < SCREEN_LR_HEIGHT/2 + rectSize; y += rectSize) {
        for (int x = -SCREEN_LR_WIDTH/2; x < SCREEN_LR_WIDTH/2 + rectSize; x += rectSize) {
          ofSetColor( colors[index+5] );
          ofDrawRectangle(x, y, rectSize*2, rectSize*2);
          index++;
        }
      }
      ofPopMatrix();
      break;
    }
    case PS_SCREEN_RIGHT:
    {
      ofPushMatrix();
      ofTranslate( SCREEN_LR_WIDTH/2, SCREEN_LR_HEIGHT/2);
      int index = 0;
      for (int y = -SCREEN_LR_HEIGHT/2; y < SCREEN_LR_HEIGHT/2 + rectSize; y += rectSize) {
        for (int x = -SCREEN_LR_WIDTH/2; x < SCREEN_LR_WIDTH/2 + rectSize; x += rectSize) {
          ofSetColor( colors[index+10] );
          ofDrawRectangle(x, y, rectSize*2, rectSize*2);
          index++;
        }
      }
      ofPopMatrix();
      break;
    }
    default:
    {
      break;
    }
  }
}


void Seun::modeOpening_seq3_circleRythm( PSystemScreen screen ) {
  static int keyInterval = 50;
  
  if (prevSequence != sequence && pSystems.size() == 0) {
    modeOpening_init();
  }
  
  if (ofGetKeyPressed() && keyInterval <= 0) {
    keyInterval = 50;
    // CENTER
    pSystems[0].particles.push_back( Particle()
                                    .position( ofPoint(ofRandom(-150,150),ofRandom(-150,150)) )
                                    .velocity( ofPoint(ofRandom(-1.5,1.5),ofRandom(-1.5,1.5)) )
                                    .setMass( ofRandom(5,15) )
                                    .setLifeReduction( ofRandom(0.007, 0.008) )
                                    .setScaleLifeTarget( 0.0, ofRandom(10.0,50.0) )
                                    .setScaleSine(0.0, 0.0)
                                    );
    pSystems[1].particles.push_back( Particle()
                                    .position( ofPoint(SCREEN_LR_WIDTH/2,0) )
                                    .velocity( ofPoint(ofRandom(-3,-6),ofRandom(-2,2)) )
                                    .setMass( ofRandom(5,30) )
                                    .setLifeReduction( ofRandom(0.001, 0.01) )
                                    );
    pSystems[2].particles.push_back( Particle()
                                    .position( ofPoint(-SCREEN_LR_WIDTH/2,0) )
                                    .velocity( ofPoint(ofRandom(3,6),ofRandom(-2,2)) )
                                    .setMass( ofRandom(5,30) )
                                    .setLifeReduction( ofRandom(0.001, 0.01) )
                                    );
  }
  if (keyInterval > 0) {
    keyInterval--;
  } else {
    keyInterval = 0;
  }
  
  // draw
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
    default:
    {
      break;
    }
  }
}


void Seun::modeOpening_seq4_circleAttraction( PSystemScreen screen ) {
  // init
  static int keyInterval = 50;
  
  if (prevSequence != sequence && pSystems.size() == 0) {
    modeOpening_init();
  }
  
  if (ofGetKeyPressed() && keyInterval <= 0) {
    keyInterval = 50;
    // CENTER
    pSystems[0].particles.push_back( Particle()
                                    .position( ofPoint(ofRandom(-30,30),ofRandom(-30,30)) )
                                    .velocity( ofPoint(0,0) )
                                    .setMass( ofRandom(1, 60) )
                                    .setLifeReduction( ofRandom(0.002, 0.004) )
                                    );
    // LEFT
    pSystems[1].particles.push_back( Particle()
                                    .position( ofPoint(-SCREEN_LR_WIDTH/2,ofRandom(-SCREEN_LR_HEIGHT/2, SCREEN_LR_HEIGHT/2)) )
                                    .velocity( ofPoint(ofRandom(3,6),ofRandom(-2,2)) )
                                    .setMass( ofRandom(5,30) )
                                    .setLifeReduction( ofRandom(0.001, 0.01) )
                                    );
    // RIGHT
    pSystems[2].particles.push_back( Particle()
                                    .position( ofPoint(SCREEN_LR_WIDTH/2,ofRandom(-SCREEN_LR_HEIGHT/2, SCREEN_LR_HEIGHT/2)) )
                                    .velocity( ofPoint(ofRandom(-3,-6),ofRandom(-2,2)) )
                                    .setMass( ofRandom(5,30) )
                                    .setLifeReduction( ofRandom(0.001, 0.01) )
                                    );
    pSystems[2].particles[0].pos.x;
  }
  if (keyInterval > 0) {
    keyInterval--;
  } else {
    keyInterval = 0;
  }
  
  // draw
  switch ( screen ) {
    case PS_SCREEN_CENTER:
    {
      ParticleSystem &ps = pSystems[0];
      for (auto &p : ps.particles) {
        
        p.applyAttraction( ofPoint(0,0), 0.05);
        for (auto &other : ps.particles) {
          if (&p != &other) {
            p.checkCollision( other, 0.5);
          }
        }
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
    default:
    {
      break;
    }
  }
}


void Seun::modeOpening_seq5_circleRepultion( PSystemScreen screen ) {
  // init
  static int keyInterval = 50;
  
  if (prevSequence != sequence && pSystems.size() == 0) {
    modeOpening_init();
  }

  if (ofRandom(1) < 0.1) {
    keyInterval = 50;
    // CENTER
    pSystems[0].particles.push_back( Particle()
                                    .position( ofPoint(ofRandom(-30,30),ofRandom(-30,30)) )
                                    .velocity( ofPoint(ofRandom(-3,3),ofRandom(-3,3)) )
                                    .setMass( ofRandom(3, 30) )
                                    .setLifeReduction( 0.003 )
                                    );
    // LEFT
    pSystems[1].particles.push_back( Particle()
                                    .position( ofPoint(SCREEN_LR_WIDTH/2,ofRandom(-SCREEN_LR_HEIGHT/2, SCREEN_LR_HEIGHT/2)) )
                                    .velocity( ofPoint(ofRandom(-3,-6),ofRandom(-3,3)) )
                                    .setMass( ofRandom(2,15) )
                                    .setLifeReduction( 0.003 )
                                    );
    // RIGHT
    pSystems[2].particles.push_back( Particle()
                                    .position( ofPoint(-SCREEN_LR_WIDTH/2,ofRandom(-SCREEN_LR_HEIGHT/2, SCREEN_LR_HEIGHT/2)) )
                                    .velocity( ofPoint(ofRandom(3,6),ofRandom(-3,3)) )
                                    .setMass( ofRandom(2,15) )
                                    .setLifeReduction( 0.003 )
                                    );
    
  }
  if (keyInterval > 0) {
    keyInterval--;
  } else {
    keyInterval = 0;
  }
  
  // draw
  switch ( screen ) {
    case PS_SCREEN_CENTER:
    {
      ParticleSystem &ps = pSystems[0];
      for (auto &p : ps.particles) {
        for (auto &other : ps.particles) {
          if (&p != &other) {
            p.applyGravitation(other, G_attraction);
            //p.checkCollision( other, 0.5);
          }
        }
        p.applyForce( ofPoint(0,G_gravity*p.mass) );
        p.updateLifespan();
        p.reduceLifespan();
        p.update();
        p.checkBoundaries( ps.boundary.x, ps.boundary.y );
      }
      ps.removeParticles();
      break;
    }
    case PS_SCREEN_LEFT:
    {
      ParticleSystem &ps = pSystems[1];
      for (auto &p : ps.particles) {
        for (auto &other : ps.particles) {
          if (&p != &other) {
            p.applyGravitation(other, G_attraction);
            //p.checkCollision( other, 0.5);
          }
        }
        p.applyForce( ofPoint(0,G_gravity*p.mass) );
        p.updateLifespan();
        p.reduceLifespan();
        p.update();
        p.checkBoundaries( ps.boundary.x, ps.boundary.y );
      }
      ps.removeParticles();
      break;
    }
    case PS_SCREEN_RIGHT:
    {
      ParticleSystem &ps = pSystems[2];
      for (auto &p : ps.particles) {
        for (auto &other : ps.particles) {
          if (&p != &other) {
            p.applyGravitation(other, G_attraction);
            //p.checkCollision( other, 0.5);
          }
        }
        p.applyForce( ofPoint(0,G_gravity*p.mass) );
        p.updateLifespan();
        p.reduceLifespan();
        p.update();
        p.checkBoundaries( ps.boundary.x, ps.boundary.y );
      }
      ps.removeParticles();
      break;
    }
    default:
    {
      break;
    }
  }
}


void Seun::modeOpening_seq6_fireworks( PSystemScreen screen ) {
  
  static int keyInterval = 50;

  if (prevSequence != sequence) {
    if (pSystems.size() == 0) {
      modeOpening_init();
    }
    else if (pSystems.size() > 0) {
      for(auto &ps : pSystems) {
        for (auto &p : ps.particles) {
          p.setLifeReduction( ofRandom(0.01, 0.05) );
        }
      }
    }
  }
  
  if (ofGetMousePressed() && keyInterval <= 0) {
    ofPoint mouse = getScaledMouse();
//    pSystems[mouse.z].particles.push_back( Particle()
//                                          .position( ofPoint(mouse.x, mouse.y) )
//                                          //.velocity( ofPoint(ofRandom(-3,3),ofRandom(-3,3)) )
//                                          .setMass( ofRandom(3, 30) )
//                                          .setLifeReduction( 0.003 )
//                                          );
    if (mouse.z == 0) {
      int fireworkIndex = int(ofRandom(fireworks.size()));
      pSystems.push_back( ParticleSystem( PS_MODE_FIREWORK, PS_SCREEN_CENTER )
                         .addFireworkData( fireworks[fireworkIndex] )
                         .position( ofPoint(SCREEN_CENTER_WIDTH/2 + mouse.x, SCREEN_CENTER_HEIGHT/2 + mouse.y/2) )
                         .init()
                         );
    } else if (mouse.z == 1) {
      int fireworkIndex = int(ofRandom(fireworks.size()));
      pSystems.push_back( ParticleSystem( PS_MODE_FIREWORK, PS_SCREEN_LEFT )
                         .addFireworkData( fireworks[fireworkIndex] )
                         .position( ofPoint(SCREEN_LR_WIDTH/2 + mouse.x, SCREEN_LR_HEIGHT/2 + mouse.y/2) )
                         .init()
                         );
    } else if (mouse.z == 2) {
      int fireworkIndex = int(ofRandom(fireworks.size()));
      pSystems.push_back( ParticleSystem( PS_MODE_FIREWORK, PS_SCREEN_RIGHT )
                         .addFireworkData( fireworks[fireworkIndex] )
                         .position( ofPoint(SCREEN_LR_WIDTH/2 + mouse.x, SCREEN_LR_HEIGHT/2 + mouse.y/2) )
                         .init()
                         );
    }
    keyInterval = 50;
  }
  if (keyInterval > 0) {
    keyInterval--;
  } else {
    keyInterval = 0;
  }
  
  
  
  // draw
  switch ( screen ) {
    case PS_SCREEN_CENTER:
    {
      //normal
      ParticleSystem &ps = pSystems[0];
      for (auto &p : ps.particles) {
        for (auto &other : ps.particles) {
          if (&p != &other) {
            p.applyGravitation(other, G_attraction);
            //p.checkCollision( other, 0.5);
          }
        }
        p.applyForce( ofPoint(0,G_gravity*p.mass) );
        p.updateLifespan();
        p.reduceLifespan();
        p.update();
        p.checkBoundaries( ps.boundary.x, ps.boundary.y );
      }
      ps.removeParticles();
      //firework
      for (int i=3; i<pSystems.size(); i++) {
        if (pSystems[i].screen == PS_SCREEN_CENTER) {
          pSystems[i].update();
        }
      }
      break;
    }
    case PS_SCREEN_LEFT:
    {
      ParticleSystem &ps = pSystems[1];
      for (auto &p : ps.particles) {
        for (auto &other : ps.particles) {
          if (&p != &other) {
            p.applyGravitation(other, G_attraction);
            //p.checkCollision( other, 0.5);
          }
        }
        p.applyForce( ofPoint(0,G_gravity*p.mass) );
        p.updateLifespan();
        p.reduceLifespan();
        p.update();
        p.checkBoundaries( ps.boundary.x, ps.boundary.y );
      }
      ps.removeParticles();
      //firework
      for (int i=3; i<pSystems.size(); i++) {
        if (pSystems[i].screen == PS_SCREEN_LEFT) {
          pSystems[i].update();
        }
      }
      break;
    }
    case PS_SCREEN_RIGHT:
    {
      ParticleSystem &ps = pSystems[2];
      for (auto &p : ps.particles) {
        for (auto &other : ps.particles) {
          if (&p != &other) {
            p.applyGravitation(other, G_attraction);
            //p.checkCollision( other, 0.5);
          }
        }
        p.applyForce( ofPoint(0,G_gravity*p.mass) );
        p.updateLifespan();
        p.reduceLifespan();
        p.update();
        p.checkBoundaries( ps.boundary.x, ps.boundary.y );
      }
      ps.removeParticles();
      //firework
      for (int i=3; i<pSystems.size(); i++) {
        if (pSystems[i].screen == PS_SCREEN_RIGHT) {
          pSystems[i].update();
        }
      }
      break;
    }
    default:
    {
      break;
    }
  }
  
  // remove only fireworks;
  for(int i=int(pSystems.size()-1); i>=3; i--) {
    if (pSystems[i].particles.size() == 0) {
      pSystems.erase(pSystems.begin()+i);
    }
  }
}



//void Seun::modeOpening_seq2_rectRythm( PSystemScreen screen ) {
//  switch ( screen ) {
//    case PS_SCREEN_CENTER:
//    {
//      break;
//    }
//    case PS_SCREEN_LEFT:
//    {
//      break;
//    }
//    case PS_SCREEN_RIGHT:
//    {
//      break;
//    }
//    default:
//    {
//      break;
//    }
//  }
//}

































//
