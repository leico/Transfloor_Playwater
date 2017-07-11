//
//  SineFiled.h
//  emptyExample
//
//  Created by leico_studio on 2017/07/11.
//
//

#ifndef SineFiled_h
#define SineFiled_h

#include "Base.h"
#include "Sine.h"

class SineField : public Base{

  std :: list<Sine> waves;

  public:
   SineField(void){};
  ~SineField(void){
    waves.clear();
  };
  
  void setup(void){

  }

  void update(void){
    for(std :: list<Sine> :: iterator it = waves.begin() ; it != waves.end() ; ++ it){
      it -> Update();
    }
    ofSoundUpdate();
  }

  void osc(vector<ofxOscMessage> &m){

    while(waves.size() < m.size()){
      waves.push_back(Sine());
      (-- waves.end()) -> Setup();
    }

    while(waves.size() > m.size())
      waves.pop_front();
  }

  void draw(){

    for(std :: list<Sine> :: iterator it = waves.begin() ; it != waves.end() ; ++ it)
      it -> Draw();
  }

};

#endif /* SineFiled_h */
