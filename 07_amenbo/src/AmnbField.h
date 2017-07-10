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

  const static int AMNB_NUM = 16;
  const static int MARGIN   = 50;

  amnb amenbo[AMNB_NUM];

  public:
    void setup(){
      for(int i = 0 ; i < AMNB_NUM ; ++ i){
        amenbo[i].Setup(
            ofPoint( ofRandom(MARGIN, ofGetWidth()  - MARGIN)
                   , ofRandom(MARGIN, ofGetHeight() - MARGIN) )
          , 0.1
        );
      }
    };

    void update(){
      for(int i = 0 ; i < AMNB_NUM ; ++ i)
        amenbo[i].Update();
    };
    void osc(vector< ofxOscMessage> &m){
      for(int i = 0 ; i < AMNB_NUM ; ++ i)
        amenbo[i].Osc(m);
    };
    void draw(){
      for(int i = 0 ; i < AMNB_NUM ; ++ i)
        amenbo[i].Draw();
    };

};

#endif /* AmnbField_h */
