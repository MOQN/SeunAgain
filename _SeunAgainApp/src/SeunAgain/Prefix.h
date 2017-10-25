//
//  Prefix.hpp
//  SeunAgain
//
//  Created by MOQN on 10/6/17.
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxSyphon.h"



// Macros
#define INIT_MODE 0
#define TEST_MODE 0
#define URL_IMAGE_ADJUSTMENT 0

#define RENDER_FBO_UNTIL 0

#define SIN_COS_RESOLUTION 1440  // 360 * 4

#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 900
#define SCREEN_CENTER_WIDTH 800
#define SCREEN_CENTER_HEIGHT 1800
#define SCREEN_LR_WIDTH 1500
#define SCREEN_LR_HEIGHT 600
#define SCREEN_GAP 30
#define GUI_WIDTH 200

#define SOUND_CIRCLE_PITCH 280
#define PARTICLE_SIZE 3


enum PSystemMode {
  PS_MODE_NORMAL,
  PS_MODE_SOUND,
  PS_MODE_3D,
  PS_MODE_FIREWORK,
  PS_MODE_FIREWORK_3D,
  PS_MODE_TEST
};
enum PSystemScreen {
  PS_SCREEN_CENTER,
  PS_SCREEN_LEFT,
  PS_SCREEN_RIGHT,
  PS_SCREEN_LR
};
enum ParticleShape {
  P_SHAPE_CIRCLE,
  P_SHAPE_PLANE,
  P_SHAPE_BOX,
  P_SHAPE_SPHERE,
  P_SHAPE_CONE,
  P_SHAPE_PIPE
};

extern array<float,SIN_COS_RESOLUTION> sinArray, cosArray;
extern float G_gravity, G_attraction, G_depth, G_alpha, G_rotVelX, G_rotVelY;

static void setupSinCos() {
  for (int i=0; i<SIN_COS_RESOLUTION; i++) {
    float radian = ofMap(i, 0,SIN_COS_RESOLUTION, 0, TWO_PI);
    sinArray[i] = sin(radian);
    cosArray[i] = cos(radian);
  }
}
static float mSin(float radian) {
  float r = ofWrap(radian, 0, TWO_PI);
  int index = floor(ofMap(r, 0, TWO_PI, 0,SIN_COS_RESOLUTION));
  return sinArray[index];
}

static float mCos(float radian) {
  float r = ofWrap(radian, 0, TWO_PI);
  int index = floor(ofMap(r, 0, TWO_PI, 0,SIN_COS_RESOLUTION));
  return cosArray[index];
}

static ofPoint mLerp(ofPoint start, ofPoint end, float amt) {
  return start + amt * (end - start);
}

static ofPoint mMap(ofPoint value, ofPoint inputMin, ofPoint inputMax, ofPoint outputMin, ofPoint outputMax) {
  float x = ofMap(value.x, inputMin.x, inputMax.x, outputMin.x, outputMax.x);
  float y = ofMap(value.y, inputMin.y, inputMax.y, outputMin.y, outputMax.y);
  float z = ofMap(value.z, inputMin.z, inputMax.z, outputMin.z, outputMax.z);
  return ofPoint(x,y,z);
}

