//
//  Sine.h
//  emptyExample
//
//  Created by leico_studio on 2017/07/11.
//
//

#ifndef Sine_h
#define Sine_h

#include "ofMain.h"
#include "Base.h"

class Sine{

  const static int DISPLAY_AMPLITUDE = 50;
  const static int BASE_FREQ = 100;
  const static int MAX_SPEED = 50;

  ofSoundPlayer sine;
  ofPoint pos;
  float volume;
  float speed;

  public:
  
   Sine(void){
     sine.load("sound/100.wav");
     sine.setMultiPlay(false);
     sine.setLoop(true);
     sine.setVolume(0);
   }

  ~Sine(void){
    sine.stop();
    sine.unload();
  }

  void Setup(void){
    sine.play();
  }


  void Update(void){
    sine.setVolume(volume);
    sine.setSpeed (speed);
  }

  void Osc(ofxOscMessage &m){
    if(m.getAddress() == "/human"){
      pos.x = m.getArgAsInt32(0);
      pos.y = m.getArgAsInt32(1);
      pos.z = m.getArgAsInt32(2);
      volume =                     abs( ofMap(pos.x, 0, Base :: ofGetWidth() , -1, 1) );
      speed  =  MAX_SPEED * (1.0 - abs( ofMap(pos.y, 0, Base :: ofGetHeight(), -1, 1) ) );
    }
  }


  void Draw(void){

    ofBeginShape();
      for(int y = 0 ; y < Base :: ofGetHeight() + 5 ; y += 5){
        ofVertex(pos.x + DISPLAY_AMPLITUDE * cos(speed * BASE_FREQ + (y - pos.y) ), y);
      }
    ofEndShape();

  }

};

#endif /* Sine_h */
