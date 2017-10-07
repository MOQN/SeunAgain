'use strict';

var cvs;
var socket = io();
var drawing = false;

var colorH, colorS, colorB, hue;
var osc;
var midiNotes = [48, 50, 52, 53, 55, 57, 59, 60, 62];
var intervalShaked = false;

var img_logo;

function setup(){
  cvs = createCanvas(windowWidth, windowHeight);
  cvs.id('canvas');

  noStroke();
  setShakeThreshold(30);

  hue = random(360);
  colorH = hue;
  colorS = 255;
  colorB = 255;
  colorMode(HSB);

  osc = new p5.Oscillator('sine');
  osc.start();
  osc.amp(0.0); //slient

  img_logo = loadImage("img/logo.png");
  imageMode(CENTER);
}


function draw(){
  colorH = (hue + sin(frameCount * 0.03) * 15 + 360) % 360;
  if (colorS < 254) {
    colorS = lerp(colorS, 255, 0.03);
  } else {
    colorS = 255;
  }

  if (intervalShaked > 1) {
    intervalShaked--;
    var oscFreq = midiToFreq(90);
    osc.freq(oscFreq);
    osc.amp(1, 0.01)
  } else if (intervalShaked == 1) {
    intervalShaked--;
    osc.amp(0, 0.5);
  } else {
    intervalShaked = 0;
  }

  background(colorH, colorS, colorB);
  var imgW = width/2;
  var imgH = imgW * img_logo.height / img_logo.width;
  image(img_logo, width/2, height/2, imgW, imgH);
}


function windowResized() {
  resizeCanvas(windowWidth, windowHeight);
}

function touchStarted() {
  colorS = 0;

  var midiIndex = floor(map(mouseX, 0, width, 0, midiNotes.length));
  var oscFreq = midiToFreq(midiNotes[midiIndex]);
  osc.freq(oscFreq);
  osc.amp(1, 0.01); // volume, fadeOut Speed

  sendData(mouseX, mouseY, colorH, true);
}

function touchEnded() {
  osc.amp(0, 0.5);
}

function deviceShaken() {
  hue = random(360);
  intervalShaked = 10;
}

function sendData(x, y, h, emit) {
  var data = {
    pos: [x / width, y / height],
      hue: h
  };
  if(!emit){
    return;
  }
  console.log(data);
  socket.emit('drawing', data);
}

// limit the number of events per second
// function throttle(callback, delay) {
//     var previousCall = new Date().getTime();
//     return function() {
//         var time = new Date().getTime();
//
//         if ((time - previousCall) >= delay) {
//             previousCall = time;
//             callback.apply(null, arguments);
//         }
//     };
// }
