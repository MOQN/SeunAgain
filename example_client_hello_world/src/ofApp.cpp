#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    //client.connect("localhost", 3000);
    client.connect("www.seun.space");
    
    ofSetLogLevel(OF_LOG_ERROR);
    
    client.addListener(this);
    
    ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofDrawBitmapString(client.isConnected() ? "Client is connected" : "Client disconnected :(", 10, 15);
    
    client.send("request data");
    
}

//--------------------------------------------------------------
void ofApp::onConnect( ofxLibwebsockets::Event& args ){
    cout<<"on connected"<<endl;
}

//--------------------------------------------------------------
void ofApp::onOpen( ofxLibwebsockets::Event& args ){
    cout<<"on open"<<endl;
}

//--------------------------------------------------------------
void ofApp::onClose( ofxLibwebsockets::Event& args ){
    cout<<"on close"<<endl;
}

//--------------------------------------------------------------
void ofApp::onIdle( ofxLibwebsockets::Event& args ){
    cout<<"on idle"<<endl;
}

//--------------------------------------------------------------
void ofApp::onMessage( ofxLibwebsockets::Event& args ){
    cout<< "frameNum: ";
    cout<< ofGetFrameNum() <<endl;

    cout<<"got message "<<args.message<<endl;
    
    incoming = args.message;
    
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
    }
    
    
}

//--------------------------------------------------------------
void ofApp::onBroadcast( ofxLibwebsockets::Event& args ){
    cout<<"got broadcast "<<args.message<<endl;
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
