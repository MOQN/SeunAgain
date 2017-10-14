"use strict";

var cvs;
var socket = io();

var gui;
//button States
//
//0: ready
//1: touch
//2: shake
//3: melody
//4: seun sounds
//5: closing
var params = {
    buttonState: 0
};

var buttonState;

function setup(){
    cvs = createCanvas(windowWidth, windowHeight);
    cvs.id('canvas');

    //background(0);
    noStroke();

    socket.on('setState', function(data){
        console.log("setting button state");
        console.log(data);
        params.buttonState = parseInt(data);
        console.log(params);
    });


    gui = new dat.GUI();
    buttonState = gui.add(params, 'buttonState', {
        Ready: 0,
        Touch: 1,
        Shake: 2,
        Melody: 3,
        Seun: 4,
        Closing: 5
    });

    gui.domElement.style.position = "absolute";
    gui.domElement.style.left = (windowWidth - 245) / 2 + "px";

}


function draw(){
    background(255);

    buttonState.onFinishChange(function(value){
        changeState(value, true);
    });

}

function changeState(data, emit){
    if(!emit){
        return;
    }
    socket.emit('changeState', {
        state: params.buttonState
    });
}