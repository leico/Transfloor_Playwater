//
//  mydraw.h
//  emptyExample
//
//  Created by LIFE_MAC25  on 2017/07/07.20:00ごろ
//
//　　lines

#ifndef mydraw_h
#define mydraw_h

#include "Ripple.h"
#include "EaseLine.h"
#include "ofxSimpleTimer.h"

class amnb{


  const static int AMNB_SIZE = 20;
  const static int RANGE     = 100;
  const static int MARGIN    = 50;

  float easing;

  ofColor color;
  Change<ofPoint> pos;

  ofxSimpleTimer<bool> aloned;
  const static int ALONE_TIME = 30000;
  void AloneRipple(bool &id);

  Ripple   *alone;
  Ripple   *move;
  EaseLine *locus;

public:

   amnb(void) : alone(NULL), move(NULL), locus(NULL){}
  ~amnb(void){
    aloned.Stop ();
    aloned.Clear(this, &:: amnb :: AloneRipple);
    
    delete alone;
    delete move;
    delete locus;
  }



  void Setup(const ofPoint& initpos, const float _easing){

    easing = _easing;
    pos.Setup(initpos, initpos, easing);

    alone = NULL;
    move  = NULL;
    locus = NULL;

    aloned.Setup(true, this, &:: amnb :: AloneRipple);
    aloned.Start(ALONE_TIME, 1);


    color = ofColor(255);

    ofSetLineWidth(3);
    ofSetCircleResolution(60); //丸の解像度
    //ofNoFill();
    ofFill();

    ofBackground(0);

  }
  //-----------------------------------------------------
  void Update(void){

    if(alone != NULL){
      alone -> Update();

      if( alone -> End() ){
        delete alone; 
        alone = NULL; 
      }
    }

    if(move  != NULL){
      move -> Update();

      if( move -> End() ){
        delete move;
        move = NULL;
      }
    }

    if(locus != NULL){
      locus -> Update();

      if( locus -> End() ){
        delete locus;
        locus = NULL;
      }
    }

    pos.Update();
    aloned.Update();



  }
  //-----------------------------------------------------
  void Osc(vector <ofxOscMessage> &m){

    for(int i = 0 ; i < m.size() ; ++ i){
      if(m[i].getAddress() == "/human"){
        ofPoint human( m[i].getArgAsInt32(0), m[i].getArgAsInt32(1) ); //(x, y)

        if(pos.Current().distance( human ) <= RANGE){

          ofPoint goal = ofPoint( 
                  ofRandom(MARGIN, Base :: ofGetWidth()  - MARGIN)
                , ofRandom(MARGIN, Base :: ofGetHeight() - MARGIN)
              );

          pos.Target(goal);

          if(move == NULL)
            move  = new Ripple(pos.Current(), color, 500, easing);
          if(locus != NULL)
            delete locus;
          locus = new EaseLine(color, pos.Current(), easing, pos.Target() , easing / 2);

          aloned.Stop();
          aloned.Start(ALONE_TIME, 1);
        }
      }
    }

  }
  //------------------------------------------------------
  void Draw(void){

    ofFill();
    ofDrawCircle(pos.Current(), AMNB_SIZE);

    ofNoFill();
    if( alone != NULL) alone -> Draw();
    if( move  != NULL) move  -> Draw();
    if( locus != NULL) locus -> Draw();


  }

  //------------------------------------------------------

};

inline void amnb :: AloneRipple(bool &id){
    alone = new Ripple(pos.Current(), ofColor(255), 500, easing);
    aloned.Start(ALONE_TIME, 1);
  }


#endif /* mydraw_h */
