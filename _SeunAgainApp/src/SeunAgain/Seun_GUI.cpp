//
//  Seun_GUI.cpp
//  SeunAgain
//
//  Created by MOQN on 10/23/17.
//

#include "Seun.h"


void Seun::setupGUI() {
  mainParameters.setName("Setting");
  mainParameters.add( guiDisplayMode.set("DisplayMode", 1, 0, 3) );
  mainParameters.add( guiOffsetX.set("xOffset", 0, -1200, 1200) );
  mainParameters.add( guiScale.set("Scale", 0.48, 0.35, 1.0) );
  mainParameters.add( guiMainMode.set("Mode", INIT_MODE, 0, 6) );
  mainParameters.add( guiSyphonToggle.set("Syphon", false) );
  mainParameters.add( guiWebsocketToggle.set("Websocket", false) );
  // Opening
  mainParameters.add( guiAttraction.set("Attraction", 0, -300, 300) );
  mainParameters.add( guiGravity.set("Gravity", 0, -1.5, 3.0) );
  // Closing
  mainParameters.add( guiDepth.set("Depth", 0, 0.0001, 1.0) );
  mainParameters.add( guiAlpha.set("Alpha", 255.0, 0.0, 255.0) );
  mainParameters.add( guiBallRad.set("BallRad", 6.5, 2.5, 6.5) );
  mainParameters.add( guiBallAttraction.set("BallAttraction", 0.01, 0.01, 0.1) );
  mainParameters.add( guiBallCollision.set("BallCollision", 1.5, 0.1, 3.0) );
  mainParameters.add( guiRotationVelY.set("RotationY", 0.0, 0.0, 1.0) );
  mainParameters.add( guiRotationVelX.set("RotationX", 0.0, 0.0, 0.1) );
  
  
  mainGui.setup(mainParameters);
  mainGui.setPosition(ofGetWidth() - GUI_WIDTH, 0);
}

void Seun::updateGUI() {
  // update mode
  if (guiMainMode != prevMainMode) {
    changeMode( guiMainMode );
  }
  prevMainMode = guiMainMode;
  G_attraction = ofLerp(G_attraction, guiAttraction, 0.01);
  G_gravity = ofLerp(G_gravity, guiGravity, 0.005);
  G_depth = ofLerp(G_depth, guiDepth, 0.001);
  G_alpha = ofLerp(G_alpha, guiAlpha, 0.01);
  
  G_rotVelX = ofLerp(G_rotVelX, guiRotationVelX, 0.005);
  G_rotVelY = ofLerp(G_rotVelY, guiRotationVelY, 0.005);
}
