//
//  Seun_GUI.cpp
//  SeunAgain
//
//  Created by MOQN on 10/23/17.
//

#include "Seun.h"


void Seun::setupGUI() {
  mainParameters.setName("Setting");
  mainParameters.add( guiMainMode.set("Mode", 0, 0, 9) );
  mainParameters.add( guiWebsocketToggle.set("Websocket", false) );
  mainParameters.add( guiSyphonToggle.set("Syphon", false) );
  mainParameters.add( guiDisplayMode.set("DisplayMode", 1, 0, 3) );
  mainParameters.add( guiScale.set("Scale", 0.48, 0.35, 1.0) );
  mainParameters.add( guiOffsetX.set("X-Offset", 0, -1200, 1200) );
  //
  mainParameters.add( guiAttaction.set("Attraction", 0, -300, 300) );
  mainParameters.add( guiGravity.set("Gravity", 0, -3, 3) );
  
  mainGui.setup(mainParameters);
  mainGui.setPosition(ofGetWidth() - GUI_WIDTH, 0);
}

void Seun::updateGUI() {
  // update mode
  if (guiMainMode != prevMainMode) {
    changeMode( guiMainMode );
  }
  prevMainMode = guiMainMode;
  G_attraction = ofLerp(G_attraction, guiAttaction, 0.01);
  G_gravity = ofLerp(G_gravity, guiGravity, 0.005);
}
