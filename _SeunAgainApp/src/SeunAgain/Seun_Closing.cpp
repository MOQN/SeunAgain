//
//  Seun_Closing.cpp
//  SeunAgain
//
//  Created by MOQN on 10/25/17.
//


#include "Seun.h"

// Mode: Closing
void Seun::modeClosing_init() {
  modeChanged = false;
  ofSetSphereResolution(8);
  pSystems.clear();
  pSystems.push_back( ParticleSystem( PS_MODE_3D, PS_SCREEN_CENTER )
                     .position( ofPoint(0,0) )
                     .setBoundary( ofPoint(SCREEN_CENTER_WIDTH, SCREEN_CENTER_HEIGHT) )
                     );
  pSystems.push_back( ParticleSystem( PS_MODE_3D, PS_SCREEN_LR )
                     .position( ofPoint(0,0) )
                     .setBoundary( ofPoint(SCREEN_LR_WIDTH, SCREEN_LR_HEIGHT) )
                     );
  pSystems.push_back( ParticleSystem( PS_MODE_3D, PS_SCREEN_LR )
                     .position( ofPoint(0,0) )
                     .setBoundary( ofPoint(SCREEN_LR_WIDTH, SCREEN_LR_HEIGHT) )
                     );
  pSystems.push_back( ParticleSystem( PS_MODE_3D, PS_SCREEN_CENTER )
                     .position( ofPoint(0,0) )
                     .setBoundary( ofPoint(SCREEN_CENTER_WIDTH, SCREEN_CENTER_HEIGHT) )
                     );
  pSystems.push_back( ParticleSystem( PS_MODE_3D, PS_SCREEN_LR )
                     .position( ofPoint(0,0) )
                     .setBoundary( ofPoint(SCREEN_LR_WIDTH, SCREEN_LR_HEIGHT) )
                     );
  pSystems.push_back( ParticleSystem( PS_MODE_3D, PS_SCREEN_LR )
                     .position( ofPoint(0,0) )
                     .setBoundary( ofPoint(SCREEN_LR_WIDTH, SCREEN_LR_HEIGHT) )
                     );
  pSystems.push_back( ParticleSystem( PS_MODE_3D, PS_SCREEN_LR )
                     .position( ofPoint(0,0) )
                     .setBoundary( ofPoint(SCREEN_CENTER_WIDTH, SCREEN_CENTER_HEIGHT) )
                     );
}

