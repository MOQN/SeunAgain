#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  setupWebsocket();
  seunApp.init();
}

//--------------------------------------------------------------
void ofApp::update(){
  updateWebsocket();
  seunApp.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
  seunApp.draw();
  displayWebsocket();
}






//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  seunApp.keyPressed( key );
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
  
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
  
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






/// Libwebsocket ///



void ofApp::setupWebsocket() {
  ofSetLogLevel(OF_LOG_VERBOSE);
  //client.connect("localhost", 3000);
  client.connect("www.seun.space");
  ofSetLogLevel(OF_LOG_ERROR);
  
  client.addListener(this);
}

void ofApp::updateWebsocket() {
  client.send("request data");
}

void ofApp::displayWebsocket() {
  ofPushStyle();
  
  stringstream ss;
  if (client.isConnected()) {
    ofSetColor(150,150,255);
    ss << "Client is connected.";
  } else {
    ofSetColor(255,0,0);
    ss << "Client is disconnected.";
  }
  
  ofDrawBitmapString( ss.str(), 10, 120);
  
  //ofDrawBitmapString(client.isConnected() ? "Client is connected" : "Client disconnected :(", 10, 120);
  
  ofPopStyle();
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
void ofApp::onBroadcast( ofxLibwebsockets::Event& args ){
  cout<<"got broadcast "<<args.message<<endl;
}
//--------------------------------------------------------------
void ofApp::onMessage( ofxLibwebsockets::Event& args ){
  //cout<<"got message "<<args.message<<endl;
  
  string incoming = args.message;
  
  if (incoming != "{}") {
    cout << incoming << endl;
    
    //incoming = incoming.substr(1, incoming.size() - 3);
    //incoming.erase(std::remove(incoming.begin(), incoming.end(), '"'), incoming.end());
    /*
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
    */
    
    /*
    numP = readyStr.size() / 4;
    
    for(int i = 0; i < numP; i++){
      string id = readyStr[i * 4];
      float x = ofToFloat(readyStr[i * 4 + 1]) * ofGetWidth();
      //cout << x << endl;
      float y = ofToFloat(readyStr[i * 4 + 2]) * ofGetHeight();
      int hue = ofToInt(readyStr[i * 4 + 3]);
    }
     */
    
  }
}
