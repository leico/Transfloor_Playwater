//
//  tkm001.h
//  mySketch
//
//  Created by asamiTakami on 2015/11/26.
//
//

#ifndef __mySketch__tkm001__
#define __mySketch__tkm001__
#include "ofMain.h"
#include "Base.h"




class tkm001 :public Base{
    
private:
    int hueNum;
    int frameNum;
    vector < ofPoint > humans; //vector 可変長配列　超便利配列！
    
    ofFbo fbo;
    
    bool aBack;
    int countRiset;
    
public:
    void setup(void){
        hueNum=0;
        ofSetBackgroundAuto(true);
        ofFill();
        
        fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
        
        fbo.begin();
        ofClear(200);
        fbo.end();
    }
    
    
    
    void osc(vector<ofxOscMessage> &m){
        
        humans.resize(m.size());// m.size()でvectorの大きさ、resizeでサイズ変更
        int j = 0;
        for(int i = 0 ; i < m.size() ; ++i ){
            if(m[i].getAddress()== "/human"){
                
                humans[j].x = m[i].getArgAsInt32(0);
                humans[j].y = m[i].getArgAsInt32(1);
                humans[j].z = m[i].getArgAsInt32(2);
                
                ++j;
            }
        }
    }
    
    
    
    
    
    void update(void){
        
        frameNum = (frameNum  + 1) % 6;
        hueNum   = (frameNum == 0) ? (hueNum + 1) % 256 : hueNum;
    }
    
    
    
    
    
    
    void draw(void){
        
        
        fbo.begin();
        //ofColor c;
        //c.setHsb(hueNum, 255, 255,200);
        //ofSetColor( c );
        
        for(int i = 0 ;i < humans.size() ;i ++){
            
            
            ofColor ccol;
            //ccol.setHsb(ofMap(sin(ofMap(float(ofGetMouseX()),0, float(ofGetWidth()),0.0f,10.0f)+ofGetElapsedTimef()), -1,1,0.0f,1.f)*255, 180, 255);
            ccol.setHsb(180,0, 150,ofRandom(255, 100));
            ofSetColor(ccol);
            ofSetCircleResolution(32);
            ofDrawCircle(humans[i].x + ofRandom(-10, 10),humans[i].y +ofRandom(-10, 10),ofRandom(5, 15));
            ofDrawCircle(humans[i].x + ofRandom(-10, 10),humans[i].y +ofRandom(-10, 10),ofRandom(5, 15));
            ofDrawCircle(humans[i].x + ofRandom(-40, 40),humans[i].y +ofRandom(-40, 40),ofRandom(1, 7));
            ofDrawCircle(humans[i].x + ofRandom(-40, 40),humans[i].y +ofRandom(-40, 40),ofRandom(1, 5));
            
            int ttime = int(ofGetElapsedTimef()*10)%2;
            if(ttime == 0){
                
                aBack = true;}
            if(aBack == true && ttime == 1){
                countRiset ++;
                ofSetColor(200 ,200,200,15);
                ofDrawRectangle(0, 0, 1280, 1440);
                
                if(countRiset == 150){
                    countRiset = 0;
                }
                aBack = false ;
                
            }
            if(countRiset == 149){
                ofSetColor(200 ,200,200,100);
                ofDrawRectangle(0, 0, 1280, 1440);
                
            }
            
            /* ofPushMatrix();
             
             ofTranslate(humans[i].x,humans[i].y,humans[i].z);
             int z = humans[i].z;
             
             ofDrawCircle(0, 0, z/6);
             ofPopMatrix();*/
        }
        fbo.end();
        
        ofSetColor(255);
        fbo.draw(0, 0);
        
    }
    
    void resize(const int w, const int h){
        Base :: resize(w, h);
        setup();
    }
    
    
    
    
    
    
    
    
    
    
    
};


#endif /* defined(__mySketch__tkm001__) */
