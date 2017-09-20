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

  const static int DISPLAY_AMPLITUDE = 100;
  const static int BASE_FREQ = 100;
  const static int MAX_SPEED = 20;

  static int size;

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
    
   Sine(const Sine& other){
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
    sine.setVolume(volume / size);
    sine.setSpeed (speed);
  }

  void Osc(ofxOscMessage &m){
    if(m.getAddress() == "/human"){
      pos.x = m.getArgAsInt32(0);
      pos.y = m.getArgAsInt32(1);
      pos.z = m.getArgAsInt32(2);
      volume =         abs( ofMap(pos.x, 0, Base :: ofGetWidth() , -1, 1) )  ;
      speed  =  static_cast<float>(MAX_SPEED) * (1.0 - abs( ofMap(pos.y, 0, Base :: ofGetHeight(), -1, 1) ) );
    }
  }


  void Draw(void){

    ofBeginShape();
      for(double radian = 0, delta = TWO_PI/1000 ; radian < TWO_PI ; radian += delta){
        int y = static_cast<int>( ofMap(radian, 0, TWO_PI, 0, Base :: ofGetHeight()) );
        float time = static_cast<float>(DISPLAY_AMPLITUDE) * volume * cos(speed * radian);
        cout << time << endl;
        ofVertex(pos.x + time, y);
      }
    ofEndShape();

  }

  static int Size(void){ return size; }
  static int Size(const int _size){ size = _size; return size; }

};

#endif /* Sine_h */
