#pragma once

#include "ofMain.h"

#include "ofxLibwebsockets.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        ofxLibwebsockets::Client client;
    
        // websocket methods
        void onConnect( ofxLibwebsockets::Event& args );
        void onOpen( ofxLibwebsockets::Event& args );
        void onClose( ofxLibwebsockets::Event& args );
        void onIdle( ofxLibwebsockets::Event& args );
        void onMessage( ofxLibwebsockets::Event& args );
        void onBroadcast( ofxLibwebsockets::Event& args );
    
        string incoming;
        vector<string> readyStr;
        int numP;
    
    class Particle{
    public:
        string id;
        ofPoint acc, vel, pos;
        int hue;
        ofColor col;
        float mass;
        
        Particle(string _id, ofPoint _pos, int _hue){
            id = _id;
            pos = _pos;
            hue = _hue;
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
    
};
