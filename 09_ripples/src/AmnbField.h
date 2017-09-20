//
//  AmnbField.h
//  emptyExample
//
//  Created by leico_studio on 2017/07/10.
//
//

#ifndef AmnbField_h
#define AmnbField_h

#include "ofMain.h"
#include "Base.h"
#include "amnb.h"

class AmnbField : public Base{

  const static int AMNB_MAX = 10;
  const static int AMNB_MIN = 3;
  const static int MARGIN   = 50;

  vector<amnb> amenbo;

  public:
    void setup(){
      amenbo.resize(ofRandom(AMNB_MIN, AMNB_MAX));
      for(int i = 0 ; i < amenbo.size() ; ++ i){
        amenbo.at(i).Setup(
            ofPoint( ofRandom(MARGIN, ofGetWidth()  - MARGIN)
                   , ofRandom(MARGIN, ofGetHeight() - MARGIN) )
          , 0.1
        );
      }
    };

    void update(){
      for(int i = 0 ; i < amenbo.size() ; ++ i)
        amenbo[i].Update();
    };
    void osc(vector< ofxOscMessage> &m){
      for(int i = 0 ; i < amenbo.size() ; ++ i)
        amenbo[i].Osc(m);
    };
    void draw(){
      for(int i = 0 ; i < amenbo.size() ; ++ i)
        amenbo[i].Draw();
    };

};

#endif /* AmnbField_h */
