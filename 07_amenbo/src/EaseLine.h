//
//  EaseLine.h
//  emptyExample
//
//  Created by leico_studio on 2017/07/10.
//
//

#ifndef EaseLine_h
#define EaseLine_h

#include "ofMain.h"
#include "Change.h"

class EaseLine{

  ofColor color;

  Change<ofPoint> start;
  Change<ofPoint> goal;

  bool end;

  public:
  /* ============================================================= *
   * constructor / destructor                                      *
   * ============================================================= */
  EaseLine(void){
    ofPoint zero(0, 0, 0);

    start.Setup(zero, zero, 0);
    goal .Setup(zero, zero, 0);

    end = false;
  }

  ~EaseLine(void){}

  /* ============================================================= *
   * EaseLine( const ofColor &_color                               *
   *         , const ofPoint &_start, const float start_resist     *
   *         , const ofPoint &_goal , const float  goal_resist)    *
   * ============================================================= */
  EaseLine( const ofColor &_color
          , const ofPoint &_start, const float start_resist
          , const ofPoint &_goal,  const float  goal_resist)
  {
    color = _color;
    
    start.Setup(_start, _goal, start_resist);
    goal .Setup(_start, _goal, goal_resist);
    
  }

  /* ============================================================= *
   * Setup   ( const ofColor &_color                               *
   *         , const ofPoint &_start, const float start_resist     *
   *         , const ofPoint &_goal , const float  goal_resist)    *
   * ============================================================= */
  void Setup( const ofColor &_color
            , const ofPoint &_start, const float start_resist
            , const ofPoint &_goal,  const float  goal_resist)
  {
    color = _color;
    
    start.Setup(_start, _goal, start_resist);
    goal .Setup(_start, _goal, goal_resist);
  }

  /* ======================================================================= *
   * Update(void)                                                            *
   * ======================================================================= */
  void Update(void){
    
    start.Update();
    goal .Update();

    if( start.Current().match( start.Target() ) && goal.Current().match( goal.Target() ) )
        end = true;
  } 
  /* ======================================================================= *
   * Draw(void)                                                              *
   * ======================================================================= */
  void Draw(void){
    ofSetColor  ( color );
    ofDrawLine  ( start.Current(), goal.Current() );
  }

  /* ======================================================================= *
   * bool End(void)                                                          *
   * ======================================================================= */
  const bool End(void){
    return end;
  }


};

#endif /* EaseLine_h */
