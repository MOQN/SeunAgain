#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);
    
}

//--------------------------------------------------------------
void ofApp::update(){


}

//--------------------------------------------------------------
void ofApp::draw(){
    
    int port = 3000;
    string dest = "http://localhost:" + ofToString(port) + "/get";
    
//    string dest = "https://js6450.github.io/data.json";
    ofHttpResponse resp = ofLoadURL(dest);
    
    incoming = resp.data;
    
    if(incoming != "{}"){
        cout << incoming << endl;

        incoming = incoming.substr(1, incoming.size() - 3);
        incoming.erase(std::remove(incoming.begin(), incoming.end(), '"'), incoming.end());
        
        vector<string> subStr = ofSplitString(incoming, "},");
        for(string s : subStr){
            vector<string> subStr = ofSplitString(s, ":{pos:[");
            for(string s: subStr){
                vector<string> subStr = ofSplitString(s, "],hue:");
                for(string s: subStr){
                    vector<string> subStr = ofSplitString(s, ",");
                    for(string s: subStr){
                        readyStr.push_back(s);
                    }
                }
                
            }
        }
        
        numP = readyStr.size() / 4;
        
        for(int i = 0; i < numP; i++){
            string id = readyStr[i * 4];
            float x = ofToFloat(readyStr[i * 4 + 1]) * ofGetWidth();
            //cout << x << endl;
            float y = ofToFloat(readyStr[i * 4 + 2]) * ofGetHeight();
            int hue = ofToInt(readyStr[i * 4 + 3]);
            particles.push_back(Particle(id, ofPoint(x, y), hue));
        }
        
        for(Particle p: particles){
            p.display();
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
//--------------------------------------------------------------

