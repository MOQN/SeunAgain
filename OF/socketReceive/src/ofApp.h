#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        string incoming;
        vector<string> readyStr;
        int numP;
    
    class Particle{
    public:
        string id;
        ofPoint acc, vel, pos;
        ofColor col;
        float mass;
        
        Particle(string _id, ofPoint _pos, int hue){
            id = _id;
            pos = _pos;
//            vel = _vel;
            acc = ofPoint::zero();
            col.setHsb(hue, 255, 255);
            mass = ofRandom(10, 25);
        }
        
        void update(){
            vel += acc;
            pos += vel;
            acc *= 0;
        }
        
        void display(){
            ofPushStyle();
            ofSetColor(col);
            ofDrawSphere(pos, mass);
            ofPopStyle();
        }
        
    };
    
    
    vector<Particle> particles;
    //ofEasyCam cam;
    
    
		
};