void Seun::modeClosing_display( PSystemScreen screen ) {
  ofPushStyle();
  
  // init
  static bool climax = false;
  static ofPoint origin = ofPoint(0,-SCREEN_CENTER_HEIGHT/2,0);
  static bool init = true;
  if (init) {
    camCenter.disableMouseInput();
    camCenter.setDistance( 1558.85 );
    camCenter.setFov( 60 );
    camLeft.disableMouseInput();
    camLeft.setDistance( 519.615 );
    camLeft.setFov( 60 );
    camRight.disableMouseInput();
    camRight.setDistance( 519.615 );
    camRight.setFov( 60 );
    init = false;
  }
  if (prevSequence != sequence) {
    climax = false;
  }
  
  // trigger
  static int triggerInterval = 50;
  if (triggerInterval > 0) {
    triggerInterval--;
  } else {
    triggerInterval = 0;
  }
  
  if ( ofGetKeyPressed() && triggerInterval <= 0 ) {
    if ( keyCode == ' ' ) {
      for (int i=0; i<3; i++) {
        for (auto &p : pSystems[i].particles) {
          p.applyForce( ofPoint( ofRandom(-50,50),ofRandom(-50,50),ofRandom(-50,50) ) );
        }
      }
      climax = true;
      triggerInterval = 50;
    }
    if ( keyCode == 'v' || keyCode == 'V' ) {
      int fireworkIndex = int(ofRandom(fireworks.size()));
      pSystems.push_back( ParticleSystem( PS_MODE_FIREWORK_3D, PS_SCREEN_CENTER )
                         .addFireworkData( fireworks[fireworkIndex] )
                         .position( ofPoint(0,0,0) )
                         .init()
                         );
      triggerInterval = 50;
    }
  }
  if (ofGetMousePressed() && triggerInterval <= 0) {
    ofPoint mouse = getScaledMouse();
    
    //if (mouse.z == 0) {
    //
    //}
    //    else if (mouse.z == 1) {
    //      int fireworkIndex = int(ofRandom(fireworks.size()));
    //      pSystems.push_back( ParticleSystem( PS_MODE_FIREWORK_3D, PS_SCREEN_LEFT )
    //                         .addFireworkData( fireworks[fireworkIndex] )
    //                         .position( ofPoint(SCREEN_LR_WIDTH/2 + mouse.x, SCREEN_LR_HEIGHT/2 + mouse.y/2) )
    //                         .init()
    //                         );
    //    } else if (mouse.z == 2) {
    //      int fireworkIndex = int(ofRandom(fireworks.size()));
    //      pSystems.push_back( ParticleSystem( PS_MODE_FIREWORK_3D, PS_SCREEN_RIGHT )
    //                         .addFireworkData( fireworks[fireworkIndex] )
    //                         .position( ofPoint(SCREEN_LR_WIDTH/2 + mouse.x, SCREEN_LR_HEIGHT/2 + mouse.y/2) )
    //                         .init()
    //                         );
    //    }
    
    triggerInterval = 50;
  }
  
  // update Angles
  rotationAngle.x += G_rotVelX;
  rotationAngle.y += G_rotVelY;
  
  // update
  if (bgmClosing.getPosition() > 0.00 && bgmClosing.getPosition() < 0.38) {
    // generate Paticles
    int startingHeight = 200;
    float randomness = ofMap(bgmClosing.getPosition(), 0.0, 0.38, 0.002, 0.025);
    if (ofRandom(1) < randomness) {
      pSystems[0].particles.push_back( Particle()
                                      .position( ofPoint(ofRandom(-SCREEN_CENTER_WIDTH/2, SCREEN_CENTER_WIDTH/2), SCREEN_CENTER_HEIGHT/2 + startingHeight, 0) )
                                      .setColor( ofColor( ofRandom(50,255) ) )
                                      .velocity( ofPoint(0,ofRandom(-3,3), ofRandom(-3,3)*G_depth) )
                                      .setAngle( ofPoint(ofRandom(360)*G_depth,ofRandom(360)*G_depth,ofRandom(360)) )
                                      .setAngleVelocity( ofPoint(ofRandom(-1,1)*G_depth,ofRandom(-1,1)*G_depth,ofRandom(-1,1)) )
                                      .setMass( ofRandom(1, 6) * ofRandom(1, 6) )
                                      .setLifeReduction( ofRandom(0.0005, 0.003) )
                                      );
      pSystems[1].particles.push_back( Particle()
                                      .position( ofPoint(ofRandom(-SCREEN_LR_WIDTH/2, SCREEN_LR_WIDTH/2), SCREEN_LR_HEIGHT/2 + startingHeight, 0) )
                                      .setColor( ofColor( ofRandom(50,255) ) )
                                      .velocity( ofPoint(0,ofRandom(-3,3), ofRandom(-3,3)*G_depth) )
                                      .setAngle( ofPoint(ofRandom(360)*G_depth,ofRandom(360)*G_depth,ofRandom(360)) )
                                      .setAngleVelocity( ofPoint(ofRandom(-1,1)*G_depth,ofRandom(-1,1)*G_depth,ofRandom(-1,1)) )
                                      .setMass( ofRandom(1, 5) * ofRandom(1, 5) )
                                      .setLifeReduction( ofRandom(0.0005, 0.003) )
                                      );
      pSystems[2].particles.push_back( Particle()
                                      .position( ofPoint(ofRandom(-SCREEN_LR_WIDTH/2, SCREEN_LR_WIDTH/2), SCREEN_LR_HEIGHT/2 + startingHeight, 0) )
                                      .setColor( ofColor( ofRandom(50,255) ) )
                                      .velocity( ofPoint(0,ofRandom(-3,3), ofRandom(-3,3)*G_depth) )
                                      .setAngle( ofPoint(ofRandom(360)*G_depth,ofRandom(360)*G_depth,ofRandom(360)) )
                                      .setAngleVelocity( ofPoint(ofRandom(-1,1)*G_depth,ofRandom(-1,1)*G_depth,ofRandom(-1,1)) )
                                      .setMass( ofRandom(1, 5) * ofRandom(1, 5) )
                                      .setLifeReduction( ofRandom(0.0005, 0.003) )
                                      );
    }
  }
  if (bgmClosing.getPosition() > 0.35 && bgmClosing.getPosition() < 0.43) {
    if (ofRandom(1) < 0.02) {
      pSystems[3].particles.push_back( Particle()
                                      .position( ofPoint(ofRandom(-SCREEN_CENTER_WIDTH * 2, SCREEN_CENTER_WIDTH * 2),
                                                         ofRandom(-SCREEN_CENTER_HEIGHT, SCREEN_CENTER_HEIGHT ),
                                                         -SCREEN_CENTER_WIDTH) )
                                      .setColor( ofColor( ofRandom(100,150) ) )
                                      .velocity( ofPoint(0,0, ofRandom(-3,-10)) )
                                      .setMass( ofRandom(5, 15) )
                                      .setLifeReduction( 0.002 )
                                      );
      pSystems[4].particles.push_back( Particle()
                                      .position( ofPoint(ofRandom(-SCREEN_LR_WIDTH * 3, SCREEN_LR_WIDTH * 3),
                                                         ofRandom(-SCREEN_LR_WIDTH * 2, SCREEN_LR_WIDTH * 2),
                                                         -SCREEN_LR_WIDTH) )
                                      .setColor( ofColor( ofRandom(100,150) ) )
                                      .velocity( ofPoint(0,0, ofRandom(-3,-10)) )
                                      .setMass( ofRandom(10, 30) )
                                      .setLifeReduction( 0.002 )
                                      );
      pSystems[5].particles.push_back( Particle()
                                      .position( ofPoint(ofRandom(-SCREEN_LR_WIDTH * 3, SCREEN_LR_WIDTH * 3),
                                                         ofRandom(-SCREEN_LR_WIDTH * 2, SCREEN_LR_WIDTH * 2),
                                                         -SCREEN_LR_WIDTH) )
                                      .setColor( ofColor( ofRandom(100,150) ) )
                                      .velocity( ofPoint(0,0, ofRandom(-3,-10)) )
                                      .setMass( ofRandom(10, 30) )
                                      .setLifeReduction( 0.002 )
                                      );
    }
  }
  if (bgmClosing.getPosition() > 0.49 ) {
    if (ofRandom(1) < 0.1) {
      pSystems[3].particles.push_back( Particle()
                                      .position( ofPoint(ofRandom(-SCREEN_CENTER_WIDTH * 2, SCREEN_CENTER_WIDTH * 2),
                                                         ofRandom(-SCREEN_CENTER_HEIGHT * 2, 0),
                                                         ofRandom(-SCREEN_CENTER_WIDTH * 2, SCREEN_CENTER_WIDTH * 2)) )
                                      .setColor( ofColor( ofRandom(50,255),ofRandom(50,255),ofRandom(50,255) ) )
                                      .velocity( ofPoint(0, ofRandom(0.5,2), 0) )
                                      .setMass( ofRandom(2, 6) )
                                      .setScaleSine(ofRandom(0.02, 0.04), 0.1)
                                      .setLifeReduction( 0.002 )
                                      );
      pSystems[4].particles.push_back( Particle()
                                      .position( ofPoint(ofRandom(-SCREEN_LR_WIDTH * 2, SCREEN_LR_WIDTH * 2),
                                                         ofRandom(-SCREEN_LR_HEIGHT*2, -SCREEN_LR_HEIGHT),
                                                         ofRandom(-SCREEN_LR_WIDTH * 2, SCREEN_LR_WIDTH * 2)) )
                                      .setColor( ofColor( ofRandom(50,255),ofRandom(50,255),ofRandom(50,255) ) )
                                      .velocity( ofPoint(0, ofRandom(1,4), 0) )
                                      .setMass( ofRandom(3, 10) )
                                      .setScaleSine(ofRandom(0.02, 0.04), 0.1)
                                      .setLifeReduction( 0.002 )
                                      );
      pSystems[5].particles.push_back( Particle()
                                      .position( ofPoint(ofRandom(-SCREEN_LR_WIDTH * 2, SCREEN_LR_WIDTH * 2),
                                                         ofRandom(-SCREEN_LR_HEIGHT*2, -SCREEN_LR_HEIGHT),
                                                         ofRandom(-SCREEN_LR_WIDTH * 2, SCREEN_LR_WIDTH * 2)) )
                                      .setColor( ofColor( ofRandom(50,255),ofRandom(50,255),ofRandom(50,255) ) )
                                      .velocity( ofPoint(0, ofRandom(1,4), 0) )
                                      .setMass( ofRandom(3, 10) )
                                      .setScaleSine(ofRandom(0.02, 0.04), 0.1)
                                      .setLifeReduction( 0.002 )
                                      );
    }
  }
  if (climax && pSystems[6].particles.size() < 400 && pSystems.size() <= 7) {
    //origin
    if (origin.y < 100) {
      origin.y+=0.5;
    } else {
      origin.y = 100;
    }
    
    if (ofRandom(1) < 0.1) {
      ofPoint pos;
      if (bgmClosing.getPosition() < 0.80) {
        pos = origin;
      } else {
        pos = ofPoint(ofRandom(-SCREEN_CENTER_HEIGHT,SCREEN_CENTER_HEIGHT),
                      ofRandom(-SCREEN_CENTER_HEIGHT,SCREEN_CENTER_HEIGHT),
                      ofRandom(-SCREEN_CENTER_HEIGHT,SCREEN_CENTER_HEIGHT)
                      );
      }
      pSystems[6].particles.push_back( Particle()
                                      .position( pos )
                                      .setColor( ofColor(ofRandom(50,255),ofRandom(50,255),ofRandom(50,255)) )
                                      .velocity( ofPoint(ofRandom(-1,1), ofRandom(-1,1), ofRandom(-1,1)) )
                                      .setAngle( ofPoint(ofRandom(360)*G_depth,ofRandom(360)*G_depth,ofRandom(360)) )
                                      .setAngleVelocity( ofPoint(ofRandom(-1,1)*G_depth,ofRandom(-1,1)*G_depth,ofRandom(-1,1)) )
                                      .setMass( ofRandom(1, guiBallRad) * ofRandom(1, guiBallRad) )
                                      .setScaleLifeTarget(1.0, 0.0)
                                      .setLifeReduction( ofRandom(0.001, 0.002) )
                                      );
    }
  }
  
  
  // draw
  switch ( screen ) {
    case PS_SCREEN_CENTER:
    {
      // update
      camCenter.setDistance( 1558.85 + G_depth * 500);
      // draw
      camCenter.begin();
      ofEnableDepthTest();
      ofEnableAlphaBlending();
      
      ofRotateX( rotationAngle.x );
      ofRotateY( rotationAngle.y );
      
      // CENTER - falling rects
      {
        ParticleSystem &ps = pSystems[0];
        for (auto &p : ps.particles) {
          if (!climax) {
            ofPoint gravity = ofPoint(0,-1,0);
            p.applyForce(gravity);
            p.checkBottomOnly(SCREEN_CENTER_HEIGHT);
            p.applyRestitution(0.97);
          } else {
            p.updateLifespan();
            p.reduceLifespan();
            p.applyRestitution(0.99);
          }
          for (auto &other : ps.particles) {
            if (&p != &other) {
              p.checkCollision( other, 0.6 );
            }
          }
          p.update();
          p.updateAngle();
          p.display3D( P_SHAPE_BOX, G_alpha );
        }
        if (climax) ps.removeParticles();
      }
      // CENTER - random rects
      {
        ParticleSystem &ps = pSystems[3];
        for (auto &p : ps.particles) {
          p.update();
          p.updateLifespan();
          p.reduceLifespan();
          if (bgmClosing.getPosition() < 0.48) {
            p.display3D( P_SHAPE_BOX, 0 );
          } else {
            p.display3D( P_SHAPE_SPHERE, G_alpha );
          }
        }
        ps.removeParticles();
      }
      // CENTER - climax
      {
        ParticleSystem &ps = pSystems[6];
        for (auto &p : ps.particles) {
          p.applyAttraction( origin, guiBallAttraction );
          for (auto &other : ps.particles) {
            if (&p != &other) {
              p.checkCollision( other, guiBallCollision );
            }
          }
          p.update();
          p.applyRestitution(0.9);
          p.updateLifespan();
          p.reduceLifespan();
          p.display3D( P_SHAPE_SPHERE, G_alpha );
        }
        ps.removeParticles();
      }
      // CENTER: Firework
      {
        for (int i=7; i<pSystems.size(); i++) {
          for (auto &p : pSystems[i].particles) {
            p.pos.z = ofRandom(-3,3);
            p.display3D( P_SHAPE_BOX, 255 );
          }
        }
      }
      
      ofDisableAlphaBlending();
      ofDisableDepthTest();
      camCenter.end();
      camCenter.draw();
      break;
    }
    case PS_SCREEN_LEFT:
    {
      camLeft.begin();
      ofEnableDepthTest();
      ofEnableAlphaBlending();
      
      ofRotateX( rotationAngle.x );
      ofRotateY( rotationAngle.y );
      
      // LEFT - falling rects
      {
        ParticleSystem &ps = pSystems[1];
        for (auto &p : ps.particles) {
          if (!climax) {
            ofPoint gravity = ofPoint(0,-1,0);
            p.applyForce(gravity);
            p.checkBottomOnly(SCREEN_CENTER_HEIGHT);
            p.applyRestitution(0.97);
          } else {
            p.updateLifespan();
            p.reduceLifespan();
            p.applyRestitution(0.99);
          }
          for (auto &other : ps.particles) {
            if (&p != &other) {
              p.checkCollision( other, 0.6 );
            }
          }
          p.update();
          p.updateAngle();
          p.display3D( P_SHAPE_BOX, G_alpha );
        }
        if (climax) ps.removeParticles();
      }
      // LEFT - random rects
      {
        ParticleSystem &ps = pSystems[4];
        for (auto &p : ps.particles) {
          p.update();
          p.updateLifespan();
          p.reduceLifespan();
          if (bgmClosing.getPosition() < 0.48) {
            p.display3D( P_SHAPE_BOX, 0 );
          } else {
            p.display3D( P_SHAPE_SPHERE, G_alpha );
          }
        }
        ps.removeParticles();
      }
      
      ofDisableAlphaBlending();
      ofDisableDepthTest();
      camLeft.end();
      camLeft.draw();
      break;
    }
    case PS_SCREEN_RIGHT:
    {
      camRight.begin();
      ofEnableDepthTest();
      ofEnableAlphaBlending();
      
      ofRotateX( rotationAngle.x );
      ofRotateY( rotationAngle.y );
      
      // RIGHT - falling rects
      {
        ParticleSystem &ps = pSystems[2];
        for (auto &p : ps.particles) {
          if (!climax) {
            ofPoint gravity = ofPoint(0,-1,0);
            p.applyForce(gravity);
            p.checkBottomOnly(SCREEN_CENTER_HEIGHT);
            p.applyRestitution(0.97);
          } else {
            p.updateLifespan();
            p.reduceLifespan();
            p.applyRestitution(0.99);
          }
          for (auto &other : ps.particles) {
            if (&p != &other) {
              p.checkCollision( other, 0.6 );
            }
          }
          p.update();
          p.updateAngle();
          p.display3D( P_SHAPE_BOX, G_alpha );
        }
        if (climax) ps.removeParticles();
      }
      // RIGHT - random rects
      {
        ParticleSystem &ps = pSystems[5];
        for (auto &p : ps.particles) {
          p.update();
          p.updateLifespan();
          p.reduceLifespan();
          if (bgmClosing.getPosition() < 0.48) {
            p.display3D( P_SHAPE_BOX, 0 );
          } else {
            p.display3D( P_SHAPE_SPHERE, G_alpha );
          }
        }
        ps.removeParticles();
      }
      
      ofDisableAlphaBlending();
      ofDisableDepthTest();
      camRight.end();
      camRight.draw();
      break;
    }
    default:
    {
      break;
    }
  }
  
  ofPopStyle();
  prevSequence = sequence;
}






