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
  
  ofDrawBitmapString( ss.str(), 100, 20);
  
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
  //cout<<"on idle"<<endl;
}
//--------------------------------------------------------------
void ofApp::onBroadcast( ofxLibwebsockets::Event& args ){
  cout<<"got broadcast "<<args.message<<endl;
}
//--------------------------------------------------------------
void ofApp::onMessage( ofxLibwebsockets::Event& args ){
  cout<<"got message: "<<args.message<<endl;
  seunApp.wsDataReceived( args.message );
}











//
